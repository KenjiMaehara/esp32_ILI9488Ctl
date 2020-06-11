/*
Sketch to generate the setup() calibration values, these are reported
to the Serial Monitor.

The sketch has been tested on the ESP8266 and screen with XPT2046 driver.
*/

#include "FS.h"

#include <SPI.h>
#include <TFT_eSPI.h>      // Hardware-specific library

TFT_eSPI tft = TFT_eSPI(); // Invoke custom library


uint16_t calData[5] = { 301, 3495, 393, 3211, 7 };


unsigned long targetTime = 0;
byte red = 31;
byte green = 0;
byte blue = 0;
byte state = 0;
unsigned int colour = red << 11; // Colour order is RGB 5+6+5 bits each

//------------------------------------------------------------------------------------------

void setupTFTScreen() {
  // Use serial port
  Serial.begin(115200);

  // Initialise the TFT screen
  tft.init();

  // Set the rotation before we calibrate
  tft.setRotation(1);


  // Use this calibration code in setup():
  uint16_t calData[5] = { 301, 3495, 393, 3211, 7 };
  tft.setTouch(calData);

  // Calibrate the touch screen and retrieve the scaling factors
  touch_calibrate200610(calData);

  /*
  // Replace above line with the code sent to Serial Monitor
  // once calibration is complete, e.g.:
  uint16_t calData[5] = { 286, 3534, 283, 3600, 6 };
  tft.setTouch(calData);
  */

  // Clear the screen
  tft.fillScreen(TFT_BLACK);
  tft.drawCentreString("Touch screen to test!",tft.width()/2, tft.height()/2, 2);


  // Use this calibration code in setup():
  //uint16_t calData[5] = { 301, 3495, 393, 3211, 7 };
  //tft.setTouch(calData);

}

//------------------------------------------------------------------------------------------


//------------------------------------------------------------------------------------------


//------------------------------------------------------------------------------------------

// Code to run a screen calibration, not needed when calibration values set in setup()
void touch_calibrate200610(uint16_t calData[])
{
  //uint16_t calData[5];
  uint8_t calDataOK = 0;

  // Calibrate
  tft.fillScreen(TFT_BLACK);
  tft.setCursor(20, 0);
  tft.setTextFont(2);
  tft.setTextSize(1);
  tft.setTextColor(TFT_WHITE, TFT_BLACK);

  tft.println("Touch corners as indicated");

  tft.setTextFont(1);
  tft.println();

  tft.calibrateTouch(calData, TFT_MAGENTA, TFT_BLACK, 15);

  Serial.println(); Serial.println();
  Serial.println("// Use this calibration code in setup():");
  Serial.print("  uint16_t calData[5] = ");
  Serial.print("{ ");

  for (uint8_t i = 0; i < 5; i++)
  {
    Serial.print(calData[i]);
    if (i < 4) Serial.print(", ");
  }

  Serial.println(" };");
  Serial.print("  tft.setTouch(calData);");
  Serial.println(); Serial.println();

  tft.fillScreen(TFT_BLACK);

  tft.setTextColor(TFT_GREEN, TFT_BLACK);
  tft.println("Calibration complete!");
  tft.println("Calibration code sent to Serial port.");

  //delay(4000);
  vTaskDelay(4000);
}









// This is the file name used to store the calibration data
// You can change this to create new calibration files.
// The SPIFFS file name must start with "/".
#define CALIBRATION_FILE "/TouchCalData2"

// Set REPEAT_CAL to true instead of false to run calibration
// again, otherwise it will only be done once.
// Repeat calibration if you change the screen rotation.
#define REPEAT_CAL false

// Keypad start position, key sizes and spacing
#define KEY_X 40 // Centre of key
#define KEY_Y 96
#define KEY_W 62 // Width and height
#define KEY_H 30
#define KEY_SPACING_X 18 // X and Y gap
#define KEY_SPACING_Y 20
#define KEY_TEXTSIZE 1   // Font size multiplier

// Using two fonts since numbers are nice when bold
#define LABEL1_FONT &FreeSansOblique12pt7b // Key label font 1
#define LABEL2_FONT &FreeSansBold12pt7b    // Key label font 2

// Numeric display box size and location
#define DISP_X 1
#define DISP_Y 10
#define DISP_W 238
#define DISP_H 50
#define DISP_TSIZE 3
#define DISP_TCOLOR TFT_CYAN

// Number length, buffer for storing it and character index
#define NUM_LEN 12
char numberBuffer[NUM_LEN + 1] = "";
uint8_t numberIndex = 0;

// We have a status line for messages
#define STATUS_X 120 // Centred on this
#define STATUS_Y 65

// Create 15 keys for the keypad
char keyLabel[15][5] = {"New", "Del", "Send", "1", "2", "3", "4", "5", "6", "7", "8", "9", ".", "0", "#" };
uint16_t keyColor[15] = {TFT_RED, TFT_DARKGREY, TFT_DARKGREEN,
  TFT_BLUE, TFT_BLUE, TFT_BLUE,
  TFT_BLUE, TFT_BLUE, TFT_BLUE,
  TFT_BLUE, TFT_BLUE, TFT_BLUE,
  TFT_BLUE, TFT_BLUE, TFT_BLUE
};

// Invoke the TFT_eSPI button class and create all the button objects
TFT_eSPI_Button key[15];

//------------------------------------------------------------------------------------------

//------------------------------------------------------------------------------------------


//------------------------------------------------------------------------------------------

void touch_calibrate()
{
  uint16_t calData[5];
  uint8_t calDataOK = 0;

  // check file system exists
  if (!SPIFFS.begin()) {
    Serial.println("Formating file system");
    SPIFFS.format();
    SPIFFS.begin();
  }

  // check if calibration file exists and size is correct
  if (SPIFFS.exists(CALIBRATION_FILE)) {
    if (REPEAT_CAL)
    {
      // Delete if we want to re-calibrate
      SPIFFS.remove(CALIBRATION_FILE);
    }
    else
    {
      File f = SPIFFS.open(CALIBRATION_FILE, "r");
      if (f) {
        if (f.readBytes((char *)calData, 14) == 14)
        calDataOK = 1;
        f.close();
      }
    }
  }

  if (calDataOK && !REPEAT_CAL) {
    // calibration data valid
    tft.setTouch(calData);
  } else {
    // data not valid so recalibrate
    tft.fillScreen(TFT_BLACK);
    tft.setCursor(20, 0);
    tft.setTextFont(2);
    tft.setTextSize(1);
    tft.setTextColor(TFT_WHITE, TFT_BLACK);

    tft.println("Touch corners as indicated");

    tft.setTextFont(1);
    tft.println();

    if (REPEAT_CAL) {
      tft.setTextColor(TFT_RED, TFT_BLACK);
      tft.println("Set REPEAT_CAL to false to stop this running again!");
    }

    tft.calibrateTouch(calData, TFT_MAGENTA, TFT_BLACK, 15);

    tft.setTextColor(TFT_GREEN, TFT_BLACK);
    tft.println("Calibration complete!");

    // store data
    File f = SPIFFS.open(CALIBRATION_FILE, "w");
    if (f) {
      f.write((const unsigned char *)calData, 14);
      f.close();
    }
  }
}

//------------------------------------------------------------------------------------------



//------------------------------------------------------------------------------------------

// Print something in the mini status bar
void status(const char *msg) {
  tft.setTextPadding(240);
  //tft.setCursor(STATUS_X, STATUS_Y);
  tft.setTextColor(TFT_WHITE, TFT_DARKGREY);
  tft.setTextFont(0);
  tft.setTextDatum(TC_DATUM);
  tft.setTextSize(1);
  tft.drawString(msg, STATUS_X, STATUS_Y);
}

//------------------------------------------------------------------------------------------




void TFT_init(void){

  // Initialise the TFT screen
  tft.init();

  // Set the rotation before we calibrate
  tft.setRotation(1);

  // Calibrate the touch screen and retrieve the scaling factors
  touch_calibrate();

  // Clear the screen
  tft.fillScreen(TFT_BLACK);

  // Draw keypad background
  tft.fillRect(0, 0, 600, 320, TFT_DARKGREY);

  // Draw number display area and frame
  //tft.fillRect(DISP_X, DISP_Y, DISP_W, DISP_H, TFT_BLACK);
  //tft.drawRect(DISP_X, DISP_Y, DISP_W, DISP_H, TFT_WHITE);

  tft.setCursor(20, 30);    // Set cursor to x = 70, y = 175
  tft.setTextColor(TFT_WHITE, TFT_BLACK);  // Set text colour to white and background to black
}


void task_TFTScreen( void *pvParameters ){

  BaseType_t xStatus;
  const TickType_t xTicksToWait = 500UL;
  xSemaphoreGive(xMutex);



  int screenCount = 0;
  int screenChange = true;

  // Use serial port
  Serial.begin(115200);


  TFT_init();

  while(1)
  {
    xStatus = xSemaphoreTake(xMutex, xTicksToWait);

    if (screenChange == true) {

      TFT_init();
      if(screenCount == 0)
      {
        drawKeypadScreen001();
        tft.setCursor(20, 30);    // Set cursor to x = 70, y = 175
        tft.setTextColor(TFT_WHITE, TFT_BLACK);  // Set text colour to white and background to black
        tft.println("Screen001");
        Serial.print("drawKeypadScreen001\n");
      }
      else if (screenCount == 1) {
        drawKeypadScreen002();
        tft.setCursor(20, 30);    // Set cursor to x = 70, y = 175
        tft.setTextColor(TFT_WHITE, TFT_BLACK);  // Set text colour to white and background to black
        tft.println("Screen002");
        Serial.print("drawKeypadScreen002\n");
      }
      else if (screenCount == 2) {
        drawKeypadScreen003();
        tft.setCursor(20, 30);    // Set cursor to x = 70, y = 175
        tft.setTextColor(TFT_WHITE, TFT_BLACK);  // Set text colour to white and background to black
        tft.println("Screen003");
        Serial.print("drawKeypadScreen003\n");
      }
      else if (screenCount == 3) {
        drawKeypadScreen004();
        tft.setCursor(20, 30);    // Set cursor to x = 70, y = 175
        tft.setTextColor(TFT_WHITE, TFT_BLACK);  // Set text colour to white and background to black
        tft.println("Screen004");
        Serial.print("drawKeypadScreen004\n");
      }

      screenChange = false;
      //screenCount++;
      tft.setTouch(calData);
    }



    uint16_t t_x = 0, t_y = 0; // To store the touch coordinates

    // Pressed will be set true is there is a valid touch on the screen
    boolean pressed = tft.getTouch(&t_x, &t_y);

    // / Check if any key coordinate boxes contain the touch coordinates
    for (uint8_t b = 0; b < 15; b++) {
      if (pressed && key[b].contains(t_x, t_y)) {
        key[b].press(true);  // tell the button it is pressed
      } else {
        key[b].press(false);  // tell the button it is NOT pressed
      }
    }

    // Check if any key has changed state
    for (uint8_t b = 0; b < 15; b++) {

      if (b < 3) tft.setFreeFont(LABEL1_FONT);
      else tft.setFreeFont(LABEL2_FONT);

      if (key[b].justReleased())
      {
        key[b].drawButton();     // draw normal
        if(b==0)
        {
          screenCount++;
          if(screenCount > 3)
          screenCount = 0;
          screenChange = true;
        }
      }

      if (key[b].justPressed()) {
        key[b].drawButton(true);  // draw invert

        // if a numberpad button, append the relevant # to the numberBuffer
        if (b >= 3) {
          if (numberIndex < NUM_LEN) {
            numberBuffer[numberIndex] = keyLabel[b][0];
            numberIndex++;
            numberBuffer[numberIndex] = 0; // zero terminate
          }
          status(""); // Clear the old status
        }

        // Del button, so delete last char
        if (b == 1) {
          numberBuffer[numberIndex] = 0;
          if (numberIndex > 0) {
            numberIndex--;
            numberBuffer[numberIndex] = 0;//' ';
          }
          status(""); // Clear the old status
        }

        if (b == 2) {
          status("Sent value to serial port");
          Serial.println(numberBuffer);
        }
        // we dont really check that the text field makes sense
        // just try to call
        if (b == 0) {
          status("Value cleared");
          numberIndex = 0; // Reset index to 0
          numberBuffer[numberIndex] = 0; // Place null in buffer
        }

        // Update the number display field
        tft.setTextDatum(TL_DATUM);        // Use top left corner as text coord datum
        tft.setFreeFont(&FreeSans18pt7b);  // Choose a nicefont that fits box
        tft.setTextColor(DISP_TCOLOR);     // Set the font colour

        // Draw the string, the value returned is the width in pixels
        int xwidth = tft.drawString(numberBuffer, DISP_X + 4, DISP_Y + 12);

        // Now cover up the rest of the line up by drawing a black rectangle.  No flicker this way
        // but it will not work with italic or oblique fonts due to character overlap.
        tft.fillRect(DISP_X + 4 + xwidth, DISP_Y + 1, DISP_W - xwidth - 5, DISP_H - 2, TFT_BLACK);

        //delay(10); // UI debouncing
        vTaskDelay(10);
      }
    }

    if(xStatus == pdTRUE )
    {
      sharedResource = 1;
      //Serial.print("shared resource change by task2 : ");
      //Serial.println(sharedResource);
    }

    xSemaphoreGive(xMutex);
    vTaskDelay(10);
    //delay(1000);


  }
}



// Keypad start position, key sizes and spacing
#define KEY_X_screen001 90 // Centre of key
#define KEY_Y_screen001 96
//#define KEY_W_screen001 62 // Width and height
//#define KEY_H_screen001 30
#define KEY_W_screen001 110 // Width and height
#define KEY_H_screen001 60
#define KEY_SPACING_X_screen001 18 // X and Y gap
#define KEY_SPACING_Y_screen001 20
#define KEY_TEXTSIZE_screen001 1   // Font size multiplier


// Create 15 keys for the keypad
char keyLabel_screen001[15][5] = {"next", "back", "Send", "a", "b", "c", "d", "e", "f", "g", "h", "i", ".", "0", "#" };
uint16_t keyColor_screen001[15] = {TFT_BLUE, TFT_BLUE, TFT_BLUE,
  TFT_BLUE, TFT_BLUE, TFT_BLUE,
  TFT_BLUE, TFT_BLUE, TFT_BLUE,
  TFT_BLUE, TFT_BLUE, TFT_BLUE,
  TFT_BLUE, TFT_BLUE, TFT_BLUE
};


void drawKeypadScreen001()
{
  // Draw the keys
  for (uint8_t row = 0; row < 2; row++) {
    for (uint8_t col = 0; col < 1; col++) {
      uint8_t b = col + row * 1;

      if (b < 3) tft.setFreeFont(LABEL1_FONT);
      else tft.setFreeFont(LABEL2_FONT);

      key[b].initButton(&tft, KEY_X_screen001 + col * (KEY_W_screen001 + KEY_SPACING_X_screen001),
      KEY_Y_screen001 + row * (KEY_H_screen001 + KEY_SPACING_Y_screen001), // x, y, w, h, outline, fill, text
      KEY_W_screen001, KEY_H_screen001, TFT_WHITE, keyColor_screen001[b], TFT_WHITE,
      keyLabel_screen001[b], KEY_TEXTSIZE_screen001);
      key[b].drawButton();
    }
  }
}








// Keypad start position, key sizes and spacing
#define KEY_X_screen002 90 // Centre of key
#define KEY_Y_screen002 96
//#define KEY_W_screen002 62 // Width and height
//#define KEY_H_screen002 30
#define KEY_W_screen002 110 // Width and height
#define KEY_H_screen002 60
#define KEY_SPACING_X_screen002 18 // X and Y gap
#define KEY_SPACING_Y_screen002 20
#define KEY_TEXTSIZE_screen002 1   // Font size multiplier


// Create 15 keys for the keypad
char keyLabel_screen002[15][5] = {"next", "back", "Send", "a", "b", "c", "d", "e", "f", "g", "h", "i", ".", "0", "#" };
uint16_t keyColor_screen002[15] = {TFT_BLUE, TFT_BLUE, TFT_BLUE,
  TFT_BLUE, TFT_BLUE, TFT_BLUE,
  TFT_BLUE, TFT_BLUE, TFT_BLUE,
  TFT_BLUE, TFT_BLUE, TFT_BLUE,
  TFT_BLUE, TFT_BLUE, TFT_BLUE
};


void drawKeypadScreen002()
{
  // Draw the keys
  for (uint8_t row = 0; row < 2; row++) {
    for (uint8_t col = 0; col < 1; col++) {
      uint8_t b = col + row * 1;

      if (b < 3) tft.setFreeFont(LABEL1_FONT);
      else tft.setFreeFont(LABEL2_FONT);

      key[b].initButton(&tft, KEY_X_screen002 + col * (KEY_W_screen002 + KEY_SPACING_X_screen002),
      KEY_Y_screen002 + row * (KEY_H_screen002 + KEY_SPACING_Y_screen002), // x, y, w, h, outline, fill, text
      KEY_W_screen002, KEY_H_screen002, TFT_WHITE, keyColor_screen002[b], TFT_WHITE,
      keyLabel_screen002[b], KEY_TEXTSIZE_screen002);
      key[b].drawButton();
    }
  }
}








// Keypad start position, key sizes and spacing
#define KEY_X_screen003 90 // Centre of key
#define KEY_Y_screen003 96
//#define KEY_W_screen003 62 // Width and height
//#define KEY_H_screen003 30
#define KEY_W_screen003 110 // Width and height
#define KEY_H_screen003 60
#define KEY_SPACING_X_screen003 18 // X and Y gap
#define KEY_SPACING_Y_screen003 20
#define KEY_TEXTSIZE_screen003 1   // Font size multiplier


// Create 15 keys for the keypad
char keyLabel_screen003[15][5] = {"next", "back", "Send", "a", "b", "c", "d", "e", "f", "g", "h", "i", ".", "0", "#" };
uint16_t keyColor_screen003[15] = {TFT_BLUE, TFT_BLUE, TFT_BLUE,
  TFT_BLUE, TFT_BLUE, TFT_BLUE,
  TFT_BLUE, TFT_BLUE, TFT_BLUE,
  TFT_BLUE, TFT_BLUE, TFT_BLUE,
  TFT_BLUE, TFT_BLUE, TFT_BLUE
};


void drawKeypadScreen003()
{
  // Draw the keys
  for (uint8_t row = 0; row < 2; row++) {
    for (uint8_t col = 0; col < 1; col++) {
      uint8_t b = col + row * 1;

      if (b < 3) tft.setFreeFont(LABEL1_FONT);
      else tft.setFreeFont(LABEL2_FONT);

      key[b].initButton(&tft, KEY_X_screen003 + col * (KEY_W_screen003 + KEY_SPACING_X_screen003),
      KEY_Y_screen003 + row * (KEY_H_screen003 + KEY_SPACING_Y_screen003), // x, y, w, h, outline, fill, text
      KEY_W_screen003, KEY_H_screen003, TFT_WHITE, keyColor_screen003[b], TFT_WHITE,
      keyLabel_screen003[b], KEY_TEXTSIZE_screen003);
      key[b].drawButton();
    }
  }
}



// Keypad start position, key sizes and spacing
#define KEY_X_screen004 90 // Centre of key
#define KEY_Y_screen004 96
//#define KEY_W_screen004 62 // Width and height
//#define KEY_H_screen004 30
#define KEY_W_screen004 110 // Width and height
#define KEY_H_screen004 60
#define KEY_SPACING_X_screen004 18 // X and Y gap
#define KEY_SPACING_Y_screen004 20
#define KEY_TEXTSIZE_screen004 1   // Font size multiplier


// Create 15 keys for the keypad
char keyLabel_screen004[15][5] = {"next", "back", "Send", "a", "b", "c", "d", "e", "f", "g", "h", "i", ".", "0", "#" };
uint16_t keyColor_screen004[15] = {TFT_BLUE, TFT_BLUE, TFT_BLUE,
  TFT_BLUE, TFT_BLUE, TFT_BLUE,
  TFT_BLUE, TFT_BLUE, TFT_BLUE,
  TFT_BLUE, TFT_BLUE, TFT_BLUE,
  TFT_BLUE, TFT_BLUE, TFT_BLUE
};


void drawKeypadScreen004()
{
  // Draw the keys
  for (uint8_t row = 0; row < 2; row++) {
    for (uint8_t col = 0; col < 1; col++) {
      uint8_t b = col + row * 1;

      if (b < 3) tft.setFreeFont(LABEL1_FONT);
      else tft.setFreeFont(LABEL2_FONT);

      key[b].initButton(&tft, KEY_X_screen004 + col * (KEY_W_screen004 + KEY_SPACING_X_screen004),
      KEY_Y_screen004 + row * (KEY_H_screen004 + KEY_SPACING_Y_screen004), // x, y, w, h, outline, fill, text
      KEY_W_screen004, KEY_H_screen004, TFT_WHITE, keyColor_screen004[b], TFT_WHITE,
      keyLabel_screen004[b], KEY_TEXTSIZE_screen004);
      key[b].drawButton();
    }
  }
}

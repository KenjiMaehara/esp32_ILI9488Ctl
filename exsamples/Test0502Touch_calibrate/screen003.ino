void screen003(uint16_t calData[]) {


  // Use serial port
  Serial.begin(115200);

  // Initialise the TFT screen
  tft.init();

  // Set the rotation before we calibrate
  tft.setRotation(1);

  // Calibrate the touch screen and retrieve the scaling factors
  touch_calibrate();

  // Clear the screen
  tft.fillScreen(TFT_BLACK);

  // Draw keypad background
  tft.fillRect(0, 0, 600, 320, TFT_GREEN);

  // Draw number display area and frame
  //tft.fillRect(DISP_X, DISP_Y, DISP_W, DISP_H, TFT_BLACK);
  //tft.drawRect(DISP_X, DISP_Y, DISP_W, DISP_H, TFT_WHITE);

  tft.setCursor(20, 30);    // Set cursor to x = 70, y = 175
  tft.setTextColor(TFT_WHITE, TFT_BLACK);  // Set text colour to white and background to black
  tft.println("Screen003");


  // Draw keypad
  drawKeypadScreen003();


  tft.setTouch(calData);


  while(1)
  {
  
    
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
            return;
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
  
        delay(10); // UI debouncing
      }
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

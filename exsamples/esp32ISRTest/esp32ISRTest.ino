/*
 *  ESP32 GPIO interrupt test
 *  2020.1.28
 *  JH7UBC Keiji Hata
 */

//#define LED_Pin 27
#define SW_Pin 35
//volatile int state = LOW;
volatile int gTest = 0;

void setup() {
  Serial.begin(115200);
  pinMode(SW_Pin, INPUT_PULLUP);
  //pinMode(LED_Pin, OUTPUT);
  attachInterrupt(SW_Pin, ISRTest, FALLING);
}

void loop() {
  //digitalWrite(LED_Pin, state);
    //Serial.println("test");
    //delay(1000);
}

void ISRTest(){
  gTest++;
  //state = !state;
  Serial.print("ISR found:");
  Serial.println(gTest);
  delay(500);
}

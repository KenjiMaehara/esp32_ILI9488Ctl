/*
 *  ESP32 GPIO interrupt test
 *  2020.1.28
 *  JH7UBC Keiji Hata
 */

//#define LED_Pin 27
#define SW_Pin 33
//volatile int state = LOW;

void setup() {
  pinMode(SW_Pin, INPUT_PULLUP);
  //pinMode(LED_Pin, OUTPUT);
  attachInterrupt(SW_Pin, ISRTest, FALLING);
}

void loop() {
  //digitalWrite(LED_Pin, state);
}

void ISRTest(){
  delay(10);
  //state = !state;
  Serial.println("ISR found");
}

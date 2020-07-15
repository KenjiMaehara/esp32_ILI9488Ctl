#include <Wire.h>
#include "Adafruit_MCP23017.h"

Adafruit_MCP23017 mcp2;

int n=0;

void setup() {
  Serial.begin(115200);
  //Serial1.begin(115200);
  Serial1.begin(9600, SERIAL_8N1, 16, 17);
  //Serial2.begin(115200);

  Wire.begin(25,26);
  mcp2.begin(0x01);
  mcp2.pinMode(11, OUTPUT);

}

void loop() {

  // read from port 0, send to port 1:
  if (Serial1.available()>0) {

    String str = Serial1.readStringUntil('\n');
    Serial.print("talk:");
    Serial.println(str);
    Serial.println("");

    mcp2.digitalWrite(11, HIGH);
    delay(20);
    mcp2.digitalWrite(11, LOW);
    delay(100);
  }

  //delay(1000);
  //Serial.print("test read read");

}

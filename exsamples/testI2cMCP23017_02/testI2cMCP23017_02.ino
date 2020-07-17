#include <Wire.h>
#include "Adafruit_MCP23017.h"

Adafruit_MCP23017 mcp1;
Adafruit_MCP23017 mcp2;
Adafruit_MCP23017 mcp3;
Adafruit_MCP23017 mcp4;
Adafruit_MCP23017 mcp5;

void setup() {
  Wire.begin(25,26);
  mcp1.begin(0x01);
  mcp2.begin(0x03);
  mcp3.begin(0x04);
  mcp4.begin(0x05);
  mcp5.begin(0x06);
  for (int i = 0; i <= 15; i++) {
    mcp1.pinMode(i, OUTPUT);
    mcp2.pinMode(i, OUTPUT);
    mcp3.pinMode(i, OUTPUT);
    mcp4.pinMode(i, OUTPUT);
    mcp5.pinMode(i, OUTPUT);
  }
}

void loop() {
  for (int i = 8; i <= 15; i++) {
    mcp1.digitalWrite(i, HIGH);
    delay(20);
    mcp1.digitalWrite(i, LOW);
  }
  for (int i = 8; i <= 15; i++) {
    mcp2.digitalWrite(i, HIGH);
    delay(20);
    mcp2.digitalWrite(i, LOW);
  }
  for (int i = 0; i <= 7; i++) {
    mcp2.digitalWrite(i, HIGH);
    delay(20);
    mcp2.digitalWrite(i, LOW);
  }
  for (int i = 8; i <= 15; i++) {
    mcp3.digitalWrite(i, HIGH);
    delay(20);
    mcp3.digitalWrite(i, LOW);
  }
  for (int i = 0; i <= 7; i++) {
    mcp3.digitalWrite(i, HIGH);
    delay(20);
    mcp3.digitalWrite(i, LOW);
  }
  for (int i = 8; i <= 15; i++) {
    mcp4.digitalWrite(i, HIGH);
    delay(20);
    mcp4.digitalWrite(i, LOW);
  }
  for (int i = 0; i <= 7; i++) {
    mcp4.digitalWrite(i, HIGH);
    delay(20);
    mcp4.digitalWrite(i, LOW);
  }

  for (int i = 8; i <= 15; i++) {
    mcp5.digitalWrite(i, HIGH);
    delay(20);
    mcp5.digitalWrite(i, LOW);
  }
  for (int i = 0; i <= 7; i++) {
    mcp5.digitalWrite(i, HIGH);
    delay(20);
    mcp5.digitalWrite(i, LOW);
  }

  for (int i = 0; i <= 7; i++) {
    mcp1.digitalWrite(i, HIGH);
    delay(20);
    mcp1.digitalWrite(i, LOW);
  }
}

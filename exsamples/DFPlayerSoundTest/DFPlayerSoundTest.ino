#include <Wire.h>
#include "Adafruit_MCP23017.h"

Adafruit_MCP23017 mcp1;

HardwareSerial Serial_df(2);
int number=0;

void setup() {
    Serial_df.begin(9600, SERIAL_8N1, 32, 33);

    Wire.begin(25,26);
    mcp1.begin(0x00);
    mcp1.pinMode(4, INPUT);
}

void loop() {


  if (mcp1.digitalRead(4)!=false) {
      Serial_df.write(0x7e);
      Serial_df.write(0xff);
      Serial_df.write(0x06);    //命令6バイト
      Serial_df.write(0x12);    //指定フォルダ　　＊0x12 mp3フォルダ
      Serial_df.write(0x00);
      Serial_df.write(0x00);
      Serial_df.write(number++);    //play
      //Serial_d  f.write(0xfe);
      //Serial_df.write(0xe8);
      Serial_df.write(0xef);
      delay(1000);
  }


  //delay(5000);
}

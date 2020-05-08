


#include "Wire.h"
 
void setup()
{
//int SDA=25
//int SCL=26
Wire.begin(25,26); // wake up I2C bus
// set I/O pins to outputs
Wire.beginTransmission(0x20);
Wire.write(0x00); // IODIRA register
Wire.write(0xFF); // set all of port A to Input
Wire.endTransmission();

Wire.beginTransmission(0x20);
Wire.write(0x02); // IOOLA register
Wire.write(0x00); // PortA I/O極性　0:L :H
Wire.endTransmission();

Wire.beginTransmission(0x20);
Wire.write(0x0C); // IOOLA register
Wire.write(0xFF); // PortA 0:Pullup無効 1:PullUP有効　
Wire.endTransmission();




//Wire.beginTransmission(0x20);
//Wire.write(0x0E); // INTFA register 割込Flag SetUp
//Wire.write(0xFF); // PortA 0:Intrupt無し1:Intrupt有り
//Wire.endTransmission();

}
 
void loop()
{
// Wire.beginTransmission(0x40);
// Wire.write(0x12); // address bank A
// Wire.write((byte)0xAA); // value to send - all HIGH
// Wire.endTransmission();
// delay(500);
// Wire.beginTransmission(0x40);
// Wire.write(0x12); // address bank A
// Wire.write((byte)0x55); // value to send - all HIGH
// Wire.endTransmission();
// delay(500);
}

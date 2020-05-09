#include <Wire.h>
 
// デバイスアドレス(スレーブ)
uint8_t DEVICE_ADDRESS = 0x20;  // 2進 100000
 
// 前回のボタンの状態
// ※レジスタへの書き込み回数を減らす為です。
int pre_button = LOW;  
 
void setup() {
  pinMode(27,INPUT);
  
  // マスタとしてI2Cバスに接続する
  Wire.begin();       
 
  // 初期設定(IODIRA/IODIRB)
  Wire.beginTransmission(DEVICE_ADDRESS);
    // 先頭アドレスへ
    Wire.write(0x00);
    // I/O設定Aの全てを出力設定にする
    Wire.write(0x00);
    // I/O設定Bの全てを出力設定にする
    Wire.write(0x00);    
  Wire.endTransmission();
 
  // GPIOA(GPA0～GPA7)
  Wire.beginTransmission(DEVICE_ADDRESS);
    Wire.write(0x12);
    // 全てのGPAピンをHIGH(出力)にする    
    Wire.write(0xff);
  Wire.endTransmission();
 
  // GPIOB(GPB0～GPB7)
  Wire.beginTransmission(DEVICE_ADDRESS);
    Wire.write(0x13);
    //  GPB0をLOW(入力)でそれ以外のGPBピンはHIGH(出力)にする
    Wire.write(0xfe); // 2進 11111110
  Wire.endTransmission();   
}
 
void loop() {  
  if (digitalRead(27) == HIGH){
    if(pre_button != HIGH){
      // 全てのGPBピンをHIGH(出力)にする
      Wire.beginTransmission(DEVICE_ADDRESS);
        Wire.write(0x13);      
        Wire.write(0xff); // 2進 11111111
      Wire.endTransmission();
      pre_button = HIGH;
    }    
  }else{
    if(pre_button != LOW){    
      // GPB0をLOW(入力)でそれ以外のGPBピンはHIGH(出力)にする
      Wire.beginTransmission(DEVICE_ADDRESS);
        Wire.write(0x13);      
        Wire.write(0xfe); // 2進 11111110
      Wire.endTransmission();
      pre_button = LOW;
    }
  }
}  

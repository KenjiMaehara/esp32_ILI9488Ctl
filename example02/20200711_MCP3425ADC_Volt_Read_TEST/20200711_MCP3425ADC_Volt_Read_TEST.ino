#include <Wire.h>
#include <MCP342x.h>
 
uint8_t address = 0x68;
MCP342x adc = MCP342x(address);
 
void setup(void)
{
  Serial.begin(115200);
// Wire.begin(21,22);    // I2C_BUS:SDA1,SCL1
  Wire.begin(25,26);    // I2C_BUS:SDA2,SCL2 
// Wire.setClock(clockFrequency);
 Wire.setClock(1000000);   //I2CBUSSpeeD:400KHz

  MCP342x::generalCallReset();
  delay(1);
 
  Wire.requestFrom(address, (uint8_t)1);
  if (!Wire.available()) {
    Serial.print("指定のデバイスが見つかりません。");
    Serial.println(address, HEX);
    while (1);
  }
 
}
 
void loop(void)
{
  long value = 0;
  MCP342x::Config status;
 
  uint8_t err = adc.convertAndRead(MCP342x::channel1, MCP342x::oneShot,
           MCP342x::resolution16, MCP342x::gain1,
           1000000, value, status);
  if (err) {
    Serial.print("Convert error: ");
    Serial.println(err);
  }
  else {
    Serial.print("Value: ");
  //  Serial.println(value * 2.048 / 32767);
   Serial.println(value * 2.048 / 32767*8);   //抵抗分割比: 1K:7k(6.8k+200Ω)
   
  }
 
  delay(10);
}


// ADCの精度　測定結果       誤差は抵抗値の精度の問題、ADCNo1とNo2を入れ替えても誤差は同じ
// 電圧計(V)  試作機No1(V)  電圧計(V)  試作機No2(V)
//  15.007      15.02       15.002    14.85
//  14.502      14.51       14.506    14.36
//  14.207      14.22       14.200    14.05  BATT･Full → 14.2V Uper
//  14.000      14.01       14.004    13.86
//  13.498      13.51       13.506    13.37
//  13.004      13.01       13.005    12.87
//  12.503      12.51       12.508    12.37
//  12.005      12.01       12.007    11.88   BATT･LOW復旧
//  11.502      11.50       11.502    11.37
//  11.005      11.00       11.000    10.88   BATT･LOW発生
//  10.503      10.50       10.500    10.38
//  10.004      10.00       10.007    9.89
//   9.704       9.69        9.704    9.59   BATT･OFF 9.7V→Under VOLT
//   9.503       9.49        9.506    9.39
//   9.004       8.99        9.005    8.89
//   8.506       8.49        8.500    8.39
//   8.005       7.99
//   7.501       7.48
//   7.007       6.98

  

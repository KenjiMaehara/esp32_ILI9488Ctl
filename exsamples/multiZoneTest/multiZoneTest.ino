// http://nopnop2002.webcrow.jp/SC16IS75x/SC16IS750-1.html



#include <Wire.h>
#include <SC16IS750.h>
#include <string.h>
#include <SPI.h>

SC16IS750 i2cuart = SC16IS750(SC16IS750_PROTOCOL_I2C,SC16IS750_ADDRESS_AA);
SC16IS750 i2cuart02 = SC16IS750(SC16IS750_PROTOCOL_I2C,SC16IS750_ADDRESS_AB);

uint8_t gAddr[32];
uint8_t gControl[32];


//Connect TX and RX with a wire and run this sketch

#define baudrate 9600
//#define baudrate 57600
//#define baudrate 115200
//#define baudrate 230400SS
//#define baudrate 460800
//#define baudrate 921600

void setup()
{
  Serial.begin(115200);

   //int SDA1=21   ;GPIO21を割当     2020/0528追加
   //int SCL1=22   ;GPIO22を割当     2020/0528追加
  Wire.begin(21,22);  // wake up I2C bus　     2020/0528追加


  Serial.println("start i2cuart");
  // UART to Serial Bridge Initialization
  i2cuart.begin(baudrate);               //baudrate setting
  if (i2cuart.ping()!=1) {
      Serial.println("i2cuart device not found");
      while(1);
  } else {
      Serial.println("i2cuart device found");
  }

  i2cuart02.begin(baudrate);               //baudrate setting
  if (i2cuart02.ping()!=1) {
      Serial.println("i2cuart02 device not found");
      while(1);
  } else {
      Serial.println("i2cuart02 device found");
  }

  Serial.print("start serial communication. baudrate = ");
  Serial.println(baudrate);
}





uint8_t multiZoon(uint8_t reg_addr,uint8_t reg_ctr)
{
  i2cuart02.write(0xfe);
  i2cuart02.write(reg_addr);
  i2cuart02.write(reg_ctr);
  i2cuart02.write(0xfd);


  uint8_t receive;

  for (size_t i = 0; i < 4; i++) {
    if (i2cuart02.available() > 0){
      // read the incoming byte:
      if (i==2) {
        receive = i2cuart02.read();
      }
      else
      {
        i2cuart02.read();
      }
    }
  }


  return receive;
}



void loop()
{
  uint8_t receive;
  int test=0;

  while(1)
  {

    for (size_t i = 0; i < 3; i++) {
      if (test==0) {
        receive = multiZoon(i,0x05);
      }
      else
      {
        receive = multiZoon(i,0x0A);
      }

      Serial.print("receive data : ");
      Serial.println(receive);
      delay(100);

    }

    if (test != 0) {
      test = 0;
    }
    else
    {
      test++;
    }
  }
}

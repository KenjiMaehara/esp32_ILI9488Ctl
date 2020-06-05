#include <Wire.h>
#include <SC16IS750.h>
#include <string.h>
#include <SPI.h>

SC16IS750 i2cuart = SC16IS750(SC16IS750_PROTOCOL_I2C,SC16IS750_ADDRESS_AA);

//Connect TX and RX with a wire and run this sketch

#define baudrate 9600
//#define baudrate 57600
//#define baudrate 115200
//#define baudrate 230400
//#define baudrate 460800
//#define baudrate 921600

int count=0;
int oldCount=0;

void setup()
{
  Serial.begin(baudrate);

   //int SDA1=21   ;GPIO21を割当     2020/0528追加      
   //int SCL1=22   ;GPIO22を割当     2020/0528追加
  Wire.begin(21,22,400000);  // wake up I2C bus　     2020/0528追加  


  Serial.println("start i2cuart");
  // UART to Serial Bridge Initialization
  delay(100);
  i2cuart.begin(baudrate);               //baudrate setting
  delay(1000);

  
  if (i2cuart.ping()!=1) {
      Serial.println("device not found");
      while(1);
  } else {
      Serial.println("device found");
  }
  Serial.print("start serial communication. baudrate = ");
  Serial.println(baudrate);
}

void loop()
{
  char buffer02[64] = {0};
  //static char buffer[64] = {0};
  static int index = 0;


  //printf("testesetwetewjiofjie \n");
  strcpy(buffer02,"testesetwetewjiofjieowjofjweonmfowenfownownofnwe \n");
  printf(" buffer02 = %s\n", buffer02);

  Serial.println("------i2c write start ----------");

  //i2cuart.EnableTransmit(1);
  
    for(int j=0;j<20;j++)
    {
      i2cuart.write(buffer02[j]);
        delay(10);
    }
  
  delay(5000);

}

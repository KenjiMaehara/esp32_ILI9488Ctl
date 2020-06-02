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
  Serial.begin(115200);

   //int SDA1=21   ;GPIO21を割当     2020/0528追加      
   //int SCL1=22   ;GPIO22を割当     2020/0528追加
  Wire.begin(21,22);  // wake up I2C bus　     2020/0528追加  


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
  
  static char buffer[64] = {0};
  static int index = 0;

  Serial.println("------i2c write start ----------");
  while(1)
  {
  i2cuart.write(count);
  while(i2cuart.available()==0);
  delay(10);
  count++;

  if(count > oldCount+20)
  {
    oldCount = count;
    i2cuart.write(0x0a);
    while(i2cuart.available()==0);
    i2cuart.write(0x0d);
    //while(i2cuart.available()==0);

    if(count>100)
    {
      oldCount=0;
      count=0;
    }
    break;

  }
  }
  
  delay(5000);

  Serial.println("------i2c read start ----------");
  while(1)
  {
  if (i2cuart.available() > 0){
    // read the incoming byte:
    char c = i2cuart.read();

    if (c == 0x0d) {

    } else if (c == 0x0a) {
      Serial.print("[");
      Serial.print(buffer);
      Serial.println("]");
      index = 0;
      break;
    } else {
      buffer[index++] = c;
      buffer[index] = 0;
    }

    if (i2cuart.available()==0)
    {
      break;
    }
  }

  }
}

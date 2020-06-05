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

void setupSC16IS740()
{
  //Serial.begin(115200);

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

void task_SC16IS740_TEST( void *param )
{
  setupSC16IS740();

while(1)
{

  
  char buffer02[64] = {0};
  //static char buffer[64] = {0};
  static int index = 0;

  Serial.println("------i2c write start ----------");
  strcpy(buffer02,"01234567890123456789\n\r");
  printf(" buffer02 = %s\n", buffer02);

  //i2cuart.EnableTransmit(1);
  
    for(int j=0;j<sizeof(buffer02);j++)
    {
      i2cuart.write(buffer02[j]);
        //delay(10);
    }
    i2cuart.write(0x0a);
  
  //delay(1000);
  vTaskDelay(1000);

 Serial.println("------i2c read start ----------");
 char buffer03[64] = {0};
 
  while(1)
  {
  if (i2cuart.available() > 0){
    // read the incoming byte:
    char c = i2cuart.read();

    if (c == 0x0d) {

    } else if (c == 0x0a) {
      Serial.print("[");
      Serial.print(buffer03);
      Serial.println("]");
      Serial.println();
      Serial.println();
      index = 0;
      //break;
    } else {
      buffer03[index++] = c;
      buffer03[index] = 0;
    }

    if(index > 60)
    {
      index = 0;
    }

  }
  else
  {
      index = 0;
      break;
  }

  }
  //delay(5000);
  vTaskDelay(5000);

}
}

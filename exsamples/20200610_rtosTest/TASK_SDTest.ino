#include <SD.h>

int cs_SD = 15;
const char* f_name ="/test1.txt";
int bangou = 0;
File myFile;

void setupSDTest() {
  //Serial.begin(115200);
  SD.begin(cs_SD);
  Serial.println("SD_conect...");
  delay(10);

}
void task_SDTest( void *pvParameters ) {
  //SD.begin(cs_SD);
  //Serial.println("SD_conect...");
  //delay(10);

  BaseType_t xStatus;
  const TickType_t xTicksToWait = 1000UL; //
  xSemaphoreGive(xMutex);



  setupSDTest();




  while(1)
  {
    xStatus = xSemaphoreTake(xMutex, xTicksToWait);

    if (!SD.begin(cs_SD)){
      Serial.println("Card failed");
    }
    //------------------------
    if(SD.begin(cs_SD)){
      Serial.println("card ok!");
      myFile = SD.open(f_name,FILE_APPEND);
      bangou++;
      if(myFile){
        myFile.println("");
        myFile.print(bangou);
        myFile.print(" : test kakikomi OK!");
        Serial.print("");
        Serial.print(bangou);
        Serial.print(" : Card kakikomi ok");
        myFile.close();
      }else{
        Serial.print(" : Card kakikomi shippai");
      }

    }

    if(xStatus == pdTRUE)
    {
      sharedResource = 100;
      Serial.print("shared resource change by task1 : ");
      Serial.println(sharedResource);
    }

    xSemaphoreGive(xMutex);
    delay(500);



  }
}

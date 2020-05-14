#include <SD.h>
  
int cs_SD = 5;
const char* f_name ="/test1.txt";
int bangou = 0;
File myFile;
  
void setup() {
   Serial.begin(115200);
   
}
void loop() {
    SD.begin(cs_SD);
     Serial.println("SD_conect...");
    delay(10);
     
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
  
delay(1000);
 }
}

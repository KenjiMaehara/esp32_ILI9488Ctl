//  http://robo.mydns.jp/Lecture/index.php?%C5%C5%BB%D2%B9%A9%BA%EE%2FESP32
// 社内WiFi環境"Buffalo-G-6098"よりntpServer = "pool.ntp.org"に接続して、時間を取得 
// その時間をシリアル通信で表示 
//  このProgramはWiFiを経由して、時間を取得するのみです。

#include <WiFi.h>
#include "time.h"

#include <Wire.h>
#include <RTClib.h>

#include "FS.h"
#include <SPI.h>
#include <TFT_eSPI.h>      // Hardware-specific library

TFT_eSPI tft = TFT_eSPI(); // Invoke custom library



unsigned long targetTime = 0;
byte red = 31;
byte green = 0;
byte blue = 0;
byte state = 0;
unsigned int colour = red << 11; // Colour order is RGB 5+6+5 bits each



uint16_t calData[5] = { 301, 3495, 393, 3211, 7 };

const char* ssid       = "TP-Link_CACC";   //YOUR_SSID:MEL"Buffalo-A-6098"
const char* password   = "63281538";   //YOUR_PASS:MEL"4vheeeg737sby"

const char* ntpServer = "pool.ntp.org";   //  NTP サービスを提供するタイムサーバ
const long  gmtOffset_sec = 3600*8;       //  UCT時間に8時間を加算
const int   daylightOffset_sec = 3600;   //  NTP_Serverへの更新時間間隔 

struct tm gTimeinfo;


void task0(void* arg)
{
    Serial.print("*******task0 start*******");
    screenSetup();
     while (1)
     {
        
        screen001(calData);
        screen002(calData);
        //screen003(calData);
        //screen004(calData);
        //delay(1000);
     }
}

void task1(void* arg)
{
    //Serial.print("*******task1 start*******");
    //Wifi_setup();
    //DC3232_setup ();
    //setTimeToRtc();
     
     while (1)
     {
        
        //DC3232Func();
        //delay(1000);
     }
}






void printLocalTime()
{
  //struct tm timeinfo;
  if(!getLocalTime(&gTimeinfo)){
    Serial.println("Failed to obtain time");
    return;
  }
  Serial.println(&gTimeinfo, "%A, %B %d %Y %H:%M:%S");   // 
}



void Wifi_setup()
{
  Serial.begin(115200);
  
  //connect to WiFi
  Serial.printf("Connecting to %s ", ssid);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
      delay(500);
      Serial.print(".");
  }
  Serial.println(" CONNECTED");
  
  //init and get the time
  configTime(gmtOffset_sec, daylightOffset_sec, ntpServer);
  printLocalTime();

  //disconnect WiFi as it's no longer needed
  WiFi.disconnect(true);
  WiFi.mode(WIFI_OFF);
}


void setup()
{
     Serial.begin(115200);
     Serial.print("setup task");

     // create tasks
     xTaskCreatePinnedToCore(task0, "Task0", 4096, NULL, 1, NULL, 0);
     xTaskCreatePinnedToCore(task1, "Task1", 4096, NULL, 1, NULL, 1);
}

void loop()
{
  delay(1000);

}

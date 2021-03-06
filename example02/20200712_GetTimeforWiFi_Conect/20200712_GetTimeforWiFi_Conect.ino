//  http://robo.mydns.jp/Lecture/index.php?%C5%C5%BB%D2%B9%A9%BA%EE%2FESP32
// 社内WiFi環境"Buffalo-G-6098"よりntpServer = "pool.ntp.org"に接続して、時間を取得 
// その時間をシリアル通信で表示 
//  このProgramはWiFiを経由して、時間を取得するのみです。

#include <WiFi.h>
#include "time.h"

#include <Wire.h>
#include <RTClib.h>

const char* ssid       = "Buffalo-G-6098";   //YOUR_SSID:MEL"TP-Link_CACC"
const char* password   = "4vheeeg737sby";   //YOUR_PASS:MEL"63281538"

const char* ntpServer = "pool.ntp.org";   //  NTP サービスを提供するタイムサーバ
const long  gmtOffset_sec = 3600*8;       //  UCT時間に8時間を加算
const int   daylightOffset_sec = 3600;   //  NTP_Serverへの更新時間間隔 

struct tm gTimeinfo;


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
  Wifi_setup();
  DC3232_setup ();
  setTimeToRtc();
}

void loop()
{
  delay(1000);
  printLocalTime();
  DC3232Func ();
  setTimeToRtc();
}

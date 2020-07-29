/*
 * このスケッチは、MELのWiFi環境で"Buffalo-G-6098"を経由して、NTPClientに接続して、UTCの時間を取得する。
 * 取得した時間から、現在の時刻を計算して、シリアル出力すると同時にDS3231にメモリする。
 * WiFi環境が通信断になった場合、DS3231の年月日時間を元に表示する。
 * 現在、このスケッチには、次の問題が有る。
 * 1．ProgramがRestartの時、WiFiが接続されないと、Programそのものが起ち上がらない。
 * 2．WiFiから時間がとれなかった時は、DS3231RTCの時間で動作するようにする事。
 * 3．WiFiの設定を簡単に設定できるようにする事。
 * 4．曜日は漢字表記で御願いします。それと曜日が一致しません。Programを見直して修正を御願いします。
 * 5．SQWに1Hzを出力するようにSetupしてあります。
 * 6．温度を測定します。
 * 7．温度の精度は、デジタル温度センサー出力精度：±3℃、最小単位0.25℃
 *
 *http://marchan.e5.valueserver.jp/cabin/comp/jbox/arc202/doc21102.html
 * File:      esp32RTC.ino
 * Function:  Real time clock with NTP time correction and battery backup.
 * Date:      2018/01/09 (Source file: espRTC.ino 2017/01/16)
 * Author:    M.Ono
 *
 * Hardware   MCU:  ESP32
 *            RTC:  DS1307 I2C Real tiime clock module.
 */
#include <RTClib.h>
#include <Wire.h>
#include <WiFi.h>
#include <NTPClient.h>
#include <WiFiUdp.h>

#include "RTClib.h"
RTC_DS3231 rtc;

// I2C Address
#define DS3231_ADDRESS 0x68   // Realtime clock

// WiFi connection
//const char* ssid = "elecom2g-0a5417";   //YOUR_SSID:MEL"Buffalo-A-6098"
//const char* password = "794u9w5t7cxi";   //YOUR_PASS:MEL"4vheeeg737sby"

//const char* ssid = "Buffalo-A-6098";   //YOUR_SSID:MEL"Buffalo-A-6098"
//const char* password = "4vheeeg737sby";   //YOUR_PASS:MEL"4vheeeg737sby"

const char* ssid = "TP-Link_8DA0";   //YOUR_SSID:MEL"TP-Link_8DA0"
const char* password = "69733970";   //YOUR_PASS:MEL"69733970"

// Time adjust
WiFiUDP ntpUDP;
NTPClient timeClient(ntpUDP);
const char* sNtpUrl = "ntp.nict.jp";
int  iNtpOffset = 32400;      // UTC + 9h (3600sec * 9h)sec.
int  iNtpInterval = 2;        // minutes
int  iAdjustTime = 0;
const int iMaxmin = 1453;     // Minutes of day.	//const int iMaxmin = 1440;     // Minutes of day.

// DS1307 Clock data
struct ClockData {
    byte year;
    byte month;
    byte day;
    byte week;
    byte hour;
    byte minute;
    byte sec;
    byte ctrl;
};
ClockData dtClock;

/*****************************************************************************
 *                          Predetermined Sequence                           *
 *****************************************************************************/
void setup() {
    Serial.begin(115200);     // TxD0,RxD0

    // Prepare I2C protocol.
    Wire.begin(21,22);        // Define(SDA1, SCL1)

  // 20200513TEST追加　SQW 1Hz出力に設定
   Wire.beginTransmission(0x68);         // RTC DS3231 ADRS 68h
   Wire.write(0x0E);                     // ADRS:0Eh
   Wire.write(0b01000000);              // SQW→1Hz出力 for BATT･Back Up Enable
   Wire.endTransmission();               // Ends I2C communication

    // Prepare WiFi system.
    WiFi.begin(ssid, password);   //WiFi.begin(ssid, password);
    while (WiFi.status() != WL_CONNECTED) {
      delay(500);
      Serial.print(".");
    }
    Serial.println("\r\nWiFi connected!");

    // Recreate NTPClient object.
    timeClient = NTPClient(ntpUDP, sNtpUrl, iNtpOffset);
}

void loop() {
    // Check date input ('hh/mm/dd/w') from serial buffer.
    if (Serial.available() >= 8) {
        String date = Serial.readString();
        setDate(date);
    }

    // Adjust the time automatically at specified intervals.
    getDateTime(&dtClock);
    int now = getTransitTime(editTime(dtClock));
    if (now >= iAdjustTime) {
        if (timeClient.update()) {
            String strJST = timeClient.getFormattedTime();
            Serial.print("JST time = "); Serial.println(strJST);
            setTime(strJST);
            iAdjustTime = now + iNtpInterval;
            if (iAdjustTime >= iMaxmin)
                iAdjustTime -= iMaxmin;
        }
    }

    // Display the current date and time on the serial monitor.
    getDateTime(&dtClock);
    Serial.print("Now: ");
    Serial.print(editDateTime(dtClock));
    Serial.print("(");
    Serial.print(tellDayOfWeek(dtClock.week));
   Serial.println(")");
   Serial.print("  temp: ");
   Serial.print(rtc.getTemperature());
   Serial.print("  ℃");
   Serial.println();



    delay(1000);
}
/*****************************************************************************/

/*
 * Get elapsed time(minutes) based on zero hour.
 *    Argument: (String)Time string 'hh:mm:ss'
 *    Return:   (Integer)Transit time (minutes)
 */
int getTransitTime(String strTime)
{
    return strTime.substring(0, 2).toInt() * 60 + strTime.substring(3, 5).toInt();
}

/* ======================== DS1307 Clock Control ============================*/

/*
 * Read data from DS1307 Register
 */
void getDateTime(ClockData *dt)
{
    int iValue = 0;

    Wire.beginTransmission(DS3231_ADDRESS); //DS3231_ADDRESS
    Wire.write(iValue);
    Wire.endTransmission();
    Wire.requestFrom(DS3231_ADDRESS, 7);    //DS3231_ADDRESS
    dt->sec = Wire.read();
    dt->minute = Wire.read();
    dt->hour = Wire.read();
    dt->week = Wire.read();
    dt->day = Wire.read();
    dt->month = Wire.read();
    dt->year = Wire.read();
}

/*
 * Tell day of week from code.
 */
String tellDayOfWeek(byte num)
{
    static String week[] = {"Sun", "Mon", "Tue", "Wed", "Thu", "Fri", "Sat"};
//   static String week[] = {"日", "月", "火", "水", "木", "金", "土"};
    if (num >= 1 && num <= 7)

      //return week[num-1];
      return week[num+1];

    else
      return "";
}

/*
 * Set DS1307 time register.
 *    Argument: (String)Time string 'hh:mm:ss'.
 */
void setTime(String sTime)
{
    byte bValue = 0x00;   //Top Address
    String buf = sTime;
    buf.replace(":", "");  buf.trim();
    if (buf.length() == 6) {
        byte hour = (buf.charAt(0) << 4) + (buf.charAt(1) & 0x0f);
        byte minute = (buf.charAt(2) << 4) + (buf.charAt(3) & 0x0f);
        byte sec = (buf.charAt(4) << 4) + (buf.charAt(5) & 0x0f);
        Wire.beginTransmission(DS3231_ADDRESS);
        Wire.write(bValue);
        Wire.write(sec);
        Wire.write(minute);
        Wire.write(hour);
        Wire.endTransmission();
    }
}

/*
 * Set DS3231 date register.
 *    Argument: (String)Time string 'yy/mm/dd/w'.
 */
void setDate(String sDate)
{
    byte bValue = 0x03;   //Top Address
    String buf = sDate;
    buf.replace("/", "");  buf.trim();
    if (buf.length() >= 6) {
        byte year = (buf.charAt(0) << 4) + (buf.charAt(1) & 0x0f);
        byte month = (buf.charAt(2) << 4) + (buf.charAt(3) & 0x0f);
        byte day = (buf.charAt(4) << 4) + (buf.charAt(5) & 0x0f);
        byte week = 0x00;
        if (buf.length() == 7) {
            week = (buf.charAt(6) & 0x07);
          if (week < 0x01 || week > 0x07)
            week = 0x01;
        }
        Wire.beginTransmission(DS3231_ADDRESS);
        Wire.write(bValue);
        Wire.write(week);
        Wire.write(day);
        Wire.write(month);
        Wire.write(year);
        Wire.endTransmission();
    }
}

/*
 * Edit DS3231 date and time.
 */
String editDateTime(ClockData dt)
{
    return editDate(dt) + " " + editTime(dt);
}

/*
 * Edit time register.
 */
String editTime(ClockData dt)
{
    String buf = "";
    char wbuf[12];
    sprintf(wbuf, "%02x:%02x:%02x", (int)dt.hour, (int)dt.minute, (int)dt.sec);
    buf.concat(wbuf);
    return buf;
}

/*
 * Edit date register.
 */
String editDate(ClockData dt)
{
    String buf = "20";
    char wbuf[12];
    sprintf(wbuf, "%02x/%02x/%02x", (int)dt.year, (int)dt.month, (int)dt.day);
    buf.concat(wbuf);
    return buf;
}

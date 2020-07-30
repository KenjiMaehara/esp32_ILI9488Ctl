// RTC(DS3231)単体の動作試験
// RTCに最初に時間設定する場合は、21行目のコメントを外し、コンパイル時間(約1分30秒位)を想定して年月日時間を設定する。
// 時間の設定が終われば、21行目をコメントアウトした後、再書き込みを行っておけば、バッテリー動作が可能な時間内は、修正する必要なし。
// 実際は、プログラムで時間の再設定をするかどうかを問合せできるようにして、おけばこの問題は解決する。
// 2020/05/05 14:30:12の時点で、2秒遅れで動作している。
// ユニットの電源をOFF-ONしても、時間が崩れる事は無い。








//#include <Wire.h>
//#include <RTClib.h>
RTC_DS3231 rtc;
char daysOfTheWeek[7][12] = {"Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday"};
void DC3232_setup () {

  Wire.begin(21,22);        // Define(SDA, SCL)
   delay(10); 
  Serial.begin(115200);     // スケッチのツールのシリアルモニターをONすると、現在の時刻が表示される。
   delay(1000);
  if (! rtc.begin()) {
    Serial.println("Not find RTC");
    while (1);
  }
//時刻補正
//     rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
//    rtc.adjust(DateTime(2020, 5, 5, 14, 4, 0));     //RTCに最初に書き込む時間を設定2020年,5月,5日,14時,4分0秒、修正後、コメントアウトする。

}



void setTimeToRtc()
{
  //時刻補正
  //     rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
  rtc.adjust(DateTime(gTimeinfo.tm_year - 100, gTimeinfo.tm_mon + 1, gTimeinfo.tm_mday, gTimeinfo.tm_hour, gTimeinfo.tm_min, gTimeinfo.tm_sec));     //RTCに最初に書き込む時間を設定2020年,5月,5日,14時,4分0秒、修正後、コメントアウトする。

}



void DC3232Func () {
    DateTime now = rtc.now();

    Serial.print(now.year(), DEC);
    Serial.print('/');
    Serial.print(now.month(), DEC);
    Serial.print('/');
    Serial.print(now.day(), DEC);
    Serial.print(" (");
    Serial.print(daysOfTheWeek[now.dayOfTheWeek()]);
    Serial.print(") ");
    Serial.print(now.hour(), DEC);
    Serial.print(':');
    Serial.print(now.minute(), DEC);
    Serial.print(':');
    Serial.print(now.second(), DEC);
    Serial.println();

    delay(1000);
}

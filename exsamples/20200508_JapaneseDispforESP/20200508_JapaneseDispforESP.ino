//参照したWEB"https://www.mgo-tec.com/blog-entry-kanji-font-esp32-oled-ssd1331-scroll.html"
//使用する日本語Fontは、東雲Fontで、全角ゴシック：　shnmk16.bdfと半角ゴシック：　shnm8x16r.bdf
//日本語FontはSD_Cardに保存、UTF-8 文字コードから Shift_JIS へ変換するテーブルファイルが必要と書いてあります。
// 変換方法はUtf8Sjis.tblで行うと書いてあります。
// 理由　Arduino IDE のスケッチ（ソースコード）に入力した日本語漢字は UTF-8 コードの文字列になるので、
// それを Shift_JIS  文字コードに変換するライブラリです。

// The SPIFFS (FLASH filing system) is used to hold touch screen   //20200508追加_20200429_Keypad_480*320より
// calibration data                                                //20200508追加_20200429_Keypad_480*320より 

//　#include "FS.h"                                                //20200508追加_20200429_Keypad_480*320より

//  #include <SPI.h>                                              //20200508追加_20200429_Keypad_480*320より
// #include <TFT_eSPI.h>      // Hardware-specific library        //20200508追加_20200429_Keypad_480*320より



#include "ESP32_SD_ShinonomeFNT.h"
#include "ESP32_SD_UTF8toSJIS.h"
// #include "ESP32_SSD1331.h"                                   //20200508_TFT_480*320に変更の為、使用しない
 
const char* UTF8SJIS_file = "/font/Utf8Sjis.tbl"; //UTF8 Shift_JIS 変換テーブルファイル名を記載しておく
const char* Shino_Zen_Font_file = "/font/shnmk16.bdf"; //全角フォントファイル名を定義
const char* Shino_Half_Font_file = "/font/shnm8x16.bdf"; //半角フォントファイル名を定義
 
const uint8_t CS_SD = 5; //SD card CS ( Chip Select )
 
const uint8_t SCLK_OLED =  14; //SCLK
const uint8_t MOSI_OLED =  13; //MOSI (Master Output Slave Input)
const uint8_t MISO_OLED =  12; //これは実際は使っていない。MISO (Master Input Slave Output)
const uint8_t CS_OLED = 15;
const uint8_t DC_OLED =  16; //OLED DC(Data/Command)
const uint8_t RST_OLED =  4; //OLED Reset
 
ESP32_SSD1331 ssd1331(SCLK_OLED, MISO_OLED, MOSI_OLED, CS_OLED, DC_OLED, RST_OLED);
 
ESP32_SD_ShinonomeFNT SFR(CS_SD, 24000000);
 
void setup() {
  Serial.begin(115200);
  ssd1331.SSD1331_Init(); //OLED SSD1331 初期化
 
  //※この関数を使う場合はStrDirect_ShinoFNT_readALL関数を使う場合限定。
  //３つのファイルを同時に開くため、後でクローズすることが必要。
  SFR.SD_Shinonome_Init3F(UTF8SJIS_file, Shino_Half_Font_file, Shino_Zen_Font_file);
 
  uint8_t font_buf[12][16];
  uint16_t sj_length;
  String str = "日本語漢字！";
   
  sj_length = SFR.StrDirect_ShinoFNT_readALL(str, font_buf); //String 文字列から一気にフォント変換
  ssd1331.SSD1331_8x16_Font_DisplayOut(sj_length, 0, 0, 7, 7, 3, font_buf); //OLED SSD1331 へ出力
   
  str = "ESP-WROOM-32";
  sj_length = SFR.StrDirect_ShinoFNT_readALL(str, font_buf); //String 文字列から一気にフォント変換
  ssd1331.SSD1331_8x16_Font_DisplayOut(sj_length, 0, 16, 7, 0, 0, font_buf); //OLED SSD1331 へ出力
 
  str = "半角もイケる";
  sj_length = SFR.StrDirect_ShinoFNT_readALL(str, font_buf); //String 文字列から一気にフォント変換
  ssd1331.SSD1331_8x16_Font_DisplayOut(sj_length, 0, 32, 0, 7, 0, font_buf); //OLED SSD1331 へ出力
 
  str = "ｱｶｻﾀﾅﾊﾏﾔﾗﾜﾝ";
  sj_length = SFR.StrDirect_ShinoFNT_readALL(str, font_buf); //String 文字列から一気にフォント変換
  ssd1331.SSD1331_8x16_Font_DisplayOut(sj_length, 0, 48, 0, 0, 3, font_buf); //OLED SSD1331 へ出力
 
  SFR.SD_Shinonome_Close3F(); //StrDirect_ShinoFNT_readALL関数を使う場合、必ず閉じておく
}
 
void loop() {
 
}

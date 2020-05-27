#include <WiFi.h>

#include "FS.h"
#include "SD.h"
#include "SPI.h"

// SSIDとPASSを渡すための構造体
typedef struct {
  String ssidInfo;
  String passInfo;
} WifiInfo;

const char* path = "/pass.txt";

void setup() {
  Serial.begin(115200);
  // SDカードがマウントされているかの確認
  if(!SD.begin()){
    Serial.println("Card Mount Failed");
    while (1) {}
  }
  // カードタイプの取得
  uint8_t cardType = SD.cardType();
  if(cardType == CARD_NONE){
    Serial.println("No SD card attached");
    while (1) {}
  }
  // テキストファイルの読み込み
  WifiInfo result = readFileText(SD, path);

  // 設定された値が正しいかどうかを判定
  if (result.ssidInfo == NULL || result.ssidInfo == "") {
    Serial.println("read file error!");
    while (1) {}
  } else {
    connectWifi(stringTochar(result.ssidInfo), stringTochar(result.passInfo));
  }
}

void loop() {

}

/**
 * SDカードの中にあるファイルを読み込んで中のテキストを抽出する関数
 */
WifiInfo readFileText(fs::FS &fs, const char * path){
  String result[] = {"", ""}; 
  WifiInfo resultInfo = {result[0], result[1]};

  // ファイルを開く
  File file = fs.open(path);
  if (!file){
    Serial.printf("file: %s ", path);
    Serial.println("Failed to open file for reading");
    return resultInfo;
  }

  // ファイルの中身をテキストとして読み込む
  int cnt = 0;
  while(file.available()){
    result[cnt] = result[cnt] + char(file.read());
    if (result[cnt].indexOf('\n') != -1) {
      result[cnt] = result[cnt].substring(0, result[cnt].length()-1);
      cnt++;
      if (cnt == 3) {
        break;
      }
    }
  }
  file.close();
  resultInfo.ssidInfo = result[0];
  resultInfo.passInfo = result[1];
  return resultInfo;
}

 /* Wifi接続関数 */
void connectWifi(char* ssid, char* password) {
  Serial.print("Connecting to ");
  Serial.println(ssid);

  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
}

/**
 * 文字列をchar*に変換する関数
 */
char* stringTochar(String command){
  if(command.length()!=0){
    char *p = const_cast<char*>(command.c_str());
    return p;
  }
}

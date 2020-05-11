//ライブラリを取得
#include <SD.h>

// CSを5に設定
const uint8_t cs_SD = 5; 

///ESP_Densou_test.txtというファイルがSDに生成される
const char* fname = "/ESP_Densou_test.txt";

int i = 0;

//Fileオブジェクトをfile(任意)と定義
File file;

//SD準備関数
void prepare_sd(){
  // 連続書き込みモードでファイルを開く
  file = SD.open(fname, FILE_APPEND);

  // 20回hello worldを書き込む
  for(i=0; i<20; i++)
  {
    //書き込み
    file.println("Hello world");

    //シリアルモニタに"Writing now"と表示がされる
    Serial.println("Writing now");

    // ファイルを閉じる
    file.close();
    delay(1000);  
  }
}


//初期化関数
void setup()
{
  //IDEのデータ通信速度を9600bpsとしてください
  Serial.begin(115200);

  //SDモジュールが接続できるか否か
  if(SD.begin(cs_SD, SPI, 24000000, "/sd"))
  {
    Serial.println("OK!");
  }
  else
  {
    Serial.println("NG!");
  }
}

//ループ関数
void loop(){
  //SD準備関数実行
  prepare_sd();
}

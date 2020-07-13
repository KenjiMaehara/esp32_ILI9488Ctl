HardwareSerial Serial_df(2);
int number=0;
 
void setup() {
    Serial_df.begin(9600);
}
 
void loop() {

  Serial_df.write(0x7e);
  Serial_df.write(0xff);
  Serial_df.write(0x06);    //命令6バイト
  Serial_df.write(0x12);    //指定フォルダ　　＊0x12 mp3フォルダ
  Serial_df.write(0x00);
  Serial_df.write(0x00);
  Serial_df.write(number++);    //play
  //Serial_df.write(0xfe);
  //Serial_df.write(0xe8);
  Serial_df.write(0xef);


  delay(5000);
}

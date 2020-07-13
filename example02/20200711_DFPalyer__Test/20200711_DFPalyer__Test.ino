// DFPlayerの動作確認
// UART2のSet Up Serial2.begin(9600, SERIAL_8N1, 32, 33);
// 音量調整方法の確認、外部にはハード的に音量調整SW1(volume+)､SW2(volume-)を設ける。
// 音量設定後、メッセージを出力する。
// メッセージ出力中監視はBusy PIn16(H→L→H)で確認
// 警報が継続している場合は、警報停止以外繰り返しメッセージを出力する。


void setup() {
// initialize both serial ports:

 Serial2.begin(9600, SERIAL_8N1, 32, 33);


 }

 void loop()
 {
 delay(100); 

// DFPlayer RESET
// Serial2.write(0x7E); // Start CMD
// Serial2.write(0xFF); // 
// Serial2.write(0x06); // 　
// Serial2.write(0x0C); // 
// Serial2.write(0x00);
// Serial2.write(0x00);
// Serial2.write(0x00); // RESET DFPlayer
// Serial2.write(0xEF); // End CMD

// delay(3000); 

// 1'st 音量調整(メッセージ毎に設定する。(通常　Level 16)
// 音量調整　Specified volume is level30← Power ON Reset
 Serial2.write(0x7E); // Start CMD
 Serial2.write(0xFF); // 　
 Serial2.write(0x06); // "7E FF 06 06 00 00 '1E(30)' EF" 00～255　
 Serial2.write(0x06); // 0x7E←6Byte→OxEF間、1COmmandは6Byteで構成されている。
 Serial2.write(0x00);
 Serial2.write(0x00);
 Serial2.write(0x12); // volume is level(00→30(Power ON Reset)→Max255(0xFF)
 Serial2.write(0xEF); // End CMD

  delay(100);
  
// 1'nd 音声メッセージ"No.12 エリア１の"
 Serial2.write(0x7E); // Start CMD
 Serial2.write(0xFF);
 Serial2.write(0x06); // 0x7E←6Byte→OxEF間、1COmmandは6Byteで構成されている。
 Serial2.write(0x12); // Play in the folder “MP3”
 Serial2.write(0x00);
 Serial2.write(0x00);
 Serial2.write(0x0c); //Play track "0012" in the folder “MP3”   HEXで指定
 Serial2.write(0xEF); // END CMD

 delay(1500);         // Busy CHKしていない為
 
// 2'nd 音声メッセージ
// 音量調整　Specified volume is level30← Power ON Reset
 //Serial2.write(0x7E); // Start CMD
 //Serial2.write(0xFF); // "7E FF 06 06 00 00 '1E(30)' EF" 00～255　
 //Serial2.write(0x06); // "7E FF 06 06 00 00 '1E(30)' EF" 00～255　
 //Serial2.write(0x06); // 0x7E←6Byte→OxEF間、1COmmandは6Byteで構成されている。
 //Serial2.write(0x00);
 //Serial2.write(0x00);
 //Serial2.write(0x12); // volume is level(00→30(1E)(Power ON Reset)→Max255(0xFF)
 //Serial2.write(0xEF); // End CMD

 //delay(100);          // Busy CHKしていない為
 
// 2'nd 音声メッセージ"No.03 盗難信号を"
 Serial2.write(0x7E); //
 Serial2.write(0xFF);
 Serial2.write(0x06); // 0x7E←6Byte→OxEF間、1COmmandは6Byteで構成されている。
 Serial2.write(0x12); // Play in the folder “MP3”
 Serial2.write(0x00);
 Serial2.write(0x00);
 Serial2.write(0x03); //Play track "0003" in the folder “MP3”  HEXで指定
 Serial2.write(0xEF); 
 
 delay(1800);          // Busy CHKしていない為
 
// 11'nd 音声メッセージ
// 音量調整　Specified volume is level30← Power ON Reset
 //Serial2.write(0x7E); // Start CMD
 //Serial2.write(0xFF); // "7E FF 06 06 00 00 '1E(30)' EF" 00～255　
 //Serial2.write(0x06); // "7E FF 06 06 00 00 '1E(30)' EF" 00～255　
 //Serial2.write(0x06); // 0x7E←6Byte→OxEF間、1COmmandは6Byteで構成されている。
 //Serial2.write(0x00);
 //Serial2.write(0x00);
 //Serial2.write(0x12); // volume is level(00→30(Power ON Reset)→Max255(0xFF)
 //Serial2.write(0xEF); // End CMD

 //delay(100);          // Busy CHKしていない為
 
// 11'nd 音声メッセージ"No.1 検知しました"
 Serial2.write(0x7E); //
 Serial2.write(0xFF);
 Serial2.write(0x06); // 0x7E←6Byte→OxEF間、1COmmandは6Byteで構成されている。
 Serial2.write(0x12); // Play in the folder “MP3”
 Serial2.write(0x00);
 Serial2.write(0x00);
 Serial2.write(0x01); //Play track "0001" in the folder “MP3”   HEXで指定
 Serial2.write(0xEF); 
 
 delay(3000);          // Busy CHKしていない為



  }


 

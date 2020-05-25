int n=0;

void setup() {
  Serial.begin(115200);
  //Serial1.begin(115200);
  Serial1.begin(115200, SERIAL_8N1, 32, 33);
  Serial2.begin(115200);

}

void loop() {
  n = n + 1;
  Serial.print(n, DEC);  // ASCIIコードを十進数で出力
  Serial.print(":hello_UART_0");
  Serial.println("");   //改行

  Serial1.print(n, DEC);  // ASCIIコードを十進数で出力
  Serial1.print("hello_UART_1");
  Serial1.println("");   //改行
  
  Serial2.print(n, DEC);  // ASCIIコードを十進数で出力
  Serial2.print(":hello_UART_2");
  Serial2.println("");   //改行
  
  delay(1000);
}

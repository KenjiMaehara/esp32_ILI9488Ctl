int n=0;

void setup() {
  Serial.begin(115200);
  //Serial1.begin(115200);
  Serial1.begin(115200, SERIAL_8N1, 32, 33);
  Serial2.begin(115200);

}

void loop() {

  #if 0
  n = n + 1;
  Serial.print(n, DEC);  // ASCIIコードを十進数で出力
  Serial.print(":hello_UART_0");
  Serial.println("");   //改行

  Serial1.print(n, DEC);  // ASCIIコードを十進数で出力
  Serial1.print(":hello_UART_1");
  Serial1.println("");   //改行
  
  Serial2.print(n, DEC);  // ASCIIコードを十進数で出力
  Serial2.print(":hello_UART_2");
  Serial2.println("");   //改行

  #endif
  

  // read from port 1, send to port 0:
  if (Serial.available()>0) {
    Serial.print("hello_UART_0");
    Serial.println("");   //改行

    String str = Serial.readStringUntil('\n');
    Serial.print("talk:");
    Serial.println(str);
    Serial1.print("talk:");
    Serial1.println(str);
    Serial2.print("talk:");
    Serial2.println(str);
  }

  // read from port 0, send to port 1:
  if (Serial1.available()>0) {
    Serial.print("hello_UART_1");
    Serial.println("");   //改行
    
    String str = Serial1.readStringUntil('\n');
    Serial.print("talk:");
    Serial.println(str);
    Serial1.print("talk:");
    Serial1.println(str);
    Serial2.print("talk:");
    Serial2.println(str);
  }

  // read from port 0, send to port 1:
  if (Serial2.available()>0) {
    Serial.print("hello_UART_2");
    Serial.println("");   //改行
    
    String str = Serial2.readStringUntil('\n');
    Serial.print("talk:");
    Serial.println(str);
    Serial1.print("talk:");
    Serial1.println(str);
    Serial2.print("talk:");
    Serial2.println(str);
  }

  delay(1000);

}

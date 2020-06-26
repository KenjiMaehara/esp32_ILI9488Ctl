/*
  ReadAnalogVoltage

  Reads an analog input on pin 0, converts it to voltage, and prints the result to the Serial Monitor.
  Graphical representation is available using Serial Plotter (Tools > Serial Plotter menu).
  Attach the center pin of a potentiometer to pin A0, and the outside pins to +5V and ground.

  This example code is in the public domain.

  http://www.arduino.cc/en/Tutorial/ReadAnalogVoltage
*/

// the setup routine runs once when you press reset:
void setup() {
  // initialize serial communication at 9600 bits per second:
  Serial.begin(9600);
}

// the loop routine runs over and over again forever:
void loop() {
  // read the input on analog pin 0:
  int sensorValue = analogRead(A0);
  Serial.println(sensorValue);
  // Convert the analog reading (which goes from 0 - 4095) to a voltage (0 - 15V): 
     float voltage = sensorValue*(0.00393);
  //  9.0V: 8.89～8.98V      9.5V:9.33～9.52V 　　
  // 10.0V: 9.86～9.98V     10.5V:10.42～10.55V 　
  // 11.0V: 10.99～11.15V   11.5V:11.53～11.62V 　
  // 12.0V: 12.13～12.27V   12.5V:12.73～12.84V 　13V以下の場合、補正無し
  // 13.0V: 13.64～13.77V   13.5V:14.39～14.56V   13V以上、15V以下の場合、-0.8を減算補正
  // 14.0V: 15.21～15.45V         　　　　　　　　　 15V以上の場合、-1.4を減算　
  // 15.0V: 16.00V 以上は全て15Vとする。　　　　　　　 
  // print out the value you read:
  Serial.println(voltage);
  delay(1000);        // delay in between reads for stability
}

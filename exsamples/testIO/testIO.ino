void setup() {
Serial.begin(115200);
pinMode(2, OUTPUT);
}

void loop() {
digitalWrite(2, HIGH); 
delay(1000); 
digitalWrite(2, LOW);
delay(1000);
Serial.println("Test_Print");
}

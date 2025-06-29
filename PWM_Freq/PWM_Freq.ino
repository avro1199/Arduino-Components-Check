void setup() {
  // put your setup code here, to run once:
  TCCR0B = TCCR0B & B11111000 | B00000001;
  Serial.begin(115200);
  analogWrite(5, 30);

}

void loop() {
  // put your main code here, to run repeatedly:
  // for(int i = 0; i < 256; i++){
  //   analogWrite(5, i);
  //   Serial.println(i);
  //   delay(50);
  // }
  // digitalWrite(5, 0);
  delay(500);

}

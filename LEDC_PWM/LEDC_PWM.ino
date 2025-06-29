void setup() {
  // put your setup code here, to run once:
  ledcSetup(0, 10000, 8);
  ledcSetup(1, 10000, 8);
  ledcAttachPin(18, 0);
  ledcAttachPin(19, 1);
  Serial.begin(115200);
}

void loop() {
  // put your main code here, to run repeatedly:
  // ledcWrite(0, 0);
  // delay(3000);
  // for(int i = 0; i <= 1000; i+=100){
  //   ledcWrite(0, i);
  //   Serial.println(i);
  //   delay(3000);
  // }
  ledcWrite(0, 0);
  ledcWrite(1, 0);
  delay(2000);
  ledcWrite(0, 0);
  ledcWrite(1, 255);
  delay(2000);
  ledcWrite(0, 255);
  ledcWrite(1, 255);
  delay(2000);
  ledcWrite(0, 255);
  ledcWrite(1, 0);
  delay(2000);
  ledcWrite(0, 0);
  ledcWrite(1, 0);
  delay(2000);
  for (int i = 0; i <= 255; i += 5) {
    ledcWrite(0, i);
    ledcWrite(1, 255-i);
    delay(500);
  }
}

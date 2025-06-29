void setup() {
  // put your setup code here, to run once:
  ledcAttach(26, 10000, 10);
  Serial.begin(115200);
}

void loop() {
  // put your main code here, to run repeatedly:
  ledcWrite(26, 0);
  delay(3000);
  for(int i = 0; i <= 1000; i+=100){
    ledcWrite(26, i);
    Serial.println(i);
    delay(3000);
  }
}

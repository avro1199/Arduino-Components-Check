void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
}

void loop() {
  // put your main code here, to run repeatedly:
  analogWrite(5, 0);
  Serial.println(0);
  delay(3000);
  for (int i = 0; i <= 210; i += 30) {
    analogWrite(5, i);
    Serial.println(i);
    delay(3000);
  }
  
}

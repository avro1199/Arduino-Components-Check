void setup() {
  // put your setup code here, to run once:
  pinMode(2, OUTPUT);
  Serial.begin(115200);

  Serial.println("Started...");
  delay(1000);

  for(int i = 0; i < 256; i++){
    analogWrite(18, i);
    analogWrite(19, 0);
    Serial.println(i);
    delay(100);
  }
  delay(500);
  digitalWrite(2, 1);

  analogWrite(18, 255);
  analogWrite(19, 255);
  delay(1000);
  digitalWrite(2, 0);

  for(int i = 0; i < 256; i++){
    analogWrite(18, 0);
    analogWrite(19, i);
    Serial.println(i);
    delay(100);
  }
  delay(1000);

}

void loop() {
  // put your main code here, to run repeatedly:
  analogWrite(18, 0);
  analogWrite(19, 0);
  digitalWrite(2, 0);
  delay(2000);

  analogWrite(18, 255);
  analogWrite(19, 0);
  digitalWrite(2, 1);
  delay(2000);

  analogWrite(18, 255);
  analogWrite(19, 255);
  digitalWrite(2, 0);
  delay(2000);

  analogWrite(18, 0);
  analogWrite(19, 255);
  digitalWrite(2, 1);
  delay(2000);
}

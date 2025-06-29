void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  analogWrite(5, 0);

}

void loop() {
  // put your main code here, to run repeatedly:
  unsigned long t1 = micros();
  Serial.print(analogRead(A7));
  Serial.print("  =>  ");
  // delayMicroseconds(30);
  Serial.print(micros()-t1);
  Serial.println("uS");
  delay(300);

}

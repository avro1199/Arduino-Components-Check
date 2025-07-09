void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
}

void loop() {
  // put your main code here, to run repeatedly:
  for (int i = 1; i <= 100; i++) {
    ledcAttach(26, 1000 * i, 8);
    ledcWrite(26, 80);
    Serial.println("Frequency = "+String(i)+" kHz");
    delay(2000);
    ledcDetach(26);
  }
}

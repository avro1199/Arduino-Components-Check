void setup() {
  // put your setup code here, to run once:
  pinMode(15, INPUT_PULLUP);
  pinMode(16, INPUT_PULLUP);
  pinMode(17, INPUT_PULLUP);

  Serial.begin(115200);
  analogWrite(5, 0);
}

void loop() {
  // put your main code here, to run repeatedly:
  if(!digitalRead(15)){
    Serial.println("Right");
    delay(300);
  }
  else if(!digitalRead(16)){
    Serial.println("Left");
    delay(300);
  }
  else if(!digitalRead(17)){
    Serial.println("Middle");
    delay(300);
  }
}

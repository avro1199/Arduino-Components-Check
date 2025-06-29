#define btn_l PA1
#define btn_u PA2
#define btn_m PA3
#define btn_r PC14
#define btn_d PC15

void setup() {
  // put your setup code here, to run once:
  pinMode(btn_d, INPUT_PULLUP);
  pinMode(btn_u, INPUT_PULLUP);
  pinMode(btn_l, INPUT_PULLUP);
  pinMode(btn_r, INPUT_PULLUP);
  pinMode(btn_m, INPUT_PULLUP);
}

void loop() {
  // put your main code here, to run repeatedly:
  if(!digitalRead(btn_u))
  {
    Serial.println("UP is Working!");
  }
  if(!digitalRead(btn_m))
  {
    Serial.println("Mid is Working!");
  }
  if(!digitalRead(btn_d))
  {
    Serial.println("DN is Working!");
  }
  if(!digitalRead(btn_l))
  {
    Serial.println("Left is Working!");
  }
  if(!digitalRead(btn_r))
  {
    Serial.println("Right is Working!");
  }
  delay(100);
}

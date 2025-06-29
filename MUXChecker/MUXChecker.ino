int d = 2;

void setup() {
  // put your setup code here, to run once:
  pinMode(2, OUTPUT);
  pinMode(4, OUTPUT);
  Serial.begin(115200);

}

void loop() {
  // put your main code here, to run repeatedly:
  // Serial.println(analogRead(34));
  // digitalWrite(2, (touchRead(T4) < 40));
  digitalWrite(2, HIGH);
  digitalWrite(4, HIGH);
  // Serial.print("3 => ");
  Serial.print(analogRead(34));
  Serial.print(", ");
  delay(d);
  digitalWrite(2, LOW);
  digitalWrite(4, HIGH);
  // Serial.print("1 => ");
  Serial.print(analogRead(34));
  Serial.print(", ");
  delay(d);
  digitalWrite(2, LOW);
  digitalWrite(4, LOW);
  // Serial.print("0 => ");
  Serial.print(analogRead(34));
  Serial.println(" ");
  delay(d);

}

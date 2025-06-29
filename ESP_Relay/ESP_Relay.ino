void setup() {
  // put your setup code here, to run once:
  pinMode(17, OUTPUT);
  pinMode(2, OUTPUT);
  Serial.begin(115200);

}

void loop() {
  // put your main code here, to run repeatedly:
  if(touchRead(T0) < 50){
    digitalWrite(17, HIGH);
    digitalWrite(2, HIGH);
    Serial.println("Activated!");
  }
  else{
    digitalWrite(17, LOW);
    digitalWrite(2, LOW);
  }
  Serial.println(touchRead(T0));

}

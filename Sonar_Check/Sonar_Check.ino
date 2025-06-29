#include<NewPing.h>

NewPing sonar_l(4, 4, 100);
NewPing sonar_f(2, 2, 100);
NewPing sonar_r(14, 14, 100);

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  analogWrite(5, 0);

}

void loop() {
  // put your main code here, to run repeatedly:
  Serial.print(sonar_l.ping_cm());
  Serial.print(" <=> ");
  Serial.print(sonar_f.ping_cm());
  Serial.print(" <=> ");
  Serial.print(sonar_r.ping_cm());
  Serial.print(" <=> ");
  Serial.print(analogRead(A6));
  Serial.println();

  delay(100);
}

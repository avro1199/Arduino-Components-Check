#include <Servo.h>

Servo rj;

void setup() {
  // put your setup code here, to run once:
  rj.attach(11, 1000, 2000);
  delay(4000);

}

void loop() {
  // put your main code here, to run repeatedly:
  rj.write(0);
  delay(2000);

  rj.write(20);
  delay(3000);

  rj.write(50);
  delay(3000);

  rj.write(90);
  delay(3000);

}

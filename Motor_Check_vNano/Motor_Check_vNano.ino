#define lmf 3
#define lmb 9
#define rmf 11
#define rmb 10

void setup() {
  // put your setup code here, to run once:
  pinMode(lmf, OUTPUT);
  pinMode(lmb, OUTPUT);
  pinMode(rmf, OUTPUT);
  pinMode(rmb, OUTPUT);
  analogWrite(5, 0);
}

void loop() {
  // put your main code here, to run repeatedly:
  motor(200, 200);
  delay(2000);
  motor(0, 0);
  delay(2000);
  motor(-200, -200);
  delay(2000);
  brake();
  delay(500);
  motor(0, 0);
  delay(2000);
}

void motor(int lms, int rms) {
  if (lms >= 0) {
    digitalWrite(lmb, 0);
    analogWrite(lmf, lms);
  } else {
    lms *= -1;
    digitalWrite(lmf, 0);
    analogWrite(lmb, lms);
  }

  if (rms >= 0) {
    digitalWrite(rmb, 0);
    analogWrite(rmf, rms);
  } else {
    rms *= -1;
    digitalWrite(rmf, 0);
    analogWrite(rmb, rms);
  }
}

void brake()
{
  digitalWrite(lmf, 1);
  digitalWrite(lmb, 1);
  digitalWrite(rmf, 1);
  digitalWrite(rmb, 1);
}

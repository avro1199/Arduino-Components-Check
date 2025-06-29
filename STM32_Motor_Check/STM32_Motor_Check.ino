#define lmf PB4
#define lmb PB5
#define rmf PB7
#define rmb PB6

#define led PB12

void setup() {
  // put your setup code here, to run once:
  pinMode(lmf, OUTPUT);
  pinMode(lmb, OUTPUT);
  pinMode(rmf, OUTPUT);
  pinMode(rmb, OUTPUT);

  pinMode(led, OUTPUT);

  motor(0, 0);
  digitalWrite(led, 0);
  delay(1000);
}

void loop() {
  // put your main code here, to run repeatedly:
  digitalWrite(led, 1);
  motor(-100, 100);
  delay(5000);

  digitalWrite(led, 0);
  motor(0,0);
  delay(2000);

  digitalWrite(led, 1);
  motor(-100, -100);
  delay(5000);

  digitalWrite(led, 0);
  motor(0,0);
  delay(2000);

  digitalWrite(led, 1);
  motor(100, 100);
  delay(5000);
  
  digitalWrite(led, 0);
  delay(200);
  digitalWrite(led, 1);
  delay(200);
  digitalWrite(led, 0);
  delay(200);
  digitalWrite(led, 1);
  delay(200);

  brake();

  digitalWrite(led, 0);
  motor(0,0);
  delay(2000);
}

void motor(int lms, int rms)
{
    if (lms >= 0)
    {
        analogWrite(lmf, lms);
        analogWrite(lmb, 0);
    }
    else
    {
        lms *= -1;
        analogWrite(lmf, 0);
        analogWrite(lmb, lms);
    }

    if (rms >= 0)
    {
        analogWrite(rmf, rms);
        analogWrite(rmb, 0);
    }
    else
    {
        rms *= -1;
        analogWrite(rmf, 0);
        analogWrite(rmb, rms);
    }
}

void brake()
{
    analogWrite(lmf, 255);
    analogWrite(lmb, 255);
    analogWrite(rmf, 255);
    analogWrite(rmb, 255);

    delay(1000);
}
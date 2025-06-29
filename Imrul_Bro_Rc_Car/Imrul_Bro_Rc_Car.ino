#define lmf 9
#define lmb 8
#define lms 10
#define rmf 5
#define rmb 4
#define rms 3

char ch;
int speed = 80;

void wheel(int a, int b){
  if(a>=0){
    digitalWrite(lmf, HIGH);
    digitalWrite(lmb, LOW);
  }
  else{
    a *= -1;
    digitalWrite(lmf, LOW);
    digitalWrite(lmb, HIGH);
  }

  if(b>=0){
    digitalWrite(rmf, HIGH);
    digitalWrite(rmb, LOW);
  }
  else{
    b *= -1;
    digitalWrite(rmf, LOW);
    digitalWrite(rmb, HIGH);
  }

  analogWrite(lms, a);
  analogWrite(rms, b);
}

void setup() {
  // put your setup code here, to run once
  // delay(1000);
  // wheel(-200, 100);
  Serial.begin(115200);

}

void loop() {
  // put your main code here, to run repeatedly:
  if(Serial.available()){
    ch = Serial.read();
    Serial.println(ch);
    if(ch == 'S'){
      wheel(0, 0);
    }
    if(ch >= '0' && ch <= '9'){
      speed = 70 + (20*(ch - '0'));
      Serial.println(speed);
    }
    else if(ch == 'F'){
      wheel(speed, speed);
    }
    else if (ch == 'B') {
      wheel(-speed, -speed);
    }
    else if (ch == 'R') {
      wheel(speed, -speed);
    }
    else if (ch == 'L') {
      wheel(-speed, speed);
    }
  }

}

#include <CD74HC4067.h>

             //s0 s1 s2 s3
CD74HC4067 mux(6, 12, 7, 8);  // create a new CD74HC4067 object with its four control pins


void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  analogWrite(5, 0);
}

void loop() {
  // put your main code here, to run repeatedly:
  for(int i = 0; i < 8; i++)
  {
    mux.channel(i);
    delayMicroseconds(5);
    Serial.print(analogRead(A7));
    Serial.print("   ");
  }
  Serial.println();
  delay(100);

}

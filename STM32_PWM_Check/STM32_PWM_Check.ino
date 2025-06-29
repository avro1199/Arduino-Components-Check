#include "Arduino.h"

void setup() {
  // put your setup code here, to run once:
  pinMode(PB4, OUTPUT);
  pinMode(PB5, OUTPUT);
  pinMode(PB6, OUTPUT);
  pinMode(PB7, OUTPUT);
  Serial.begin(115200);
  while (!Serial)
    ;
  analogWriteResolution(10);
  analogWriteFrequency(20000L);
}

void loop() {
  // put your main code here, to run repeatedly:
  for (int i = 0; i <= 255; i += 5) {
    analogWrite(PB6, i);
    analogWrite(PB7, 255 - i);
    Serial.println(i);
    delay(300);
    if (i == 0) delay(1000);
  }

  for (int i = 0; i <= 255; i += 5) {
    analogWrite(PB4, i);
    analogWrite(PB6, 255 - i);
    Serial.println(i);
    delay(300);
  }

  for (int i = 0; i < 255; i += 5) {
    analogWrite(PB5, i);
    Serial.println(i);
    delay(300);
    if (i == 0) delay(2000);
  }
}

#include <Wire.h>
#include "SSD1306Ascii.h"
#include "SSD1306AsciiWire.h"
#include <NewPing.h>
#include <CD74HC4067.h>

// 0X3C+SA0 - 0x3C or 0x3D
#define I2C_ADDRESS 0x3C

// Define proper RST_PIN if required.
#define RST_PIN -1

#define lmf 19
#define lmb 18
#define rmf 16
#define rmb 17

#define btn_r 25
#define btn_l 32
#define btn_d 33
#define btn_m 35
#define btn_u 34

#define coreless 26
#define led 2

SSD1306AsciiWire oled;
NewPing sonar(23, 23, 100);
// s0  s1  s2  s3
CD74HC4067 my_mux(12, 13, 27, 14);

uint64_t strt, stp;
uint32_t a1, a2;
uint32_t s[10];
uint8_t d;
uint8_t m = 0;


void coreless_check() {
  ledcWrite(coreless, 20);
  delay(4000);
  ledcWrite(coreless, 30);
  delay(4000);
  ledcWrite(coreless, 40);
  delay(4000);
  ledcWrite(coreless, 50);
  delay(4000);
  ledcWrite(coreless, 70);
  delay(4000);
  ledcWrite(coreless, 100);
  delay(4000);
  ledcWrite(coreless, 120);
  delay(4000);
  ledcWrite(coreless, 150);
  delay(4000);
  ledcWrite(coreless, 200);
  delay(4000);
  ledcWrite(coreless, 250);
  delay(4000);
  ledcWrite(coreless, 0);
}

void motor(int lms, int rms) {
  if (lms >= 0) {
    ledcWrite(lmf, lms);
    ledcWrite(lmb, 0);
  } else {
    lms *= -1;
    ledcWrite(lmf, 0);
    ledcWrite(lmb, lms);
  }

  if (rms >= 0) {
    ledcWrite(rmf, rms);
    ledcWrite(rmb, 0);
  } else {
    rms *= -1;
    ledcWrite(rmf, 0);
    ledcWrite(rmb, rms);
  }
}

void setup() {
  // put your setup code here, to run once:
  pinMode(25, INPUT_PULLUP);
  pinMode(33, INPUT_PULLUP);
  pinMode(32, INPUT_PULLUP);
  pinMode(35, INPUT_PULLUP);
  pinMode(34, INPUT_PULLUP);

  pinMode(led, OUTPUT);

  Serial.begin(115200);

  Wire.begin();
  Wire.setClock(400000L);

#if RST_PIN >= 0
  oled.begin(&SH1106_128x64, I2C_ADDRESS, RST_PIN);
#else   // RST_PIN >= 0
  oled.begin(&SH1106_128x64, I2C_ADDRESS);
#endif  // RST_PIN >= 0

  ledcAttach(lmf, 10000, 8);
  ledcAttach(lmb, 10000, 8);
  ledcAttach(rmf, 10000, 8);
  ledcAttach(rmb, 10000, 8);

  ledcAttach(coreless, 10000, 8);

  ledcWrite(coreless, 0);

  oled.setFont(Adafruit5x7);
  oled.set2X();
  oled.println("  Rj Avro");
  oled.println();
  oled.print(" <<Hello>>");
  delay(4000);
  oled.clear();
  oled.println("Start:");
  delay(1000);

  oled.set1X();
}

void loop() {
  // put your main code here, to run repeatedly:
  if (m > 7) {
    m = 2;
  }

  if (!digitalRead(btn_r)) {
    Serial.println("Right Pressed!");
    oled.clear();
    oled.println("Right Pressed!");
    motor(200, -200);
    delay(300);
  }
  if (!digitalRead(btn_d)) {
    Serial.println("Down Pressed!");
    oled.clear();
    oled.println("Down Pressed!");
    motor(-200, -200);
    delay(300);
  }
  if (!digitalRead(btn_l)) {
    Serial.println("Left Pressed!");
    oled.clear();
    oled.println("Left Pressed!");
    motor(-200, 200);
    delay(300);
  }
  if (!digitalRead(btn_m)) {
    Serial.println("Middle Pressed!");
    oled.clear();
    oled.println("Middle Pressed!");
    motor(0, 0);
    coreless_check();
    delay(300);
  }
  if (!digitalRead(btn_u)) {
    Serial.println("Up Pressed!");
    oled.clear();
    oled.println("Up Pressed!");
    motor(200, 200);
    delay(300);
  }

  oled.clear();
  my_mux.channel(m);
  // oled.println();
  strt = micros();
  a1 = analogRead(36);
  a2 = analogRead(39);
  stp = micros() - strt;
  // oled.print(m);
  // oled.print("->");
  // oled.println(map(a1, 0, 4095, 0, 10));

  //
  for (int i = 0; i < 10; i++) {
    my_mux.channel(i);
    s[i] = analogRead(36);
  }

  for (int i = 0; i < 10; i++) {
    Serial.print(s[i]);
    Serial.print("  ");
  }
  Serial.println();

  oled.clear();
  for (int i = 3; i >= 0; i--) {
    oled.setCursor(0, 2 * i);
    oled.print(s[3 - i]);
  }
  for (int i = 4; i < 7; i++) {
    oled.print(" ");
    if (i == 4 || i == 6) {
      oled.print(" ");
    }
    oled.print(s[i]);
  }
  for (int i = 7; i < 10; i++) {
    oled.setCursor(102, 2 * (i - 6));
    oled.print(s[i]);
  }
  // Serial.println();
  // oled.println(a2);
  // oled.println(stp);
  // oled.print("D -> ");
  // d = sonar.ping_cm();
  // oled.print(d);
  if (d < 10 && d > 0) {
    digitalWrite(led, 1);
  } else {
    digitalWrite(led, 0);
  }
  // m++;
  delay(1);
}

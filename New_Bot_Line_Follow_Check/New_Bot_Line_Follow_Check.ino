#include <Wire.h>
#include "SSD1306Ascii.h"
#include "SSD1306AsciiWire.h"
#include <NewPing.h>
#include <CD74HC4067.h>

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

//                s0  s1  s2  s3
CD74HC4067 my_mux(12, 13, 27, 14);
SSD1306AsciiWire oled;
NewPing sonar(23, 23, 100);

uint16_t s[10], thresh[] = {3000, 3000, 3000, 3000, 3000, 3000, 3000, 3000, 3000, 3000};
uint16_t sensor, base[] = {512,256, 128, 64, 32, 16, 8, 4, 2, 1};
uint8_t sum_trn, sum_pid;

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
  oled.begin(&SH1106_128x64, 0x3C);

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
  if (!digitalRead(btn_r)) {
    Serial.println("Right Pressed!");
    oled.clear();
    oled.println("Right Pressed!");
    oled.println();
    oled.println("--Analog Show--");
    delay(100);
    show_analog();
  }
  if (!digitalRead(btn_d)) {
    Serial.println("Down Pressed!");
    oled.clear();
    oled.println("--Coreless Check! --");
    delay(500);
    coreless_check();
  }
  if (!digitalRead(btn_l)) {
    Serial.println("Left Pressed!");
    oled.clear();
    oled.println("Left Pressed!");
    oled.println("--Digital Show--");
    delay(300);
    show_digital();
  }
  if (!digitalRead(btn_m)) {
    Serial.println("Middle Pressed!");
    oled.clear();
    oled.println("Middle Pressed!");
    motor(0, 0);
    delay(300);
  }
  if (!digitalRead(btn_u)) {
    Serial.println("Up Pressed!");
    oled.clear();
    oled.println(" -- Line Follow -- ");
    delay(100);
    line_follow();
  }
  delay(10);
}

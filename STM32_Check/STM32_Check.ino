#include <Wire.h>
#include "SSD1306Ascii.h"
#include "SSD1306AsciiWire.h"

// 0X3C+SA0 - 0x3C or 0x3D
#define I2C_ADDRESS 0x3C

// Define proper RST_PIN if required.
#define RST_PIN -1

SSD1306AsciiWire oled;

unsigned int m1 = 0, m2 = 0, m3 = 0;
uint16_t i = 0;
bool l1 = 0;

// the setup function runs once when you press reset or power the board
void setup() {
  // initialize digital pin LED_BUILTIN as an output.
  Wire.begin();
  Wire.setClock(400000L);

#if RST_PIN >= 0
  oled.begin(&SH1106_128x64, I2C_ADDRESS, RST_PIN);
#else   // RST_PIN >= 0
  oled.begin(&SH1106_128x64, I2C_ADDRESS);
#endif  // RST_PIN >= 0

  oled.setFont(Adafruit5x7);

  uint32_t m = micros();
  oled.clear();
  oled.println("Hello world!");
  oled.println("A long line may be truncated");
  oled.println();
  oled.set2X();
  oled.println("2X demo");
  oled.set1X();
  oled.print("\nmicros: ");
  oled.print(micros() - m);

  
  pinMode(PB8, INPUT_PULLUP);
  pinMode(PB9, OUTPUT);
  pinMode(PC13, OUTPUT);
  // Serial.begin();
  digitalWrite(PC13, 1);
}

// the loop function runs over and over again forever
void loop() {
  // m1 = millis();
  if ((millis() - m1) > 10) {
    if (l1 == 0) {
      analogWrite(PB9, i);
      i += 5;
      if (i >= 255) {
        l1 = 1;
      }
    }
    if (l1 == 1) {
      analogWrite(PB9, i);
      i -= 5;
      if (i <= 0) {
        l1 = 0;
      }
    }
    m1 = millis();
  }
  if (millis() - m2 > 1000) {
    Serial.println("Namaste World !");
    m2 = millis();
  }
  if (millis() - m3 > 10) {
    Serial.println(digitalRead(PB8));
    m3 = millis();
  }
}

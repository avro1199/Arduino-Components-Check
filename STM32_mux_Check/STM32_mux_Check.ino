#include <Wire.h>
#include <Adafruit_SH110X.h>
#include <Adafruit_GFX.h>
#include <CD74HC4067.h>



Adafruit_SH1106G oled = Adafruit_SH1106G(128, 64, &Wire);
CD74HC4067 my_mux(PA7, PA6, PB0, PB1);

// uint16_t a_val[8];
unsigned long t, t1;
uint16_t a_val[10];

void setup()
{
  pinMode(PA5, INPUT);
  analogReadResolution(12);

  Wire.setSCL(PB8);
  Wire.setSDA(PB9);
  Wire.setClock(400000L);
  Wire.begin();

  Serial.begin(115200);
  // while (!Serial)
  //   ;
  delay(250);
  oled.begin(0x3c);

  oled.display();
  delay(2000);

  //Rj Check
  oled.clearDisplay();
  oled.setTextColor(SH110X_WHITE);
  oled.setCursor(0, 0);
  oled.println("Failure is always an option");
  oled.println("          --Rj Avro");
  oled.display();

  delay(1000);
}

void loop()
{
    for (int i = 0; i < 10; i++) {
        my_mux.channel(i);
        // delayMicroseconds(2);
        a_val[i] = analogRead(PA5);
        // Serial.print(a_val[i]);
        // Serial.print(" <=> ");
        // delay(1);
    }
    // Serial.println();
    show_bar(a_val, 10, 0, 4095);
    delay(50);
}

void show_bar(uint16_t *data, uint8_t size, uint16_t min, uint16_t max) {
  oled.clearDisplay();
  oled.setRotation(90);

  for (int i = 0; i < size; i++) {
    oled.fillRect(114 - ((i * 12)), 0, 10, map(constrain(data[i], min, max), min, max, 0, 64), 1);
  }
  oled.display();
  oled.setRotation(0);
}
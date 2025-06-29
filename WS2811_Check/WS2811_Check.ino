#include "FastLED.h"

// How many leds in your strip?
#define NUM_LEDS 16

// For led chips like Neopixels, which have a data line, ground, and power, you just
// need to define DATA_PIN.  For led chipsets that are SPI based (four wires - data, clock,
// ground, and power), like the LPD8806 define both DATA_PIN and CLOCK_PIN
#define DATA_PIN 13

// Define the array of leds
CRGB leds[NUM_LEDS];

#define del 100

void setup() {
  // Uncomment/edit one of the following lines for your leds arrangement.
  // FastLED.addLeds<TM1803, DATA_PIN, RGB>(leds, NUM_LEDS);
  // FastLED.addLeds<TM1804, DATA_PIN, RGB>(leds, NUM_LEDS);
  // FastLED.addLeds<TM1809, DATA_PIN, RGB>(leds, NUM_LEDS);
  // FastLED.addLeds<WS2811, DATA_PIN, GRB>(leds, NUM_LEDS);
  FastLED.addLeds<WS2812, DATA_PIN, RGB>(leds, NUM_LEDS);
  // FastLED.addLeds<WS2812B, DATA_PIN, RGB>(leds, NUM_LEDS);
  // FastLED.addLeds<NEOPIXEL, DATA_PIN>(leds, NUM_LEDS);
  // FastLED.addLeds<APA104, DATA_PIN, RGB>(leds, NUM_LEDS);
  // FastLED.addLeds<UCS1903, DATA_PIN, RGB>(leds, NUM_LEDS);
  // FastLED.addLeds<UCS1903B, DATA_PIN, RGB>(leds, NUM_LEDS);
  // FastLED.addLeds<GW6205, DATA_PIN, RGB>(leds, NUM_LEDS);
  // FastLED.addLeds<GW6205_400, DATA_PIN, RGB>(leds, NUM_LEDS);

  // FastLED.addLeds<WS2801, RGB>(leds, NUM_LEDS);
  // FastLED.addLeds<SM16716, RGB>(leds, NUM_LEDS);
  // FastLED.addLeds<LPD8806, RGB>(leds, NUM_LEDS);
  // FastLED.addLeds<P9813, RGB>(leds, NUM_LEDS);
  // FastLED.addLeds<APA102, RGB>(leds, NUM_LEDS);
  // FastLED.addLeds<DOTSTAR, RGB>(leds, NUM_LEDS);

  // FastLED.addLeds<WS2801, DATA_PIN, CLOCK_PIN, RGB>(leds, NUM_LEDS);
  // FastLED.addLeds<SM16716, DATA_PIN, CLOCK_PIN, RGB>(leds, NUM_LEDS);
  // FastLED.addLeds<LPD8806, DATA_PIN, CLOCK_PIN, RGB>(leds, NUM_LEDS);
  // FastLED.addLeds<P9813, DATA_PIN, CLOCK_PIN, RGB>(leds, NUM_LEDS);
  // FastLED.addLeds<APA102, DATA_PIN, CLOCK_PIN, RGB>(leds, NUM_LEDS);
  // FastLED.addLeds<DOTSTAR, DATA_PIN, CLOCK_PIN, RGB>(leds, NUM_LEDS);
}

void fill(struct CRGB clr = CRGB::Red, long del_time = 100) {
  for (int i = 0; i < 4; i++) {
    for (int j = 0; j < 4; j++) {
      if ((i > 0 && i < 3) && (j > 0 && j < 3)) {
        if (clr == CRGB::Green) {
          leds[4 * i + j] = CRGB::Red;
        } else {
          leds[4 * i + j] = CRGB::Yellow;
        }

        continue;
      }
      leds[4 * i + j] = clr;
      FastLED.show();
    }
    delay(del_time);
  }
  for (int i = 0; i < 16; i++) {
    leds[i] = CRGB::Black;
  }
  FastLED.show();
  delay(10);
}

void arw(char *dir = "up", struct CRGB clr = CRGB::Red) {
  int up[] = { 0, 4, 6, 10, 11, 12, 13, 14 };
  int down[] = { 1, 2, 4, 5, 7, 8, 11, 12 };
  int left[] = { 0, 4, 6, 10, 11, 12, 13, 14 };
  int right[] = { 0, 4, 6, 10, 11, 12, 13, 14 };
  int *led, len;

  if(dir == "up"){
    led = up;
    len = sizeof(up);
  }
  else if(dir == "down"){
    led = down;
    len = sizeof(down);
  }

  for (int i = 0; i < 16; i++) {
    leds[i] = 0x000000;
  }
  for (int i = 0; i < len; i++) {
    leds[led[i]] = clr;
  }
  FastLED.show();
}


void loop() {
  // Turn the LED on, then pause
  FastLED.setBrightness(50);
  fill(CRGB::Red, 200);
  arw("up", 0x00AA44);
  delay(1000);
  arw("down", 0xAA00AA);
  delay(1000);
  fill(CRGB::Green, 200);
}
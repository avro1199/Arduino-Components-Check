#include <math.h>

#define DAC_PIN 25

const int sampleRate = 20000;   // 20 kHz sampling
const int tableSize = 256;

uint8_t sineTable[tableSize];

void setup() {
  // Generate sine lookup table (0–255 for DAC)
  for (int i = 0; i < tableSize; i++) {
    float angle = (2.0 * PI * i) / tableSize;
    sineTable[i] = (sin(angle) * 127.0) + 128; // shift to 0–255
  }
}

void loop() {
  // Sweep from 100 Hz to 1000 Hz
  for (int freq = 100; freq <= 3000; freq += 100) {
    
    int delayMicros = 1000000 / (freq * tableSize);

    unsigned long startTime = millis();

    // Play each frequency for ~2 seconds
    while (millis() - startTime < 2000) {
      for (int i = 0; i < tableSize; i++) {
        dacWrite(DAC_PIN, sineTable[i]);
        delayMicroseconds(delayMicros);
      }
    }
  }
}
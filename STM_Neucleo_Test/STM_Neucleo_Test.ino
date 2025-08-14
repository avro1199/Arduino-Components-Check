void setup() {
  // DAC pins don't need pinMode() — they are handled internally
    analogWriteResolution(12); // Set resolution to 12 bits
    analogWriteFrequency(20000); // Set frequency for PA5 (DAC output)
}

void loop() {
  // Sweep from 0V to 3.3V
  for (int val = 0; val <= 4095; val += 10) { // 12-bit DAC: 0–4095
    analogWrite(PA6, val); // Output DAC voltage
    delay(20);
  }

  // Sweep from 3.3V back to 0V
  for (int val = 4095; val >= 0; val -= 10) {
    analogWrite(PA6, val);
    delay(20);
  }
}
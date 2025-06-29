#include "Arduino.h"

HardwareTimer timer3(TIM3);
HardwareTimer timer4(TIM4);

void setup() {
  // TIM3: PB4 (CH1), PB5 (CH2)
  // TIM4: PB6 (CH1), PB7 (CH2)

  // Set Prescaler to 7 (ensures ~50 kHz)
  timer3.setPrescaleFactor(7);
  timer4.setPrescaleFactor(7);

  // Set PWM resolution (ARR = 255 for 0-255 range)
  timer3.setOverflow(255, TICK_FORMAT);
  timer4.setOverflow(255, TICK_FORMAT);

  // Set initial duty cycles (0-255)
  timer3.setCaptureCompare(TIM_CHANNEL_1, 127, TICK_COMPARE_FORMAT);  // 50% on PB4
  timer3.setCaptureCompare(TIM_CHANNEL_2, 64, TICK_COMPARE_FORMAT);   // 25% on PB5
  timer4.setCaptureCompare(TIM_CHANNEL_1, 191, TICK_COMPARE_FORMAT);  // 75% on PB6
  timer4.setCaptureCompare(TIM_CHANNEL_2, 255, TICK_COMPARE_FORMAT);  // 100% on PB7

  // Start PWM
  timer3.resume();
  timer4.resume();
}

void loop() {
  // Example: Change duty cycle dynamically
  static uint8_t duty = 0;
  timer3.setCaptureCompare(TIM_CHANNEL_1, duty, TICK_COMPARE_FORMAT);
  duty = (duty + 10) % 256;  // Increase duty cycle (0-255)
  delay(100);
}

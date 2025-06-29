
void setup() {
  // put your setup code here, to run once:
  pinMode(PB13, OUTPUT);
  pinMode(PB14, OUTPUT);

  pinMode(PB15, OUTPUT);
  pinMode(PA8, OUTPUT);

  pinMode(PA4, INPUT);

  analogReadResolution(12);

  // generate a test 2kHz square wave on PB9 PWM pin, using Timer 4 channel 4
  // PB9 is Timer 4 Channel 4 from Arduino_Core_STM32/variants/STM32F4xx/F411C(C-E)(U-Y)/PeripheralPins_BLACKPILL_F411CE.c
  // analogWrite(PB9, 127);       // configures PB9 as PWM output pin at default frequency (1kHz) and resolution (8 bits), 50% duty cycle
  // analogWriteFrequency(2000);  // default PWM frequency is 1kHz, change it to 2kHz
  // analogWriteResolution(16);   // set PWM resolution to 16 bits, default is 8 bits
  // analogWrite(PB9, 32767);     // 32767 for 16 bits -> 50% duty cycle so a square wave
}

int val;
void loop() {
  // put your main code here, to run repeatedly:
  val = analogRead(A4);
  Serial.print(val);
  Serial.print(" -> ");
  // val = map(val, 0, 1023, 0, 255);
  Serial.println(val);

  // analogWrite(PB13, val);
  // analogWrite(PB14, 255 - val);

  // analogWrite(PB15, val);
  // analogWrite(PA8, 255 - val);
}

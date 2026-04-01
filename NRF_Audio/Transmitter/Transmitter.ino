#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>

#define MIC_PIN 34 // ADC input from MAX9814
RF24 radio(4, 5);  // CE, CSN

const byte address[6] = "00001";
uint8_t audioBuffer[32];

void setup()
{
  Serial.begin(115200);
  radio.begin();
  radio.setAutoAck(false);
  radio.setDataRate(RF24_1MBPS);
  radio.setPALevel(RF24_PA_MAX);
  radio.openWritingPipe(address);
  radio.stopListening();
}

void loop()
{
  for (int i = 0; i < 32; i++)
  {
    int sample = analogRead(MIC_PIN); // 0-4095
    sample = sample >> 4;             // convert to 8-bit (0-255)
    audioBuffer[i] = sample;
    delayMicroseconds(5); // 8 kHz sampling
  }
  radio.write(&audioBuffer, sizeof(audioBuffer));
}
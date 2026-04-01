#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>

#define DAC_PIN 25
RF24 radio(4, 5); // CE, CSN
const byte address[6] = "00001";
uint8_t audioBuffer[32];

void setup()
{
    Serial.begin(115200);
    radio.begin();
    radio.setAutoAck(false);
    radio.setDataRate(RF24_1MBPS);
    radio.setPALevel(RF24_PA_MIN);
    radio.openReadingPipe(0, address);
    radio.startListening();
}

void loop()
{
    if (radio.available())
    {
        radio.read(&audioBuffer, sizeof(audioBuffer));
        for (int i = 0; i < 32; i++)
        {
            dacWrite(DAC_PIN, audioBuffer[i]);
            delayMicroseconds(5); // match TX
        }
    }
}
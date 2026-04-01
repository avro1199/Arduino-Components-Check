#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>

RF24 radio(4, 5); // CE, CSN

const byte address[6] = "00001";

int receivedData;

void setup() {
  Serial.begin(115200);

  radio.begin();
  radio.setAutoAck(false);
  radio.setDataRate(RF24_1MBPS);
  radio.setPALevel(RF24_PA_LOW);

  radio.openReadingPipe(0, address);
  radio.startListening();

  Serial.println("Receiver Ready...");
}

void loop() {
  if (radio.available()) {
    radio.read(&receivedData, sizeof(receivedData));

    Serial.print("Received: ");
    Serial.println(receivedData);
  }
}
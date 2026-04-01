#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>

// RF24 radio(9, 10); // Nano: CE, CSN
// For ESP32 TX use: 
RF24 radio(4, 5);

const byte address[6] = "00001";

int counter = 0;

void setup() {
  Serial.begin(115200);

  radio.begin();
  radio.setAutoAck(false);
  radio.setDataRate(RF24_1MBPS); // more stable than 2MBPS
  radio.setPALevel(RF24_PA_LOW);

  radio.openWritingPipe(address);
  radio.stopListening();
}

void loop() {
  bool ok = radio.write(&counter, sizeof(counter));

  Serial.print("Sent: ");
  Serial.print(counter);
  Serial.println(ok ? " ✔" : " ❌");

  counter++;
  delay(500);
}
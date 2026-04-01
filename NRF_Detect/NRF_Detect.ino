#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>

// CE, CSN pins
RF24 radio(9, 10);

void setup() {
  Serial.begin(115200);

  if (!radio.begin()) {
    Serial.println("❌ nRF24L01 NOT detected!");
    while (1);  // stop here
  }

  Serial.println("✅ nRF24L01 detected successfully!");

  // Print some details
  radio.printDetails();
}

void loop() {
  // nothing needed
}
#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>
#include <printf.h>

// ESP32 pin configuration
#define CE_PIN 4
#define CSN_PIN 5

// SPI pins (VSPI)
#define SCK_PIN 18
#define MISO_PIN 19
#define MOSI_PIN 23

const uint64_t adress = 0xE8E8F0F0E1LL;

// Create RF24 object
RF24 radio(CE_PIN, CSN_PIN);

void setup()
{
  Serial.begin(115200);
  delay(1000);

  Serial.println("NRF24L01P test Script starting...");
  Serial.println("If you do not see a long message after this line, something is not right!");

  // Initialize SPI with ESP32 pins
  SPI.begin(SCK_PIN, MISO_PIN, MOSI_PIN, CSN_PIN);

  // Required for printDetails()
  printf_begin();

  // Start radio
  if (!radio.begin())
  {
    Serial.println("NRF24 not detected!");
    while (1);
  }

  // Settings
  radio.setPALevel(RF24_PA_HIGH);
  radio.setDataRate(RF24_250KBPS);

  //adress
  radio.openReadingPipe(1,adress);

  // Start listening
  radio.startListening();

  // Print details
  radio.printDetails();
}

void loop()
{
  // nothing here
}
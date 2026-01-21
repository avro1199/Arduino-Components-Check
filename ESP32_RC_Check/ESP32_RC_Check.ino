#include <Arduino.h>

// iBUS constants
static const uint8_t IBUS_FRAME_LEN = 32; // bytes
static const uint32_t IBUS_BAUD = 115200; // typical for iBUS

// UART2 on ESP32
HardwareSerial IBusSerial(2);

// Change pins as you like
static const int IBUS_RX_PIN = 16; // connect receiver iBUS here
static const int IBUS_TX_PIN = 17; // not used, but required by begin()

static uint8_t frame[IBUS_FRAME_LEN];
static uint8_t idx = 0;

static inline uint16_t ibusChecksum(const uint8_t *buf)
{
    uint16_t sum = 0;
    for (int i = 0; i < 30; i++)
        sum += buf[i];
    return 0xFFFF - sum;
}

// Returns true when a valid frame is parsed; channels filled with up to 14 values
static bool readIbusFrame(uint16_t ch[14])
{
    while (IBusSerial.available() > 0)
    {
        uint8_t b = (uint8_t)IBusSerial.read();

        // Frame header for iBUS servo data is typically: 0x20 0x40
        if (idx == 0)
        {
            if (b != 0x20)
                continue; // wait for start
            frame[idx++] = b;
            continue;
        }

        frame[idx++] = b;

        if (idx == 2)
        {
            if (frame[1] != 0x40)
            { // not a servo frame
                idx = 0;
                continue;
            }
        }

        if (idx >= IBUS_FRAME_LEN)
        {
            idx = 0;

            uint16_t rxChk = (uint16_t)frame[30] | ((uint16_t)frame[31] << 8);
            uint16_t calcChk = ibusChecksum(frame);
            if (rxChk != calcChk)
                return false;

            for (int i = 0; i < 14; i++)
            {
                int off = 2 + i * 2;
                ch[i] = (uint16_t)frame[off] | ((uint16_t)frame[off + 1] << 8);
            }
            return true;
        }
    }
    return false;
}

void setup()
{
    Serial.begin(115200);
    delay(200);

    IBusSerial.begin(IBUS_BAUD, SERIAL_8N1, IBUS_RX_PIN, IBUS_TX_PIN);
    Serial.println("ESP32 iBUS receiver started.");
}

void loop()
{
    static uint16_t ch[14];

    if (readIbusFrame(ch))
    {
        // Example: print first 10 channels
        Serial.print("CH: ");
        for (int i = 0; i < 10; i++)
        {
            Serial.print(ch[i]);
            if (i < 9)
                Serial.print(", ");
        }
        Serial.println();
    }

    // Do other work here; UART reception remains interrupt-driven
}
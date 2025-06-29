#include <FS.h>
#include <SD.h>
#include <driver/i2s.h>

#define SD_CS_PIN 5           // SD card chip select pin
#define I2S_BCK_PIN 26        // Bit Clock (BCK)
#define I2S_LRCK_PIN 25       // Word Select (LRCK)
#define I2S_DIN_PIN 27        // Data Input (DIN)

const char* audioFiles[] = {"/audio1.wav", "/audio2.wav", "/audio3.wav"};
const int numFiles = sizeof(audioFiles) / sizeof(audioFiles[0]);

void setup() {
  Serial.begin(115200);

  // Initialize SD card
  if (!SD.begin(SD_CS_PIN)) {
    Serial.println("SD card initialization failed!");
    while (true);  // Stop execution if SD card doesn't initialize
  }
  Serial.println("SD card initialized.");

  // Configure I2S
  i2s_config_t i2s_config = {
    .mode = (i2s_mode_t)(I2S_MODE_MASTER | I2S_MODE_TX),  // Master mode, Transmit mode
    .sample_rate = 44100,                                 // 44.1kHz sample rate
    .bits_per_sample = I2S_BITS_PER_SAMPLE_16BIT,         // 16-bit samples
    .channel_format = I2S_CHANNEL_FMT_RIGHT_LEFT,         // Stereo audio
    .communication_format = I2S_COMM_FORMAT_STAND_I2S,    // Standard I2S format
    .intr_alloc_flags = ESP_INTR_FLAG_LEVEL1,             // Interrupt priority
    .dma_buf_count = 8,                                   // DMA buffer count
    .dma_buf_len = 64,                                    // DMA buffer length
    .use_apll = false,
    .tx_desc_auto_clear = true
  };

  i2s_pin_config_t pin_config = {
    .bck_io_num = I2S_BCK_PIN,  // Bit clock pin
    .ws_io_num = I2S_LRCK_PIN,  // Word select pin
    .data_out_num = I2S_DIN_PIN, // Data output pin
    .data_in_num = I2S_PIN_NO_CHANGE  // No data input pin
  };

  // Initialize I2S driver
  if (i2s_driver_install(I2S_NUM_0, &i2s_config, 0, NULL) != ESP_OK) {
    Serial.println("Failed to install I2S driver!");
    while (true);  // Halt execution if I2S installation fails
  }

  if (i2s_set_pin(I2S_NUM_0, &pin_config) != ESP_OK) {
    Serial.println("Failed to set I2S pins!");
    while (true);  // Halt execution if I2S pin setup fails
  }

  Serial.println("I2S initialized. Starting playback...");
  
  // Play the audio files sequentially with a 10-second delay
  for (int i = 0; i < numFiles; i++) {
    playAudio(audioFiles[i]);
    delay(1000);  // 10-second delay between files
  }
}

void loop() {
  // Do nothing; playback handled in the setup
  // if(analogRead(33) > 3500){
  //   playAudio(audioFiles[0]);
  //   delay(500);
  }
}

void playAudio(const char* fileName) {
  File audioFile = SD.open(fileName, FILE_READ);
  if (!audioFile) {
    Serial.println("Failed to open audio file!");
    return;
  }

  uint8_t buffer[512];  // Buffer for reading audio data
  size_t bytesRead;

  while ((bytesRead = audioFile.read(buffer, sizeof(buffer))) > 0) {
    size_t bytesWritten;
    i2s_write(I2S_NUM_0, buffer, bytesRead, &bytesWritten, portMAX_DELAY);  // Send data to I2S
  }

  audioFile.close();
  Serial.println("Playback finished.");
}
#include "BluetoothSerial.h"

// Motor Pins
#define LMF 13  // Left Motor Forward
#define LMB 12  // Left Motor Backward
#define RMF 14  // Right Motor Forward
#define RMB 27  // Right Motor Backward
#define relay 23 // Relay Pin

// Motor Speed
int maxSpeed = 100;  // PWM duty cycle (0 - 255)

// Bluetooth
BluetoothSerial SerialBT;

void setup() {
  Serial.begin(115200);
  SerialBT.begin("ESP32_Car");  // Bluetooth device name

  // Attach PWM pins with frequency and resolution
  ledcAttach(LMF, 1000, 8);
  ledcAttach(LMB, 1000, 8);
  ledcAttach(RMF, 1000, 8);
  ledcAttach(RMB, 1000, 8);

  pinMode(relay, OUTPUT);

  stopCar();
}

void loop() {
  if (SerialBT.available()) {
    char command = SerialBT.read();
    Serial.println(command);

    if (command >= '0' && command <= '9') {
      maxSpeed = (command - 48) * 255 / 9;
      dacWrite(25, maxSpeed);
      Serial.println(maxSpeed);
    }

    switch (command) {
      case 'F':  // Forward
        moveForward();
        digitalWrite(relay, HIGH);
        break;

      case 'B':  // Backward
        moveBackward();
        digitalWrite(relay, LOW);
        break;

      case 'L':  // Left
        turnLeft();
        break;

      case 'R':  // Right
        turnRight();
        break;

      case 'S':  // Stop
        stopCar();
        break;

      default:
        stopCar();
        break;
    }
  }
}

// Movement Functions
void moveForward() {
  ledcWrite(LMF, maxSpeed);
  ledcWrite(LMB, 0);
  ledcWrite(RMF, maxSpeed);
  ledcWrite(RMB, 0);
}

void moveBackward() {
  ledcWrite(LMF, 0);
  ledcWrite(LMB, maxSpeed);
  ledcWrite(RMF, 0);
  ledcWrite(RMB, maxSpeed);
}

void turnLeft() {
  ledcWrite(LMF, 0);
  ledcWrite(LMB, maxSpeed);
  ledcWrite(RMF, maxSpeed);
  ledcWrite(RMB, 0);
}

void turnRight() {
  ledcWrite(LMF, maxSpeed);
  ledcWrite(LMB, 0);
  ledcWrite(RMF, 0);
  ledcWrite(RMB, maxSpeed);
}

void stopCar() {
  ledcWrite(LMF, 0);
  ledcWrite(LMB, 0);
  ledcWrite(RMF, 0);
  ledcWrite(RMB, 0);
}

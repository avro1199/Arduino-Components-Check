#include <PPM.h>

#define CHANNELS 8  // max ppm channels
#define PPM_PIN 2   // receiver ppm pin

#define lmf 10
#define lmb 5
#define rmf 9
#define rmb 6
#define en_l 8
#define en_r 7

#define br_thrs 1400
#define dead_zone 15

long lms, rms, top_speed;
uint32_t m1;
bool state = 0;


void setup() {
  ppm.begin(PPM_PIN, CHANNELS);
  Serial.begin(115200);

  pinMode(en_l, OUTPUT);
  pinMode(en_r, OUTPUT);
  pinMode(lmf, OUTPUT);
  pinMode(lmb, OUTPUT);
  pinMode(rmf, OUTPUT);
  pinMode(rmb, OUTPUT);

  pinMode(13, OUTPUT);

  //Disable unintentional movement
  neutral();
  Serial.print("Waiting for signal");
  while (!ppm.available()) {
    digitalWrite(13, 1);
    delay(500);
    digitalWrite(13, 0);
    delay(500);
    Serial.print(" .");
  }
  digitalWrite(13, 1);
  Serial.println("\n\t ## Connected Successfully ! ## ");
}

void loop() {
  top_speed = map(ppm.get(3), 1000, 2000, 0, 255);
  if (ppm.get(4) < br_thrs) {
    brake();
    m1 = millis();
    while (ppm.get(4) < br_thrs) {
      if(millis() - m1 > 100){
        m1 = millis();
        digitalWrite(13, state);
        state = !state;
      }
    }
    digitalWrite(13, 1);
  }

  lms = map(ppm.get(1), 1000, 2000, -(2 * top_speed), (2 * top_speed));
  rms = map(ppm.get(2), 1000, 2000, -(2 * top_speed), (2 * top_speed));

  if ((lms > dead_zone || lms < -dead_zone) && (rms > dead_zone || rms < -dead_zone)) {
    motor(constrain(lms, -255, 255), constrain(rms, -255, 255));
  } else {
    neutral();
  }
}

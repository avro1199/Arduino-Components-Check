/*
 * Controlling and looping through a CD74HC4067's channel outputs
 *
 *
 * Connect the four control pins to any unused digital or analog pins.
 * This example uses digital pins 4, 5, 6, and 7.
 *
 * Connect the common pin to any other available pin. This is the pin that will be
 * shared between the 16 channels of the CD74HC4067. The 16 channels will inherit the
 * capabilities of the common pin. For example, if it's connected to an analog pin,
 * you will be able to use analogRead on each of the 16 channels.
 *
*/

#include <CD74HC4067.h>

               // s0 s1 s2 s3
CD74HC4067 mux(16, 17, 18, 19);  // create a new CD74HC4067 object with its four control pins

void blink(uint8_t pin, int n_times, int del){
  for(int i = 0; i < n_times; i++){
    digitalWrite(pin, 1);
    delay(del);
    digitalWrite(pin, 0);
    delay(del);
  }
}

void setup()
{
  pinMode(4, OUTPUT);
}

void loop()
{
  // digitalWrite(4, 0);
  mux.channel(5);
  blink(4, 4, 100);

  // digitalWrite(4, 0);
  mux.channel(6);
  blink(4, 3, 200);

  // digitalWrite(4, 0);
  mux.channel(7);
  blink(4, 2, 300);
}

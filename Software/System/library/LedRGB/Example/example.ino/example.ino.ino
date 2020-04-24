#include "LedRGB.h"

#define red_pin 8
#define green_pin 9
#define blue_pin 10

LedRGB led(green_pin,blue_pin,red_pin);


void setup() {
  LedRGB led(green_pin,blue_pin,red_pin);

}

void loop() {
  led.turnOn('g'); //Turns on green colour
//  led.turnOn('b'); //Turns on blue colour
//  led.turnOn('r'); //Turns on red colour
//  led.turnOn('a'); //Turns off led

}

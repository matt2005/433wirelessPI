#include <Piwi.h>
// Example with Leds
// Plugged LEDS on Pin 6/8/9/10
// Created By Sarrailh Remi
// Public Domain

// To test it run ./ardwl_cs.sh 6 1 on the Raspberry PI


// Declare which PIN receive DATA
Piwi piwi(2);

void setup()
{
// Output on Leds
  pinMode(6,OUTPUT);
  pinMode(8,OUTPUT);
  pinMode(9,OUTPUT);
  pinMode(10,OUTPUT);
}

void loop()
{
// Listen for Rpi
  piwi.listen();
}
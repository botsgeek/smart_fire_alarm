#include <Arduino.h>
#include "fan-driver.h"
 int fan_pin = 5;


void setup()
{
  pinMode(fan_pin, OUTPUT);
  activate_fan();
  validate_before_activating();

  // put your setup code here, to run once:
  //
}

void loop()
{
  // put your main code here, to run repeatedly:
}

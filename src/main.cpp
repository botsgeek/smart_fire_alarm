#include <Arduino.h>
#include "fan-driver.h"
 



void setup()
{
  Serial.begin(9600);
  // put your setup code here, to run once:
  // fan_t* config = fan_create(NULL);
  // while( config == NULL);
  fan_config_t fan_driver;
  fan_driver.fan_pin_number = A5;

   fan_t* my_fan = fan_create(&fan_driver);
   if(my_fan != NULL){
     fan_init(my_fan);
    set_fanspeed(my_fan);
    deinit(my_fan);

   }

  
  // Serial.println("started");
  
}

void loop()
{
  // put your main code here, to run repeatedly:
}

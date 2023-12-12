#include <Arduino.h>
#include "fan-driver.h"
#include <stdbool.h>

int fanspeed ;

void activate_fan(){
    int fan_pin = 5;
    fan_state fan_operation = INITIALIZE_FAN;
    // fan_operation = FAN_SPEED;
    // fan_operation = DEACTIVATE_FAN;

    
    switch (fan_operation)
    {
    case INITIALIZE_FAN:
  
    
        for ( fanspeed = 0; fanspeed <= 125; fanspeed++)
        {
            analogWrite(fan_pin, fanspeed);
        }
        // //delay(10);
        break;
    case FAN_SPEED:
    for (fanspeed = 125; fanspeed <= 255; fanspeed++)
    {
        analogWrite(fan_pin, fanspeed);
    }
    
    delay(10);
    break;
    case DEACTIVATE_FAN:
    for ( fanspeed= 255;  fanspeed<= 0; fanspeed--)
    {
         analogWrite(fan_pin, fanspeed);
    }
    delay(10);
    
   
    break; 
    default:
        break;
    }
    


}


void validate_before_activating(){
    int fan_pin =5;
    bool activation ;

    if (fanspeed > 255)
    {
        activation = false;
        // printf("Warning fan can't start.\n Error occure when receiving signal.");
    }
    else
    {
        activation = true;
    }

    if (activation == false){
        fanspeed = 0;
        analogWrite(fan_pin, fanspeed);
        //Serial.println("fan is active");
    }
    else
    {
        for ( fanspeed = 125; fanspeed <= 255; fanspeed++)
        {
            analogWrite(fan_pin, fanspeed);
        }
        delay(10);
    }
    

    
    
}
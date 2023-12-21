#include <Arduino.h>
#include "fan-driver.h"
#include "common_headers.h"
#include <stdbool.h>

#define FAN_PIN_NUMBER A5


struct fan_t
{
    uint8_t fan_pin_number;
    bool activated;
    

};

fan_t* fan_create(const fan_config_t* config){
    if(config == NULL){
        // Serial.println("cannot craete fan object from null config");
        return NULL;
    }
    fan_t* fan_obj= (fan_t*)malloc(sizeof(fan_t));
    fan_obj->fan_pin_number = config->fan_pin_number;
    fan_obj->activated = false;
    //  Serial.println("/ fan_create is sucessful ");   
    return fan_obj; 
    
    
}
error_type_t fan_init(fan_t* fan_object){
    if(fan_object == NULL){
         return NULL_PARAMETER;
    }
    if (fan_object->fan_pin_number != FAN_PIN_NUMBER)
    {
        // Serial.println("cannot  return parameter from null config");
        return INVALID_PIN_NUMBER;
    }
    pinMode(fan_object->fan_pin_number,OUTPUT);
    fan_object->activated = true;
    //   Serial.println("/ fan_init is sucessful ");  
    return OK; 
   
}
error_type_t set_fanspeed(fan_t* fan_object){
    if(fan_object == NULL)
    return NULL_PARAMETER;
    if (fan_object->activated != true)
    {
        //  Serial.println("/ fan_ speed is sucessful ");
        return INVALID_STATE;
    }
      uint8_t fanspeed = 255;
    analogWrite(fan_object->fan_pin_number, fanspeed);
    
    return OK;
    
}
error_type_t deinit(fan_t* fan_object){
    if(fan_object){
        fan_object->activated = false;
       
    }
    free(fan_object);
    // Serial.println("/ fan_ deinit is sucessful ");
    return OK;
}



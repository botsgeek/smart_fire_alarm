#include <Arduino.h>
#include "fan-driver.h"
#include "common_headers.h"
#include <stdbool.h>

#define FAN_PIN_NUMBER A5

struct fan_t
{
    
    fan_mode_t set_fanspeed;
    bool activate;
    

};

fan_t* fan_driver_create(const fan_state_t* fan_operation){
    if(fan_operation == NULL)
    return NULL;
    fan_t* new_fan_mode = (fan_t*)malloc(sizeof(fan_t));
    new_fan_mode->set_fanspeed = fan_operation->set_fanspeed;
    new_fan_mode->activate = true;      
}

error_type_t fan_init(fan_t* fan_object){
    if (fan_object == NULL)
    return NULL_PARAMETER;

    if(fan_object->set_fanspeed > 125){
    return INVALID_STATE;
    }
    fan_object->activate = false;   
}

error_type_t set_fanspeed(fan_t* fan_object){
    if(fan_object == NULL)
    return NULL_PARAMETER;

    if (fan_object->set_fanspeed > 255)
    {
        return INVALID_STATE;
    }
    fan_object->activate =false;
}

// error_type_t deinit(fan_t* fan_object){

// }
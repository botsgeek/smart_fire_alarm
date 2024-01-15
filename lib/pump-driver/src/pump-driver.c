#include <Arduino.h>
#include "common_headers.h"
#include "pump-driver.h"
#include <stdbool.h>

#define MAX_PUMP_PIN_NUMBER 7
#define MIN_PUMP_PIN_NUMBER 2


 struct pump_t
{
    uint8_t pump_pin_number;
    bool initalized;

};
//

pump_t* pump_create(const pump_config_t* config){
    if (config == NULL)
    {
        return NULL;  
    }
    Serial.println("pump config not null");
    pump_t* pump_object = (pump_t*)malloc(sizeof(pump_t));
    pump_object->pump_pin_number = config->pump_pin_number;
    pump_object->initalized = false;
    //  Serial.println("was not able to create pump config");

    return pump_object;
    
}
//
error_type_t pump_init(pump_t* pump_object){
    if (pump_object == NULL)
    {
        return NULL_PARAMETER;
    }
    if (pump_object->pump_pin_number > MAX_PUMP_PIN_NUMBER || pump_object->pump_pin_number < MIN_PUMP_PIN_NUMBER )
    {
        return INVALID_PIN_NUMBER;
    }
    pinMode(pump_object->pump_pin_number, OUTPUT);
    pump_object->initalized = true;
     Serial.println("pin validated");
    return OK;
}
//
error_type_t pump_on(pump_t* pump_object){
    if(pump_object == NULL){
        
        return NULL_PARAMETER;
    }

    if (pump_object->initalized != true)
    {
        Serial.println("pump validated");
        return INVALID_STATE;
    }
    digitalWrite(pump_object->pump_pin_number, HIGH);
    // Serial.println("pump driver is active");
    

     Serial.println("pump driver is active");

    return OK;
}
//
error_type_t pump_off(pump_t* pump_object){
    if(pump_object == NULL){
        
        return NULL_PARAMETER;
    }

    if (pump_object->initalized != true)
    {
        Serial.println("pump validated");
        return INVALID_STATE;
    }
    digitalWrite(pump_object->pump_pin_number, LOW);
    // Serial.println("pump driver is active");


     Serial.println("pump driver is active");

    return OK;
}
//
error_type_t pump_deinit(pump_t* pump_object){
    if (pump_object)
    {
        pump_object->initalized = false;
        free(pump_object);
    }
     
        Serial.println("pump define is sucessful");
    return OK;
}


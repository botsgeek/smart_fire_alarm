#include <Arduino.h>
#include "common_headers.h"
#include "pump-driver.h"
#include <stdbool.h>

# define PUMP_PIN_NUMBER D7

typedef struct 
{
    uint8_t pump_pin_number;
    bool initalized;

}pump_t;

pump_t* pump_create(const pump_config_t* config){
    if (config == NULL)
    {
        return NULL;
    }
    pump_t* pump_object = (pump_t*)malloc(sizeof(pump_t));
    pump_object->pump_pin_number = config->pump_pin_number;
    pump_object->initalized = false;
    return pump_object;
    
}


// buzzer.c
#include <Arduino.h>
#include "buzzer.h"
#include "common_headers.h"
#include <stdbool.h>

#define MAX_BUZZER_PIN 13
#define MIN_BUZZER_PIN 2



//#define BUZZER_PIN 8 // Change this to your actual pin
 struct buzzer_t{
    uint8_t buzzer_pin;
    bool activated;
    };

// buzzer_t* buzzer_create(const buzzer_config_t* config){
//     if(config == NULL) return NULL;
//     buzzer_t* buzzer_obj = (buzzer_t*) malloc(sizeof(buzzer_t));
//     buzzer_obj->buzzer_pin = config-> buzzer_pin;
//     buzzer_obj->activated = false;
//     return buzzer_obj;
// }

    buzzer_t* buzzer_create(const uint8_t buzzer_pin){
    // if(buzzer_pin == NULL) return NULL;
    buzzer_t* buzzer_obj = (buzzer_t*) malloc(sizeof(buzzer_t));
    buzzer_obj->buzzer_pin = buzzer_pin;
    buzzer_obj->activated = false;
    return buzzer_obj;
}
  
error_type_t buzzer_init(buzzer_t* buzzer_object)
{
    if(buzzer_object == NULL)return NULL_PARAMETER;
    if(buzzer_object->buzzer_pin <  MIN_BUZZER_PIN || buzzer_object->buzzer_pin > MAX_BUZZER_PIN){
            return INVALID_PIN_NUMBER;
    }
    pinMode (buzzer_object->buzzer_pin, OUTPUT);
    buzzer_object->activated = true;
    return OK; 
}

error_type_t buzzer_deinit(buzzer_t* buzzer_object) {
    if(buzzer_object){
        buzzer_object->activated = false;
        free(buzzer_object);
    }
    return OK;
}

error_type_t buzzer_start(buzzer_t* buzzer_object, unsigned int pwm_duty_cycle) {
    if(buzzer_object == NULL){
        return NULL_PARAMETER;
    }
    if(buzzer_object->buzzer_pin <  MIN_BUZZER_PIN || buzzer_object->buzzer_pin > MAX_BUZZER_PIN){
            return INVALID_PIN_NUMBER;
    }
    if(!buzzer_object-> activated){
        return INVALID_STATE;

    }
    
        analogWrite(buzzer_object->buzzer_pin,  pwm_duty_cycle);
        return OK;
  
}

error_type_t buzzer_stop(buzzer_t* buzzer_object) {
    if(buzzer_object == NULL){
        return NULL_PARAMETER;
    }
    if(buzzer_object->buzzer_pin <  MIN_BUZZER_PIN || buzzer_object->buzzer_pin > MAX_BUZZER_PIN){
            return INVALID_PIN_NUMBER;
    }
    if(!buzzer_object-> activated){
        return INVALID_STATE;

    }
    
        analogWrite(buzzer_object->buzzer_pin, 0);
        return OK;
}
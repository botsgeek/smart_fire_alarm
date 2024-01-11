// buzzer.c
#include <Arduino.h>
#include "buzzer.h"
#include "common_headers.h"
#include <stdbool.h>

#define MAX_BUZZER_PIN 13
#define MIN_BUZZER_PIN 2
static const uint8_t pwm_duty_cycle = 255;

 struct buzzer_t{
    uint8_t buzzer_pin;
    bool activated;
    };

    buzzer_t* buzzer_create(const uint8_t buzzer_pin){
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

error_type_t buzzer_start(buzzer_t* buzzer_object, uint8_t pwm_duty_cycle) {
    if(buzzer_object == NULL){
        return NULL_PARAMETER;
    }
  
    if(!buzzer_object-> activated){
        return INVALID_STATE;

    }
    
        analogWrite(buzzer_object->buzzer_pin, pwm_duty_cycle);
        return OK;
  
}

error_type_t buzzer_stop(buzzer_t* buzzer_object) {
    if(buzzer_object == NULL){
        return NULL_PARAMETER;
    }
    
    if(!buzzer_object-> activated){
        return INVALID_STATE;

    }
    
        analogWrite(buzzer_object->buzzer_pin, 0);
        return OK;
}


error_type_t buzzer_tone(buzzer_t* buzzer_object, uint32_t tone_duration, uint32_t total_time) {
    if (buzzer_object == NULL) {
        return NULL_PARAMETER;
    }
    if (!buzzer_object->activated) {
        return INVALID_STATE;
    }

    uint32_t start_time = millis();
    uint32_t current_time;
    bool is_sound_active = false;
    current_time = millis();
    while (( millis() - start_time) < total_time) {
        if (millis() - current_time >= tone_duration){
            is_sound_active = !is_sound_active;
            analogWrite(buzzer_object->buzzer_pin, is_sound_active ? pwm_duty_cycle : 0);
            current_time = millis();
        }
      
    }

    analogWrite(buzzer_object->buzzer_pin, 0);

    return OK;
}

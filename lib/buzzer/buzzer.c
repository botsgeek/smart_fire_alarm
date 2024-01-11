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
    if(buzzer_object->buzzer_pin <  MIN_BUZZER_PIN || buzzer_object->buzzer_pin > MAX_BUZZER_PIN){
            return INVALID_PIN_NUMBER;
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
    if(buzzer_object->buzzer_pin <  MIN_BUZZER_PIN || buzzer_object->buzzer_pin > MAX_BUZZER_PIN){
            return INVALID_PIN_NUMBER;
    }
    if(!buzzer_object-> activated){
        return INVALID_STATE;

    }
    
        analogWrite(buzzer_object->buzzer_pin, 0);
        return OK;
}


error_type_t buzzer_tone(buzzer_t* buzzer_object, unsigned int tone_duration, unsigned long long total_time) {
    if (buzzer_object == NULL) {
        return NULL_PARAMETER;
    }
    if (buzzer_object->buzzer_pin < MIN_BUZZER_PIN || buzzer_object->buzzer_pin > MAX_BUZZER_PIN) {
        return INVALID_PIN_NUMBER;
    }
    if (!buzzer_object->activated) {
        return INVALID_STATE;
    }

    unsigned long start_time = millis();
    unsigned long current_time;
    bool is_sound_active = false;
    unsigned long sound_start_time = start_time;
    unsigned long silence_start_time = start_time;

    while ((current_time = millis()) - start_time < total_time) {
        if ((is_sound_active ) && (current_time - sound_start_time >= tone_duration)) {
            is_sound_active = false;
            silence_start_time = current_time;
        }

        if ((!is_sound_active) && (current_time - silence_start_time >= tone_duration)) {
            is_sound_active = true;
            sound_start_time = current_time;
        }

        analogWrite(buzzer_object->buzzer_pin, is_sound_active ? pwm_duty_cycle : 0);
    }

    analogWrite(buzzer_object->buzzer_pin, 0);

    return OK;
}

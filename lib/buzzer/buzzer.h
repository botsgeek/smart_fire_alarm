#include <stdint.h>
#ifndef _BUZZER_H_
#define _BUZZER_H_

#ifdef __cplusplus
extern "C" 
{
#endif
#include "common_headers.h"

    typedef struct buzzer_t buzzer_t;


    error_type_t buzzer_init(buzzer_t* buzzer_object);
    error_type_t buzzer_deinit(buzzer_t* buzzer_object);
    error_type_t buzzer_start(buzzer_t* buzzer_object, uint8_t pwm_duty_cycle);
    error_type_t buzzer_stop(buzzer_t* buzzer_object);
    error_type_t buzzer_tone(buzzer_t* buzzer_object, uint32_t tone_duration, uint32_t total_time);
    buzzer_t* buzzer_create(const uint8_t buzzer_pin);
#ifdef __cplusplus
}
#endif

#endif

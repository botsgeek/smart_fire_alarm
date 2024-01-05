#include <stdint.h>
#ifndef _BUZZER_H_
#define _BUZZER_H_

#ifdef __cplusplus
extern "C" 
{
#endif
#include "common_headers.h"

    typedef struct buzzer_t buzzer_t;

    typedef struct {
        uint8_t buzzer_pin;
    } buzzer_config_t;

    error_type_t buzzer_init(buzzer_t* buzzer_object);
    error_type_t buzzer_deinit(buzzer_t* buzzer_object);
    error_type_t buzzer_start(buzzer_t* buzzer_object, unsigned int pwm_duty_cycle);
    error_type_t buzzer_stop(buzzer_t* buzzer_object);

   buzzer_t* buzzer_create(const buzzer_config_t* config);

#ifdef __cplusplus
}
#endif

#endif

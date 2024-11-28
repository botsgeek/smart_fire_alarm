#ifndef _STATE_H_
#define _STATE_H_
#include <stdint.h>
#ifdef __cplusplus
extern "C" {
#endif
#include <common_headers.h>
#include <buzzer.h>
#include <fan-driver.h>
#include <pump-driver.h>
#include <lm75-manager.h>
#include <mq2-manager.h>

typedef struct state_machine_t state_machine_t;


typedef enum{
    STATE_MACHINE_NORMAL_STATE,
    STATE_MACHINE_SMOKE_NO_HEAT,
    STATE_MACHINE_HEAT_NO_SMOKE,
    STATE_MACHINE_HEAT_AND_SMOKE

}state_t;
typedef void(*state_machine_handler_t)(state_t);


typedef struct{
    // lm75_t* lm75_state;
    // mq2_t* mq2_state;
    // buzzer_t* buzzer_object;
    // fan_t* fan_object;
    // pump_t* pump_object;
    state_t current_state;
    state_machine_handler_t handler;
    
    
}state_config_t;





state_machine_t* state_machine_create(const state_config_t* state_config);
error_type_t state_machine_init(state_machine_t* state_obj);
error_type_t state_machine_deinit(state_machine_t* state_obj);
error_type_t state_machine_destroy(state_machine_t** state_obj);
error_type_t state_machine_transition(state_machine_t* state_obj, const bool heat, const bool smoke);







#ifdef __cplusplus
}
#endif

#endif
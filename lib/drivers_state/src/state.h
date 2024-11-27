#ifndef _LM75_MANAGER_H_
#define _LM75_MANAAGER_H_
#include <stdint.h>
#ifdef __cplusplus
extern "C" {
#endif
#include <common_headers.h>
#include <lm75-manager.h>
#include <mq2-manager.h>

typedef struct state_t state_t;

typedef enum{
    NORMAL_STATE,
    DETECT_SMOKE,
    DETECT_HEATS,
    IDLE_STATE,
    ACTIVATE_DRIVERS,

}state_trans_t;


typedef struct{
    lm75_t* lm75_state;
    mq2_t* mq2_state;
    state_trans_t current_state;
    
}state_config_t;





state_t* state_create(const state_config_t* config);
error_type_t state_init(state_t* state_obj);
error_type_t state_deinit(state_t* state_obj);
error_type_t state_destroy(state_t** state_obj);
error_type_t transition(state_t* state_obj, bool heat, bool smoke);






#ifdef __cplusplus
}
#endif

#endif
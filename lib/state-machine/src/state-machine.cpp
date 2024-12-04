#include <Arduino.h>
#include <state-machine.h>
#include <buzzer.h>
#include <fan-driver.h>
#include <pump-driver.h>
#include <lm75-manager.h>
#include <mq2-manager.h>

struct state_machine_t
{
    state_t current_state;
    state_machine_handler_t handler;
    bool initialize;
};

state_machine_t* state_machine_create(const state_config_t* state_config){
    if (state_config == NULL)return NULL;

    state_machine_t* state_obj = (state_machine_t*)malloc(sizeof(state_t));
    state_obj->current_state = state_config->current_state;
    state_obj->handler = state_config->handler;
    state_obj->initialize = false;
    return state_obj;   
}

error_type_t state_machine_init(state_machine_t* state_obj){
    if(state_obj == NULL)return NULL_PARAMETER;
    state_obj->initialize = true;
    return OK;
}

error_type_t state_machine_deinit(state_machine_t* state_obj){
    if (state_obj == NULL)
    {
        return NULL_PARAMETER;
    }
    if(state_obj->initialize == false)return INVALID_STATE;
    state_obj->initialize = false;
    return OK;
    
}

error_type_t state_machine_destroy(state_machine_t** state_obj){
    if(state_obj == NULL)return NULL_PARAMETER;
    *state_obj = NULL;
    free(*state_obj);
    return OK;
}

static void handle_transition(state_machine_t* state_obj, const bool heat, const bool smoke){
    if(!heat && !smoke)return;
    if(heat && !smoke){
        state_obj->current_state = STATE_MACHINE_HEAT_NO_SMOKE;
        return;
    }
    if (!heat && smoke)
    {
        state_obj->current_state = STATE_MACHINE_SMOKE_NO_HEAT;
        return;
    }
    if (heat && smoke)
    {
        state_obj->current_state = STATE_MACHINE_HEAT_AND_SMOKE;
        return;
    }
     
}

error_type_t state_machine_transition(state_machine_t* state_obj, const bool heat, const bool smoke){
    //change the bool value to const
    if(state_obj == NULL)return NULL_PARAMETER;
    if(!state_obj->initialize)return INVALID_STATE;

    //   state_t temp = state_obj->current_state;
    handle_transition(state_obj,heat,smoke);
    //   if (temp != state_obj->current_state)
    //   {
        state_obj->handler(state_obj->current_state);
      //}
      
    return OK;
     
}

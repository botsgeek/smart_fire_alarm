#include <Arduino.h>
#include <state.h>
#include <buzzer.h>
#include <fan-driver.h>
#include <pump-driver.h>
#include <lm75-manager.h>
#include <mq2-manager.h>

struct state_t
{
    lm75_t* lm75_state;
    mq2_t* mq2_state;
    buzzer_t* buzzer_object;
    fan_t* fan_object;
    pump_t* pump_object;
    state_trans_t current_state;
    bool initialize;
};

state_t* state_create(const state_config_t* config){
    if (config == NULL)return NULL;

    state_t* state_obj = (state_t*)malloc(sizeof(state_t));
    state_obj->lm75_state = config->lm75_state;
    state_obj->mq2_state = config->mq2_state;
    state_obj->current_state = config->current_state;
    state_obj->initialize = false;
    return state_obj;   
}

error_type_t state_init(state_t* state_obj){
    if(state_obj == NULL)return NULL_PARAMETER;
    state_obj->initialize = true;
    return OK;
}

error_type_t state_deinit(state_t* state_obj){
    if (state_obj == NULL)
    {
        return NULL_PARAMETER;
    }
    if(state_obj->initialize == false)return INVALID_STATE;
    state_obj->initialize = false;
    return OK;
    
}

error_type_t state_destroy(state_t** state_obj){
    if(state_obj == NULL)return NULL_PARAMETER;
    *state_obj = NULL;
    free(*state_obj);
    return OK;
}

error_type_t transition(state_t* state_obj, bool heat, bool smoke){
    if(state_obj == NULL)return NULL_PARAMETER;
    if(!state_obj->initialize)return INVALID_STATE;
      bool state;
      uint8_t pwm_cycle;
      uint8_t fan_speed;

    
     switch (state_obj->current_state)
    {
    case IDLE_STATE:
        if (!heat|| !smoke)
        {
            heat = false;
            smoke = false;
            buzzer_stop(state_obj->buzzer_object);
            pump_off(state_obj->pump_object);
            state_obj->current_state = NORMAL_STATE;
            
        }
        else if (heat && smoke)
        {
            heat = true;
            smoke = true;
            lm75_above_threshold(state_obj->lm75_state, &state);
            mq2_above_threshold(state_obj->mq2_state, &state);
            buzzer_start(state_obj->buzzer_object, &pwm_cycle);
            pump_on(state_obj->pump_object);
            set_fanspeed(state_obj->fan_object, &fan_speed);
            state_obj->current_state = ACTIVATE_DRIVERS;
        }
        
        break;
    case DETECT_SMOKE:
        if (!heat && smoke)
        {
            heat = false;
            smoke = true;
            lm75_above_threshold(state_obj->lm75_state, &state);
            mq2_above_threshold(state_obj->mq2_state, &state);
            buzzer_start(state_obj->buzzer_object, &pwm_cycle);
            set_fanspeed(state_obj->fan_object, &fan_speed);
            state_obj->current_state = ACTIVATE_DRIVERS;
        }
        else if(!heat && !smoke){
            heat = false;
            smoke = false;
            buzzer_stop(state_obj->buzzer_object);
            pump_off(state_obj->pump_object);
            state_obj->current_state = NORMAL_STATE;

        }
        break;
    case DETECT_HEATS:
        if (heat && !smoke)
        {
            heat = true;
            smoke = false;
            buzzer_start(state_obj->buzzer_object, &pwm_cycle);
            pump_on(state_obj->pump_object);
            set_fanspeed(state_obj->fan_object, &fan_speed);
            state_obj->current_state = ACTIVATE_DRIVERS; 
        }
        else if (!heat && !smoke){
            heat = false;
            smoke = false;
            buzzer_stop(state_obj->buzzer_object);
            pump_off(state_obj->pump_object);
            state_obj->current_state = NORMAL_STATE;
        }
        break;
    
    default:
        break;
    }
    return OK;
     
}


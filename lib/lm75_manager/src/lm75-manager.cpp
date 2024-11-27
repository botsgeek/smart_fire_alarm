#include <Arduino.h>
#include "lm75-manager.h"
#include <lm75.h>
#include <stdbool.h>
#include <common_headers.h>

struct lm75_t
{
    float threshold;
    lm75_t* lm75_obj;
    bool initialize;
};

lm75_t* create_lm75(const my_lm75_config_t* config_state){
    if (config_state == NULL)
    {
        return NULL;
    }

    lm75_t* lm75_state = (lm75_t*)malloc(sizeof(lm75_t));
    lm75_state->threshold = config_state->lm75_threshold;
    lm75_state->lm75_obj = config_state->lm75_obj;
    lm75_state->initialize = false;
    return  lm75_state;  
    
}

error_type_t init_lm75(lm75_t* lm75_state){
    if ( lm75_state == NULL)return NULL_PARAMETER;
     lm75_state->initialize = true;
    lm75_read( lm75_state->lm75_obj);
    return OK;    
}

error_type_t lm75_above_threshold(lm75_t* lm75_state, bool* state){
    if (lm75_state == NULL)return NULL_PARAMETER;
    if(!lm75_state->initialize)return INVALID_STATE;
    float currentTemp = lm75_read(lm75_state->lm75_obj);
    if (currentTemp > lm75_state->threshold)
    {
        *state = true;
    }else
    {
        *state = false;
    }
    
    return OK;   
}

error_type_t deinit_lm75(lm75_t* lm75_state){
    if(lm75_state== NULL)return NULL_PARAMETER;
    if(!lm75_state->initialize)return INVALID_STATE;
    lm75_state->initialize = false;
    return OK;
}

error_type_t destroy_lm75(lm75_t** lm75_state){
    if(lm75_state == NULL)return NULL_PARAMETER;
    *lm75_state = NULL;
    free(*lm75_state);
    return OK;
}



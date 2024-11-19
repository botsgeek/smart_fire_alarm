#include <Arduino.h>
#include "lm75-man.h"
#include <lm75.h>
#include <stdbool.h>
#include <common_headers.h>

struct lm75_manage_t
{
    float threshold;
    lm75_t* lm75_obj;
    bool initalize;
};

lm75_manage_t* lm75_manage_create(const lm75_manager_t* manage_state){
    if (manage_state == NULL)
    {
        return NULL;
    }

    lm75_manage_t* manage_lm75_object = (lm75_manage_t*)malloc(sizeof(lm75_manage_t));
    manage_lm75_object->threshold = manage_state->lm75_threshold;
    manage_lm75_object->lm75_obj = manage_state->lm75_obj;
    manage_lm75_object->initalize = false;
    return manage_lm75_object;  
    
}

error_type_t lm75_manage_init(lm75_manage_t* manage_lm75_object){
    if (manage_lm75_object == NULL)return NULL_PARAMETER;
    
}



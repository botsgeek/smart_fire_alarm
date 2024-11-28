#include <Arduino.h>
#include "lm75-manager.h"
#include <lm75.h>
#include <stdbool.h>
#include <common_headers.h>

struct lm75_manager_t
{
    float threshold;
    lm75_t* lm75_obj;
    bool initialize;
};

lm75_manager_t* lm75_manager_create(const lm75_manager_config_t* manager_config){
    if (manager_config == NULL)
    {
        return NULL;
    }

    lm75_manager_t* lm75_manager = (lm75_manager_t*)malloc(sizeof(lm75_manager_t));
    lm75_manager->threshold = manager_config->lm75_threshold;
    lm75_manager->lm75_obj = manager_config->lm75_obj;
    lm75_manager->initialize = false;
    return  lm75_manager;  
    
}

error_type_t lm75_manager_init(lm75_manager_t* lm75_manager){
    if ( lm75_manager == NULL)return NULL_PARAMETER;
     lm75_manager->initialize = true;
    lm75_read( lm75_manager->lm75_obj);
    return OK;    
}

error_type_t lm75_manager_above_threshold(lm75_manager_t* lm75_manager, bool* state){
    if (lm75_manager == NULL)return NULL_PARAMETER;
    if(!lm75_manager->initialize)return INVALID_STATE;
    float currentTemp = lm75_read(lm75_manager->lm75_obj);
    if (currentTemp > lm75_manager->threshold)
    {
        *state = true;
    }else
    {
        *state = false;
    }
    
    return OK;   
}

error_type_t lm75_manager_deinit(lm75_manager_t* lm75_manager){
    if(lm75_manager == NULL)return NULL_PARAMETER;
    if(!lm75_manager->initialize)return INVALID_STATE;
    lm75_manager->initialize = false;
    return OK;
}

error_type_t lm75_manager_destroy(lm75_manager_t** lm75_manager){
    if(lm75_manager == NULL)return NULL_PARAMETER;
    *lm75_manager = NULL;
    free(*lm75_manager);
    return OK;
}



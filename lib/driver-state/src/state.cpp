#include <Arduino.h>
#include <state.h>
#include <common_headers.h>
#include <lm75.h>
#include <mq2.h>
#include <buzzer.h>

class state_t
{
public:
bool normal;
bool heat;
bool smoke;
bool initalize;   
};

state_t* create_state(const state_cofig_t* config){
    if (config == NULL) return NULL;

    state_t* state_object = (state_t*)malloc(sizeof(state_t));
    state_object->heat = false;
    state_object->smoke = false;
    state_object->normal = false;
    state_object->initalize = false;
    return state_object;
}

error_type_t state_init(state_t* state_object){
    if (state_object == NULL)return NULL_PARAMETER;
    if (state_object->initalize != true)
    {
        return INVALID_STATE;
    }
    state_object->initalize = true;
    state_object->normal = true; 

    return OK;   
}

error_type_t state_deinit(state_t* state_object){
    
}





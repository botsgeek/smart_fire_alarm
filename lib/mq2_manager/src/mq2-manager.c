#include <Arduino.h>
#include <mq2-manager.h>
#include <mq2.h>
#include <common_headers.h>
#include <stdbool.h>

struct mq2_t
{
    mq2_t* mq2_obj;
    float mq2_threshold;
    bool initialize;
};

mq2_t* create(const mq2_config_t* config_state){
    if(config_state == NULL)return NULL;

    mq2_t* mq2_state = (mq2_t*)malloc(sizeof(mq2_t));
    mq2_state->mq2_obj = config_state->mq2_object;
    mq2_state->mq2_threshold = config_state->mq2_threshold;
    mq2_state->initialize = false;
    return mq2_state;
}

error_type_t lib_init(mq2_t* mq2_state){
    if(mq2_state == NULL)return NULL_PARAMETER;
    if(mq2_state->initialize!= true)return INVALID_STATE;
    mq2_state->initialize = true;
    uint16_t value;
    mq2_analog_read(mq2_state->mq2_obj, &value);
    return OK;
}

error_type_t get_above_threshold(mq2_t* mq2_state, bool* state){
    if(mq2_state == NULL)return NULL_PARAMETER;
     uint16_t value;
    float mq2Readings = mq2_analog_read(mq2_state->mq2_obj, &value);
    if (mq2Readings > mq2_state->mq2_threshold)
    {
        *state = true;
    }else
    {
        *state = false;
    }
    
    return OK;
}

error_type_t lib_deinit(mq2_t* mq2_state){
    if(mq2_state == NULL)return NULL_PARAMETER;
    if(mq2_state->initialize == false) return INVALID_STATE;
    mq2_state->initialize = false;
    return OK;
}

error_type_t lib_destory(mq2_t** mq2_state){
    if(mq2_state == NULL)return NULL_PARAMETER;
    *mq2_state= NULL;
    free(*mq2_state);
    return OK;

}


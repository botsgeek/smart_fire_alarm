#include <Arduino.h>
#include <mq2-manager.h>
#include <mq2.h>
#include <common_headers.h>
#include <stdbool.h>

struct mq2_manager_t
{
    mq2_t* mq2_obj;
    float mq2_threshold;
    bool initialize;
};

mq2_manager_t* mq2_manager_create(const mq2_manager_config_t* manager_config){
    if(manager_config == NULL)return NULL;

    mq2_manager_t* mq2_manager = (mq2_manager_t*)malloc(sizeof(mq2_manager_t));
    mq2_manager->mq2_obj = manager_config->mq2_object;
    mq2_manager->mq2_threshold = manager_config->mq2_threshold;
    mq2_manager->initialize = false;
    return mq2_manager;
}

error_type_t mq2_manager_init(mq2_manager_t* mq2_manager){
    if(mq2_manager == NULL)return NULL_PARAMETER;
    mq2_manager->initialize = true;
    uint16_t value;
    mq2_analog_read(mq2_manager->mq2_obj, &value);
    return OK;
}

error_type_t mq2_manager_above_threshold(mq2_manager_t* mq2_manager, bool* state){
    if(mq2_manager == NULL)return NULL_PARAMETER;
    if(!mq2_manager->initialize)return INVALID_STATE;
     uint16_t value;
    float mq2_read = mq2_analog_read(mq2_manager->mq2_obj, &value);
        if (mq2_read > mq2_manager->mq2_threshold)
    {
        *state = true;
    }else
    {
        *state = false;
    }
    
    return OK;
}

error_type_t mq2_manager_deinit(mq2_manager_t* mq2_manager){
    if(mq2_manager == NULL)return NULL_PARAMETER;
    if(mq2_manager->initialize == false) return INVALID_STATE;
    mq2_manager->initialize = false;
    return OK;
}

error_type_t mq2_manager_destory(mq2_manager_t** mq2_manager){
    if(mq2_manager == NULL)return NULL_PARAMETER;
    *mq2_manager= NULL;
    free(*mq2_manager);
    return OK;

}


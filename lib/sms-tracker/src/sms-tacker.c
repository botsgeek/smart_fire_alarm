#include <Arduino.h>
#include <sms-tracker.h>
#include <sim800.h>
#include <stdbool.h>
#include <common_headers.h>

#define SMS_TIME 30000
#define RESEND_TIME 20

 struct sms_tracker_t {
    int sms_time_counter;
    int follow_up_counter;
    sim800_t* sim800_obj;
    bool has_sent_sms;
    bool initalize;
};

sms_tracker_t* sms_tracker_create(const sms_tracker_config_t* sms_config){
    if (sms_config == NULL)return NULL;

    sms_tracker_t*sms_obj = (sms_tracker_t*)malloc(sizeof(sms_tracker_t));
    sms_obj->sms_time_counter = sms_config->sms_time_counter;
    sms_obj->follow_up_counter = sms_config->follow_up_counter;
    sms_obj->sim800_obj = sms_config->sim800_obj;
    sms_obj->has_sent_sms = false;
    sms_obj->initalize = false;
    return sms_obj;
}

 error_type_t sms_tracker_init(sms_tracker_t* sms_obj){
    if (sms_obj == NULL)return NULL_PARAMETER;
    sms_obj->initalize = true;
    sms_obj->has_sent_sms = false;

    return OK;
    
 }

void sms_tracker_reset_counter(sms_tracker_t*sms_obj){
    
        sms_obj->sms_time_counter = 0;
        sms_obj->follow_up_counter = 0;
        sms_obj->has_sent_sms = false;
    
 }

 void sms_tracker_handler(sms_tracker_t* sms_obj){
    
 }



 error_type_t sms_tracker_deinit(sms_tracker_t*sms_obj){
    if(sms_obj == NULL)return NULL_PARAMETER;
    sms_obj->initalize = false;
    return OK;  
 }

 error_type_t sms800_destroy(sms_tracker_t** sms_obj){
    if(sms_obj == NULL)return NULL_PARAMETER;
    *sms_obj = NULL;
    free(*sms_obj);
    return OK;
    
 }


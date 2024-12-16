#include <Arduino.h>
#include <sms-tracker.h>
#include <sim800.h>
#include <stdbool.h>
#include <common_headers.h>

#define SMS_TIME 600000
#define RESEND_TIME 600000

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
    sms_obj->has_sent_sms = true;
    return OK;
    
 }

 void sms_tracker_handler(sms_tracker_t* sms_obj){
    char phone_number[] = "+2347055587935"; // use actual phone number
    char message[] = "Fire ALert ! ! !";
    sms_obj->sms_time_counter++;
    if (sms_obj->sms_time_counter >= SMS_TIME)
    {
         sim800_send_sms(sms_obj->sim800_obj,phone_number,message);
        if (!sms_obj->has_sent_sms)
        {
            sim800_send_sms(sms_obj->sim800_obj,phone_number,message);
        }else
        {
            sms_obj->follow_up_counter++;
            if (sms_obj->follow_up_counter >= RESEND_TIME)
             {
                 sim800_send_sms(sms_obj->sim800_obj,phone_number,message);
            }
            
        }
        
        
    }
    
 }

 error_type_t sms_tracker_deinit(sms_tracker_t*sms_obj){
    if(sms_obj == NULL)return NULL_PARAMETER;
    if (sms_obj->initalize == false)
    {
        sms_obj->initalize = false;
    }
    return OK;  
 }

 error_type_t sms800_destroy(sms_tracker_t** sms_obj){
    if(sms_obj == NULL)return NULL_PARAMETER;
    *sms_obj = NULL;
    free(*sms_obj);
    return OK;
    
 }


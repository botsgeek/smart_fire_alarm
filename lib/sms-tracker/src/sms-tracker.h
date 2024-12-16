#ifndef _SMS_TRACKER_H_
#define _SMS_TRACKER_H_
#include <stdint.h>
#ifdef __cplusplus
extern "C" {
    #endif
    #include <common_headers.h>
    #include <sim800.h>
    
    typedef struct sms_tracker_t sms_tracker_t;
    typedef struct{
        int sms_time_counter;
        int follow_up_counter;
        sim800_t* sim800_obj;

    }sms_tracker_config_t;

    sms_tracker_t* sms_tracker_create(const sms_tracker_config_t* sms_config);
    void sms_tracker_handler(sms_tracker_t* sms_obj);
    error_type_t sms_tracker_init(sms_tracker_t* sms_obj);
    error_type_t sms_tracker_deinit(sms_tracker_t*sms_obj);
    error_type_t sms_tracker_destroy(sms_tracker_t**sms_obj);

#ifdef __cplusplus    
}
#endif
#endif

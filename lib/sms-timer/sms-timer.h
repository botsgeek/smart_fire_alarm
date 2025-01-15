#ifndef _SMS_TIMER_H_
#define _SMS_TIMER_H_
#ifdef __cplusplus
extern "C"{
#endif
#include <sim800.h>
#include <time.h>

typedef struct sms_tracker_t sms_tracker_t;

typedef enum{
    NORMAL,
    SENT_SMS
}sms_t;

typedef struct {

    sim800_t*sms800_obj;
    sms_t current_state;
}sms_config_t;




sms_tracker_t* sms_tracker_create(const sms_config_t* sms_config);
void sms_tracker_handler(sms_tracker_t* sms_obj);
void sms_reset_tracker(sms_tracker_t* sms_obj);




#ifdef __cplusplus
}
#endif
#endif
#ifndef _TIME_H_
#define _TIME_H_
#ifdef __cplusplus
extern "C"{
#endif
#include <common_headers.h>


typedef struct 
{
  unsigned long expiry;

}timer_t;


error_type_t timer_set_time(timer_t*sms_timer_obj, long future_time);
error_type_t timer_check_expiry(timer_t*sms_timer_obj, bool* expiry);


#ifdef __cplusplus
}
#endif
#endif

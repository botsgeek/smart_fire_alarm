#include <Arduino.h>
#include<time.h>
#include <common_headers.h>

error_type_t timer_set_time(timer_t*sms_timer_obj, long future_time ){
    if(sms_timer_obj == NULL)return NULL_PARAMETER;
   
  sms_timer_obj->expiry = millis() + future_time;
  return OK;
}

error_type_t timer_check_expiry(timer_t*timer_obj, bool* expiry){
    if(timer_obj == NULL)return NULL_PARAMETER;
  unsigned long  current_time = millis();
  if (current_time >= timer_obj->expiry)
  {
    *expiry = true;
  }else
  {
    *expiry = false;
  }
  return OK;
  
}
#include <Arduino.h>
#include <sms-timer.h>
#include <common_headers.h>
#include <sim800.h>
#include <print.h>
#include <time.h>
#define SMS_TIME 5000//send sms in 5sec
#define RESEND_TIME 120000 // send sms in 2min
constexpr char*  PHONE_NUMBER = "+2348104952432";
constexpr  char * MESSAGE  = "Fire ALert ! ! !";

struct sms_tracker_t
{
    sim800_t*sms800_obj;
    timer_t* timer_obj;
    sms_t current_state;
    bool timer_started;
};


sms_tracker_t* sms_tracker_create(const sms_config_t* sms_config){
    if(sms_config == NULL)return NULL;

    sms_tracker_t* sms_obj = (sms_tracker_t*)malloc(sizeof(sms_tracker_t));
    sms_obj->sms800_obj = sms_config->sms800_obj;
    sms_obj->current_state = sms_config->current_state;
    sms_obj->timer_started = false;
    return sms_obj;
}

void sms_tracker_handler(sms_tracker_t* sms_obj){
    Serial.println(F("entering the timer state machine!!!"));
      Serial.println(F("This is  the state timer value "));
      error_type_t err;
      bool result;


    Serial.println(sms_obj->current_state);
    switch (sms_obj->current_state)
    {
    case NORMAL:
    Serial.print(F("in normal state"));

        if (!sms_obj->timer_started)
        {
            err = timer_set_time(sms_obj->timer_obj, SMS_TIME);
            if (err != OK)
            {
                debug_printf("failed to set time");
                exit(1);
            }
            sms_obj->timer_started = true;
        }else
        {
            err = timer_check_expiry(sms_obj->timer_obj, &result);
            if (err != OK)
            {
                debug_printf("failed to check expiry");
                exit(1);
            }
            if(result){
                sms_obj->current_state = SENT_SMS;
                sms_obj->timer_started = false;
                Serial.print(F("sent an sms the first time"));
                debug_printf("phone number: %s\n",PHONE_NUMBER);
                debug_printf("message: %s\n",MESSAGE);
                err=sim800_send_sms(sms_obj->sms800_obj,PHONE_NUMBER,MESSAGE);
                if (err == OK)
                {
                Serial.println(F("sent sms is sucessful"));
                
                }else
                {
                Serial.println(F("failed to send sms!!!"));
                }  
            }
            
        }
        

        break;
       
    case SENT_SMS:
    Serial.println("in sms state");
    Serial.println("preparing to resend sms");
           if (!sms_obj->timer_started)
        {
            err = timer_set_time(sms_obj->timer_obj, RESEND_TIME);
            if (err != OK)
            {
                debug_printf("failed to set time");
                exit(1);
            }
            sms_obj->timer_started = true;
        }else
        {
            err = timer_check_expiry(sms_obj->timer_obj, &result);
            if (err != OK)
            {
                debug_printf("failed to check expiry");
                exit(1);
            }
            if(result){
                sms_obj->timer_started = false;
                Serial.println("sent an sms the second  time");
                debug_printf("phone number: %s\n",PHONE_NUMBER);
                debug_printf("message: %s\n",MESSAGE);
                err= sim800_send_sms(sms_obj->sms800_obj,PHONE_NUMBER,MESSAGE);
                if (err == OK)
                {
                Serial.println(F("sent sms is sucessful"));
                
                }else
                {
                Serial.println(F("failed to send sms!!!"));
                }  
            }
            
        }
         
        break;
    default:
        break;
    }
    
}

//Reset the sms_handler; 
void sms_reset_tracker(sms_tracker_t* sms_obj){
  if (sms_obj != NULL)
  {
    sms_obj->timer_started = false;
    sms_obj->current_state = NORMAL;
  }

}

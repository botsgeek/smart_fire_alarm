#include <stdint.h>
#if defined(ARDUINO) && ARDUINO >= 100
#elif defined(ARDUINO)
#else
#include <stdio.h>
#endif
#ifndef _RTC_H_
#define _RTC_H_
#ifdef __cplusplus
extern "C" {
 #endif

  


typedef struct rtc_t rtc_t;

typedef enum{
  INVALIDE_ADDR,
  NULL_PARAMETER,
  INVALIDE_STATE,
  FAILED,
  OK

}error_type_t;

typedef struct{
int seconds;
int minute;
int hour;
int day;
int date;
int month;
int year;

}rtc_date_time_t;

typedef struct 
{
  int alarm_sec;
  int alarm_min;
  int alarm_hr;
  int alarm_day;
  int alarm_date;
}rtc_alarm_t;

typedef struct {
  uint8_t i2c_addr; // 0x68
  uint8_t memory_addr; // 0x57
  //bool state;
}rtc_config_t;


//function decleartion
rtc_t* rtc_create(const rtc_config_t* config );
error_type_t rtc_init(rtc_t* rtc_obj);
error_type_t setDateTime( rtc_t* rtc_obj, rtc_date_time_t* set_rtc );
error_type_t getDateTime(rtc_t* rtc_obj, rtc_date_time_t* set_rtc);
error_type_t set_rtc_alarm(rtc_t* rtc_obj, rtc_alarm_t* set_alarm);
error_type_t get_rtc_alarm(rtc_t* rtc_obj,rtc_alarm_t* set_alarm);
error_type_t deinit(rtc_t* rtc_obj);
error_type_t destroy(rtc_t** rtc_obj);









  #ifdef __cplusplus
}
#endif
#endif






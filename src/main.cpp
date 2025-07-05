#include <Arduino.h>
#include <Arduino_FreeRTOS.h>
#include "rtc.h"
rtc_config_t rtc_config = {
  .i2c_addr = 0x68,
  .memory_addr = 0x57
};

rtc_date_time_t dateTime = {
    .seconds = 37,
    .minute = 57,
    .hour = 10,
    .day = 03,
    .date = 05, //weeks
    .month = 07,
    .year = 2025
    
};

rtc_alarm_t setAlarm = {
    .alarm_sec = 00,
    .alarm_min = 30,
    .alarm_hr = 10,
    .alarm_day = 05,
    .alarm_date = 07
};

rtc_t* rtc = NULL;
 error_type_t err;

void setup()
{
  // put your setup code here, to run once:
  Serial.begin(9600);

 
  rtc = rtc_create(&rtc_config);
  if (!rtc)
  {
    Serial.print("create failed");
    exit(1);
  }

  err = rtc_init(rtc);
  if (err != OK)
  {
    Serial.print("failed to init");
  }

  err = setDateTime(rtc,&dateTime);
  if (err != OK)
  {
    Serial.println("failed to set date and time");
  }

  err = set_rtc_alarm(rtc, &setAlarm);
  if (err != OK)
  {
    Serial.println("failed to set rtc");
  }
  
}

void loop()
{
  // put your main code here, to run repeatedly:

   err = getDateTime(rtc, &dateTime);
  if (err != OK)
  {
    Serial.println("could not get  date and time");
  }

  err = get_rtc_alarm(rtc, &setAlarm);
  if (err != OK)
  {
    Serial.println("failed to get alarm");
  }
  Serial.println("Alarm goes off by 10:30am");

  

 


}

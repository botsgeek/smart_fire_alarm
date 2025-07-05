#include<Arduino.h>
#include <Wire.h>
#include<stdbool.h>
#include <rtc.h>


struct rtc_t
{
    uint8_t i2c_addr;
    uint8_t memory_addr;
    bool state;
};

//  convert BCD to DEC
 static uint8_t bcdTodec(uint8_t value){
  uint8_t data = ((value >> 4) * 10) + (value & 0x0F);
  return data;
}

//convert DEC to BCD
 static uint8_t decTobcd(uint8_t val){
  uint8_t dec_data = ((val/10)<< 4) | (val% 10);
  return dec_data;
 }

rtc_t* rtc_create(const rtc_config_t* config ){
    if (config == NULL)
    {
        return NULL;
    }

    rtc_t* rtc_obj = (rtc_t*)malloc(sizeof(rtc_t));
    rtc_obj->i2c_addr = config->i2c_addr;
    rtc_obj->memory_addr = config->memory_addr;
    rtc_obj->state = false;
    return rtc_obj;   
}

error_type_t rtc_init(rtc_t* rtc_obj){
    if (rtc_obj == NULL)
    {
        return NULL_PARAMETER;
    }
    Wire.begin();
    rtc_obj->state = true;
    return OK;    
}

error_type_t setDateTime( rtc_t* rtc_obj, rtc_date_time_t* set_rtc ){
    if (rtc_obj == NULL|| set_rtc == NULL)
    {
        return NULL_PARAMETER;
    }
    
        Wire.beginTransmission(rtc_obj->i2c_addr);
        Wire.write(0x00);
        Wire.write(decTobcd(set_rtc->seconds));
        Wire.write(decTobcd(set_rtc->minute));
        Wire.write(decTobcd(set_rtc->hour));
        Wire.write(decTobcd(set_rtc->day));
        Wire.write(decTobcd(set_rtc->date));
        Wire.write(decTobcd(set_rtc->month));
        Wire.write(decTobcd(set_rtc->year % 100));
        Wire.endTransmission(false);
        return OK;

}

error_type_t getDateTime(rtc_t* rtc_obj, rtc_date_time_t* set_rtc){
    if (rtc_obj == NULL || set_rtc == NULL)
    {
        return NULL_PARAMETER;
    }
    

    Wire.beginTransmission(rtc_obj->i2c_addr);
    Wire.write(0x00);
    Wire.endTransmission(false);
    Wire.requestFrom(rtc_obj->i2c_addr, 7);

  if(Wire.available() >= 7){

    set_rtc->seconds = bcdTodec(Wire.read());
    set_rtc-> minute = bcdTodec(Wire.read());
    set_rtc-> hour = bcdTodec(Wire.read());
    set_rtc-> day = bcdTodec(Wire.read());
    set_rtc-> date = bcdTodec(Wire.read());
    set_rtc-> month = bcdTodec(Wire.read());
    set_rtc ->year = bcdTodec(Wire.read());

   
 
    Serial.print("Date: ");
    Serial.print(set_rtc->day);
    Serial.print("-");
    Serial.print(set_rtc->month);
    Serial.print("-");
    Serial.println(2000 + set_rtc->year);
    Serial.print("Time: ");
    Serial.print(set_rtc->hour);
    Serial.print(":");
    Serial.print(set_rtc->minute);
    Serial.print(":");
    Serial.println(set_rtc->seconds);
    delay(1000);
    return OK;
  }

  return FAILED;
}
error_type_t set_rtc_alarm(rtc_t* rtc_obj, rtc_alarm_t* set_alarm){
    if (rtc_obj == NULL || set_alarm == NULL)
    {
        return NULL_PARAMETER;
    }

    Wire.beginTransmission(rtc_obj->i2c_addr);
    Wire.write(0x07);
    Wire.write(decTobcd(set_alarm->alarm_sec));
    Wire.write(decTobcd(set_alarm->alarm_sec));
    Wire.write(decTobcd(set_alarm->alarm_sec));
    Wire.write(decTobcd(set_alarm->alarm_sec));
    Wire.write(decTobcd(set_alarm->alarm_sec));
    Wire.endTransmission(false);
    Serial.println("Alarm set successfully");
    return OK;
}

error_type_t get_rtc_alarm(rtc_t* rtc_obj,rtc_alarm_t* set_alarm){
    if (rtc_obj == NULL || set_alarm == NULL)
    {
        return NULL_PARAMETER;
    }
    
    Wire.beginTransmission(rtc_obj->i2c_addr);
    Wire.write(0x07);
    Wire.endTransmission(false);
    Wire.requestFrom(rtc_obj->i2c_addr,5);

    if (Wire.available() >= 5)
    {
        set_alarm->alarm_sec = bcdTodec(Wire.read());
        set_alarm->alarm_min = bcdTodec(Wire.read());
        set_alarm->alarm_hr = bcdTodec(Wire.read());
        set_alarm->alarm_day = bcdTodec(Wire.read());
        set_alarm->alarm_date = bcdTodec(Wire.read());
    }
    return OK;
}


error_type_t destroy(rtc_t** rtc_obj){
    if (rtc_obj == NULL)
    {
        return NULL_PARAMETER;
    }
    free(*rtc_obj);
    *rtc_obj = NULL;
    
    return OK;
}

error_type_t deinit(rtc_t* rtc_obj){
    if (rtc_obj == NULL)
    {
        return NULL_PARAMETER;
    }

    if(rtc_obj->state == false) return INVALIDE_STATE;
    Wire.endTransmission(true);
    rtc_obj->state = false;

    return OK;
}


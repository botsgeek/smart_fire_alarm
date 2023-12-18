#include<stdint.h>
#ifndef _FAN_DRIVER_H_
#define _FAN_DRIVER_H_
#ifdef __cplusplus
extern "C" {
#endif
#include "common_headers.h"
typedef enum{
    INITIALIZE_FAN,
    FANSPEED,
    DEACTIVATE_FAN,
}fan_mode_t;
typedef struct fan_t fan_t;
typedef struct{
    uint8_t fan_pin_number;
    fan_mode_t set_fanspeed;

}fan_state_t;

error_type_t fan_init(fan_t* fan_object);
error_type_t set_fanspeed(fan_t* fan_object);
error_type_t deinit(fan_t* fan_object);
fan_t* fan_driver_create(const fan_state_t* fan_operation);

fan_mode_t fan_int();
fan_mode_t fanspeed();
fan_mode_t dactiavte(); 



#ifdef __cplusplus
}
#endif

#endif
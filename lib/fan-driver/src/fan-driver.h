#include<stdint.h>
#ifndef _FAN_DRIVER_H_
#define _FAN_DRIVER_H_
#ifdef __cplusplus
extern "C" {
#endif
#include "common_headers.h"

typedef struct fan_t fan_t;

typedef struct{
    uint8_t fan_pin_number;

}fan_config_t;

error_type_t fan_init(fan_t* fan_object);

error_type_t set_fanspeed(fan_t* fan_object);

error_type_t deinit(fan_t* fan_object);

fan_t* fan_create(const fan_config_t* config);



#ifdef __cplusplus
}
#endif

#endif
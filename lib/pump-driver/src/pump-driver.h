#include <stdint.h>
#ifndef _PUMP_DRIVER_H_
#define _PUMP_DRIVER_H_
#ifdef __cplusplus
extern "C"{
#endif 
#include "common_headers.h"

typedef struct pump_t pump_t;

typedef struct 
{
    uint8_t pump_pin_number;
}pump_config_t;
error_type_t pump_init(pump_t* pump_object); // initalize the pump pin number
error_type_t pump_active(pump_t* pump_object); // start the water pump
error_type_t pump_deinit(pump_t* pump_object); // stop the waterpump
pump_t* pump_create(const pump_config_t* config); 




#ifdef __cplusplus
}
#endif
#endif
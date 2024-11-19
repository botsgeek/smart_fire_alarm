#ifndef _LM75_MAN_H_
#define _LM75_MAN_H_
#include <stdint.h>
#ifdef __cplusplus
extern "C" {
#endif
#include <common_headers.h>
#include <lm75.h>

typedef struct lm75_manage_t lm75_manage_t;

//lm75 manager
typedef struct{
    
    float lm75_threshold;
    lm75_t* lm75_obj;
}lm75_manager_t;

lm75_manage_t* lm75_manage_create(const lm75_manager_t* manage_state);
error_type_t lm75_get_obj(lm75_manage_t* manage_lm75_object);
error_type_t lm75_manage_deinit(lm75_manage_t* manage_lm75_object);
error_type_t lm75_manage_destroy(lm75_manage_t* manage_lm75_object);
error_type_t lm75_manage_init(lm75_manage_t* manage_lm75_object);




#ifdef __cplusplus
}
#endif

#endif
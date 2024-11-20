#ifndef _LM75_MANAGER_H_
#define _LM75_MANAAGER_H_
#include <stdint.h>
#ifdef __cplusplus
extern "C" {
#endif
#include <common_headers.h>
#include <lm75.h>

typedef struct lm75_t lm75_t;

//lm75 manager
typedef struct{
    
    float lm75_threshold;
    lm75_t* lm75_obj;
}lm75_config_t;

lm75_t* lm75_create(const lm75_config_t* config_state);
error_type_t get_above_threshold(lm75_t* lm75_state, bool* state);
error_type_t lm75_deinit(lm75_t* lm75_state);
error_type_t lm75_destroy(lm75_t** lm75_state);
error_type_t lm75_init(lm75_t* lm75_state);




#ifdef __cplusplus
}
#endif

#endif
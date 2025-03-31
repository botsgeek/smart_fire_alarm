#ifndef _LM75_MANAGER_H_
#define _LM75_MANAGER_H_
#include <stdint.h>
#ifdef __cplusplus
extern "C" {
#endif
#include <common_headers.h>
#include <lm75.h>

typedef struct lm75_manager_t lm75_manager_t;

//lm75 manager
typedef struct{
    
    float lm75_threshold;
    lm75_t* lm75_obj;

}lm75_manager_config_t;


lm75_manager_t* lm75_manager_create(const lm75_manager_config_t* manager_config);
error_type_t lm75_manager_above_threshold(lm75_manager_t* lm75_manager, bool* state);
error_type_t lm75_manager_deinit(lm75_manager_t* lm75_manager);
error_type_t lm75_manager_destroy(lm75_manager_t** lm75_manager);
error_type_t lm75_manager_init(lm75_manager_t* lm75_manager);


#ifdef __cplusplus
}
#endif

#endif
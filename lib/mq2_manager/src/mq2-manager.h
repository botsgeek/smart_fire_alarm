#ifndef _MQ2_MANAGER_H_
#define _MQ2_MANAGER_H_
#include <stdint.h>
#ifdef __cplusplus
extern "C" {
#endif
#include <common_headers.h>
#include <mq2.h>

typedef struct mq2_t mq2_t;

//mq2 manager
typedef struct{

    uint16_t mq2_threshold;
    mq2_t* mq2_object;
    

}mq2_config_t;

mq2_t* create(const mq2_config_t* config_lib);
error_type_t lib_init(mq2_t* mq2_state);
error_type_t lib_deinit(mq2_t* mq2_state);
error_type_t lib_destory(mq2_t** mq2_state);
error_type_t get_above_threshold(mq2_t* mq2_state, bool* state);






#ifdef __cplusplus
}
#endif

#endif
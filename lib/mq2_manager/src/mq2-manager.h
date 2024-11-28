#ifndef _MQ2_MANAGER_H_
#define _MQ2_MANAGER_H_
#include <stdint.h>
#ifdef __cplusplus
extern "C" {
#endif
#include <common_headers.h>
#include <mq2.h>

typedef struct mq2_manager_t mq2_manager_t;

//mq2 manager
typedef struct{

    uint16_t mq2_threshold;
    mq2_t* mq2_object;
    

}mq2_manager_config_t;

mq2_manager_t* mq2_manager_create(const mq2_manager_config_t* manager_config);
error_type_t mq2_manager_init(mq2_manager_t* mq2_manager);
error_type_t mq2_manager_deinit(mq2_manager_t* mq2_manager);
error_type_t mq2_manager_destory(mq2_manager_t** mq2_manager);
error_type_t mq2_manager_above_threshold(mq2_manager_t* mq2_manager, bool* state);






#ifdef __cplusplus
}
#endif
#endif
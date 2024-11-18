#ifndef _STATE_H_
#define _STATE_H_
#include <common_headers.h>
#include <stdint.h>

class state_t;

typedef class{
    public:
    bool smoke;
    bool heat;
    bool normal;

}state_cofig_t;


typedef class{
    public:
    float lm75_threshold;
    uint8_t lm75_object;
}heat_t;

typedef class{
    public:
    float mq2_threshold;
    uint8_t mq2_object;

}smoke_t;

typedef enum{
    NORMAL,
    ACTIVATE_PUMP,
    ACTIVATE_FAN,
    DEACTIVATE_DRIVER,
    ACTIVATE_BUZZER
}error_state_t;

state_t* create_state(const state_cofig_t* config);
error_type_t state_init(state_t* state_object);
error_type_t state_deinit(state_t* state_object);
error_type_t state_destroy(state_t** state_object);
error_state_t state_tran(bool heat, bool smoke);


#endif
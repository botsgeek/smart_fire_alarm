#include "mq2.h"
#include <stdlib.h>
#include "common_headers.h"
#if defined(ARDUINO_AVR_NANO)
#define MAX_ANALOG_PIN_NUMBER A7
#define MIN_ANALOG_PIN_NUMBER A0
#define MAX_DIGITAL_PIN_NUMBER 2
#define MIN_DIGITAL_PIN_NUMBER 13
#define MAX_DIGITAL_ISR_PIN_NUMBER 3
#define MIN_DIGITAL_ISR_PIN_NUMBER 2
#else
#define MAX_ANALOG_PIN_NUMBER 10
#define MIN_ANALOG_PIN_NUMBER 0
#define MAX_DIGITAL_PIN_NUMBER 10
#define MIN_DIGITAL_PIN_NUMBER 0
#endif

struct mq2_t {
        uint8_t analog_pin_number;
        uint8_t digital_pin_number;
        mq2_mode_t mode;
        bool initialized;
    };


static error_type_t mq2_init_analog_mode(mq2_t *mq2_object);
static error_type_t mq2_init_digital_mode(mq2_t *mq2_object);

mq2_t* mq2_create(const mq2_config_t* config){
    if(config == NULL)return NULL;
    mq2_t* new_mq_2_obj = (mq2_t*) malloc(sizeof(mq2_t));
    new_mq_2_obj->analog_pin_number = config->analog_pin_number;
    new_mq_2_obj->digital_pin_number = config->digital_pin_number;
    new_mq_2_obj->mode = config->mode;
    return new_mq_2_obj;
}

static error_type_t mq2_init_analog_mode(mq2_t* mq2_object){
    if(mq2_object == NULL)return NULL_PARAMETER;
    if(mq2_object->analog_pin_number <  MIN_ANALOG_PIN_NUMBER || mq2_object->analog_pin_number > MAX_ANALOG_PIN_NUMBER){
            return INVALID_PIN_NUMBER;
    }
    mq2_object->initialized = true;
    return OK;
}

static error_type_t mq2_init_digital_mode(mq2_t* mq2_object){
    if(mq2_object == NULL)return NULL_PARAMETER;
    if(mq2_object->analog_pin_number <  MIN_DIGITAL_PIN_NUMBER || mq2_object->analog_pin_number > MAX_DIGITAL_PIN_NUMBER){
            return INVALID_PIN_NUMBER;
    }
    pinMode(mq2_object->digital_pin_number,INPUT_PULLUP);
    mq2_object->initialized = true;
    return OK;
}
error_type_t mq2_init(mq2_t* mq2_object){
    if(mq2_object == NULL)return NULL_PARAMETER;
    if(mq2_object->mode == MQ2_ANALOG_ONLY)
    return mq2_init_analog_mode(mq2_object);
    else if(mq2_object->mode == MQ2_DIGITAL_ONLY)
    return mq2_init_digital_mode(mq2_object);
    else if(mq2_object->mode == MQ2_HYBRID){
        error_type_t analog_err = mq2_init_analog_mode(mq2_object);
        if (analog_err != OK) return analog_err;
        error_type_t digital_err = mq2_init_digital_mode(mq2_object);
        if (digital_err != OK) return analog_err;
        mq2_object->initialized = true;
        return OK;
    }
    else return INVALID_PARAMETER;
}

error_type_t mq2_init_with_isr(mq2_t* mq2_object, void(*callback)()){
    if(mq2_object == NULL)return NULL_PARAMETER;
    if(mq2_object->mode == MQ2_ANALOG_ONLY)return INVALID_PARAMETER;
    if(mq2_object->analog_pin_number <  MIN_DIGITAL_ISR_PIN_NUMBER || mq2_object->analog_pin_number > MAX_DIGITAL_ISR_PIN_NUMBER){
            return INVALID_PIN_NUMBER;
    }
    error_type_t err = mq2_init(mq2_object);
    if (err != OK)return err;
    if(callback == NULL){
        mq2_object->initialized = false;
        return INVALID_PARAMETER;
    }
    attachInterrupt(digitalPinToInterrupt(mq2_object->digital_pin_number), callback, RISING);
    mq2_object->initialized = true;
    return OK;
}

error_type_t mq2_deinit(mq2_t* mq2_object){
    // Since arduino does not de-initialized pins
    // Nothing to do here than to free our object to
    // Release the memory
    free(mq2_object);
    return OK;
}


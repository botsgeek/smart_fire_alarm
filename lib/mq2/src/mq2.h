#include <stdint.h>
#if defined(ARDUINO) && ARDUINO >= 100
#include "Arduino.h"
#elif defined(ARDUINO)
#include <"WConstants.h">
#else
#include <stdio.h>
#endif
#ifndef _MQ2_H_
#define _MQ2_H_
#ifdef __cplusplus
extern "C"
{
#endif
#include "common_headers.h"
    typedef enum
    {
        MQ2_DIGITAL_ONLY,
        MQ2_ANALOG_ONLY,
        MQ2_HYBRID,

    } mq2_mode_t;
    /**
     * @brief
     *
     */
    typedef struct mq2_t mq2_t;
    /**
     * @brief
     *
     */
    typedef struct
    {
        uint8_t analog_pin_number;
        uint8_t digital_pin_number;
        mq2_mode_t mode;
    } mq2_config_t;

    /**
     * @brief
     *
     * @param mq2_object
     * @return error_type_t
     */
    error_type_t mq2_init(mq2_t *mq2_object);
    /**
     * @brief
     *
     * @param mq2_object
     * @param callback
     * @return error_type_t
     */
    error_type_t mq2_init_with_isr(mq2_t *mq2_object, void (*callback)());
    /**
     * @brief
     *
     * @param mq2_object
     * @return error_type_t
     */
    error_type_t mq2_deinit(mq2_t *mq2_object);
    /**
     * @brief
     *
     * @param config
     * @return mq2_t*
     */
    mq2_t *mq2_create(const mq2_config_t *config);

#ifdef __cplusplus
}
#endif
#endif
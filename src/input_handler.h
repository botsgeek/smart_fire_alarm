#if defined(ARDUINO) && ARDUINO >= 100
#include "Arduino.h"
#elif defined(ARDUINO)
#include <"WConstants.h">
#else
#include <stdio.h>
#endif
#ifndef _INPUT_HANDLER_H_
#define _INPUT_HANDLER_H_
#ifdef __cplusplus
extern "C"
{
#endif
#include <lm75.h>
#include <mq2.h>
#include <Arduino_FreeRTOS.h>
#include <queue.h>
    typedef enum
    {
        NOT_TRIGGERED,
        TRIGGERED
    } sensor_state_t;

    typedef struct
    {
        sensor_state_t gas;
        sensor_state_t heat;
    } sensor_output_t;

    extern QueueHandle_t input_queue;
    void task_read_inputs(void *pvParameter);
#ifdef __cplusplus
}
#endif
#endif
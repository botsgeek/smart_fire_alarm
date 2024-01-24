#if defined(ARDUINO) && ARDUINO >= 100
#include "Arduino.h"
#elif defined(ARDUINO)
#include <"WConstants.h">
#else
#include <stdio.h>
#endif
#ifndef _SYSTEM_MANAGER_H_
#define _SYSTEM_MANAGER_H_
#ifdef __cplusplus
extern "C"
{
#endif
#include <input_handler.h>
#include <Arduino_FreeRTOS.h>
#include <queue.h>
    extern QueueHandle_t input_queue;
    void task_system_manager(void *pvParameter);
#ifdef __cplusplus
}
#endif
#endif
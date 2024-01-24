#include <Arduino.h>
#include <Arduino_FreeRTOS.h>
#include <config.h>
#include <input_handler.h>
#include <system_manager.h>
QueueHandle_t input_queue;
void setup()
{
  Serial.begin(9600);
  while (!Serial)
  {
    ; // wait for serial port to connect. Needed for native USB, on LEONARDO, MICRO, YUN, and other 32u4 based boards.
  }
  input_queue = xQueueCreate(CONFIG_INPUT_QUEUE_SIZE, sizeof(sensor_output_t));
  xTaskCreate(&task_read_inputs, "input task", 128, NULL, 2, NULL);
  xTaskCreate(&task_system_manager, "task_system_manager task", 128, NULL, 2, NULL);
}

void loop()
{
}

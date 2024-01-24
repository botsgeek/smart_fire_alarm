#include "system_manager.h"

void task_system_manager(void *pvParameter)
{
    Serial.println("Starting system manager");
    while (1)
    {
        static sensor_output_t sensor_output;
        if (xQueueReceive(input_queue, &sensor_output, pdMS_TO_TICKS(portMAX_DELAY)) == pdTRUE)
        {
            Serial.println("Received data from queue");
            Serial.println("sensor data received are gas: " + (String)(int)sensor_output.gas + " heat: " + (String)(int)sensor_output.heat);
        }
        vTaskDelay(1000 / portTICK_PERIOD_MS);
    }
}
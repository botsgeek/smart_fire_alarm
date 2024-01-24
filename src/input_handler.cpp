#include <input_handler.h>
#include <config.h>
static mq2_state_t mq2_state = NO_SMOKE;
static mq2_t *mq2_object;
static lm75_t *lm75_object;

static void callback()
{
    Serial.println("mq2 interrupt fired");
    static uint16_t value;
    mq2_digital_read(mq2_object, &value);
    mq2_state = (value == HIGH) ? SMOKE_DETECTED : NO_SMOKE;
}

static error_type_t setup_mq2()
{
    mq2_config_t mq2_config = {
        .analog_pin_number = 1,
        .digital_pin_number = CONFIG_MQ2_PIN,
        .mode = CONFIG_MQ2_MODE};
    mq2_object = mq2_create(&mq2_config);

    error_type_t err = mq2_init_with_isr(mq2_object, callback);
    if (err != OK)
    {
        return err;
    }
    return OK;
}

static error_type_t setup_lm75()
{
    lm75_config_t config = {
        .i2c_addr = CONFIG_LM75_I2C_ADDR,
        .mode = CONFIG_LM75_MODE,
        .os_pin_number = 1,
        .polarity = CONFIG_LM75_POLARITY,
        .tolerance = CONFIG_LM75_TOLERANCE,
        .resolution = CONFIG_LM75_RESOLUTION

    };

    lm75_object = lm75_create(&config);
    error_type_t err = lm75_init_comparator_mode(lm75_object);
    if (err != OK)
    {
        return err;
    }
    return OK;
}
void task_read_inputs(void *pvParameter)
{

    error_type_t err = setup_mq2();
    if (err != OK)
    {
        Serial.println("mq2 initialization failed exiting...");
        exit(1);
    }
    err = setup_lm75();
    if (err != OK)
    {
        Serial.println("lm75 initialization failed exiting...");
        exit(1);
    }
    /*
        callback is fired manually here to cater for
        when smoke detection pin is already HIGH while
        task is starting
    */
    callback();
    while (1)
    {
        Serial.println("in input task");
        static sensor_output_t sensor_output;
        if (mq2_state == SMOKE_DETECTED)
        {
            Serial.println("smoke has been detected");
        }
        float temperature = lm75_read(lm75_object);
        Serial.println("temperature read is: " + (String)temperature);
        sensor_output.gas = mq2_state == SMOKE_DETECTED ? TRIGGERED : NOT_TRIGGERED;
        sensor_output.heat = temperature > CONFIG_THRESHOLD_TEMPERATURE ? TRIGGERED : NOT_TRIGGERED;
        Serial.println("sensor data are gas: " + (String)(int)sensor_output.gas + " heat: " + (String)(int)sensor_output.heat);
        if (xQueueSend(input_queue, &sensor_output, pdMS_TO_TICKS(portMAX_DELAY)) == pdTRUE)
        {
            Serial.println("sensor data queued successfully");
        }
        else
        {
            Serial.println("data queue failed");
        }
        vTaskDelay(1000 / portTICK_PERIOD_MS);
    }
}
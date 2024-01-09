#include "sim800.h"
#include <SoftwareSerial.h>
#include <stdlib.h>
#include <Regexp.h>
#include "common_headers.h"
#if defined(ARDUINO_AVR_NANO)
#define MAX_DIGITAL_PIN_NUMBER (13)
#define MIN_DIGITAL_PIN_NUMBER (2)
static const uint8_t ACCEPTABLE_RX_PIN[] = {2, 3, 10};
#else
#define MAX_DIGITAL_PIN_NUMBER 10
#define MIN_DIGITAL_PIN_NUMBER 0
static const uint8_t ACCEPTABLE_RX_PIN[] = {0, 1, 2, 3};
#endif
#define MAX_TIMEOUT (0x10000000UL)
#define READ_BUFFER_SIZE (256U)
#define EXTRA_CHAR_COUNT (2U)
#define MESSAGE_SEND_BUFFER_SIZE (255U)
#define COMMAND_PING ("AT\r\n")
#define COMMAND_CHECK_SMS_SUPPORT ("AT+CMGF=1\r\n")
#define COMMAND_CONSTRUCT_SMS_NUMBER(x, y) \
    do                                     \
    {                                      \
        strcat((x), "AT+CMGS=");           \
        strcat((x), ("\""));               \
        strcat((x), (y));                  \
        strcat((x), ("\""));               \
        strcat((x), ("\r\n"));             \
        strcat((x), ("\0"));               \
    } while (0)

#define COMMAND_CONSTRUCT_SMS(x, y, z) \
    do                                 \
    {                                  \
        strcat((x), (y));              \
        strcat((x), (z));              \
        strcat((x), ("\0"));           \
    } while (0)
#define COMMAND_SET_GSM ("AT+CSCS=\"GSM\"\r\n")
#define ERROR_RESPONSE ("\r\nERROR")
#define OK_RESPONSE ("\r\nOK")
#define SMS_TERMINATOR \
    {                  \
        26, 0          \
    }

static const uint32_t ACCEPTABLE_BAUD_RATE[] = {1200, 2400, 4800, 9600, 19200, 28800, 38400, 57600, 76800, 115200};

static char sim800_read_buffer[READ_BUFFER_SIZE];
typedef struct
{
    SoftwareSerial *serial;
    char *response;
    uint16_t response_length;

} soft_serial_t;
static soft_serial_t sim800_serial;
struct sim800_t
{
    uint8_t tx_pin_number;
    uint8_t rx_pin_number;
    uint32_t baud_rate;
    bool initialized;
};
static error_type_t validate_rx(sim800_t *sim800_object)
{
    bool pin_found = false;
    for (uint8_t x = 0; x < sizeof(ACCEPTABLE_RX_PIN); x++)
    {
        if (sim800_object->rx_pin_number == ACCEPTABLE_RX_PIN[x])
            pin_found = true;
    }
    return pin_found == false ? INVALID_PIN_NUMBER : OK;
}
static error_type_t validate_baud(sim800_t *sim800_object)
{
    bool baud_found = false;
    for (uint8_t x = 0; x < sizeof(ACCEPTABLE_BAUD_RATE) / sizeof(uint32_t); x++)
    {
        if (sim800_object->baud_rate == ACCEPTABLE_BAUD_RATE[x])
            baud_found = true;
    }
    return baud_found == false ? INVALID_PIN_NUMBER : OK;
}

static void flush_serial()
{
    if (sim800_serial.serial == nullptr)
        return;
    while (sim800_serial.serial->available())
    {
        sim800_serial.serial->read();
    }
}

static error_type_t read(uint32_t timeout = MAX_TIMEOUT, const char *terminating_string = "")
{
    if (sim800_serial.serial == nullptr)
        return NULL_PARAMETER;
    uint32_t start_time = millis();
    uint32_t diff = 0;
    sim800_serial.response_length = 0;
    error_type_t status = FAILED;
    Serial.println("timeout value is: " + (String)(uint32_t)timeout);
    uint8_t length_of_terminating_string = strlen(terminating_string);
    uint8_t ok_length = strlen(OK_RESPONSE);
    uint8_t error_length = strlen(ERROR_RESPONSE);
    uint8_t offset = 0;
    while (diff < timeout)
    {
        diff = millis() - start_time;
        if (sim800_serial.serial->available())
        {
            if (sim800_serial.response_length >= READ_BUFFER_SIZE)
                break;
            sim800_read_buffer[sim800_serial.response_length] = sim800_serial.serial->read();
            // Serial.println("read serial: " + (String)sim800_read_buffer[sim800_serial.response_length]);
            if (strlen(terminating_string))
            {
                if (sim800_serial.response_length > length_of_terminating_string)
                {
                    offset = (sim800_serial.response_length - length_of_terminating_string);
                    if (memcmp((void *)terminating_string, (void *)(sim800_serial.response + offset), length_of_terminating_string) == 0)
                    {
                        Serial.println("reached end");
                        status = OK;
                        break;
                    }
                }
            }
            else
            {
                if (sim800_serial.response_length > ok_length)
                {
                    offset = (sim800_serial.response_length - ok_length);
                    if (memcmp((void *)OK_RESPONSE, (void *)(sim800_serial.response + offset), ok_length) == 0)
                    {
                        Serial.println("reached end");
                        status = OK;
                        break;
                    }
                }
                if (sim800_serial.response_length > error_length)
                {
                    offset = (sim800_serial.response_length - error_length);
                    if (memcmp((void *)ERROR_RESPONSE, (void *)(sim800_serial.response + offset), error_length) == 0)
                    {
                        Serial.println("reached end");
                        status = FAILED;
                        break;
                    }
                }
            }
            sim800_serial.response_length++;
            start_time = millis();
        }
    }
    Serial.println("buffer length: " + (String)READ_BUFFER_SIZE);
    Serial.println("length read: " + (String)sim800_serial.response_length);
    flush_serial();
    if (diff >= timeout)
    {
        Serial.println("timed out");
        return TIMED_OUT;
    }
    else if (sim800_serial.response_length > READ_BUFFER_SIZE)
    {
        Serial.println("buffer overflow");
        return BUFFER_OVERFLOW;
    }
    else
    {
        Serial.println("result is: " + (String)(int)status);
        return status;
    }
}

static error_type_t write(const char *write_buffer)
{
    if (sim800_serial.serial == nullptr || write_buffer == NULL)
        return NULL_PARAMETER;
    sim800_serial.serial->write(write_buffer);
    return OK;
}
static error_type_t write_and_read(const char *write_buffer, uint32_t read_timeout = MAX_TIMEOUT, const char *terminating_string = "")
{
    error_type_t err = write(write_buffer);
    if (err != OK)
    {
        return err;
    }
    return read(read_timeout, terminating_string);
}

static error_type_t ping()
{
    if (sim800_serial.serial == NULL)
        return NULL_PARAMETER;
    error_type_t err = write_and_read(COMMAND_PING, 20);
    if (err != OK)
        return err;
    for (uint16_t x = 0; x < sim800_serial.response_length; x++)
    {
        Serial.write((int)sim800_serial.response[x]);
    }
    return OK;
}
error_type_t sim800_init(sim800_t *sim800_object)
{
    if (sim800_object == NULL)
        return NULL_PARAMETER;
    if (sim800_object->tx_pin_number < MIN_DIGITAL_PIN_NUMBER || sim800_object->rx_pin_number > MAX_DIGITAL_PIN_NUMBER)
    {
        return INVALID_PIN_NUMBER;
    }
    error_type_t err = validate_rx(sim800_object);
    if (err != OK)
        return err;
    err = validate_baud(sim800_object);
    if (err != OK)
        return err;
    sim800_serial.serial = new SoftwareSerial(sim800_object->rx_pin_number, sim800_object->tx_pin_number);
    sim800_serial.serial->begin(sim800_object->baud_rate);
    memset(sim800_read_buffer, 0, READ_BUFFER_SIZE);
    sim800_serial.response = sim800_read_buffer;
    sim800_object->initialized = true;
    flush_serial();
    return OK;
}

error_type_t sim800_deinit(sim800_t *sim800_object)
{

    if (sim800_serial.serial != nullptr)
    {
        sim800_serial.serial->end();
    }
    return OK;
}
sim800_t *sim800_create(const sim800_config_t *config)
{
    if (config == NULL)
        return NULL;
    sim800_t *new_sim800_obj = (sim800_t *)malloc(sizeof(sim800_t));
    new_sim800_obj->tx_pin_number = config->tx_pin_number;
    new_sim800_obj->rx_pin_number = config->rx_pin_number;
    new_sim800_obj->baud_rate = config->baud_rate;
    new_sim800_obj->initialized = false;
    return new_sim800_obj;
}

error_type_t sim800_connect(sim800_t *sim800_object)
{
    if (sim800_object == NULL)
        return NULL_PARAMETER;
    if (!sim800_object->initialized)
        return INVALID_STATE;
    if (sim800_serial.serial == NULL)
        return NULL_PARAMETER;
    error_type_t err = ping();
    if (err != OK)
        return err;
    Serial.println("ping successful");
    err = write_and_read(COMMAND_CHECK_SMS_SUPPORT, 100);
    if (err != OK)
    {
        Serial.println("read SMS support failed");
        return err;
    }
    Serial.println("response:");
    for (uint16_t x = 0; x < sim800_serial.response_length; x++)
    {
        Serial.write((int)sim800_serial.response[x]);
    }
    return OK;
}
error_type_t sim800_send_sms(sim800_t *sim800_object, char *phone_number, char *message)
{
    if (sim800_object == NULL || phone_number == NULL || message == NULL)
        return NULL_PARAMETER;
    if (!sim800_object->initialized)
        return INVALID_STATE;
    if (sim800_serial.serial == NULL)
        return NULL_PARAMETER;
    flush_serial();
    error_type_t err = write_and_read(COMMAND_SET_GSM, 100);
    if (err != OK)
    {
        Serial.println("GSM set failed");
        return err;
    }
    char sms_command_with_number[MESSAGE_SEND_BUFFER_SIZE] = "";
    char sms_term[] = SMS_TERMINATOR;
    COMMAND_CONSTRUCT_SMS_NUMBER(sms_command_with_number, phone_number);
    Serial.println("constructed message is: ");
    Serial.println((String)sms_command_with_number);
    err = write_and_read(sms_command_with_number, 100, ">");
    if (err != OK)
    {
        Serial.println("SMS number set failed");
        return err;
    }
    memset(sms_command_with_number, 0, MESSAGE_SEND_BUFFER_SIZE);
    COMMAND_CONSTRUCT_SMS(sms_command_with_number, message, sms_term);
    Serial.println("constructed message is: ");
    Serial.println((String)sms_command_with_number);
    err = write_and_read(sms_command_with_number, 60000);
    if (err != OK)
    {
        Serial.println("SMS send failed");
        return err;
    }
    return OK;
}

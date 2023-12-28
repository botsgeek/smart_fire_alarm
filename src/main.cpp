#include <Arduino.h>
#include "lm75.h"

// Declare lm75_config as a global variable
lm75_config_t lm75_config = {
    .i2c_addr = 0x48,
    .mode = LM75_COMPARATOR_MODE,
    .os_pin_number = 2,
    .polarity = LM75_POLARITY_ACTIVE_LOW,
    .tolerance = LM75_TOLERANCE_ONE_SAMPLE,
    .resolution = LM75_RESOLUTION_12_BITS
};

// Declare lm75_object as a global variable
lm75_t* lm75_object;

void setup() {
    Serial.begin(9600);  // Initialize Serial communication

    // Initialize LM75
    lm75_object = lm75_create(&lm75_config);
    if (lm75_object == NULL) {
        // Handle memory allocation error
        return;
    }

    error_type_t init_result = lm75_init_comparator_mode(lm75_object);
    if (init_result != OK) {
        // Handle initialization error
        free(lm75_object);
        return;
    }

    // Set thresholds for Comparator Mode
    lm75_set_thresholds(lm75_object, 25.0, 26.0);  // Set hysteresis and overtemperature thresholds
}

void loop() {
    // Read temperature
    float temp_value = lm75_read(lm75_object);

    // Check if lm75_object is not NULL before accessing its members
    if (lm75_object != NULL) {
        Serial.print("Raw Temperature Register Value: ");
        unsigned temp_register = lm75_getReg(lm75_object, LM75_REGISTER_TEMP);
        Serial.println(temp_register);

        Serial.print("Temperature: ");
        Serial.print(temp_value);
        Serial.println(" °C");

        // Check if the temperature is above the set threshold
        if (temp_value > 26.0) {
            Serial.print("Temperature is above threshold! ");
            Serial.println(temp_value);
        }
    }

    // Delay for 2 seconds
    delay(2000);
    // Your main loop code here
}
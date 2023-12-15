#include <Arduino.h>
#include <Wire.h>
#include "lm75.h"


void lm75_init(lm75_config_t* lm75_config, uint8_t i2c_addr, lm75_resolution_t lm75_resolution) {
    // Initialize the I2C communication
    // Assuming Wire.begin() initializes the I2C library; replace it with your specific initialization code
    Wire.begin();

    // Populate lm75_config structure with initialization parameters
    lm75_config->i2c_addr = i2c_addr;
    lm75_config->polarity = LM75_POLARITY_ACTIVE_LOW;  // Set an initial polarity (you can change this if needed)
    lm75_config->tolerance = LM75_TOLERANCE_ONE_SAMPLE;  // Set an initial tolerance (you can change this if needed)
    lm75_config->resolution = LM75_RESOLUTION_9_BITS;
    lm75_config->configured = false;
    // Configure LM75 based on the provided parameters
    lm75_configure(lm75_config, LM75_COMPARATOR_MODE, LM75_TOLERANCE_ONE_SAMPLE, LM75_RESOLUTION_9_BITS, LM75_POLARITY_ACTIVE_LOW);
}
void lm75_deinit(lm75_config_t* lm75_config, uint8_t i2c_addr) {
    // Leave it blank if no specific cleanup is needed
}


void lm75_configure(lm75_config_t* lm75_config, lm75_mode_t mode, lm75_tolerance_t fault_tolerance, lm75_resolution_t resolution, lm75_polarity_t polarity) {
    lm75_CfgRegister lm75_regv;
    lm75_regv.mbyte = 0;  // Initialize to 0 to set reserved bits to 0

    // Populate the lm75_CfgRegister structure with the provided parameters
    lm75_regv.mbits.thermostat_mode = mode;
    lm75_regv.mbits.thermostat_fault_tolerance = fault_tolerance;
    lm75_regv.mbits.resolution = resolution;
    lm75_regv.mbits.thermostat_output_polarity = polarity;

    // Set the configuration register in the LM75
    lm75_setReg(lm75_config, LM75_REGISTER_CONFIG,  lm75_regv.mbyte);
    lm75_config->configured = true;
}

float lm75_read(lm75_config_t* lm75_config)
{
     if (!lm75_config->configured) {
        Serial.println("LM75 not configured. Please configure before reading temperature.");
        return 0.0;  // Or any other appropriate value indicating an error
    }
    uint16_t tempX = lm75_getReg(lm75_config, LM75_REGISTER_TEMP);
    int16_t tempS = (int16_t)tempX;  // Convert to signed int

    float lm75_temp = (float)tempS / 256.0F;
    return lm75_temp;
}



unsigned lm75_getReg(lm75_config_t* lm75_config, lm75_register_t lm75_reg)
{
    unsigned result = 0xFFFF;
    Wire.beginTransmission(lm75_config->i2c_addr);
    Wire.write((uint8_t)lm75_reg);
    Wire.endTransmission();
    Wire.requestFrom(lm75_config->i2c_addr, (uint8_t)(lm75_reg == LM75_REGISTER_CONFIG ? 1 : 2));

    if (Wire.available())
    {
        result = Wire.read();
        if (lm75_reg != LM75_REGISTER_CONFIG)
        {
            result = (result << 8) | Wire.read();
        }
    }

    return result;
}

void lm75_setReg(lm75_config_t* lm75_config, lm75_register_t lm75_reg, uint8_t newValue)
{
    Wire.beginTransmission(lm75_config->i2c_addr);
    Wire.write((uint8_t)lm75_reg);
    Wire.write(newValue);
    Wire.endTransmission();
}
// lm75.c

#include <Wire.h>
#include "lm75.h"
#include <Arduino.h>

void initialize(TempI2C_LM75* lm75, uint8_t i2c_addr, Resolution resolution) {
    Wire.begin();
    lm75->i2c_addr = i2c_addr;
    configure(lm75, comparator_mode, one_sample, resolution, active_low);
}

void deinitialize(TempI2C_LM75* lm75) {
    // Leave it blank if no specific cleanup is needed
}

void configure(TempI2C_LM75* lm75, ThermostatMode mode, ThermostatFaultTolerance fault_tolerance, Resolution resolution, OSPolarity polarity) {
    CfgRegister regv;
    regv.mbyte = 0;  // Initialize to 0 to set reserved bits to 0

    regv.mbits.thermostat_mode = mode;
    regv.mbits.thermostat_fault_tolerance = fault_tolerance;
    regv.mbits.resolution = resolution;
    regv.mbits.thermostat_output_polarity = polarity;

    setReg(lm75, config_reg, regv.mbyte);
}

float readTemperature(TempI2C_LM75* lm75) {
    union {
        unsigned short tempX;
        short tempS;
    } temperature;

    temperature.tempX = getReg(lm75, temp_reg);
    return (temperature.tempS / 256.0F);
}

unsigned getReg(TempI2C_LM75* lm75, LM75Register reg) {
    unsigned Result = 0xFFFF;

    Wire.beginTransmission(lm75->i2c_addr);
    Wire.write(reg);
    Wire.endTransmission();

    Wire.requestFrom(lm75->i2c_addr, uint8_t(2));
    if (Wire.available()) {
        Result = Wire.read();
        if (reg != config_reg) {
            Result = (Result << 8) | Wire.read();
        }
    }

    return Result;
}

void setReg(TempI2C_LM75* lm75, LM75Register reg, uint8_t newValue) {
    Wire.beginTransmission(lm75->i2c_addr);
    Wire.write(reg);
    Wire.write(newValue);
    Wire.endTransmission();
}

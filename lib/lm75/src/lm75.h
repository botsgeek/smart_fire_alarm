// lm75.h

#ifndef TempI2C_LM75_h
#define TempI2C_LM75_h

#include <inttypes.h>
#include <Wire.h>

typedef enum { nine_bits = 0, ten_bits, eleven_bits, twelve_bits } Resolution;
typedef enum { comparator_mode = 0, interrupt_mode } ThermostatMode;
typedef enum { one_sample = 0, two_samples, four_samples, six_samples } ThermostatFaultTolerance;
typedef enum { active_low = 0, active_high } OSPolarity;

typedef enum { temp_reg = 0, config_reg, THyst_reg, TOS_reg } LM75Register;

typedef union _CfgRegister {
    struct {
        uint8_t shutdown : 1;
        uint8_t thermostat_mode : 1;
        uint8_t thermostat_output_polarity : 1;
        uint8_t thermostat_fault_tolerance : 2;
        uint8_t resolution : 2;
        uint8_t reserved : 1;
    } mbits;

    uint8_t mbyte;
} CfgRegister;

typedef struct {
    uint8_t i2c_addr;
} TempI2C_LM75;

void initialize(TempI2C_LM75* lm75, uint8_t i2c_addr, Resolution resolution);
void deinitialize(TempI2C_LM75* lm75);

void configure(TempI2C_LM75* lm75, ThermostatMode mode, ThermostatFaultTolerance fault_tolerance, Resolution resolution, OSPolarity polarity);
float readTemperature(TempI2C_LM75* lm75);

unsigned getReg(TempI2C_LM75* lm75, LM75Register reg);
void setReg(TempI2C_LM75* lm75, LM75Register reg, uint8_t newValue);

#endif

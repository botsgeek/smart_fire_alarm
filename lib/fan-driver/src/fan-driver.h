#ifndef _FAN_DRIVER_H_
#define _FAN_DRIVER_H_
#ifdef __cplusplus
extern "C" {
#endif
typedef enum{
    INITIALIZE_FAN,
    FAN_SPEED,
    DEACTIVATE_FAN,
}fan_state;
void activate_fan();
void validate_before_activating();
#ifdef __cplusplus
}
#endif

#endif
#ifndef _COMMON_HEADERS_H_
#define _COMMON_HEADERS_H_
#ifdef __cplusplus
extern "C"
{
#endif
#define SENSOR_INVALID_VALUE (-1)
    typedef enum
    {
        OK,
        NULL_PARAMETER,
        INVALID_PARAMETER,
        INVALID_PIN_NUMBER,
        INVALID_STATE,
        INVALID_MODE,
        FAILED

    } error_type_t;
#ifdef __cplusplus
}
#endif
#endif
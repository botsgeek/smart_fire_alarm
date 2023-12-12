#ifndef _COMMON_HEADERS_H_
#define _COMMON_HEADERS_H_
#ifdef __cplusplus
extern "C"
{
#endif
    typedef enum
    {
        OK,
        INVALID_PARAMETER,
        INVALID_PIN_NUMBER,
        FAILED

    } error_type_t;
#ifdef __cplusplus
}
#endif
#endif
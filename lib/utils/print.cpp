#include <print.h>
#include <Arduino.h>
void debug_printf(const char* format_string, ...) {
    constexpr int buffer_size = 50;
    char buffer[buffer_size];

    va_list args; // Declare a va_list to handle variadic arguments
    va_start(args, format_string); // Initialize the va_list with the format_string

    vsnprintf(buffer, buffer_size, format_string, args); // Safely format the string into the buffer
    va_end(args); // Clean up the va_list

    Serial.println(buffer); // Print the formatted string to Serial
}
#include <Arduino.h>
#include "buzzer.h"

#define BUZZER_PIN 5  // Replace with your actual buzzer pin
#define PWM_DUTY_CYCLE 200  // Adjust the PWM duty cycle as needed
#define DELAY_BETWEEN_TONES 100  // Adjust the delay between waves as needed
#define DELAY_BETWEEN_WAVE 5000
buzzer_t* myBuzzer;

const unsigned int toneDutyCycles[] = {128, 150, 180, 200};
void setup() {
    buzzer_config_t buzzerConfig = {.buzzer_pin = BUZZER_PIN};
    myBuzzer = buzzer_create(&buzzerConfig);

    if (myBuzzer != NULL) {
        buzzer_init(myBuzzer);
        // Other setup code if needed
    } else {
        // Handle error if object creation fails
    }
}

// void loop() {
//     // Start the buzzer with the specified PWM duty cycle
//     buzzer_start(myBuzzer, PWM_DUTY_CYCLE);

//     delay(DELAY_BETWEEN_WAVE);

//     // Stop the buzzer
//     buzzer_stop(myBuzzer);

//     //delay(DELAY_BETWEEN_WAVE);
// }

void loop() {
    // Iterate through the array of duty cycles to play different tones
    for (unsigned int i = 0; i < sizeof(toneDutyCycles) / sizeof(toneDutyCycles[0]); ++i) {
        // Start the buzzer with the current duty cycle
        buzzer_start(myBuzzer, toneDutyCycles[i]);

        delay(DELAY_BETWEEN_TONES);

        // Stop the buzzer
        buzzer_stop(myBuzzer);

        //delay(DELAY_BETWEEN_WAVE);
    }
}

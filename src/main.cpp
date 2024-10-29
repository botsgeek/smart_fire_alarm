#include <Arduino.h>
#include <Arduino_FreeRTOS.h>
#include <sim800.h>

sim800_t* sim800_driver;
void setup()
{
  // put your setup code here, to run once:
  Serial.begin(9600);
  
   sim800_config_t config = {
        .tx_pin_number = 13,
        .rx_pin_number = 10,
        .rst_pin_number = 2,
        .baud_rate = 9600
   };

   sim800_driver= sim800_create(&config);
   if (sim800_driver == NULL)
   {
    Serial.println("Failed to create sim800 obj");
    exit(1);
   }
    error_type_t err;
    err = sim800_connect(sim800_driver);
    if (err != OK)
    {
      Serial.println("sim800 failed to connect");
      exit(1);
    }

    // err = Validate_rst(sim800_driver);
    // if (err != OK)
    // {
    //   Serial.println("failed to validate rst");
    //   exit(1);
    // }
    // err = sim800_reset(sim800_driver);
    // if (err != OK)
    // {
    //   Serial.println("failed to reset sim800");
    //   delay(20);
    // }
    

    //  char phone_number[] = "+2347068666080"; // Replace with actual phone number
    // char message[] = "Hello World";
    // err = sim800_send_sms(sim800_driver, phone_number, message);
    // if (err != OK) {
    //     Serial.println("Failed to send SMS.");
    //     exit(1);
    // } 
    
    

         

}

void loop()
{
  // put your main code here, to run repeatedly:
}

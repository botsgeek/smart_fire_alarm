#include <Arduino.h>
#include <unity.h>
#include <state-machine.h>
#define TAG "TEST"

void setUp(void)
{
  // set stuff up here
}

void tearDown(void)
{
  // clean stuff up here
}

void setup()
{
  Serial.begin(9600);
  // should be the same value as for the `test_speed` option in "platformio.ini"
  // default value is test_speed=115200
  delay(2000);

  runUnityTest();
}
void loop()
{
}

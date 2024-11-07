#include <unity.h>
#include <Arduino.h>
#include <lm75.h>
#define TAG "TEST"

lm75_t* my_lm75;
lm75_t* wrong_lm75;

void setUp(void)
{
  // set stuff up here
}

void tearDown(void)
{
  // clean stuff up here
}

void test_create(void){
    lm75_config_t config = {
        .i2c_addr = 0x048,
        .mode = LM75_COMPARATOR_MODE,
        .os_pin_number = 2,
        .polarity = LM75_POLARITY_ACTIVE_LOW,
        .tolerance = LM75_TOLERANCE_ONE_SAMPLE,
        .resolution = LM75_RESOLUTION_9_BITS};
    my_lm75 = lm75_create(&config);
    TEST_ASSERT_NOT_EQUAL(NULL,my_lm75);
    //wrong_lm75 = lm75

}

int runUnityTest(void){
    UNITY_BEGIN();
    RUN_TEST(test_create);
    return UNITY_END();
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

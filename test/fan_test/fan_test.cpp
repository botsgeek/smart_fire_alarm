#include <unity.h>
#include <Arduino.h>
#include <fan-driver.h>
#define TAG "TEST"

fan_t* my_fan;
fan_t* fake_my_fan;

void setUp(void)
{
  // set stuff up here
}

void tearDown(void)
{
  // clean stuff up here
}

void test_create(void){
    fan_config_t config ={.fan_pin_number = 5};
    my_fan = fan_create(&config);
    TEST_ASSERT_NOT_EQUAL(NULL, my_fan);
    fake_my_fan = fan_create(NULL);
    TEST_ASSERT_EQUAL(NULL, my_fan);

}
void test_wrong_fan_init(void){
    fan_config_t config ={.fan_pin_number = 5};
    my_fan = fan_create(&config);
    TEST_ASSERT_NOT_EQUAL(NULL,my_fan);
    error_type_t err = fan_init(my_fan);
    TEST_ASSERT_EQUAL(INVALID_PIN_NUMBER,err);
    free(my_fan);

    fan_config_t config1 ={.fan_pin_number = 11};
    my_fan = fan_create(&config1);
    TEST_ASSERT_NOT_EQUAL(NULL, my_fan);
    err = fan_init(my_fan);
    TEST_ASSERT_EQUAL(INVALID_PIN_NUMBER,err);
    free(my_fan);

    err = fan_init(NULL);
    TEST_ASSERT_EQUAL(NULL_PARAMETER, err);

}

void test_right_fan_init(void){
    fan_config_t config = {.fan_pin_number = 5};
    my_fan = fan_create(&config);
    TEST_ASSERT_NOT_EQUAL(NULL,my_fan);
    error_type_t err = fan_init(my_fan);
    TEST_ASSERT_EQUAL(INVALID_PIN_NUMBER, err);
    free(my_fan);

    fan_config_t config2 = {.fan_pin_number = 40};
    my_fan = fan_create(&config2);
    TEST_ASSERT_NOT_EQUAL(NULL, my_fan);
    err = fan_init(my_fan);
    TEST_ASSERT_EQUAL(INVALID_PIN_NUMBER, err);
    free(my_fan);

    err = fan_init(NULL);
    TEST_ASSERT_EQUAL(NULL_PARAMETER, err);

}
int runUnityTests(void){
    UNITY_BEGIN();
    RUN_TEST(test_create);
    RUN_TEST(test_wrong_fan_init);
    RUN_TEST(test_right_fan_init);
    return UNITY_END();
}
void setup()
{
  Serial.begin(9600);
  // should be the same value as for the `test_speed` option in "platformio.ini"
  // default value is test_speed=115200
  delay(2000);

  runUnityTests();
}
void loop()
{
}
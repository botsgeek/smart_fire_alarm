#include <unity.h>
#include <Arduino.h>
#include <fan-driver.h>
#define TAG "TEST"

fan_t* my_fan;
fan_t* fake_fan;

void setUp(void)
{
  // set stuff up here
}

void tearDown(void)
{
  // clean stuff up here
}

void test_fan_create(void){
    fan_config_t config ={.fan_pin_number = 5};
    my_fan = fan_create(&config);
    TEST_ASSERT_NOT_EQUAL(NULL, my_fan);
    fake_fan = fan_create(NULL);
    TEST_ASSERT_EQUAL(NULL, fake_fan);
    free(my_fan);
}
void test_fan_init(void){
    fan_config_t config ={.fan_pin_number = 5};
    my_fan = fan_create(&config);
    error_type_t err = fan_init(my_fan);
    TEST_ASSERT_EQUAL(OK,err);
    free(my_fan);

    fan_config_t config1 ={.fan_pin_number = 11};
    my_fan = fan_create(&config1);
    err = fan_init(my_fan);
    TEST_ASSERT_EQUAL(INVALID_PIN_NUMBER, err);
    free(my_fan);
    err = fan_init(NULL);
    TEST_ASSERT_EQUAL(NULL_PARAMETER,err);
    
    

}

void test_fan_speed(void){
  uint8_t fanspeed = 100;
  fan_config_t config = {.fan_pin_number = 3};
  my_fan = fan_create(&config);
  error_type_t err = set_fanspeed(my_fan, fanspeed);
  TEST_ASSERT_EQUAL(INVALID_STATE,err);
  err = fan_init(my_fan);
  TEST_ASSERT_EQUAL(OK,err);
  err = set_fanspeed(NULL, fanspeed);
  TEST_ASSERT_EQUAL(NULL_PARAMETER,err);
  free(my_fan);
  
}

void test_fan_deinit(void){
  uint8_t fanspeed=100;
  fan_config_t config = {.fan_pin_number = 3};
  my_fan = fan_create(&config);

  error_type_t err = set_fanspeed(my_fan,fanspeed);
  TEST_ASSERT_EQUAL(INVALID_STATE,err);
  err = deinit(NULL);
  TEST_ASSERT_EQUAL(NULL_PARAMETER,err);

  err = deinit(my_fan);
  TEST_ASSERT_EQUAL(INVALID_STATE,err);

  err = fan_init(my_fan);
  err = deinit(my_fan);
  TEST_ASSERT_EQUAL(OK,err);
  
  err = set_fanspeed(my_fan,fanspeed);
  TEST_ASSERT_EQUAL(INVALID_STATE,err);
  free(my_fan);
}

void test_fan_Destroy(void){
  error_type_t err = destroy(NULL);
  TEST_ASSERT_EQUAL(NULL_PARAMETER, err);
  fan_config_t config = {.fan_pin_number = 3};
  my_fan = fan_create(&config);

  err = destroy(&my_fan);
  TEST_ASSERT_EQUAL(OK,err);
  TEST_ASSERT_EQUAL(NULL,my_fan);
}
int runUnityTests(void){
    UNITY_BEGIN();
    RUN_TEST(test_fan_create);
    RUN_TEST(test_fan_init);
    RUN_TEST(test_fan_speed);
    RUN_TEST(test_fan_deinit);
    RUN_TEST(test_fan_Destroy);
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
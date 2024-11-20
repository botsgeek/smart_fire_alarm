#include <Arduino.h>
#include <unity.h>
#include <pump-driver.h>
#define TAG "TEST"

pump_t* my_pump;
pump_t * bad_pump;


void setUp(void)
{
  // set stuff up here
}

void tearDown(void)
{
  // clean stuff up here
}

void test_create(void){
    pump_config_t config = {.pump_pin_number = 7};
    my_pump = pump_create(&config);
    TEST_ASSERT_NOT_EQUAL(NULL, my_pump);
    bad_pump = pump_create(NULL);
    TEST_ASSERT_EQUAL(NULL,bad_pump);
}

void test_init(void){
  // check if it init with vaild pin number
  pump_config_t config1 = {.pump_pin_number = 6};
  my_pump = pump_create(&config1);
  error_type_t err = pump_init(my_pump);
  TEST_ASSERT_EQUAL(OK, err);
  free(my_pump);

  // check if a wrong pin number is used
  pump_config_t config2 = {.pump_pin_number = 12};
  my_pump = pump_create(&config2);
  err = pump_init(my_pump);
  TEST_ASSERT_EQUAL(INVALID_PIN_NUMBER,err);
  free(my_pump);
  err = pump_init(NULL);
  TEST_ASSERT_EQUAL(NULL_PARAMETER,err);
}

void test_on(void){
  pump_config_t config3 = {.pump_pin_number = 5};
  my_pump = pump_create(&config3);
  error_type_t err1 = pump_on(my_pump);
  TEST_ASSERT_EQUAL(INVALID_STATE, err1);
  err1 = pump_init(my_pump);
  TEST_ASSERT_EQUAL(OK, err1);
  err1 = pump_on(NULL);
  TEST_ASSERT_EQUAL(NULL_PARAMETER, err1);
  free(my_pump);
  }

void test_off(void){
  pump_config_t config3 = {.pump_pin_number = 4};
  my_pump = pump_create(&config3);
  error_type_t err1 = pump_off(my_pump);
  TEST_ASSERT_EQUAL(INVALID_STATE, err1);
  err1 = pump_init(my_pump);
  TEST_ASSERT_EQUAL(OK, err1);
  err1 = pump_off(NULL);
  TEST_ASSERT_EQUAL(NULL_PARAMETER, err1);
  free(my_pump);
}

void test_deinit(void){
  pump_config_t config3 = {.pump_pin_number = 7};
  my_pump = pump_create(&config3);

   
  error_type_t err = pump_on(my_pump);
  TEST_ASSERT_EQUAL(INVALID_STATE, err);
  err = pump_off(my_pump);
  TEST_ASSERT_EQUAL(INVALID_STATE, err);
  err = pump_deinit(NULL);
  TEST_ASSERT_EQUAL(NULL_PARAMETER,err);

  err = pump_deinit(my_pump);
  TEST_ASSERT_EQUAL(INVALID_STATE,err);

  err = pump_init(my_pump);
  err = pump_deinit(my_pump);
  TEST_ASSERT_EQUAL(OK, err);

  err = pump_on(my_pump);
  TEST_ASSERT_EQUAL(INVALID_STATE, err);
  err = pump_off(my_pump);
  TEST_ASSERT_EQUAL(INVALID_STATE, err);
  free(my_pump);
 
}

void test_destroy(void){
  error_type_t err = pump_destroy(NULL);
  TEST_ASSERT_EQUAL(NULL_PARAMETER,err);

  pump_config_t config3 = {.pump_pin_number = 7};
  my_pump = pump_create(&config3);

  err = pump_destroy(&my_pump);
  TEST_ASSERT_EQUAL(OK,err);
  TEST_ASSERT_EQUAL(NULL,my_pump); 

}

int runUnityTest(){
    UNITY_BEGIN();
    RUN_TEST(test_create);
    RUN_TEST(test_init);
    RUN_TEST(test_on);
    RUN_TEST(test_off);
    RUN_TEST(test_deinit);
    RUN_TEST(test_destroy);
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


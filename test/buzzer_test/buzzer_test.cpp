#include <Arduino.h>
#include <unity.h>
#include <buzzer.h>
#define TAG "TEST"

buzzer_t* my_buzzer;
buzzer_t* my_fake_buzzer;

 uint8_t pwn_cycle = 1;
 uint32_t duration;
 uint32_t total_time;

void setUp(void)
{
  // set stuff up here
}

void tearDown(void)
{
  // clean stuff up here
}

void test_buzzer_config(void){
    buzzer_config_t config ={.buzzer_pin = 13};
    my_buzzer = buzzer_create(&config);
    TEST_ASSERT_NOT_EQUAL(NULL,my_buzzer);
    my_fake_buzzer = buzzer_create(NULL);
    TEST_ASSERT_EQUAL(NULL, my_fake_buzzer);
    free(my_buzzer);

}

void test_buzzer_init(void){
  error_type_t err = buzzer_init(NULL);
  TEST_ASSERT_EQUAL(NULL_PARAMETER,err);

   buzzer_config_t config ={.buzzer_pin = 6};
    my_buzzer = buzzer_create(&config);
    err = buzzer_init(my_buzzer);
    TEST_ASSERT_EQUAL(OK,err);

    buzzer_config_t config1 ={.buzzer_pin = A4};
    my_buzzer = buzzer_create(&config1);
    err = buzzer_init(my_buzzer);
    TEST_ASSERT_EQUAL(INVALID_PIN_NUMBER,err);
    free(my_buzzer);
}

void test_buzzer_start(void){
 
  error_type_t err = buzzer_start(NULL,pwn_cycle);
  TEST_ASSERT_EQUAL(NULL_PARAMETER, err);

   buzzer_config_t config ={.buzzer_pin = 2};
    my_buzzer = buzzer_create(&config);
    err = buzzer_init(my_buzzer);
    TEST_ASSERT_EQUAL(OK,err);
    err = buzzer_start(my_buzzer, pwn_cycle);
    TEST_ASSERT_EQUAL(OK, err);

    buzzer_config_t config1 ={.buzzer_pin = A2};
    my_buzzer = buzzer_create(&config1);
    err = buzzer_init(my_buzzer);
    TEST_ASSERT_EQUAL(INVALID_PIN_NUMBER,err);
    err = buzzer_start(my_buzzer,pwn_cycle);
    TEST_ASSERT_EQUAL(INVALID_STATE, err);
    free(my_buzzer);
}

void test_buzzer_stop(void){
  error_type_t err = buzzer_stop(NULL);
  TEST_ASSERT_EQUAL(NULL_PARAMETER,err);

  buzzer_config_t config ={.buzzer_pin = 12};
    my_buzzer = buzzer_create(&config);
    err = buzzer_init(my_buzzer);
    TEST_ASSERT_EQUAL(OK,err);
    err = buzzer_stop(my_buzzer);
    TEST_ASSERT_EQUAL(OK, err);

    buzzer_config_t config1 ={.buzzer_pin = 1};
    my_buzzer = buzzer_create(&config1);
    err = buzzer_init(my_buzzer);
    TEST_ASSERT_EQUAL(INVALID_PIN_NUMBER,err);
    err = buzzer_stop(my_buzzer);
    TEST_ASSERT_EQUAL(INVALID_STATE, err);
    free(my_buzzer);
}

void test_buzzer_tone(void){
 
  error_type_t err = buzzer_tone(NULL, duration, total_time);
  TEST_ASSERT_EQUAL(NULL_PARAMETER, err);

  buzzer_config_t config ={.buzzer_pin = 10};
    my_buzzer = buzzer_create(&config);
    err = buzzer_init(my_buzzer);
    TEST_ASSERT_EQUAL(OK,err);
    err = buzzer_tone(my_buzzer,duration,total_time);
    TEST_ASSERT_EQUAL(OK, err);

    buzzer_config_t config2 ={.buzzer_pin = A5};
    my_buzzer = buzzer_create(&config2);
    err = buzzer_init(my_buzzer);
    TEST_ASSERT_EQUAL(INVALID_PIN_NUMBER,err);
    err = buzzer_stop(my_buzzer);
    TEST_ASSERT_EQUAL(INVALID_STATE, err);
    free(my_buzzer);
}

void test_buzzer_deinit(void){
   buzzer_config_t config2 ={.buzzer_pin = 13};
    my_buzzer = buzzer_create(&config2);
  error_type_t err = buzzer_start(my_buzzer,pwn_cycle);
  err = buzzer_stop(my_buzzer);
  err = buzzer_tone(my_buzzer,duration,total_time);
  TEST_ASSERT_EQUAL(INVALID_STATE,err);
  err = buzzer_deinit(NULL);
  TEST_ASSERT_EQUAL(NULL_PARAMETER, err);

  err = buzzer_deinit(my_buzzer);
  TEST_ASSERT_EQUAL(INVALID_STATE, err);

  err = buzzer_init(my_buzzer);
  err = buzzer_deinit(my_buzzer);
  TEST_ASSERT_EQUAL(OK,err);
  free(my_buzzer);

}

void test_buzzer_Destroy(void){
  error_type_t err = buzzer_destroy(NULL);
  TEST_ASSERT_EQUAL(NULL_PARAMETER, err);

  buzzer_config_t config2 ={.buzzer_pin = A5};
  my_buzzer = buzzer_create(&config2);
  err = buzzer_destroy(&my_buzzer);
  TEST_ASSERT_EQUAL(OK,err);
  TEST_ASSERT_EQUAL(NULL,my_buzzer);
  

}

int runUnityTests(void){
  UNITY_BEGIN();
  RUN_TEST(test_buzzer_config);
  RUN_TEST(test_buzzer_init);
  RUN_TEST(test_buzzer_start);
  RUN_TEST(test_buzzer_stop);
  RUN_TEST(test_buzzer_tone);
  RUN_TEST(test_buzzer_deinit);
  RUN_TEST(test_buzzer_Destroy);

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
#include <Arduino.h>
#include <unity.h>
#include <lm75-manager.h>
#include <lm75.h>
#define TAG "TEST"

lm75_manager_t* my_lm75_manager;
lm75_manager_t* fake_lm75_manager;
lm75_t* my_lm75;


void setUp(void)
{
  // set stuff up here
}

void tearDown(void)
{
  // clean stuff up here
}

void test_lm75_manager_create(void){
  lm75_manager_config_t lm75_manager_config = {.lm75_threshold = 30,
  .lm75_obj = my_lm75};
  my_lm75_manager = lm75_manager_create(&lm75_manager_config);
  TEST_ASSERT_NOT_EQUAL(NULL, my_lm75_manager);
  fake_lm75_manager = lm75_manager_create(NULL);
  TEST_ASSERT_EQUAL(NULL,fake_lm75_manager);
}

void test_lm75_manager_init(void){
  error_type_t err = lm75_manager_init(NULL);
  TEST_ASSERT_EQUAL(NULL_PARAMETER, err);

   lm75_manager_config_t lm75_manager_config = {.lm75_threshold = 30,
  .lm75_obj = my_lm75};
  my_lm75_manager = lm75_manager_create(&lm75_manager_config);
  err = lm75_manager_init(my_lm75_manager);
  TEST_ASSERT_EQUAL(OK, err);
  free(my_lm75_manager);

}

void test_lm75_manager_above_threshold(void){
  bool state;
  error_type_t err = lm75_manager_above_threshold(NULL, &state);
  TEST_ASSERT_EQUAL(NULL_PARAMETER, err);

  lm75_manager_config_t lm75_manager_config = {.lm75_threshold = 30,
  .lm75_obj = NULL};
  my_lm75_manager = lm75_manager_create(&lm75_manager_config);
  err = lm75_manager_above_threshold(my_lm75_manager, &state);
  TEST_ASSERT_EQUAL(INVALID_STATE,err);

err = lm75_manager_init(my_lm75_manager);
err = lm75_manager_above_threshold(my_lm75_manager, &state);
TEST_ASSERT_EQUAL(OK,err);  

}

void test_lm75_manager_deinit(void){
  bool state;
  error_type_t err;

   lm75_manager_config_t lm75_manager_config = {.lm75_threshold = 30,
  .lm75_obj = NULL};
  my_lm75_manager = lm75_manager_create(&lm75_manager_config);
  err = lm75_manager_above_threshold(my_lm75_manager, &state);
  TEST_ASSERT_EQUAL(INVALID_STATE,err);
  err = lm75_manager_deinit(NULL);
  TEST_ASSERT_EQUAL(NULL_PARAMETER,err);

  err = lm75_manager_deinit(my_lm75_manager);
  TEST_ASSERT_EQUAL(INVALID_STATE, err);

  err = lm75_manager_init(my_lm75_manager);
  err = lm75_manager_deinit(my_lm75_manager);
  TEST_ASSERT_EQUAL(OK, err);

  free(my_lm75_manager);

}

void test_lm75_manager_destroy(void){
  error_type_t err = lm75_manager_destroy(NULL);
  TEST_ASSERT_EQUAL(NULL_PARAMETER, err);

  err = lm75_manager_destroy(&my_lm75_manager);
  TEST_ASSERT_EQUAL(OK,err);
  TEST_ASSERT_EQUAL(NULL,my_lm75_manager);

}

int runUnityTest(void){
  UNITY_BEGIN();
  RUN_TEST(test_lm75_manager_create);
  RUN_TEST(test_lm75_manager_init);
  RUN_TEST(test_lm75_manager_above_threshold);
  RUN_TEST(test_lm75_manager_deinit);
  RUN_TEST(test_lm75_manager_destroy);
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

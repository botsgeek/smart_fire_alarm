#include <Arduino.h>
#include <unity.h>
#include <mq2-manager.h>
#include <mq2.h>
#define TAG "TEST"

mq2_manager_t* my_mq2_manager;
mq2_manager_t* fake_mq2_manager;
mq2_t* my_mq2;

void setUp(void)
{
  // set stuff up here
}

void tearDown(void)
{
  // clean stuff up here
}

void test_mq2_manager_create(void){
    mq2_manager_config_t mq2_manager_config = { .mq2_threshold = 100,
    .mq2_object = my_mq2};
    my_mq2_manager = mq2_manager_create(&mq2_manager_config);
    TEST_ASSERT_NOT_EQUAL(NULL,my_mq2_manager);
    fake_mq2_manager = mq2_manager_create(NULL);
    TEST_ASSERT_EQUAL(NULL,fake_mq2_manager);
}

void test_mq2_manager_init(void){
  error_type_t err = mq2_manager_init(NULL);
  TEST_ASSERT_EQUAL(NULL_PARAMETER, err);

  mq2_manager_config_t mq2_manager_config = {.mq2_threshold = 100,
  .mq2_object = my_mq2};
  my_mq2_manager =mq2_manager_create(&mq2_manager_config);
  err = mq2_manager_init(my_mq2_manager);
  TEST_ASSERT_EQUAL(OK,err);

  free(my_mq2_manager);  
}

void test_mq2_manager_above_threshold(void){
  bool state;
  error_type_t err = mq2_manager_above_threshold(NULL, &state);
  TEST_ASSERT_EQUAL(NULL_PARAMETER, err);

  mq2_manager_config_t mq2_manager_config = {.mq2_threshold = 100,
  .mq2_object = my_mq2};
  my_mq2_manager = mq2_manager_create(&mq2_manager_config);
  err =mq2_manager_init(my_mq2_manager);
  err = mq2_manager_above_threshold(my_mq2_manager,&state);
  TEST_ASSERT_EQUAL(OK, err);

  mq2_manager_config_t mq2_manager_config1 = {.mq2_threshold = 100,
  .mq2_object = NULL};
  my_mq2_manager = mq2_manager_create(&mq2_manager_config1);
  err = mq2_manager_above_threshold(my_mq2_manager, &state);
  TEST_ASSERT_EQUAL(INVALID_STATE, err);
  free(my_mq2_manager);

}

void test_mq2_manager_deinit(void){
  bool state;
  error_type_t err;
 
  err = mq2_manager_above_threshold(my_mq2_manager, &state);
  TEST_ASSERT_EQUAL(INVALID_STATE,err);
  err = mq2_manager_deinit(NULL);
  TEST_ASSERT_EQUAL(NULL_PARAMETER, err);

  err = mq2_manager_deinit(my_mq2_manager);
  TEST_ASSERT_EQUAL(INVALID_STATE, err);

  err = mq2_manager_init(my_mq2_manager);
  err = mq2_manager_deinit(my_mq2_manager);
  TEST_ASSERT_EQUAL(OK,err);

  free(my_mq2_manager);
}

void test_mq2_manager_destroy(void){
  error_type_t err = mq2_manager_destory(NULL);
  TEST_ASSERT_EQUAL(NULL_PARAMETER, err);

  err = mq2_manager_destory(&my_mq2_manager);
  TEST_ASSERT_EQUAL(OK, err);
  TEST_ASSERT_EQUAL(NULL, my_mq2_manager);
}

int runUnityTest(void){
    UNITY_BEGIN();
    RUN_TEST(test_mq2_manager_create);
    RUN_TEST(test_mq2_manager_init);
    RUN_TEST(test_mq2_manager_above_threshold);
    RUN_TEST(test_mq2_manager_deinit);
    RUN_TEST(test_mq2_manager_destroy);
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

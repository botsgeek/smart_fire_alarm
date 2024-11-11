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
    wrong_lm75 = lm75_create(NULL);
    TEST_ASSERT_EQUAL(NULL, wrong_lm75);

}

void test_init_comparator_mode(void){
  error_type_t err = lm75_init_comparator_mode(NULL);
  TEST_ASSERT_EQUAL(INVALID_PARAMETER, err);

  lm75_config_t config1 = {
        .i2c_addr = 0x048,
        .mode = LM75_COMPARATOR_MODE,
        .os_pin_number = 2,
        .polarity = LM75_POLARITY_ACTIVE_LOW,
        .tolerance = LM75_TOLERANCE_ONE_SAMPLE,
        .resolution = LM75_RESOLUTION_9_BITS};
    my_lm75 = lm75_create(&config1);
    err = lm75_init_comparator_mode(my_lm75);
    TEST_ASSERT_EQUAL(OK, err);
    

     err = lm75_init_comparator_mode(my_lm75);
    TEST_ASSERT_EQUAL(INVALID_STATE, err);
    free(my_lm75);    
}

void test_lm75_read(void){

  lm75_config_t config1 = {
        .i2c_addr = 0x048,
        .mode = LM75_COMPARATOR_MODE,
        .os_pin_number = 2,
        .polarity = LM75_POLARITY_ACTIVE_LOW,
        .tolerance = LM75_TOLERANCE_ONE_SAMPLE,
        .resolution = LM75_RESOLUTION_9_BITS};
    my_lm75 = lm75_create(&config1);
  error_type_t err = lm75_init_comparator_mode(my_lm75);
  TEST_ASSERT_EQUAL(OK, err);
  float err1 = lm75_read(my_lm75);
  TEST_ASSERT_EQUAL(OK, err1);
  free(my_lm75);

    err = lm75_init_comparator_mode(my_lm75);
    TEST_ASSERT_EQUAL(INVALID_STATE, err);
    err1 = lm75_read(NULL);
    TEST_ASSERT_EQUAL(INVALID_TEMPERATURE, err1);

}

void test_deinit(void){

  lm75_config_t config1 = {
        .i2c_addr = 0x048,
        .mode = LM75_COMPARATOR_MODE,
        .os_pin_number = 2,
        .polarity = LM75_POLARITY_ACTIVE_LOW,
        .tolerance = LM75_TOLERANCE_ONE_SAMPLE,
        .resolution = LM75_RESOLUTION_9_BITS};
    my_lm75 = lm75_create(&config1);
  float err1 = lm75_read(NULL);
  TEST_ASSERT_EQUAL(INVALID_TEMPERATURE,err1);
  error_type_t err = lm75_deinit(NULL);
  TEST_ASSERT_EQUAL(NULL_PARAMETER, err);

  err = lm75_deinit(my_lm75);
  TEST_ASSERT_EQUAL(INVALID_STATE, err);

  err = lm75_init_comparator_mode(my_lm75);
  err = lm75_deinit(my_lm75);
  TEST_ASSERT_EQUAL(OK, err);
  free(my_lm75);

}

void test_destroy(void){
  error_type_t err = lm75_destroy(NULL);
  TEST_ASSERT_EQUAL(NULL_PARAMETER, err);

  lm75_config_t config1 = {
        .i2c_addr = 0x048,
        .mode = LM75_COMPARATOR_MODE,
        .os_pin_number = 2,
        .polarity = LM75_POLARITY_ACTIVE_LOW,
        .tolerance = LM75_TOLERANCE_ONE_SAMPLE,
        .resolution = LM75_RESOLUTION_9_BITS};
    my_lm75 = lm75_create(&config1);
    err = lm75_destroy(&my_lm75);
    TEST_ASSERT_EQUAL(OK, err);
    TEST_ASSERT_EQUAL(NULL, my_lm75);

}

int runUnityTest(void){
    UNITY_BEGIN();
    RUN_TEST(test_create);
    RUN_TEST(test_init_comparator_mode);
    RUN_TEST(test_lm75_read);
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

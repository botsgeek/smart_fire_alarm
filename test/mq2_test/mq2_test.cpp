#include <unity.h>
#include <Arduino.h>
#include <mq2.h>
#define TAG "TEST"

mq2_t *my_mq;
mq2_t *my_mq_fake;
void setUp(void)
{
  // set stuff up here
}

void tearDown(void)
{
  // clean stuff up here
}
void test_create(void)
{
  // test stuff
  mq2_config_t config = {
      .analog_pin_number = A0,
      .digital_pin_number = 0,
      .mode = MQ2_ANALOG_ONLY};
  my_mq = mq2_create(&config);
  TEST_ASSERT_NOT_EQUAL(NULL, my_mq);
  //   error_type_t err = mq2_init(my_mq);
  //   TEST_ASSERT_EQUAL(OK,err);
  my_mq_fake = mq2_create(NULL);
  TEST_ASSERT_EQUAL(NULL, my_mq_fake);
}

void test_init_wrong_configs(void)
{
  // more test stuff
  mq2_config_t config = {
      .analog_pin_number = A0,
      .digital_pin_number = 0,
      .mode = MQ2_DIGITAL_ONLY};
  my_mq = mq2_create(&config);
  TEST_ASSERT_NOT_EQUAL(NULL, my_mq);
  error_type_t err = mq2_init(my_mq);
  TEST_ASSERT_EQUAL(INVALID_PIN_NUMBER, err);
  free(my_mq);
  mq2_config_t config2 = {
      .analog_pin_number = 30,
      .digital_pin_number = 0,
      .mode = MQ2_ANALOG_ONLY};
  my_mq = mq2_create(&config2);
  TEST_ASSERT_NOT_EQUAL(NULL, my_mq);
  err = mq2_init(my_mq);
  TEST_ASSERT_EQUAL(INVALID_PIN_NUMBER, err);
  free(my_mq);
  mq2_config_t config3 = {
      .analog_pin_number = 30,
      .digital_pin_number = 0,
      .mode = MQ2_HYBRID};
  my_mq = mq2_create(&config3);
  TEST_ASSERT_NOT_EQUAL(NULL, my_mq);
  err = mq2_init(my_mq);
  TEST_ASSERT_EQUAL(INVALID_PIN_NUMBER, err);
  free(my_mq);
  mq2_config_t config4 = {
      .analog_pin_number = 30,
      .digital_pin_number = 2,
      .mode = MQ2_HYBRID};
  my_mq = mq2_create(&config4);
  TEST_ASSERT_NOT_EQUAL(NULL, my_mq);
  err = mq2_init(my_mq);
  TEST_ASSERT_EQUAL(INVALID_PIN_NUMBER, err);
  free(my_mq);
  mq2_config_t config5 = {
      .analog_pin_number = A2,
      .digital_pin_number = 0,
      .mode = MQ2_HYBRID};
  my_mq = mq2_create(&config5);
  TEST_ASSERT_NOT_EQUAL(NULL, my_mq);
  err = mq2_init(my_mq);
  TEST_ASSERT_EQUAL(INVALID_PIN_NUMBER, err);
  free(my_mq);
  err = mq2_init(NULL);
  TEST_ASSERT_EQUAL(NULL_PARAMETER, err);
}

void test_init_corrrect_configs(void)
{
  // more test stuff
  mq2_config_t config = {
      .analog_pin_number = A7,
      .digital_pin_number = 0,
      .mode = MQ2_ANALOG_ONLY};
  my_mq = mq2_create(&config);
  TEST_ASSERT_NOT_EQUAL(NULL, my_mq);
  error_type_t err = mq2_init(my_mq);
  TEST_ASSERT_EQUAL(OK, err);
  free(my_mq);
  mq2_config_t config2 = {
      .analog_pin_number = 30,
      .digital_pin_number = 2,
      .mode = MQ2_DIGITAL_ONLY};
  my_mq = mq2_create(&config2);
  TEST_ASSERT_NOT_EQUAL(NULL, my_mq);
  err = mq2_init(my_mq);
  TEST_ASSERT_EQUAL(OK, err);
  free(my_mq);
  mq2_config_t config3 = {
      .analog_pin_number = A3,
      .digital_pin_number = 4,
      .mode = MQ2_HYBRID};
  my_mq = mq2_create(&config3);
  TEST_ASSERT_NOT_EQUAL(NULL, my_mq);
  err = mq2_init(my_mq);
  TEST_ASSERT_EQUAL(OK, err);
  free(my_mq);
}
void callback()
{
}

void test_init_with_isr_wrong_configs(void)
{
  // more test stuff
  mq2_config_t config = {
      .analog_pin_number = A0,
      .digital_pin_number = 4,
      .mode = MQ2_DIGITAL_ONLY};
  my_mq = mq2_create(&config);
  TEST_ASSERT_NOT_EQUAL(NULL, my_mq);
  error_type_t err = mq2_init_with_isr(my_mq, callback);
  TEST_ASSERT_EQUAL(INVALID_PIN_NUMBER, err);
  free(my_mq);
  mq2_config_t config2 = {
      .analog_pin_number = 30,
      .digital_pin_number = 2,
      .mode = MQ2_ANALOG_ONLY};
  my_mq = mq2_create(&config2);
  TEST_ASSERT_NOT_EQUAL(NULL, my_mq);
  err = mq2_init_with_isr(my_mq, callback);
  TEST_ASSERT_EQUAL(INVALID_MODE, err);
  free(my_mq);
  mq2_config_t config3 = {
      .analog_pin_number = 30,
      .digital_pin_number = 2,
      .mode = MQ2_HYBRID};
  my_mq = mq2_create(&config3);
  TEST_ASSERT_NOT_EQUAL(NULL, my_mq);
  err = mq2_init_with_isr(my_mq, NULL);
  TEST_ASSERT_EQUAL(NULL_PARAMETER, err);
  free(my_mq);
  mq2_config_t config4 = {
      .analog_pin_number = 30,
      .digital_pin_number = 2,
      .mode = MQ2_HYBRID};
  my_mq = mq2_create(&config4);
  TEST_ASSERT_NOT_EQUAL(NULL, my_mq);
  err = mq2_init_with_isr(NULL, callback);
  TEST_ASSERT_EQUAL(NULL_PARAMETER, err);
  free(my_mq);
}

void test_init_with_isr_correct_configs(void)
{
  // more test stuff
  mq2_config_t config = {
      .analog_pin_number = A7,
      .digital_pin_number = 2,
      .mode = MQ2_DIGITAL_ONLY};
  my_mq = mq2_create(&config);
  TEST_ASSERT_NOT_EQUAL(NULL, my_mq);
  error_type_t err = mq2_init_with_isr(my_mq, callback);
  TEST_ASSERT_EQUAL(OK, err);
  free(my_mq);
  mq2_config_t config2 = {
      .analog_pin_number = A3,
      .digital_pin_number = 3,
      .mode = MQ2_HYBRID};
  my_mq = mq2_create(&config2);
  TEST_ASSERT_NOT_EQUAL(NULL, my_mq);
  err = mq2_init_with_isr(my_mq, callback);
  TEST_ASSERT_EQUAL(OK, err);
  free(my_mq);
}

void test_analog_read(void)
{
  // more test stuff
  uint16_t sensor_value;
  mq2_config_t config = {
      .analog_pin_number = A7,
      .digital_pin_number = 0,
      .mode = MQ2_ANALOG_ONLY};
  my_mq = mq2_create(&config);
  TEST_ASSERT_NOT_EQUAL(NULL, my_mq);
  error_type_t err = mq2_digital_read(my_mq, &sensor_value);
  TEST_ASSERT_EQUAL(INVALID_STATE, err);
  err = mq2_init(my_mq);
  TEST_ASSERT_EQUAL(OK, err);
  mq2_config_t config2 = {
      .analog_pin_number = 30,
      .digital_pin_number = 2,
      .mode = MQ2_DIGITAL_ONLY};
  my_mq_fake = mq2_create(&config2);
  TEST_ASSERT_NOT_EQUAL(NULL, my_mq_fake);
  err = mq2_init(my_mq_fake);
  TEST_ASSERT_EQUAL(OK, err);
  err = mq2_analog_read(NULL, &sensor_value);
  TEST_ASSERT_EQUAL(NULL_PARAMETER, err);
  err = mq2_analog_read(my_mq, NULL);
  TEST_ASSERT_EQUAL(NULL_PARAMETER, err);

  err = mq2_analog_read(my_mq_fake, &sensor_value);
  TEST_ASSERT_EQUAL(INVALID_MODE, err);

  err = mq2_analog_read(my_mq, &sensor_value);
  TEST_ASSERT_EQUAL(OK, err);
}

void test_digital_read(void)
{
  // more test stuff
  uint16_t sensor_value;
  mq2_config_t config = {
      .analog_pin_number = 30,
      .digital_pin_number = 2,
      .mode = MQ2_DIGITAL_ONLY};
  my_mq = mq2_create(&config);
  TEST_ASSERT_NOT_EQUAL(NULL, my_mq);
  error_type_t err = mq2_digital_read(my_mq, &sensor_value);
  TEST_ASSERT_EQUAL(INVALID_STATE, err);
  err = mq2_init(my_mq);
  TEST_ASSERT_EQUAL(OK, err);
  mq2_config_t config2 = {
      .analog_pin_number = A7,
      .digital_pin_number = 0,
      .mode = MQ2_ANALOG_ONLY};
  my_mq_fake = mq2_create(&config2);
  TEST_ASSERT_NOT_EQUAL(NULL, my_mq_fake);
  err = mq2_init(my_mq_fake);
  TEST_ASSERT_EQUAL(OK, err);
  err = mq2_digital_read(NULL, &sensor_value);
  TEST_ASSERT_EQUAL(NULL_PARAMETER, err);
  err = mq2_digital_read(my_mq, NULL);
  TEST_ASSERT_EQUAL(NULL_PARAMETER, err);

  err = mq2_digital_read(my_mq_fake, &sensor_value);
  TEST_ASSERT_EQUAL(INVALID_MODE, err);

  err = mq2_digital_read(my_mq, &sensor_value);
  TEST_ASSERT_EQUAL(OK, err);
}

void test_deinit(void)
{
  // more test stuff
  mq2_config_t config = {
      .analog_pin_number = 30,
      .digital_pin_number = 2,
      .mode = MQ2_DIGITAL_ONLY};
  my_mq = mq2_create(&config);
  TEST_ASSERT_NOT_EQUAL(NULL, my_mq);
  error_type_t err = mq2_init(my_mq);
  TEST_ASSERT_EQUAL(OK, err);
  mq2_deinit(my_mq);
  uint16_t sensor_value;
  err = mq2_digital_read(my_mq, &sensor_value);
  TEST_ASSERT_EQUAL(INVALID_STATE, err);
}

int runUnityTests(void)
{
  UNITY_BEGIN();
  RUN_TEST(test_create);
  RUN_TEST(test_init_wrong_configs);
  RUN_TEST(test_init_corrrect_configs);
  RUN_TEST(test_init_with_isr_wrong_configs);
  RUN_TEST(test_init_with_isr_correct_configs);
  RUN_TEST(test_analog_read);
  RUN_TEST(test_digital_read);
  RUN_TEST(test_deinit);
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

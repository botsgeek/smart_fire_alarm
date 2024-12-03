#include <unity.h>
#include <Arduino.h>
#include <sim800.h>
#define TAG "TEST"

sim800_t* my_sim800;
sim800_t* fake_Sim800;

void setUp(void)
{
  // set stuff up here
}

void tearDown(void)
{
  // clean stuff up here
}

void test_create(void){
    sim800_config_t config = {
        .tx_pin_number =11,
        .rx_pin_number = 10,
        .rst_pin_number = 2 ,
        .baud_rate = 9600,
    };
    my_sim800 = sim800_create(&config);
    TEST_ASSERT_NOT_EQUAL(NULL, my_sim800);
    fake_Sim800 = sim800_create(NULL);
    TEST_ASSERT_EQUAL(NULL, fake_Sim800);
}

void test_init(void){
  sim800_config_t config = {
    .tx_pin_number =11,
    .rx_pin_number = 10,
    .rst_pin_number = 2 ,
    .baud_rate = 9600,

  };
  error_type_t err;
  my_sim800 = sim800_create(&config);
  err = sim800_init(my_sim800);
  TEST_ASSERT_EQUAL(OK, err);

  sim800_config_t config1 = {
    .tx_pin_number =12,
    .rx_pin_number = 13,
    .rst_pin_number = 1 ,
    .baud_rate = 115200,

  };
  error_type_t err2;
  my_sim800 = sim800_create(&config1);
  err2 = sim800_init(my_sim800);
  TEST_ASSERT_EQUAL(INVALID_PIN_NUMBER, err2);
  free(my_sim800);

  err = sim800_init(NULL);
  TEST_ASSERT_EQUAL(NULL_PARAMETER,err);
}

void test_deinit(void){
   sim800_config_t config = {
    .tx_pin_number =11,
    .rx_pin_number = 10,
    .rst_pin_number = 2 ,
    .baud_rate = 9600,

  };
  error_type_t err;
  my_sim800 = sim800_create(&config);
  err = sim800_init(my_sim800);
  err = sim800_deinit(my_sim800);
  TEST_ASSERT_EQUAL(OK, err);



}

void test_connect(void){
  error_type_t err = sim800_connect(NULL);
  TEST_ASSERT_EQUAL(NULL_PARAMETER,err);

   sim800_config_t config = {
    .tx_pin_number =11,
    .rx_pin_number = 10,
    .rst_pin_number = 2 ,
    .baud_rate = 9600,

  };
  my_sim800 = sim800_create(&config);
  err = sim800_init(my_sim800);
  err = sim800_connect(my_sim800);
  TEST_ASSERT_EQUAL(OK, err);

   sim800_config_t config1 = {
    .tx_pin_number =9,
    .rx_pin_number = 6,
    .rst_pin_number = 11 ,
    .baud_rate = 2400,

  };
  my_sim800 = sim800_create(&config1);
  err= sim800_init(my_sim800);
  TEST_ASSERT_EQUAL(INVALID_PIN_NUMBER, err);
  err = sim800_connect(my_sim800);
  TEST_ASSERT_EQUAL(INVALID_STATE, err);
  free(my_sim800);
}

void test_send_sms(void){
  char number;
  char message;
  error_type_t err = sim800_send_sms(NULL,&number,&message);
  TEST_ASSERT_EQUAL(NULL_PARAMETER, err);

   sim800_config_t config = {
    .tx_pin_number =7,
    .rx_pin_number = 6,
    .rst_pin_number = 4 ,
    .baud_rate = 115200,

  };
  my_sim800 = sim800_create(&config);
  err = sim800_init(my_sim800);
  TEST_ASSERT_EQUAL(INVALID_PIN_NUMBER, err);
  err = sim800_send_sms(my_sim800,&number,&message);
  TEST_ASSERT_EQUAL(INVALID_STATE, err);
  free(my_sim800);

}

void test_destroy(void){
  error_type_t err = sim800_destroy(NULL);
  TEST_ASSERT_EQUAL(NULL_PARAMETER, err);

   sim800_config_t config = {
    .tx_pin_number =11,
    .rx_pin_number = 10,
    .rst_pin_number = 2 ,
    .baud_rate = 9600,

  };
  my_sim800 = sim800_create(&config);
  err = sim800_destroy(&my_sim800);
  TEST_ASSERT_EQUAL(OK, err);
  TEST_ASSERT_EQUAL(NULL,my_sim800);
}

int runUnityTests(void){
  UNITY_BEGIN();
  RUN_TEST(test_create);
  RUN_TEST(test_init);
  RUN_TEST(test_deinit);
  RUN_TEST(test_connect);
  RUN_TEST(test_send_sms);
  RUN_TEST(test_destroy);
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


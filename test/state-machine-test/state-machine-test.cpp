#include <Arduino.h>
#include <unity.h>
#include <state-machine.h>
#include <buzzer.h>
#include <fan-driver.h>
#include <pump-driver.h>
#define MQ2_THRESHOLD 100
#define LM75_THRESHOLD 30
#define FAN_ON_SPEED 255
#define FAN_OFF_SPEED 0
#define BUZZER_PWM_CYCLE 100
#define TAG "TEST"

state_machine_t* my_state_machine;
state_machine_t* fake_state_machine;
buzzer_t* buzzer;
fan_t* fan;
pump_t* pump;




void setUp(void)
{
  // set stuff up here
}

void tearDown(void)
{
  // clean stuff up here
}

void fire_alarm_handler(state_t current_state)
{
  Serial.println("fireAlarm triggered");
switch (current_state)
        {
        case STATE_MACHINE_NORMAL_STATE:
            buzzer_stop(buzzer);
            pump_off(pump);
            set_fanspeed(fan, FAN_OFF_SPEED); 
            Serial.println("in normal state");
            break;
        case STATE_MACHINE_HEAT_NO_SMOKE:
            buzzer_start(buzzer, BUZZER_PWM_CYCLE);
            pump_on(pump);
            set_fanspeed(fan, FAN_ON_SPEED); 
            Serial.println("in HEAT_NO_SMOKE state");
            break;
        case STATE_MACHINE_SMOKE_NO_HEAT:
            buzzer_start(buzzer, BUZZER_PWM_CYCLE);
            set_fanspeed(fan, FAN_ON_SPEED);
            Serial.println("in SMOKE_NO_HEAT state");
            break;  
        case STATE_MACHINE_HEAT_AND_SMOKE:
            buzzer_start(buzzer, BUZZER_PWM_CYCLE);
            pump_on(pump);
            set_fanspeed(fan, FAN_ON_SPEED);
            Serial.println("in HEAT_AND_SMOKE state");
            break;      
                    
        default:
            break;
        }

}


void test_state_machine_create(void){
  state_config_t state_machine_config = {.current_state = STATE_MACHINE_NORMAL_STATE, 
  .handler = fire_alarm_handler};
  my_state_machine = state_machine_create(&state_machine_config);
  TEST_ASSERT_NOT_EQUAL(NULL,my_state_machine);
  fake_state_machine = state_machine_create(NULL);
  TEST_ASSERT_EQUAL(NULL, fake_state_machine);
}

void test_state_machine_init(void){
  error_type_t err = state_machine_init(NULL);
  TEST_ASSERT_EQUAL(NULL_PARAMETER, err);

  state_config_t state_machine_config = {.current_state = STATE_MACHINE_HEAT_AND_SMOKE, 
  .handler = fire_alarm_handler};
  my_state_machine = state_machine_create(&state_machine_config);
  err = state_machine_init(my_state_machine);
  TEST_ASSERT_EQUAL(OK, err);
  free(my_state_machine);
}

void test_state_machine_transistion(void){
  bool smoke = false;
  bool heat = false;
  error_type_t err = state_machine_transition(NULL,smoke,heat);
  TEST_ASSERT_EQUAL(NULL_PARAMETER, err);

  state_config_t state_machine_config = {.current_state = STATE_MACHINE_NORMAL_STATE, 
  .handler = fire_alarm_handler};
  my_state_machine = state_machine_create(&state_machine_config);
  err = state_machine_transition(my_state_machine,smoke,heat);
  TEST_ASSERT_EQUAL(INVALID_STATE, err);

   state_config_t state_machine_config1 = {.current_state = STATE_MACHINE_HEAT_AND_SMOKE, 
  .handler = fire_alarm_handler};
  my_state_machine = state_machine_create(&state_machine_config1);
  err = state_machine_transition(my_state_machine,smoke,heat);
  err = state_machine_init(my_state_machine);
  TEST_ASSERT_EQUAL(OK, err);

  free(my_state_machine);
}

void test_state_machine_deinit(void){
  bool smoke = false;
  bool heat = false;
   state_config_t state_machine_config1 = {.current_state = STATE_MACHINE_NORMAL_STATE, 
  .handler = fire_alarm_handler};
  my_state_machine = state_machine_create(&state_machine_config1);
  error_type_t err = state_machine_transition(my_state_machine,smoke,heat);
  TEST_ASSERT_EQUAL(INVALID_STATE, err);
  err = state_machine_deinit(NULL);
  TEST_ASSERT_EQUAL(NULL_PARAMETER,err);

  err = state_machine_deinit(my_state_machine);
  TEST_ASSERT_EQUAL(INVALID_STATE,err); 

  err = state_machine_init(my_state_machine);
  err = state_machine_deinit(my_state_machine);
  TEST_ASSERT_EQUAL(OK,err); 

  free(my_state_machine);
}

void test_state_machine_destroy(void){
  error_type_t err = state_machine_destroy(NULL);
  TEST_ASSERT_EQUAL(NULL_PARAMETER, err);

  err = state_machine_destroy(&my_state_machine);
  TEST_ASSERT_EQUAL(OK, err);
  TEST_ASSERT_EQUAL(NULL,my_state_machine);
}

int runUnityTest(void){
  UNITY_BEGIN();
  RUN_TEST(test_state_machine_create);
  RUN_TEST(test_state_machine_init);
  RUN_TEST(test_state_machine_transistion);
  RUN_TEST(test_state_machine_deinit);
  RUN_TEST(test_state_machine_destroy);
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

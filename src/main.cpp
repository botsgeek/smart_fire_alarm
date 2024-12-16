#include <Arduino.h>
#include <state-machine.h>
#include <mq2.h>
#include <pump-driver.h>
#include <lm75-manager.h>
#include <lm75.h>
#include <fan-driver.h>
#include <mq2-manager.h>
#include <sim800.h>
#include <buzzer.h>
#include <sms-tracker.h>
#include <common_headers.h>
#define MQ2_THRESHOLD 100
#define LM75_THRESHOLD 30
#define FAN_ON_SPEED 255
#define FAN_OFF_SPEED 0
#define BUZZER_PWM_CYCLE 100
void fire_alarm_handler(state_t current_state);
void water_alarm_handler(state_t current_state);
// #include <Arduino_FreeRTOS.h>
buzzer_config_t buzzer_config = {
                                    .buzzer_pin = 3}; buzzer_t *
                                buzzer;

fan_config_t fan_config = {
    .fan_pin_number = 4};

fan_t *fan=NULL;

pump_config_t pump_config = {
                                .pump_pin_number = 5};

                            pump_t *
                            pump;

mq2_config_t mq2_config = {
    .analog_pin_number = A0,
    .digital_pin_number = 6,
    .mode = MQ2_HYBRID};

mq2_t *mq2=NULL;
lm75_config_t lm75_config = {
  .i2c_addr = 0x48,
  .mode = LM75_COMPARATOR_MODE, 
  .os_pin_number = 2, 
  .polarity = LM75_POLARITY_ACTIVE_HIGH,
  .tolerance =LM75_TOLERANCE_FOUR_SAMPLES,
  .resolution = LM75_RESOLUTION_10_BITS,
  };
lm75_t* lm75=NULL;

sim800_config_t sim800_config= {
  .tx_pin_number = 11,
  .rx_pin_number = 10,
  .rst_pin_number = 7,
  .baud_rate = 9600,

};

sim800_t* sim800=NULL;
lm75_manager_t* lm75_manager=NULL;
mq2_manager_t* mq2_manager=NULL;


state_machine_t* state_machine=NULL;

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
            sms_tracker_handler(sms);
            Serial.println("in HEAT_AND_SMOKE state");
            break;                 
        default:
            break;
        }

}
void water_alarm_handler(state_t current_state){
  Serial.println("Water alarm triggered");
}
void setup()
{
  error_type_t err;
  Serial.begin(9600);
  // put your setup code here, to run once:

  //mq2 create and init
  mq2 = mq2_create(&mq2_config);
  if(!mq2){
    Serial.println("mq2 create failed");
    exit(1);
  }
  err = mq2_init(mq2);
  if(err != OK){
      Serial.println("mq2 init create failed");
    exit(1);
  }
 
    //lm75 create and init
  lm75 = lm75_create(&lm75_config);
  if(!lm75){
    Serial.println("lm75 create failed");
    exit(1);
  }
  err = lm75_init_comparator_mode(lm75);
  if(err != OK){
    Serial.println("lm75  init create failed");
    exit(1);
  }

    //buzzer create and init
  buzzer = buzzer_create(&buzzer_config);
  if(!buzzer){
    Serial.println("buzzer create failed");
    exit(1);
  }
  err = buzzer_init(buzzer);
  if(err != OK){
    Serial.println("buzzer init create failed");
    exit(1);
  }

    //pump create and init
  pump = pump_create(&pump_config);
  if(!pump){
    Serial.println("pump create failed");
    exit(1);
  }
  err = pump_init(pump);
  if(err != OK){
    Serial.println("pump init create failed");
    exit(1);
  }

    //fan create and init
  fan = fan_create(&fan_config);
  if(!fan){
    Serial.println("fan create failed");
    exit(1);
  }
  err = fan_init(fan);
  if(err != OK){
      Serial.println("fan init create failed");
    exit(1);
  }

    //sim800 create and init
  sim800 = sim800_create(&sim800_config);
  if(!sim800){
    exit(1);
  }
  err = sim800_init(sim800);
  if(err != OK){
    exit(1);
  }

//sim800 connect , reset and send sms
  err = sim800_connect(sim800);
    if (err != OK)
    {
      Serial.println("sim800 failed to connect");
      exit(1);
    }

    err = sim800_reset(sim800);
    if (err != OK)
    {
        Serial.println("should have reset now");
        exit(1);
    }
    
           
     
              
// mq2 manager config, create and init
  mq2_manager_config_t mq2_manager_config = {
  .mq2_threshold = MQ2_THRESHOLD,
  .mq2_object = mq2,
};

mq2_manager = mq2_manager_create(&mq2_manager_config);
if(!mq2_manager){
  Serial.println("mq2 manager create failed");
  exit(1);
}
err = mq2_manager_init(mq2_manager);
if(err != OK){
  Serial.println("mq2 manager init create failed");
  exit(1);
}

// lm75 manager config, create and init
lm75_manager_config_t lm75_manager_config = {
  .lm75_threshold = LM75_THRESHOLD,
  .lm75_obj = lm75,
};

lm75_manager = lm75_manager_create(&lm75_manager_config);
if(!lm75_manager){
  Serial.println("lm75 manager create failed");
  exit(1);
}
err = lm75_manager_init(lm75_manager);
if(err != OK){
  Serial.println("lm75 manager init create failed");
  exit(1);
}


// state machine config, create and init
state_config_t state_config = {
  .current_state = STATE_MACHINE_NORMAL_STATE,
  .handler = fire_alarm_handler
  
};

state_machine = state_machine_create(&state_config);
if(!state_machine){
  Serial.println("state_machine create failed");
  exit(1);
}
err = state_machine_init(state_machine);
if(err != OK){
  Serial.println("state_machine init create failed");
  exit(1);
}

}

void loop()
{
  bool heat;
  bool smoke;
  error_type_t err;
  err = lm75_manager_above_threshold(lm75_manager,&heat);
  if(err != OK){
    Serial.println("lm75 attempt to get threshold failed");
  }
  
  err = mq2_manager_above_threshold(mq2_manager,&smoke);
  if(err != OK){
    Serial.println("mq2 attempt to get threshold failed");
  }

  err = state_machine_transition(state_machine,heat,smoke);
  if(err != OK){
    Serial.println("state machine transition failed");
  }
  delay(1000);
  // put your main code here, to run repeatedly:
}

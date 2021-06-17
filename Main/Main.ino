#include <Arduino.h>
#include "math.h"
#include "Wire.h"
#include "soc/soc.h"
#include "soc/rtc_cntl_reg.h"


float radian = 57.2957795;



void setup() {
  Serial.begin(115200);
  
  MOTOR_setup();
  RGB_setup();
  OLED_setup();
  IR_setup();
  ENCODER_setup();

  SET_MOTOR(0, 0);
  SET_MOTOR(1, 0);

  RGB_UPDATE();
  IR_SWITCH(0);

  delay(100);

  LPS_TARGET_ON(-200, 100, 50);
  LPS_SET_PID(0.1, 0, -1, 0);
  RGB_OFF();

}



int i = 0;
float start_time = millis();
float start_loop_time = millis();
float loop_time = 0;
float prev_speed = 0;



void loop() {
  loop_time = millis() - start_loop_time;
  start_loop_time = millis();
  
  int* result = LPS_UPDATE( loop_time, ENC_SPD(0, loop_time), ENC_SPD(1, loop_time) );
  if (LPS_INFO(0) && LPS_INFO(1)) {
    SET_MOTOR(0, result[0]);
    SET_MOTOR(1, result[1]);
    
  } else if (LPS_INFO(0)) {
    LPS_PID_OFF();
    SET_MOTOR(0, 0);
    SET_MOTOR(1, 0);
  }
  
  float* crd = LPS_CRD();

  /* DEBUG */
  int bot_direction = crd[2];
  String ROW1 = "x:" + String(crd[0]) + " y:" + String(crd[1]);
  String ROW2 = "l:" + String(MOTOR_SPD(0)) + " r:" + String(MOTOR_SPD(1)) + " a:" + String(bot_direction%360);
  String ROW3 = "d:" + String(LPS_INFO(4)) + " e:" + String(LPS_INFO(6));
  OLED(ROW1, ROW2, ROW3);
  /* DEBUG */
}

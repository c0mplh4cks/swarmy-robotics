#include <Arduino.h>
#include "math.h"
#include "Wire.h"
#include "soc/soc.h"
#include "soc/rtc_cntl_reg.h"


double radian = 57.2957795;
int target_index = 0;

static double targets[][3] = {{0, 20, 5}, {20, 20, 0}, {20, 20, 5}, {20, 0, 0}, {20, 0, 5}, {0, 0, 0}, {0, 0, 5}, {0, 10, 0}};
int target_max = 8;



void PID_ON() {
  SPD_PID_ON();
  LPS_PID_ON();
}

void PID_OFF() {
  SPD_PID_OFF();
  LPS_PID_OFF();
}

void setup() {
  Serial.begin(115200);
  
  MOTOR_setup();
  //RGB_setup();
  OLED_setup();
  IR_setup();
  ENCODER_setup();
  BUTTON_setup();

  SET_MOTOR(0, 0);
  SET_MOTOR(1, 0);

  IR_SWITCH(0);

  SPD_SET_PID(0.5, 0.55, 1);

  while (BUTTON(0) == false && IR_RECV(0) < 3500 && IR_RECV(4) < 3500) {
    OLED("Press button", "to start", "");
    delay(10);
  }
  IR_SWITCH(1);
  delay(10);
  IR_SWITCH(0);
  OLED("", "", "");

  delay(100);

  //SET_MOTOR(0, 255);
  //SET_MOTOR(1, 255);

}



int i = 0;
double start_time = millis();
double start_loop_time = millis();
double loop_time = 0;



void loop() {
  loop_time = millis() - start_loop_time;
  start_loop_time = millis();
  double spdl = ENC_SPD(0);
  double spdr = ENC_SPD(1);
  
  double* result = LPS_UPDATE( loop_time, spdl, spdr );
  int* spds = SPD_UPDATE(loop_time, result[0], result[1], spdl, spdr);
  if (LPS_INFO(0) && LPS_INFO(1)) {
    SET_MOTOR(0, spds[0]);
    SET_MOTOR(1, spds[1]);
    
  } else if (LPS_INFO(0)) {
    PID_OFF();
  }
    
  MOTOR_UPDATE(loop_time);
  double* crd = LPS_CRD();

  /* Target */
  if (LPS_INFO(1) == false && target_index < target_max) { /* Change Target */
    LPS_SET_PID(0.3, 0, 5, targets[target_index][2]);
    LPS_TARGET_ON(targets[target_index][0], targets[target_index][1], 1);
    target_index++;
    PID_ON();
    
  } else if (LPS_INFO(1) == false && target_index == target_max) { /* END of Targets */
    target_index++;
    LPS_PID_OFF();
    SET_MOTOR(0, 0);
    SET_MOTOR(1, 0);
    PID_OFF();
  }
  /* Target */

  /* DEBUG */
  int bot_direction = crd[2];
  String ROW1 = "x:" + String(crd[0]) + " y:" + String(crd[1]);
  String ROW2 = "l:" + String(spdl / (loop_time / 1000)) + " r:" + String(spdr / (loop_time / 1000)) + " a:" + String(bot_direction);
  String ROW3 = "tl:" + String(MOTOR_SPD(0)) + " tr:" + String(MOTOR_SPD(1)) + " e:" + String(LPS_INFO(6));
  OLED(ROW1, ROW2, ROW3);
  /* DEBUG */
}

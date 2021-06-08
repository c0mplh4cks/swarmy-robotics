#include <Arduino.h>
#include "Wire.h"
#include "soc/soc.h"
#include "soc/rtc_cntl_reg.h"



void setup() {
  Serial.begin(115200);
  
  MOTOR_setup();
  RGB_setup();
  OLED_setup();
  IR_setup();

  SET_MOTOR(0, 42);
  SET_MOTOR(1, -42);

  RGB(0, 255, 0, 0, 20);
  OLED("POTATO", "42", "SWARMY");
  IR_SWITCH(1);

}

void loop() {
  for (int i=0; i<8; i++) {
    Serial.print( IR_RECV(i) );
  }

}

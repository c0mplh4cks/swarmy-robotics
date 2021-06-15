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
  BUTTON_setup();

  RGB_UPDATE();
  IR_SWITCH(0);
}



void loop() {
  /* OLED */
  while (BUTTON() == false) {
    OLED("Good morning", "Goedemorgen", "Dobroe utra");
    delay(50);
  }
  OLED("", "", "");
  
  delay(100);
  BUTTON_OFF();
  
  
  /* Motor */
  while (BUTTON() == false) {
    OLED("MOTOR TEST", "", "");
    
    for (int i=-255; i<256; i++) {
      SET_MOTOR(0, i);
      SET_MOTOR(1, i);
      delay(10);
    }
    SET_MOTOR(0, 0);
    SET_MOTOR(1, 0);
  }
  
  delay(100);
  BUTTON_OFF();
  
  /* RGB */
  while (BUTTON() == false) {
    OLED("RGB TEST", "", "RED");

    for (int c=0; c<255; c++) {
      for (int i=0; i<8; i++) {
        RGB_SET(i, c, 0, 0, 50);
      }
      RGB_UPDATE();
      delay(10);
    }
  }
  
  delay(100);
  BUTTON_OFF();

  while (BUTTON() == false) {
    OLED("RGB TEST", "", "GREEN");

    for (int c=0; c<255; c++) {
      for (int i=0; i<8; i++) {
        RGB_SET(i, 0, c, 0, 50);
      }
      RGB_UPDATE();
      delay(10);
    }
  }

  delay(100);
  BUTTON_OFF();

  while (BUTTON() == false) {
    OLED("RGB TEST", "", "BLUE");

    for (int c=0; c<255; c++) {
      for (int i=0; i<8; i++) {
        RGB_SET(i, 0, 0, c, 50);
      }
      RGB_UPDATE();
      delay(10);
    }
  }

  delay(100);
  BUTTON_OFF();

  while (BUTTON() == false) {
    OLED("RGB TEST", "", "WHITE");

    for (int c=0; c<255; c++) {
      for (int i=0; i<8; i++) {
        RGB_SET(i, c, c, c, 50);
      }
      RGB_UPDATE();
      delay(10);
    }
  }
  RGB_OFF();

  delay(100);
  BUTTON_OFF();


  /* IR SENSOR */
  for (int i=0; i<8; i++) {
    while (BUTTON() == false) {
      OLED("IR SENSOR TEST", "index: " + String(i), "value: " + String(IR_RECV(i)));
      delay(50);  
    }
    delay(500);
    BUTTON_OFF();
  }

  delay(100);


  /* IR LED */
  while (BUTTON() == false) {
    OLED("IR LED TEST", "", "ON");
    IR_SWITCH(1);
    delay(1000); 
    IR_SWITCH(0);
    OLED("IR LED TEST", "", "OFF");
    delay(1000);
  }
  delay(100);
  BUTTON_OFF();
}
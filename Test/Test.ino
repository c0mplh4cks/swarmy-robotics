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
  ENCODER_setup();

  RGB_UPDATE();
  IR_SWITCH(0);

  delay(100);
  RGB_OFF();
}



void loop() {
  /* OLED */
  while (BUTTON() == false) {
    OLED("- SWARMY TESTING -", "PresS thE buTton", "to StarT...");
    delay(100);
    OLED("\\ SWARMY TESTING /", "pRess_the_butTon", "To sTart,..");
    delay(100);
    OLED("| SWARMY TESTING |", "prEss The ButtOn", "tO stArt.,.");
    delay(100);
    OLED("/ SWARMY TESTING \\", "preSs tHe bUttoN", "to_staRt..,");
    delay(100);
  }
  OLED("", "", "");
  
  delay(100);
  BUTTON_OFF();
  
  /* IR CG */
  IR_SWITCH(1);
  
  while (BUTTON() == false) {
    float* cg = IR_CG(100u);
    
    OLED("IR CG TEST", "cgx:" + String(cg[0]), "cgy:" + String(cg[1]));
    delay(50);
  }
  OLED("", "", "");

  delay(100);
  BUTTON_OFF();
  IR_SWITCH(0);
  

  /* Encoder */
  while (BUTTON() == false) {
    OLED("ENCODER TEST", "index 0: " + String(ENC_DIST(0)), "index 1: " + String(ENC_DIST(1)));
    delay(50);
  }
  OLED("", "", "");

  delay(100);
  BUTTON_OFF();
  
  
  /* Motor */
  while (BUTTON() == false) {
    for (int i=0; i>-256; i=i-5) {
      SET_MOTOR(0, i);
      SET_MOTOR(1, i);
      OLED("MOTOR TEST", "spd 0:" + String(MOTOR_SPD(0)) + " 1:" + String(MOTOR_SPD(1)), "enc 0:" + String(ENC_DIST(0)) + " 1:" + String(ENC_DIST(1)));
      delay(50);
    }
    for (int i=-255; i<0; i=i+5) {
      SET_MOTOR(0, i);
      SET_MOTOR(1, i);
      OLED("MOTOR TEST", "spd 0:" + String(MOTOR_SPD(0)) + " 1:" + String(MOTOR_SPD(1)), "enc 0:" + String(ENC_DIST(0)) + " 1:" + String(ENC_DIST(1)));
      delay(50);
    }
    for (int i=0; i<256; i=i+5) {
      SET_MOTOR(0, i);
      SET_MOTOR(1, i);
      OLED("MOTOR TEST", "spd 0:" + String(MOTOR_SPD(0)) + " 1:" + String(MOTOR_SPD(1)), "enc 0:" + String(ENC_DIST(0)) + " 1:" + String(ENC_DIST(1)));
      delay(50);
    }
    for (int i=255; i>0; i=i-5) {
      SET_MOTOR(0, i);
      SET_MOTOR(1, i);
      OLED("MOTOR TEST", "spd 0:" + String(MOTOR_SPD(0)) + " 1:" + String(MOTOR_SPD(1)), "enc 0:" + String(ENC_DIST(0)) + " 1:" + String(ENC_DIST(1)));
      delay(50);
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
    RGB_OFF();
    RGB_SET(i, 255, 0, 0, 10);
    delay(10);
    RGB_UPDATE();
    while (BUTTON() == false) {
      OLED("IR SENSOR TEST", "index: " + String(i), "value: " + String(IR_RECV(i)));
      delay(50);  
    }
    delay(500);
    BUTTON_OFF();
  }
  
  delay(100);
  RGB_OFF();
  delay(10);
  RGB_UPDATE();

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

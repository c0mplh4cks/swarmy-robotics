const int freq = 5000;
const int resolution = 8;

int motorPWMA, motorPWMB;
int motorPins[4] = {19, 18, 17, 16}; // M1A, M1B, M2A, M2B
int motor[4] = {0, 1, 2, 3};



void SET_MOTOR(int index, int speed) {
  int cspeed = constrain(abs(speed), 0, 255);
  
  if (index == 0) { // Links
    if (speed >= 0) {
      ledcWrite(motor[0], 255);
      ledcWrite(motor[1], 255-cspeed);

    } else {
      ledcWrite(motor[1], 255);
      ledcWrite(motor[0], 255-cspeed);
    }

  } else if (index == 1) { // Rechts
    if (speed >= 0) {
      ledcWrite(motor[2], 255);
      ledcWrite(motor[3], 255-cspeed);

    } else {
      ledcWrite(motor[3], 255);
      ledcWrite(motor[2], 255-cspeed);
    }
  }
    
}



void MOTOR_setup() {
  for (int i = 0; i < 4; i++) {
    ledcSetup(motor[i], freq, resolution);
    ledcAttachPin(motorPins[i], motor[i]);
  }
}

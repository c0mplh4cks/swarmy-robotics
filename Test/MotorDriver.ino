const int freq = 5000;
const int resolution = 8;

int motorPins[4] = {19, 18, 17, 16}; // M1A, M1B, M2A, M2B
int motor[4] = {0, 1, 2, 3};

int mspdL = 0;
int mspdR = 0;



void SET_MOTOR(int index, int speed) {
  int cspeed = constrain(abs(speed), 0, 255);
  
  if (index == 0) { 
    mspdL = speed;
    if (speed >= 0) {
      ledcWrite(motor[0], 255);
      ledcWrite(motor[1], 255-cspeed);

    } else {
      ledcWrite(motor[1], 255);
      ledcWrite(motor[0], 255-cspeed);
    }
  } else  if (index == 1) { 
    mspdR = speed;
    if (speed >= 0) {
      ledcWrite(motor[2], 255);
      ledcWrite(motor[3], 255-cspeed);

    } else {
      ledcWrite(motor[3], 255);
      ledcWrite(motor[2], 255-cspeed);
    }
  }
    
}



int MOTOR_SPD(int index) {
  if (index == 0) {
    return mspdL;
  } else if (index == 1) {
    return mspdR;
  }
}



void MOTOR_setup() {
  for (int i = 0; i < 4; i++) {
    ledcSetup(motor[i], freq, resolution);
    ledcAttachPin(motorPins[i], motor[i]);
  }
}

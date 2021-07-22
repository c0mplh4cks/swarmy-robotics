const int freq = 5000;
const int resolution = 8;

int motorPins[4] = {17, 16, 19, 18}; // M1A, M1B, M2A, M2B
int motor[4] = {0, 1, 2, 3};

int mspdL = 0;
int mspdR = 0;

int targetL = 0;
int targetR = 0;

double accm = 10;





void SET_MOTOR(int index, int spd) {
  if (index == 0) {
    targetL = spd; 
  } else if (index == 1) {
    targetR = spd;
  }
}



void MOTOR_PWM(int index, int spd) {
  int cspeed = constrain(abs(spd), 0, 255);
  
  if (index == 0) { 
    mspdL = spd;
    if (spd >= 0) {
      ledcWrite(motor[0], 255);
      ledcWrite(motor[1], 255-cspeed);

    } else {
      ledcWrite(motor[1], 255);
      ledcWrite(motor[0], 255-cspeed);
    }
  } else  if (index == 1) { 
    mspdR = spd;
    if (spd >= 0) {
      ledcWrite(motor[2], 255);
      ledcWrite(motor[3], 255-cspeed);

    } else {
      ledcWrite(motor[3], 255);
      ledcWrite(motor[2], 255-cspeed);
    }
  }  
}



double BRAKE_TIME(double loop_time) {
  int s;
  if (mspdL > mspdR) {s = mspdL;}
  else {s = mspdR;}
  double bt = abs(s/accm * (loop_time / 1000));
  return bt;
}



int MOTOR_SPD(int index) {
  if (index == 0) {
    return mspdL;
  } else if (index == 1) {
    return mspdR;
  }
}



void MOTOR_UPDATE(double loop_time) {
  int diffL = targetL - mspdL;
  if (diffL > accm) {
    MOTOR_PWM(0, mspdL + accm);  
    
  } else if (diffL < -accm) {
    MOTOR_PWM(0, mspdL - accm);  
    
  } else {
    MOTOR_PWM(0, mspdL + diffL);  
  }
  
  int diffR = targetR - mspdR;
  if (diffR > accm) {
    MOTOR_PWM(1, mspdR + accm);  
    
  } else if (diffR < -accm) {
    MOTOR_PWM(1, mspdR - accm);  
    
  } else {
    MOTOR_PWM(1, mspdR + diffR);  
  }
  
}



void MOTOR_setup() {
  for (int i = 0; i < 4; i++) {
    ledcSetup(motor[i], freq, resolution);
    ledcAttachPin(motorPins[i], motor[i]);
  }
}

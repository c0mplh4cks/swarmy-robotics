#define ENCODEROUTPUT 32



volatile long encoderValue0 = 0;
volatile long encoderValue1 = 0;

float wheel_dia = 115;
float pulse_rpm = 350;
float pulse_mm = wheel_dia / pulse_rpm;

int encoderPin0 = 36;
int encoderPin1 = 39;



void ENCODER_setup() {
  pinMode(encoderPin0, INPUT);
  pinMode(encoderPin1, INPUT);
  attachInterrupt(encoderPin0, updateEncoder0, RISING);
  attachInterrupt(encoderPin1, updateEncoder1, RISING);
}



void updateEncoder0() {
  int spd = MOTOR_SPD(0);
  if (spd > 0) {
    encoderValue0++; 
  } else {
    encoderValue0--;
  }
}

void updateEncoder1() {
  int spd = MOTOR_SPD(1);
  if (spd > 0) {
    encoderValue1++; 
  } else {
    encoderValue1--;
  }
}



int ENC_PULSES(int index) {
  if (index == 0) {
    return encoderValue0;
  } else if (index == 1) {
    return encoderValue1;
  }
}



float ENC_MM(int index) {
  if (index == 0) {
    return encoderValue0*pulse_mm;
  } else if (index == 1) {
    return encoderValue1*pulse_mm;
  }
}

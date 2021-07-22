#define ENCODEROUTPUT 32

volatile long encoderValue0 = 0;
volatile long encoderValue1 = 0;
volatile long encoderPrev0 = 0;
volatile long encoderPrev1 = 0;

double wheel_dia = 11.5;
double pulse_rpm = 350;
double pulse_pd = wheel_dia / pulse_rpm;

int encoderPin0 = 39;
int encoderPin1 = 36;





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
  } else if (spd < 0) {
    encoderValue0--;
  }
}

void updateEncoder1() {
  int spd = MOTOR_SPD(1);
  if (spd > 0) {
    encoderValue1++; 
  } else if (spd < 0) {
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



double ENC_DST(int index) {
  if (index == 0) {
    return encoderValue0*pulse_pd;
  } else if (index == 1) {
    return encoderValue1*pulse_pd;
  }
}



double ENC_SPD(int index) {
  if (index == 0) {
    double diff = encoderValue0 - encoderPrev0;
    double spd = diff * pulse_pd; 
    encoderPrev0 = encoderValue0;
    return spd;
    
  } else if (index == 1) {
    double diff = encoderValue1 - encoderPrev1;
    double spd = diff * pulse_pd; 
    encoderPrev1 = encoderValue1;
    return spd;
    
  }
}

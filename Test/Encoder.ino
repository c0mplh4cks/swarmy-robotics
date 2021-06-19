#define ENCODEROUTPUT 32



volatile long encoderValue0 = 0;
volatile long encoderValue1 = 0;
volatile long encoderPrev0 = 0;
volatile long encoderPrev1 = 0;

float wheel_dia = 11.5;
float pulse_rpm = 350;
float pulse_pd = wheel_dia / pulse_rpm;

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



float ENC_DIST(int index) {
  if (index == 0) {
    return encoderValue0*pulse_pd;
  } else if (index == 1) {
    return encoderValue1*pulse_pd;
  }
}



float ENC_SPD(int index, float loop_time) {
  if (index == 0) {
    float diff = encoderValue0 - encoderPrev0;
    float spd = diff * pulse_pd; // / (loop_time / 1000);
    encoderPrev0 = encoderValue0;
    return spd;
    
  } else if (index == 1) {
    float diff = encoderValue1 - encoderPrev1;
    float spd = diff * pulse_pd; // / (loop_time / 1000);
    encoderPrev1 = encoderValue1;
    return spd;
    
  }
}

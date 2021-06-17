#define ENCODEROUTPUT 32



volatile long encoderValue0 = 0;
volatile long encoderValue1 = 0;

int encoderPin0 = 36;
int encoderPin1 = 39;



void ENCODER_setup() {
  pinMode(encoderPin0, INPUT);
  pinMode(encoderPin1, INPUT);
  attachInterrupt(encoderPin0, updateEncoder0, RISING);
  attachInterrupt(encoderPin1, updateEncoder1, RISING);
}



void updateEncoder0() {
  encoderValue0++;
}

void updateEncoder1() {
  encoderValue1++;
}



int ENCODER(int index) {
  if (index == 0) {
    return encoderValue0;
  } else if (index == 1) {
    return encoderValue1;
  }
}

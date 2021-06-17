int irLedSwitchPin = 2;

int S0 = 27;
int S1 = 26;
int S2 = 25;

int MultiPins[8][3] = {
  {0, 0, 0},
  {1, 0, 0},
  {0, 1, 0},
  {1, 1, 0},
  {0, 0, 1},
  {1, 0, 1},
  {0, 1, 1},
  {1, 1, 1}
};



void IR_SWITCH(int s) {
  if (s == 0) {
    digitalWrite(irLedSwitchPin, LOW);
    
  } else if (s == 1) {
    digitalWrite(irLedSwitchPin, HIGH);
  }
}



int IR_RECV(int index) {
  digitalWrite(S0, MultiPins[index][0]);
  digitalWrite(S1, MultiPins[index][1]);
  digitalWrite(S2, MultiPins[index][2]);

  return map(analogRead(34), 0, 4096, 255, 0);
}



float* IR_CG(float f) {
  int weights[8];
  float sumM = 0;
  float sumX = 0;
  float sumY = 0;

  for (int i=0; i<8; i++) {
    weights[i] = IR_RECV(i);
    sumM = sumM + weights[i];
    sumX = sumX + cos( (360/8*i+90)/radian ) * weights[i];
    sumY = sumY + sin( (360/8*i+90)/radian ) * weights[i];
  }

  float crd[2];
  crd[0] = (1/sumM) * sumX * f;
  crd[1] = (1/sumM) * sumY * f;

  return crd;
}



void IR_setup() {
  pinMode(irLedSwitchPin, OUTPUT);
  pinMode(S0, OUTPUT);
  pinMode(S1, OUTPUT);
  pinMode(S2, OUTPUT);
  
  digitalWrite(irLedSwitchPin, LOW);
  digitalWrite(S0, HIGH);
  digitalWrite(S1, HIGH);
  digitalWrite(S2, HIGH);
}
  

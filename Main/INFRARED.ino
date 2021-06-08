int irLedSwitchPin = 2;

// Multiplexer pins
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
    Serial.print(" IrledOFF ");
    
  } else if (s == 1) {
    digitalWrite(irLedSwitchPin, HIGH);
    Serial.print(" IrledON ");
  }
}



int IR_RECV(int index) {
  digitalWrite(S0, MultiPins[index][0]);
  digitalWrite(S1, MultiPins[index][1]);
  digitalWrite(S2, MultiPins[index][2]);

  return map(analogRead(34), 0, 4096, 1, 255);
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
  

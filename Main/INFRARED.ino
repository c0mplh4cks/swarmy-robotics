int irLedSwitchPin = 2;

// Multiplexer pins
int S0 = 27;
int S1 = 26;
int S2 = 25;



void IR_SWITCH(int s) {
  if (s == 0) {
    digitalWrite(irLedSwitchPin, LOW);
    Serial.print(" IrledOFF ");
    
  } else if (s == 1) {
    digitalWrite(irLedSwitchPin, HIGH);
    Serial.print(" IrledON ");
  }
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
  

int pinButton[3] = {35, 32, 14};
volatile bool ButtonValue[3] = {false, false, false};



void BUTTON_setup() {
  pinMode(pinButton[0], INPUT);
  attachInterrupt(pinButton[0], update_button0, RISING);
  pinMode(pinButton[1], INPUT);
  attachInterrupt(pinButton[1], update_button1, RISING);
  pinMode(pinButton[2], INPUT);
  attachInterrupt(pinButton[2], update_button2, RISING);
}



bool BUTTON(int index) {
  if (ButtonValue[index] == true) {
    delay(10);
    ButtonValue[index] = false;
    return true;
  }
  
  return false;
}



void update_button0() {
  ButtonValue[0] = true;
}

void update_button1() {
  ButtonValue[1] = true;
}

void update_button2() {
  ButtonValue[2] = true;
}

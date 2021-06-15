int pinButton = 35;
bool ButtonValue = false;





bool BUTTON() {
  return ButtonValue;
}

void BUTTON_OFF() {
  ButtonValue = false;
}



void BUTTON_setup() {
  pinMode(pinButton, INPUT);
  attachInterrupt(pinButton, update_button, RISING);
}



void update_button() {
  ButtonValue = true;
}

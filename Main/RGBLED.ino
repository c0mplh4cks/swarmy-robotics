#include "Adafruit_NeoPixel.h"



int ledPin = 33;
const int ledAmount = 8;
int ledBrightness = 10;
int ledColors[8][3];

Adafruit_NeoPixel strip = Adafruit_NeoPixel(ledAmount, ledPin, NEO_GRB + NEO_KHZ800);



void RGB_SET(int index, int r, int g, int b, int brightness) {
  ledColors[index][0] = r;
  ledColors[index][1] = g;
  ledColors[index][2] = b;
  uint32_t color = strip.Color(r, g, b);
  strip.setPixelColor(index, color);
  strip.setBrightness(brightness);  
}



void RGB_UPDATE() {
  strip.show();
}



void RGB_OFF() {
  bool ureq = false;
  
  for (int i=0; i<ledAmount; i++) {
    bool clean = true;
    
    for (int c=0; c<3; c++) {
      if (ledColors[i][c] != 0) {
        ledColors[i][c] = 0;
        clean = false;
        ureq = true;
      }
    }
    
    if (clean == false) {
      RGB_SET(i, 0, 0, 0, 20);
    }
  }
  
  if (ureq == true) {
    RGB_UPDATE(); 
  }
}



void RGB_setup() {
  strip.begin();
  strip.setBrightness(ledBrightness);
  strip.show();
}

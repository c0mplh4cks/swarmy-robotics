#include "Adafruit_NeoPixel.h"



int ledPin = 33;
const int ledAmount = 8;
int ledBrightness = 10;

Adafruit_NeoPixel strip = Adafruit_NeoPixel(ledAmount, ledPin, NEO_GRB + NEO_KHZ800);



void RGB(int index, int r, int g, int b, int brightness) {
  uint32_t color = strip.Color(r, g, b);
  strip.setPixelColor(index, color);
  strip.setBrightness(brightness);  
  strip.show();
}


void RGB_setup() {
  strip.begin();
  strip.setBrightness(ledBrightness);
  strip.show();
}

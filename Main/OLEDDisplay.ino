#include "U8g2lib.h"



U8G2_SSD1306_128X32_UNIVISION_F_SW_I2C u8g2(U8G2_R0, SCL, SDA, U8X8_PIN_NONE);



void OLED(int index, String text) {
  u8g2.clearBuffer();
  u8g2.setFont(u8g2_font_t0_12_tf);

  if (index == 0) {
    u8g2.setCursor(0, 8);
  } else if (index == 1) {
    u8g2.setCursor(0, 20);
  } else if (index == 2) {
    u8g2.setCursor(0, 32);
  }
  u8g2.print(text);

  u8g2.sendBuffer();
  delay(50);
}



void OLED_setup() {
  u8g2.begin();
}

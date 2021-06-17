#include "U8g2lib.h"



U8G2_SSD1306_128X32_UNIVISION_F_SW_I2C u8g2(U8G2_R0, SCL, SDA, U8X8_PIN_NONE);



void OLED(String row0, String row1, String row2) {
  u8g2.clearBuffer();
  
  u8g2.setCursor(0, 8);
  u8g2.print(row0);
  u8g2.setCursor(0, 20);
  u8g2.print(row1);
  u8g2.setCursor(0, 32);
  u8g2.print(row2);

  u8g2.sendBuffer();
}



void OLED_setup() {
  u8g2.begin();
  u8g2.setFont(u8g2_font_t0_12_tf);
}

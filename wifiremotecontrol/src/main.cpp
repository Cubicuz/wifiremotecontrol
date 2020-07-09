#include <Arduino.h>
#include "RotaryWrapper.h"

#include <U8g2lib.h>
#include <Wire.h>

uint8_t x(20), y(30);
bool redraw(0);

RotaryWrapper rt1(GPIO_NUM_32, GPIO_NUM_33, [](unsigned char dir){
  switch (dir)
  {
  case DIR_CW:
    x++;
    redraw=true;
    break;
  case DIR_CCW:
    x--;
    redraw=true;
    break;
  default:
    break;
  }
});
RotaryWrapper rt2(GPIO_NUM_25, GPIO_NUM_26, [](unsigned char dir){
  switch (dir)
  {
  case DIR_CW:
    y++;
    redraw=true;
    break;
  case DIR_CCW:
    y--;
    redraw=true;
    break;
  default:
    break;
  }
});
U8G2_SSD1306_128X64_NONAME_F_HW_I2C oled(U8G2_R0, /* reset=*/ U8X8_PIN_NONE);


void drawCircle(){
  oled.clearBuffer();
  oled.drawCircle(x, y, 2);
  oled.sendBuffer();
}

void setup() {
  // put your setup code here, to run once:
  Serial.begin(19200);
  oled.setI2CAddress(0x78);
  oled.begin();
  drawCircle();
}

void loop() {
  // put your main code here, to run repeatedly:
  rt1.process();
  rt2.process();
  if (redraw){
    Serial.printf("x: %i y: %i\n", x, y);
    redraw=false;
    drawCircle();
  }
}
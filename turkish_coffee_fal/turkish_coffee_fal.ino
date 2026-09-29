#include <TFT_eSPI.h>

TFT_eSPI tft = TFT_eSPI();

void setup() {
  tft.init();
  tft.setRotation(1);   // 1 = landscape, 2 = portrait
}

uint16_t coffeeColor  = 0x38E1;
uint16_t foamColor    = 0xBC6B;
uint16_t creamColor   = 0xEEF8;
uint16_t groundsColor = 0x28C1;

void loop() {
  foam();
}

void foam(){
  tft.fillScreen(coffeeColor);
  for (int i = 0; i < 900; i++) {
    int16_t x = random(tft.width());
    int16_t y = random(tft.height());
    int16_t r = random(3, 10);
    if (random(100) < 25) {
      tft.fillCircle(x, y, r, coffeeColor);   // pop bubble
    } else {
      tft.fillCircle(x, y, r, foamColor);
      tft.drawCircle(x, y, r, creamColor);    // light edge
    }
    delay(20);
  }
}

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
  flipCup();
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

void flipCup(){
  // cream grows out from the center until reaches the corners
  for (int16_t r = 0; r <= tft.width() / 2 + 20; r += 3) {
    tft.fillCircle(tft.width() / 2, tft.height() / 2, r, creamColor);
    delay(20);
  }
}

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
  int fal = random(2);   // 0 = moon, 1 = star
  foam();
  flipCup();
  grounds(fal);
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

void grounds(int fal){
  int16_t x = 0;
  int16_t y = 0;
  for (int i = 0; i < 1500; i++) {
    x += random(-3, 4);   // -3 to 3
    y += random(-3, 4);

    if (random(100) < 3) {
      x = -1;   // new splotch
    }
    while (!inShape(fal, x, y)) {   // pick spots until one is inside the shape
      x = random(tft.width());
      y = random(tft.height());
    }
    tft.fillCircle(x, y, random(1, 4), groundsColor);

    // stray specks
    if (random(100) < 15) {
      tft.fillCircle(random(tft.width()), random(tft.height()), 1, groundsColor);
    }
    delay(10);
  }
}

bool inShape(int fal, int16_t x, int16_t y){
  if (fal == 0) {
    // moon = big circle with a second circle taking a bite out of it
    return inCircle(x, y, 172, 67, 55) && !inCircle(x, y, 197, 58, 48);
  }
  // star = a tall diamond and a wide diamond crossed, plus a circle in the middle
  int16_t dx = abs(x - 172);
  int16_t dy = abs(y - 67);
  return dx * 60 + dy * 18 < 18 * 60 || dx * 18 + dy * 60 < 18 * 60 || inCircle(x, y, 172, 67, 20);
}

bool inCircle(int16_t x, int16_t y, int16_t cx, int16_t cy, int16_t r){
  return (x - cx) * (x - cx) + (y - cy) * (y - cy) < r * r;
}

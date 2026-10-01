#include <TFT_eSPI.h>

TFT_eSPI tft = TFT_eSPI();

void setup() {
  tft.init();
  tft.setRotation(1);  
}

uint16_t coffeeColor    = 0x38E1;
uint16_t foamColor      = 0xBC6B;
uint16_t foamLightColor = 0xDDD1;
uint16_t creamColor     = 0xEEF8;
uint16_t groundsColor   = 0x28C1;
uint16_t midColor       = 0x6A25;
uint16_t stainColor     = 0xDE14;

void loop() {
  int fal = random(2);   // 0 = moon, 1 = star
  foam();
  flipCup();
  stains();
  grounds(fal);
  showFortune(fal);
  delay(6000);   // time to read fortune
}

void foam(){
  tft.fillScreen(coffeeColor);
  for (int i = 0; i < 1200; i++) {
    int16_t x = random(tft.width());
    int16_t y = random(tft.height());
    int16_t r = random(2, 7);
    if (random(100) < 25) {
      tft.fillCircle(x, y, r, coffeeColor);   // pop bubble
    } else {
      if (random(3) == 0) {
        tft.fillCircle(x, y, r, foamLightColor);
      } else {
        tft.fillCircle(x, y, r, foamColor);
      }
      tft.drawCircle(x, y, r, creamColor);    // light edge
    }
    delay(8);
  }
}

void flipCup(){
  // cream grows out from the center
  for (int16_t r = 0; r <= tft.width() / 2 + 20; r += 3) {
    tft.fillCircle(tft.width() / 2, tft.height() / 2, r, creamColor);
    delay(20);
  }
}

void stains(){
  // light coffee stains
  for (int i = 0; i < 12; i++) {
    int16_t sx = random(tft.width());
    int16_t sy = random(tft.height());
    for (int j = 0; j < 5; j++) {
      tft.fillCircle(sx + random(-10, 11), sy + random(-6, 7), random(4, 10), stainColor);
    }
    for (int j = 0; j < 6; j++) {
      tft.fillCircle(sx + random(-12, 13), sy + random(-8, 9), random(0, 2), midColor);
    }
    delay(100);
  }
}

void grounds(int fal){
  int16_t x = 0;
  int16_t y = 0;
  for (int i = 0; i < 1500; i++) {
    x += random(-3, 4);   
    y += random(-3, 4);

    if (random(100) < 3) {
      x = -1;   // new splotch
    }
    while (!inShape(fal, x, y)) {   // pick spots until one is inside shape
      x = random(tft.width());
      y = random(tft.height());
    }
    if (random(2) == 0) {
      tft.fillCircle(x, y, random(1, 4), groundsColor);
    } else {
      tft.fillCircle(x, y, random(1, 4), midColor);   
    }

    // stray specks
    if (random(100) < 15) {
      tft.fillCircle(random(tft.width()), random(tft.height()), random(0, 2), midColor);
    }
    delay(10);
  }
}

bool inShape(int fal, int16_t x, int16_t y){
  if (fal == 0) {
    // moon = big circle with a second circle 
    return inCircle(x, y, 172, 67, 55) && !inCircle(x, y, 197, 58, 48);
  }
  // star = a tall diamond and a wide diamond crossed
  int16_t dx = abs(x - 172);
  int16_t dy = abs(y - 67);
  return dx * 60 + dy * 18 < 18 * 60 || dx * 18 + dy * 60 < 18 * 60 || inCircle(x, y, 172, 67, 20);
}

bool inCircle(int16_t x, int16_t y, int16_t cx, int16_t cy, int16_t r){
  return (x - cx) * (x - cx) + (y - cy) * (y - cy) < r * r;
}

void showFortune(int fal){
  String word = "Luck";
  if (fal == 0) {
    word = "Success";
  }

  tft.setTextFont(4);
  tft.setTextSize(1);
  int16_t w = tft.textWidth(word) + 16;
  int16_t boxX = 58 - w / 2;

  tft.fillRoundRect(boxX, 49, w, 38, 10, coffeeColor);
  tft.drawRoundRect(boxX, 49, w, 38, 10, foamColor);
  tft.setTextColor(creamColor);
  tft.setCursor(boxX + 8, 55);
  tft.print(word);
}

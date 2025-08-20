#include <M5Stack.h>
#include "img/header.h"
#include "img/contents.h"
#include "img/footer.h"
#include "img/medium.h"

TFT_eSprite sprite(&M5.Lcd);
const int VERSION[3] = { 1, 0, 0 };
const int SCREEN_WIDTH = 320;
const int SCREEN_HEIGHT = 240;

bool redraw = false;
int count = 0;
int h = 0;
int m = 0;
int s = 0;

void setup() {
  M5.begin();
  M5.Lcd.setSwapBytes(true);
  M5.Lcd.setBrightness(255);
  sprite.createSprite(SCREEN_WIDTH, 102);
  redraw = true;
}

void loop() {
  M5.update();
  if (redraw == true) {
    M5.Lcd.startWrite();
    // Header
    sprite.pushImage(0, 0, SCREEN_WIDTH, 58, header);
    drawMedium(217, 8, h / 10);
    drawMedium(233, 8, h % 10);
    drawMedium(264, 8, m / 10);
    drawMedium(280, 8, m % 10);
    sprite.pushSprite(0, 0);
    // Main
    sprite.pushImage(0, 0, SCREEN_WIDTH, 80, contents);
    sprite.pushSprite(0, 58);
    // Footer
    sprite.pushImage(0, 0, SCREEN_WIDTH, 102, footer);
    sprite.pushSprite(0, 138);
    M5.Lcd.endWrite();
    redraw = false;
  }
  count++;
  if (count == 30) {
    s++;
    if (s >= 60) {
      redraw = true;
      s = 0;
      m++;
    }
    if (m >= 60) {
      m = 0;
      h++;
    }
    if (h >= 100) {
      h = 0;
    }
    count = 0;
  }
  delay(1000 / 30);
}

void drawMedium(int x, int y, int i) {
  unsigned short medium[320];
  int msize = sizeof(medium);
  switch (i) {
    case 0:
      memcpy(medium, medium0, msize);
      break;
    case 1:
      memcpy(medium, medium1, msize);
      break;
    case 2:
      memcpy(medium, medium2, msize);
      break;
    case 3:
      memcpy(medium, medium3, msize);
      break;
    case 4:
      memcpy(medium, medium4, msize);
      break;
    case 5:
      memcpy(medium, medium5, msize);
      break;
    case 6:
      memcpy(medium, medium6, msize);
      break;
    case 7:
      memcpy(medium, medium7, msize);
      break;
    case 8:
      memcpy(medium, medium8, msize);
      break;
    case 9:
      memcpy(medium, medium9, msize);
      break;
  }
  sprite.pushImage(x, y, 16, 20, medium);
  return;
}

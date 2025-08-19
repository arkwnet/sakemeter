#include <M5Stack.h>
#include "img/background.h"

TFT_eSprite sprite(&M5.Lcd);
const int VERSION[3] = { 1, 0, 0 };
const int SCREEN_WIDTH = 320;
const int SCREEN_HEIGHT = 240;
int count = 0;

void setup() {
  M5.begin();
  M5.Lcd.setSwapBytes(true);
  M5.Lcd.setBrightness(255);
  sprite.createSprite(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2);
}

void loop() {
  M5.update();
  if (count % 10 == 0) {
    M5.Lcd.startWrite();
    // 左上
    sprite.pushImage(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, background);
    sprite.pushSprite(0, 0);
    // 左下
    sprite.pushImage(0, -1 * (SCREEN_HEIGHT / 2), 320, 240, background);
    sprite.pushSprite(0, SCREEN_HEIGHT / 2);
    // 右上
    sprite.pushImage(-1 * (SCREEN_WIDTH / 2), 0, 320, 240, background);
    sprite.pushSprite(SCREEN_WIDTH / 2, 0);
    // 右下
    sprite.pushImage(-1 * (SCREEN_WIDTH / 2), -1 * (SCREEN_HEIGHT / 2), 320, 240, background);
    sprite.pushSprite(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2);
    M5.Lcd.endWrite();
  }
  count++;
  if (count == 30) {
    count = 0;
  }
  delay(1000);
}

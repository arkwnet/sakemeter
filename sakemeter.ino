#include <M5Stack.h>
#include "img/header.h"
#include "img/contents.h"
#include "img/footer.h"

TFT_eSprite sprite(&M5.Lcd);
const int VERSION[3] = { 1, 0, 0 };
const int SCREEN_WIDTH = 320;
const int SCREEN_HEIGHT = 240;
int count = 0;

void setup() {
  M5.begin();
  M5.Lcd.setSwapBytes(true);
  M5.Lcd.setBrightness(255);
  sprite.createSprite(SCREEN_WIDTH, 102);
}

void loop() {
  M5.update();
  if (count % 10 == 0) {
    M5.Lcd.startWrite();
    // Header
    sprite.pushImage(0, 0, SCREEN_WIDTH, 58, header);
    sprite.pushSprite(0, 0);
    // Main
    sprite.pushImage(0, 0, SCREEN_WIDTH, 80, contents);
    sprite.pushSprite(0, 58);
    // Footer
    sprite.pushImage(0, 0, SCREEN_WIDTH, 102, footer);
    sprite.pushSprite(0, 138);
  }
  count++;
  if (count == 30) {
    count = 0;
  }
  delay(1000);
}

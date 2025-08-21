#include <M5Stack.h>
#include "img/header.h"
#include "img/contents.h"
#include "img/footer.h"
#include "img/large.h"
#include "img/medium.h"
#include "img/type.h"
#include "img/amount.h"

const int VERSION[3] = { 1, 0, 0 };
const int SCREEN_WIDTH = 320;
const int SCREEN_HEIGHT = 240;

bool redrawHeader = false;
int redrawContents = -1;
bool redrawFooter = false;
unsigned short large[4][4032];
int count = 0;
int h = 0;
int m = 0;
int s = 0;
int alcohol = 0;
int select1 = 0;
int select2 = 0;

void setup() {
  M5.begin();
  setCpuFrequencyMhz(80);
  M5.Lcd.setSwapBytes(true);
  M5.Lcd.setBrightness(255);
  redrawHeader = true;
  redrawContents = 0;
  redrawFooter = true;
}

void loop() {
  M5.update();
  if (redrawHeader == true) {
    M5.Lcd.startWrite();
    M5.Lcd.pushImage(0, 0, SCREEN_WIDTH, 34, header);
    drawMedium(217, 8, h / 10);
    drawMedium(233, 8, h % 10);
    drawMedium(264, 8, m / 10);
    drawMedium(280, 8, m % 10);
    M5.Lcd.endWrite();
    redrawHeader = false;
  }
  if (redrawContents >= 0) {
    M5.Lcd.startWrite();
    if (redrawContents == 0) {
      M5.Lcd.pushImage(0, 34, SCREEN_WIDTH, 104, contents);
      if (alcohol >= 1000) {
        getLarge(0, alcohol / 1000 % 10);
      }
      if (alcohol >= 100) {
        getLarge(1, alcohol / 100 % 10);
      }
      if (alcohol >= 10) {
        getLarge(2, alcohol / 10 % 10);
      } else {
        getLarge(2, 0);
      }
      getLarge(3, alcohol % 10);
    }
    for (int i = 0; i < 16; i++) {
      for (int x = 0; x < 56; x++) {
        int t = redrawContents * 56 + x;
        if (alcohol >= 1000) {
          if (large[0][t] != 0x0000) {
            M5.Lcd.drawPixel(4 + x, 60 + redrawContents, large[0][t]);
          }
        }
        if (alcohol >= 100) {
          if (large[1][t] != 0x0000) {
            M5.Lcd.drawPixel(64 + x, 60 + redrawContents, large[1][t]);
          }
        }
        if (large[2][t] != 0x0000) {
          M5.Lcd.drawPixel(124 + x, 60 + redrawContents, large[2][t]);
        }
        if (large[3][t] != 0x0000) {
          M5.Lcd.drawPixel(218 + x, 60 + redrawContents, large[3][t]);
        }
      }
      redrawContents++;
      if (redrawContents >= 72) {
        redrawContents = -1;
        break;
      }
    }
    M5.Lcd.endWrite();
  }
  if (redrawFooter == true) {
    M5.Lcd.startWrite();
    M5.Lcd.pushImage(0, 138, SCREEN_WIDTH, 102, footer);
    drawType();
    drawAmount();
    M5.Lcd.endWrite();
    redrawFooter = false;
  }
  if (M5.BtnA.wasReleased()) {
    select1++;
    if (select1 >= 6) {
      select1 = 0;
    }
    redrawFooter = true;
  }
  if (M5.BtnB.wasReleased() && redrawContents == -1) {
    drink();
  }
  if (M5.BtnC.wasReleased()) {
    select2++;
    if (select2 >= 5) {
      select2 = 0;
    }
    redrawFooter = true;
  }
  count++;
  if (count == 30) {
    s++;
    if (s >= 60) {
      if (alcohol > 0) {
        alcohol--;
        redrawHeader = true;
        redrawContents = 0;
      }
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

void getLarge(int p, int i) {
  int bsize = sizeof(large[p]);
  switch (i) {
    case 0:
      memcpy(large[p], large0, bsize);
      break;
    case 1:
      memcpy(large[p], large1, bsize);
      break;
    case 2:
      memcpy(large[p], large2, bsize);
      break;
    case 3:
      memcpy(large[p], large3, bsize);
      break;
    case 4:
      memcpy(large[p], large4, bsize);
      break;
    case 5:
      memcpy(large[p], large5, bsize);
      break;
    case 6:
      memcpy(large[p], large6, bsize);
      break;
    case 7:
      memcpy(large[p], large7, bsize);
      break;
    case 8:
      memcpy(large[p], large8, bsize);
      break;
    case 9:
      memcpy(large[p], large9, bsize);
      break;
  }
  return;
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
  M5.Lcd.pushImage(x, y, 16, 20, medium);
  return;
}

void drawType() {
  int dx = 7;
  int dy = 149;
  int dw = 146;
  int dh = 38;
  switch (select1) {
    case 0:
      M5.Lcd.pushImage(dx, dy, dw, dh, type0);
      break;
    case 1:
      M5.Lcd.pushImage(dx, dy, dw, dh, type1);
      break;
    case 2:
      M5.Lcd.pushImage(dx, dy, dw, dh, type2);
      break;
    case 3:
      M5.Lcd.pushImage(dx, dy, dw, dh, type3);
      break;
    case 4:
      M5.Lcd.pushImage(dx, dy, dw, dh, type4);
      break;
    case 5:
      M5.Lcd.pushImage(dx, dy, dw, dh, type5);
      break;
  }
  return;
}

void drawAmount() {
  int dx = 167;
  int dy = 149;
  int dw = 146;
  int dh = 38;
  switch (select2) {
    case 0:
      M5.Lcd.pushImage(dx, dy, dw, dh, amount0);
      break;
    case 1:
      M5.Lcd.pushImage(dx, dy, dw, dh, amount1);
      break;
    case 2:
      M5.Lcd.pushImage(dx, dy, dw, dh, amount2);
      break;
    case 3:
      M5.Lcd.pushImage(dx, dy, dw, dh, amount3);
      break;
    case 4:
      M5.Lcd.pushImage(dx, dy, dw, dh, amount4);
      break;
  }
  return;
}

void drink() {
  float t;
  int a;
  switch (select1) {
    case 0:
      t = 0.4;
      break;
    case 1:
      t = 0.6;
      break;
    case 2:
      t = 1.0;
      break;
    case 3:
      t = 1.2;
      break;
    case 4:
      t = 2.0;
      break;
    case 5:
      t = 3.2;
      break;
  }
  switch (select2) {
    case 0:
      a = 45;
      break;
    case 1:
      a = 150;
      break;
    case 2:
      a = 300;
      break;
    case 3:
      a = 500;
      break;
    case 4:
      a = 800;
      break;
  }
  alcohol += (int)(t * a);
  if (alcohol >= 10000) {
    alcohol = 9999;
  }
  redrawContents = 0;
  return;
}

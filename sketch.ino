#include <Adafruit_SSD1306.h>
Adafruit_SSD1306 oled(128, 64, &Wire, -1);

int playerY = 10;
const int playerX = 10;
const int playerW = 6;
const int playerH = 6;

int velocity = 0;
int gravity = 1;

const int jumpBtn = 3;
bool lastBtnState = HIGH;
int jumpForce = -4;

int wallX = 128;
const int wallW = 10;
int gapY = 20;
const int gapH = 25;

void setup() {
  oled.begin(SSD1306_SWITCHCAPVCC, 0x3C);
  pinMode(jumpBtn, INPUT_PULLUP);
}

void loop() {
  bool currentBtnState = digitalRead(jumpBtn);

    if (isGameOver) {
    oled.clearDisplay();
 //Restart
    if (lastBtnState == HIGH && currentBtnState == LOW) {
      playerY = 32;
      velocity = 0;
      wallX = 128;
      isGameOver = false;
    }
    lastBtnState = currentBtnState;
    return;
  }


  if (lastBtnState == HIGH && currentBtnState == LOW) {
    velocity = jumpForce;
  }
  lastBtnState = currentBtnState;

  velocity += gravity;
  playerY += velocity;

  wallX -= 4;
 
  if (wallX < -wallW) {
    wallX = 128;
    gapY = random(5, 40);
  }

    if (playerY > 64 || playerY < 0) {
    isGameOver = true;
  }
  if (playerX + playerH > wallX && playerX < wallX + wallW) {
    if (playerY < gapY || playerY + playerW > gapY + gapH) {
      isGameOver = true;
    }
  }

  oled.clearDisplay();

  oled.fillRect(playerX, playerY, playerW, playerH, 1);

  oled.fillRect(wallX, 0, wallW, gapY, 1);
  oled.fillRect(wallX, gapY + gapH, wallW, 64 - (gapY + gapH), 1);
 
  oled.display();
  delay(30);
}




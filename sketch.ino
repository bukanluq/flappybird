#include <Wire.h>
#include <Adafruit_GFX.h>
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

bool isGameOver = false;

void setup() {
  // Generate a random seed from an unconnected analog pin for truly random walls
  randomSeed(analogRead(0));

  // Initialize the OLED. It's good practice to check if it succeeds.
  if(!oled.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
    for(;;); // Loop forever if OLED allocation fails
  }
  
  pinMode(jumpBtn, INPUT_PULLUP);
  isGameOver = false;
}

void loop() {
  bool currentBtnState = digitalRead(jumpBtn);

  if (isGameOver) {
    oled.clearDisplay();
    // Optional: You could draw "Game Over" text here!
    oled.display();
    
    // Restart logic
    if (lastBtnState == HIGH && currentBtnState == LOW) {
      playerY = 32;
      velocity = 0;
      wallX = 128;
      isGameOver = false;
    }
    lastBtnState = currentBtnState;
    return;
  }

  // Jump logic
  if (lastBtnState == HIGH && currentBtnState == LOW) {
    velocity = jumpForce;
  }
  lastBtnState = currentBtnState;

  // Physics
  velocity += gravity;
  playerY += velocity;

  // Wall movement
  wallX -= 4;
  
  if (wallX < -wallW) {
    wallX = 128;
    gapY = random(5, 40);
  }

  // Collision: Screen Bounds (Ceiling and Floor)
  if (playerY + playerH >= 64 || playerY <= 0) {
    isGameOver = true;
  }
  
  // Collision: Walls and Gaps (Fixed W/H mix-up)
  if (playerX + playerW > wallX && playerX < wallX + wallW) {
    if (playerY < gapY || playerY + playerH > gapY + gapH) {
      isGameOver = true;
    }
  }

  // Render Frame
  oled.clearDisplay();

  // Draw Player
  oled.fillRect(playerX, playerY, playerW, playerH, SSD1306_WHITE);
  //oled.drawBitmap(playerX, playerY, myBitmap, 32, 32, 1);

  // Draw Top Wall
  oled.fillRect(wallX, 0, wallW, gapY, SSD1306_WHITE);
  // Draw Bottom Wall
  oled.fillRect(wallX, gapY + gapH, wallW, 64 - (gapY + gapH), SSD1306_WHITE);
  
  oled.display();
  delay(30);
}

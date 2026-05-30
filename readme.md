Slide Show: https://docs.google.com/presentation/d/1ZeN5EIHg4GbrQnU4ulExGstJnQjHDfnnP_rsh1DP4TA/edit?usp=sharing

https://docs.google.com/presentation/d/1ZeN5EIHg4GbrQnU4ulExGstJnQjHDfnnP_rsh1DP4TA/edit?usp=sharing


# Arduino OLED Player Example

A simple Arduino project using an OLED display with the `Adafruit_SSD1306` library.  
This example draws a small square player on the screen.

---

## 📦 Requirements

Make sure the following libraries are installed in the Arduino IDE:

- Adafruit SSD1306
- Adafruit GFX

You can install them from:

`Arduino IDE → Library Manager`

---

## 🔌 Hardware Used

- Arduino board
- SSD1306 OLED Display (128x64, I2C)
- Jumper wires

### Default I2C Address
```cpp
0x3C
```

---

## 🧠 Features

- Initializes OLED display
- Draws a player square
- Refreshes the screen continuously

---

## 📄 Code

```cpp
#include <Adafruit_SSD1306.h>

Adafruit_SSD1306 oled(128, 64, &Wire, -1);

int playerY = 10;

const int playerX = 10;
const int playerW = 6;
const int playerH = 6;

void setup() {
  oled.begin(SSD1306_SWITCHCAPVCC, 0x3C);
}

void loop() {
  oled.clearDisplay();

  oled.fillRect(playerX, playerY, playerW, playerH, SSD1306_WHITE);

  oled.display();

  delay(30);
}
```

---

## 🖥️ Output

The OLED screen will display a small white square representing the player.

---

## 🚀 Future Improvements

Possible upgrades for this project:

- Add player movement using buttons or joystick
- Add gravity and jumping
- Create obstacles
- Add score system
- Turn it into a mini platformer game

---

## 📚 Library Documentation

- Adafruit SSD1306 Library
- Adafruit GFX Library

---

## 👨‍💻 Author

Made with Arduino and OLED display.

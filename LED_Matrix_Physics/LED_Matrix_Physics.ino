#include <SPI.h>
#include <Adafruit_GFX.h>
#include <Max72xxPanel.h>

// General matrix variables
const unsigned char CS = 10, hDisplays = 4, vDisplays = 1;
Max72xxPanel matrix = Max72xxPanel(CS, hDisplays, vDisplays);
bool invertedDisplay = false;

// Box simulation variables
char boxX = 0, boxY = 0, boxSize = 3; bool boxFill = false;

void setup() {
  // Serial.begin(115200);
  matrix.setIntensity(5);
  for(char i = 0; i < 4; i++) matrix.setRotation(i, 1);
  clearDisplay();
}

void loop() {
  for(char i = 0; i < 20; i++) {
    drawBox(true);
    addBoxX(1);
    delay(100);
  }
  for(char i = 0; i < 10; i++) {
    drawBox(true);
    addBoxY(1);
    delay(100);
  }
  for(char i = 0; i < 20; i++) {
    drawBox(true);
    addBoxX(-1);
    delay(100);
  }
  for(char i = 0; i < 10; i++) {
    drawBox(true);
    addBoxY(-1);
    delay(100);
  }
}

// Adds to the x coordinate of the box, making sure the box stays inside the grid
void addBoxX(int amount) {
  boxX += amount;
  if(boxX < 0) boxX = 0;
  else if(boxX > matrix.width() - boxSize) boxX = matrix.width() - boxSize;
}

// Adds to the y coordinate of the box, making sure the box stays inside the grid
void addBoxY(int amount) {
  boxY += amount;
  if(boxY < 0) boxY = 0;
  else if(boxY > matrix.height() - boxSize) boxY = matrix.height() - boxSize;
}

// Draws a box with the current box coordinates and size
// clearBeforeDrawing: Clears the display before drawing if true
void drawBox(bool clearBeforeDrawing) {
  if(clearBeforeDrawing) matrix.fillScreen(invertedDisplay);

  if(boxFill) matrix.fillRect(boxX, boxY, boxSize, boxSize, !invertedDisplay);
  else matrix.drawRect(boxX, boxY, boxSize, boxSize, !invertedDisplay);

  matrix.write();
}

// Clears the display
void clearDisplay() {
  matrix.fillScreen(invertedDisplay);
  matrix.write();
}

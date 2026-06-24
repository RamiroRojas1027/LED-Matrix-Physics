#include <SPI.h>
#include <Adafruit_GFX.h>
#include <Max72xxPanel.h>

// General matrix variables
const unsigned char CS = 10, hDisplays = 4, vDisplays = 1;
Max72xxPanel matrix = Max72xxPanel(CS, hDisplays, vDisplays);
bool invertedDisplay = false;

// Box simulation variables
unsigned char boxX = 0, boxY = 0, boxSize = 5; bool boxFill = false;

void setup() {
  // Serial.begin(115200);
  matrix.setIntensity(5);
  for(char i = 0; i < 4; i++) matrix.setRotation(i, 1);
  clearDisplay();
}

void loop() {
  for(char i = 0; i < (matrix.width() - boxSize + 1); i++) {
    drawBox(true);
    boxX = i;
    delay(100);
  }
}

// Draws a box with the current box coordinates and size
// clearBeforeDrawing: Clears the display before drawing if true
void drawBox(bool clearBeforeDrawing) {
  if(clearBeforeDrawing) matrix.fillScreen(invertedDisplay);

  if(boxX < 0) boxX = 0;
  else if(boxX > matrix.width() - boxSize) boxX = matrix.width() - boxSize;
  if(boxY < 0) boxY = 0;
  else if(boxY > matrix.height() - boxSize) boxY = matrix.height() - boxSize;

  if(boxFill) matrix.fillRect(boxX, boxY, boxSize, boxSize, !invertedDisplay);
  else matrix.drawRect(boxX, boxY, boxSize, boxSize, !invertedDisplay);

  matrix.write();
}

// Clears the display
void clearDisplay() {
  matrix.fillScreen(invertedDisplay);
  matrix.write();
}

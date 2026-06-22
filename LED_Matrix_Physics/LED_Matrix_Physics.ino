#include <LedControl.h>

// General matrix variables
LedControl lc = LedControl(12, 11, 10, 4);   // DIN, CLK, CS, numDevices
const unsigned char WIDTH = 32, HEIGHT = 8;
bool invertedDisplay = false;

// Box simulation variables
unsigned char boxX = 0, boxY = 0, boxSize = 5; bool boxFill = false;

void setup() {
  // Serial.begin(115200);
  shutdownAll(false);
  setIntensityAll(5);
  clearDisplayAll();
}

void loop() {
  for(char i = 0; i < 32; i++) {
    drawBox(false);
    boxX = i;
    drawBox(true);
    delay(100);
  }
}

// Draws a box with the current box coordinates and size
// state: Draw box if true, erase box if false
void drawBox(bool state) {
  if(invertedDisplay) state = !state;
  
  if(boxX < 0) boxX = 0;
  else if(boxX > WIDTH - boxSize) boxX = WIDTH - boxSize;
  if(boxY < 0) boxY = 0;
  else if(boxY > HEIGHT - boxSize) boxY = HEIGHT - boxSize;

  for(char x = boxX; x < boxX + boxSize; x++) {
    for(char y = boxY; y < boxY + boxSize; y++) {
      if(!boxFill && x != boxX && x != (boxX + boxSize - 1) && y != boxY && y != (boxY + boxSize - 1)) continue;
      setLED(y, x, state);
    }
  }
}

// Logic for a general setLED function including all 4 matrices, allowing for an 8x32 matrix
// Also fixes rotation of each matrix (read more in documentation)
void setLED(int row, int col, bool state) {
  if(row < 0) row = 0;
  else if(row > 7) row = 7;
  if(col < 0) col = 0;
  else if(col > 31) col = 31;

  lc.setLed(col/8, 7 - row, 7 - (col % 8), state);
}

// Set the shutdown status of all matrices
void shutdownAll(bool status) {
  for(char i = 0; i < 4; i++) {
    lc.shutdown(i, status);
  }
}

// Set the intensity of all matrices
void setIntensityAll(char intensity) {
  if(intensity < 0) intensity = 0;
  else if(intensity > 15) intensity = 15;

  for(char i = 0; i < 4; i++) {
    lc.setIntensity(i, intensity);
  }
}

// Clear the display of all matrices
void clearDisplayAll() {
  for(char i = 0; i < 4; i++) {
    lc.clearDisplay(i);
    if(invertedDisplay) {
      for(char j = 0; j < 8; j++) {
        lc.setRow(i, j, 0b11111111);
      }
    }
  }
}
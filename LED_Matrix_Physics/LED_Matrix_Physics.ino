#include <LedControl.h>

// DIN, CLK, CS, numDevices
LedControl lc = LedControl(12, 11, 10, 4);

void setup() {
  // Serial.begin(115200);
  shutdownAll(false);
  setIntensityAll(5);
  clearDisplayAll();
}

void loop() {
  for(char i = 0; i < 32; i++) {
    setLED(0, i, 1);
    delay(100);
    setLED(0, i, 0);
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
  }
}
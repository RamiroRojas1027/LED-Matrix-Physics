#include <LedControl.h>

// DIN, CLK, CS, numDevices
LedControl lc = LedControl(12, 11, 10, 4);

void setup() {
  // Serial.begin(115200);
  shutdownAll(false);
  setIntensityAll(5);
  lc.clearDisplay(0);
  lc.setLed(0, 0, 7, true);
}

void loop() {
  //
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

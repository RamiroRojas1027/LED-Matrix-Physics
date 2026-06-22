#include <LedControl.h>

// DIN, CLK, CS, numDevices
LedControl lc = LedControl(12, 11, 10, 4);

void setup() {
  // Serial.begin(115200);
  shutdownAll(false);
  setIntensityAll(5);
  lc.clearDisplay(0);
  for(char i = 0; i < 4; i++) {
    for(char j = 0; j < 8; j++) {
      lc.setRow(i, j, 0b11111111);
    }
  }
}

void loop() {
  for(char i = 0; i < 16; i++) {
    setIntensityAll(i);
    delay(1000);
  }
}

void shutdownAll(bool status) {
  for(char i = 0; i < 4; i++) {
    lc.shutdown(i, status);
  }
}

void setIntensityAll(char intensity) {
  if(intensity < 0) intensity = 0;
  else if(intensity > 15) intensity = 15;

  for(char i = 0; i < 4; i++) {
    lc.setIntensity(i, intensity);
  }
}

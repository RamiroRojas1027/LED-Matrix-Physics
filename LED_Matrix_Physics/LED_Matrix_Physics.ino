#include <LedControl.h>

// DIN, CLK, CS, numDevices
LedControl lc = LedControl(12, 11, 10, 4);

void setup() {
  // Serial.begin(115200);
  lc.shutdown(0, false);
  lc.shutdown(1, false);
  lc.shutdown(2, false);
  lc.shutdown(3, false);
  // lc.setIntensity(0, 15);
  // lc.setIntensity(1, 15);
  // lc.setIntensity(2, 15);
  // lc.setIntensity(3, 15);
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

void setIntensityAll(char intensity) {
  if(intensity < 0) intensity = 0;
  else if(intensity > 15) intensity = 15;

  for(char i = 0; i < 4; i++) {
    lc.setIntensity(i, intensity);
  }
}

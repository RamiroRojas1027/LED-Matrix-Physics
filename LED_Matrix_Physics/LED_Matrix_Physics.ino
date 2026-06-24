#include <SPI.h>
#include <Adafruit_GFX.h>
#include <Max72xxPanel.h>
#include <Wire.h>
#include <MPU6050.h>

// General matrix variables
const unsigned char CS = 10, hDisplays = 4, vDisplays = 1;
Max72xxPanel matrix = Max72xxPanel(CS, hDisplays, vDisplays);
bool invertedDisplay = false;

// Box simulation variables
char boxX = 0, boxY = 0, boxSize = 3;
float realBoxX = 0.0, realBoxY = 0.0;
bool boxFill = false;

MPU6050 mpu;

// Timers
unsigned long timer = 0;
float timeStep = 0.01;

// Pitch, Roll and Yaw values
float pitch = 0;
float roll = 0;
float yaw = 0;

// Gyro thresholds
float limit = 5.0;
float step = 0.2;

void setup() {
  // Serial.begin(115200);
  matrix.setIntensity(5);
  for(char i = 0; i < 4; i++) matrix.setRotation(i, 1);
  clearDisplay();

  // Initialize MPU6050
  while(!mpu.begin(MPU6050_SCALE_2000DPS, MPU6050_RANGE_2G)) {
    Serial.println("Could not find a valid MPU6050 sensor, check wiring!");
    delay(500);
  }

  // Calibrate gyroscope. The calibration must be at rest.
  // If you don't want calibrate, comment this line.
  // mpu.calibrateGyro();

  // Set threshold sensivty. Default 3.
  // If you don't want use threshold, comment this line or set 0.
  mpu.setThreshold(3);
}

void loop() {
  drawBox(true);
  updateGyro();
  if(roll >= limit) {
    addBoxX(step);
  } else if(roll <= -limit) {
    addBoxX(-step);
  }
  if(pitch >= limit) {
    addBoxY(-step);
  } else if(pitch <= -limit) {
    addBoxY(step);
  }
}

// Update gyroscope variables
void updateGyro() {
  timer = millis();

  // Read normalized values
  Vector norm = mpu.readNormalizeGyro();

  // Calculate Pitch, Roll and Yaw
  pitch = pitch + norm.YAxis * timeStep;
  roll = roll + norm.XAxis * timeStep;
  yaw = yaw + norm.ZAxis * timeStep;

  // Output raw
  // Serial.print(" Pitch = ");
  // Serial.print(pitch);
  // Serial.print(" Roll = ");
  // Serial.print(roll);  
  // Serial.print(" Yaw = ");
  // Serial.println(yaw);

  // Wait to full timeStep period
  delay((timeStep*1000) - (millis() - timer));
}

// Adds to the x coordinate of the box, making sure the box stays inside the grid
void addBoxX(float amount) {
  realBoxX += amount;
  boxX = int(realBoxX);
  if(boxX < 0) {
    boxX = 0;
    realBoxX = 0;
  }
  else if(boxX > matrix.width() - boxSize) {
    boxX = matrix.width() - boxSize;
    realBoxX = matrix.width() - boxSize;
  }
}

// Adds to the y coordinate of the box, making sure the box stays inside the grid
void addBoxY(float amount) {
  realBoxY += amount;
  boxY = int(realBoxY);
  if(boxY < 0) {
    boxY = 0;
    realBoxY = 0;
  }
  else if(boxY > matrix.height() - boxSize) {
    boxY = matrix.height() - boxSize;
    realBoxY = matrix.height() - boxSize;
  }
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

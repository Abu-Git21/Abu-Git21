#include <Wire.h>
#include <SPI.h>
#include "sensors.h"
#include "display.h"

void setup() {
  Serial.begin(115200);
  delay(1000);

  Wire.begin(21, 22);

  initDisplay();
  startupScreen();

  initSensors();
  sensorCheckScreen();
}

void loop() {
  readSensors();
  updateSystemStatus();
  drawDashboard();
  printSerialData();

  delay(2000);
}

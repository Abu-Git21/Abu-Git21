#ifndef DISPLAY_H
#define DISPLAY_H

#include <Arduino.h>
#include <Adafruit_GFX.h>
#include <Adafruit_ILI9341.h>

void initDisplay();
void startupScreen();
void sensorCheckScreen();
void drawDashboard();

#endif

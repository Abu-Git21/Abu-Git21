#ifndef SENSORS_H
#define SENSORS_H

#include <Arduino.h>
#include <Wire.h>
#include <SparkFun_SCD30_Arduino_Library.h>

extern SCD30 airSensor;

extern float co2;
extern float temperature;
extern float humidity;
extern int lightLevel;

extern String systemStatus;

void initSensors();
void readSensors();
void updateSystemStatus();
void printSerialData();

#endif

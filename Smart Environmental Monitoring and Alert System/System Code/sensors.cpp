#include "sensors.h"

#define LDR_PIN 34

SCD30 airSensor;

float co2 = 0;
float temperature = 0;
float humidity = 0;
int lightLevel = 0;

String systemStatus = "NORMAL";

void initSensors() {
  pinMode(LDR_PIN, INPUT);

  Serial.println("Checking SCD30...");

  if (airSensor.begin()) {
    Serial.println("SCD30 READY");
    airSensor.beginMeasuring();
  } else {
    Serial.println("SCD30 NOT DETECTED");
  }
}

void readSensors() {
  lightLevel = analogRead(LDR_PIN);

  if (airSensor.dataAvailable()) {
    co2 = airSensor.getCO2();
    temperature = airSensor.getTemperature();
    humidity = airSensor.getHumidity();
  }
}

void updateSystemStatus() {
  systemStatus = "NORMAL";

  if (co2 > 1000 || temperature > 30) {
    systemStatus = "WARNING";
  }

  if (co2 > 2000 || temperature > 40) {
    systemStatus = "ALERT";
  }
}

void printSerialData() {
  Serial.println();
  Serial.println("================================");
  Serial.println("ENVIRONMENTAL DATA");
  Serial.println("================================");

  Serial.print("CO2: ");
  Serial.print(co2);
  Serial.println(" ppm");

  Serial.print("Temperature: ");
  Serial.print(temperature);
  Serial.println(" C");

  Serial.print("Humidity: ");
  Serial.print(humidity);
  Serial.println(" %");

  Serial.print("Light Level: ");
  Serial.println(lightLevel);

  Serial.print("System Status: ");
  Serial.println(systemStatus);

  Serial.println("================================");
}

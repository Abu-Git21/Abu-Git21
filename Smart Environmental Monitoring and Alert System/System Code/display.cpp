#include "display.h"
#include "sensors.h"

#define TFT_CS   5
#define TFT_DC   27
#define TFT_RST  26

Adafruit_ILI9341 tft(TFT_CS, TFT_DC, TFT_RST);

void initDisplay() {
  tft.begin();
  tft.setRotation(1);
  tft.fillScreen(ILI9341_BLACK);
}

void startupScreen() {
  tft.fillScreen(ILI9341_BLACK);

  tft.setTextColor(ILI9341_CYAN);
  tft.setTextSize(2);

  tft.setCursor(30, 40);
  tft.println("SMART");

  tft.setCursor(30, 70);
  tft.println("ENVIRONMENTAL");

  tft.setCursor(30, 100);
  tft.println("MONITOR");

  delay(1500);

  tft.setTextColor(ILI9341_WHITE);
  tft.setTextSize(1);
  tft.setCursor(85, 150);
  tft.println("INITIALIZING...");

  tft.drawRect(40, 180, 240, 20, ILI9341_WHITE);

  for (int i = 0; i < 236; i += 4) {
    tft.fillRect(42, 182, i, 16, ILI9341_GREEN);
    delay(25);
  }

  delay(1000);
}

void sensorCheckScreen() {
  tft.fillScreen(ILI9341_BLACK);

  tft.setTextColor(ILI9341_WHITE);
  tft.setTextSize(2);
  tft.setCursor(30, 30);
  tft.println("SYSTEM CHECK");

  tft.setTextSize(1);

  tft.setCursor(30, 80);
  tft.println("SCD30: READY");

  tft.setCursor(30, 110);
  tft.println("LIGHT SENSOR: READY");

  delay(1500);
}

void drawDashboard() {
  tft.fillScreen(ILI9341_BLACK);

  tft.fillRect(0, 0, 320, 35, ILI9341_BLUE);

  tft.setTextColor(ILI9341_WHITE);
  tft.setTextSize(2);
  tft.setCursor(25, 10);
  tft.println("ENVIRONMENT MONITOR");

  tft.setTextColor(ILI9341_GREEN);
  tft.setCursor(20, 55);
  tft.print("CO2: ");
  tft.print(co2, 0);
  tft.println(" ppm");

  tft.setTextColor(ILI9341_ORANGE);
  tft.setCursor(20, 95);
  tft.print("TEMP: ");
  tft.print(temperature, 1);
  tft.println(" C");

  tft.setTextColor(ILI9341_CYAN);
  tft.setCursor(20, 135);
  tft.print("HUMIDITY: ");
  tft.print(humidity, 1);
  tft.println(" %");

  tft.setTextColor(ILI9341_YELLOW);
  tft.setCursor(20, 175);
  tft.print("LIGHT: ");
  tft.println(lightLevel);

  tft.drawRect(10, 205, 300, 30, ILI9341_WHITE);

  tft.setTextSize(1);
  tft.setCursor(20, 215);
  tft.setTextColor(ILI9341_WHITE);
  tft.print("SYSTEM STATUS: ");

  if (systemStatus == "NORMAL") {
    tft.setTextColor(ILI9341_GREEN);
  } else if (systemStatus == "WARNING") {
    tft.setTextColor(ILI9341_YELLOW);
  } else {
    tft.setTextColor(ILI9341_RED);
  }

  tft.println(systemStatus);
}

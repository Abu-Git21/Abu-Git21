# EnviroMonitor

## Overview

EnviroMonitor is an ESP32 based smart environmental monitoring system designed to collect and display real time environmental data.

The system monitors carbon dioxide levels, temperature, humidity, and ambient light conditions. Sensor data is displayed on a 2.8 inch TFT screen and printed to the Serial Monitor for testing and debugging.

The project combines embedded programming, sensor integration, analog input, I²C communication, and SPI display communication into a single monitoring system.

## Features

- Real time CO₂ monitoring
- Temperature monitoring
- Humidity monitoring
- Ambient light monitoring
- TFT display dashboard
- Serial Monitor output
- System startup screen
- Sensor initialization checks
- Environmental status monitoring
- Warning and alert conditions based on sensor readings

## Hardware

- ESP32 Development Board
- SCD30 CO₂, Temperature, and Humidity Sensor
- LDR Photoresistor
- 2.8 inch SPI TFT Display
- Breadboard
- Jumper Wires

## System Components

### SCD30 Environmental Sensor

The SCD30 monitors:

- Carbon dioxide concentration
- Temperature
- Humidity

The sensor communicates with the ESP32 using the I²C protocol.

### LDR Light Sensor

The LDR measures ambient light levels using an analog input on the ESP32.

### TFT Display

The TFT display provides a real time dashboard showing:

- CO₂ levels
- Temperature
- Humidity
- Light level
- System status

The display communicates with the ESP32 using SPI.

## Communication Protocols

| Component | Communication Method |
|---|---|
| SCD30 | I²C |
| LDR | Analog Input |
| TFT Display | SPI |

## Project Structure

```text
EnviroMonitor/
├── Smart_Environmental_Monitor.ino
├── sensors.h
├── sensors.cpp
├── display.h
├── display.cpp
├── README.md
└── images/

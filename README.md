# Solar Boat – STM32 FreeRTOS Main Control Software

This project contains the STM32-based **main control software** developed for a solar-powered hydrofoil boat. The software runs on the FreeRTOS real-time operating system and manages components such as ESC, servo motor for hydrofoils, GPS, sensors, and communication modules.

## System Overview

| Hardware Module          | Description |
|--------------------------|-------------|
| STM32F4 Series           | Main microcontroller (e.g., STM32F407VGT6, STM32F411CEU6) |
| ESC + BLDC Motor         | Speed control via PWM |
| Servo Motor              | Hydrofoil control |
| NEO-7M GPS               | Position and speed tracking |
| MPU6050                  | Accelerometer and gyroscope |
| ESP32 WiFi Module (UART) | Telemetry or remote control |
| TJA 1050                 | CANBUS communication |


## Features

- Multitasking architecture using FreeRTOS  
- ESC and servo motor control via PWM  
- UART-based communication with GPS and WiFi modules
- CANBUS-based communication with Battery Management System  
- Modular, readable, and portable code structure  
- Secure hardware connections using JST/GX locking connectors  
- Optional sensor reading via CANBUS and UART protocol
- High resulation analog reading for advanced tempurature control

## Build Instructions

1. Open the project in STM32CubeIDE  
2. You can modify the `.ioc` file using STM32CubeMX  
3. Use the **Build** & **Debug** options to flash via ST-Link


## Testing

- ESC PWM outputs were verified using an oscilloscope  
- Servo motor tested between 0°–180° angles  
- UART communication tested with RealTerm  
- GPS NMEA outputs were parsed and verified
- CANBUS communication tested with BMS outputs
- FreeRTOS task monitoring performed using `uxTaskGetSystemState()`  

## Developers

**Eren Eğdemir**  
Electrical Engineering – Yıldız Technical University  

**Furkan Ülger**  
Electrical Engineering – Yıldız Technical University  

**Yılmaz Uysal**  
Mechatronics Engineering – Yıldız Technical University

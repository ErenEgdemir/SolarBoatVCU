# Solar Boat – STM32 FreeRTOS Main Control Software

This project contains the STM32-based **main control software** developed for a solar-powered hydrofoil boat. The software runs on the FreeRTOS real-time operating system and manages components such as ESC, servo motor for hydrofoils, GPS, sensors, and communication modules.

## System Overview

| Hardware Module       | Description |
|------------------------|-------------|
| STM32F4 Series         | Main microcontroller (e.g., STM32F407VGT6, STM32F411CEU6) |
| ESC + BLDC Motor       | Speed control via PWM |
| Servo Motor            | Rudder control |
| NEO-7M GPS             | Position and speed tracking |
| MPU6050                | Accelerometer and gyroscope |
| WiFi Module (UART)     | Telemetry or remote control |


## Features

- Multitasking architecture using FreeRTOS  
- ESC and servo motor control via PWM  
- UART-based communication with GPS and WiFi modules  
- Modular, readable, and portable code structure  
- Secure hardware connections using JST/GX locking connectors  
- Optional sensor reading via RS-485 Modbus protocol  

## Project Structure

```
SolarBoat_Firmware/
├── Core/              → main.c, system initialization, clock configuration  
├── Drivers/           → ESC, Servo, GPS, MPU6050 drivers  
├── Tasks/             → FreeRTOS task files (Task.c/.h)  
├── Inc/               → Header files  
├── Src/               → Source files  
├── README.md  
├── .ioc               → STM32CubeMX project file  
└── Makefile / .project
```

## FreeRTOS Tasks

| Task Name           | Period | Description |
|---------------------|--------|-------------|
| `SensorTask`        | 50ms   | Reads sensors like MPU6050 and GPS |
| `ControlTask`       | 100ms  | Controls ESC and servo motor |
| `CommunicationTask` | 100ms  | Manages UART communication |
| `MonitorTask`       | 500ms  | Handles status LEDs and fault detection |

## Build Instructions

1. Open the project in STM32CubeIDE  
2. You can modify the `.ioc` file using STM32CubeMX  
3. Use the **Build** & **Debug** options to flash via ST-Link

Alternatively, use the Makefile to build from terminal.

## Testing

- ESC PWM outputs were verified using an oscilloscope  
- Servo motor tested between 0°–180° angles  
- UART communication tested with RealTerm  
- GPS NMEA outputs were parsed and verified  
- FreeRTOS task monitoring performed using `uxTaskGetSystemState()`  

## Developers

**Eren Eğdemir**  
Electrical Engineering – Yıldız Technical University  

**Furkan Ülger**  
Electrical Engineering – Yıldız Technical University  

**Yılmaz Uysal**  
Mechatronics Engineering – Yıldız Technical University

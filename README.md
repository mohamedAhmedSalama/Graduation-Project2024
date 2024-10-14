
# Driver Monitoring and Enhanced Child Safety in Vehicles

## Overview
This repository contains the source code and documentation for my graduation project, focused on enhancing child safety in vehicles through innovative AI and embedded systems technology. The project integrates driver monitoring and child safety systems to ensure safe transportation environments.

## Features
### Driver Monitoring System
- Utilizes YOLO v10 for real-time detection of driver distractions (e.g., looking away, drinking, smoking).
- Alerts driver with a red LED and audible buzzer when distraction or drowsiness is detected.
- Green LED indicates normal driving conditions.

### Facial Recognition and Vehicle Security
- Implements facial recognition to allow only authorized drivers to operate the vehicle.
- Prevents unauthorized access using advanced facial verification techniques.

### Child Safety System
- Monitors school bus environments to prevent incidents of children being left unattended.
- Tracks students using an attendance system upon bus disembarkation.
- Sends alerts to the driver and authorities if a child remains on the bus after disembarkation.

### Alert and Communication Modules
- Uses GSM and GPS modules to send SMS alerts with vehicle location when a child is detected in an unattended vehicle.
- Ensures timely intervention in emergency situations to safeguard children's welfare.

## Hardware Components
- Raspberry Pi 4 (8GB) for main processing and interface display.
- Raspberry Pi Camera Module 3 for driver monitoring.
- Raspberry Pi 7" Touchscreen for visual feedback and user interaction.
- STM32 F103C6 microcontrollers for embedded control tasks.
- GSM module for SMS communication.
- GPS module for vehicle location tracking.
- MCP 2515 CAN transceiver for network communication.
- LEDs and buzzer for visual and audible alerts.


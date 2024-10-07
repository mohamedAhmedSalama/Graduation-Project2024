# STM32F103 GPIO Driver

This repository contains a GPIO (General Purpose Input/Output) driver for STM32F103 microcontrollers. The driver provides functions to initialize, read, write, toggle, and configure GPIO pins.

## Table of Contents
- [Introduction](#introduction)
- [Features](#features)
- [File Structure](#file-structure)
- [Usage](#usage)
- [Under Review](#under-review)
- [Contributing](#contributing)
- [License](#license)

## Introduction

This GPIO driver is designed for STM32F103 microcontrollers and provides a simple interface for interacting with GPIO pins. It includes functions for pin initialization, reading, writing, toggling, and configuring different pin modes.

## Features

- **Initialization:** Initialize GPIO pins with various configurations.
- **Read/Write Operations:** Read and write individual pins or entire ports.
- **Toggle Operation:** Toggle the state of a specific pin.
- **Pin Locking:** Enable or disable pin locking to prevent accidental configuration changes.
- **Port Reading:** Read the entire state of a GPIO port.

## File Structure

The repository includes the following files:

- **STM32_F103xx.h:** Header file containing base addresses and structures for STM32F103 peripherals.
- **STM32_F103C6_GPIO.h:** Header file for the GPIO driver, including structures, macros, and function prototypes.
- **STM32_F103C6_GPIO.c:** Source file containing the implementation of GPIO driver functions.

## Usage

1. Include the necessary header file in your project:
    ```c
    #include "STM32_F103C6_GPIO.h"
    ```

2. Initialize GPIO pins using the `MCAL_GPIO_Init` function.
    ```c
    GPIO_typeDef* GPIOx = GPIOA;  // Replace with the desired GPIO port
    GPIO_pinConfig_typeDef PINx;

    // Configure PINx structure with desired parameters
    PINx.GPIO_pinNumber = GPIO_PIN_0;
    PINx.GPIO_mode = GPIO_MODE_OUTPUT_PUSH_PULL;
    PINx.GPIO_outputSpeed = GPIO_SPEED_OUTPUT_50M;

    // Initialize the GPIO pin
    MCAL_GPIO_Init(GPIOx, &PINx);
    ```

3. Use other GPIO functions for read, write, toggle, etc., as needed.



## Under Review

**Note: This GPIO driver is currently under review. Feedback and contributions are welcome.**

## Contributing

Contributions are welcome! If you find a bug or have an enhancement, feel free to open an issue or submit a pull request.

## License

This project is licensed under the [MIT License](LICENSE).

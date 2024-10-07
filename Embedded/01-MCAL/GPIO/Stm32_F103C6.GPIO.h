/**================================================================
 * @file         STM32_F103C6_GPIO.h
 * @brief        GPIO Peripheral Driver Header File
 * @version      1.0
 * @date         12/07/2023
 * @author       Khaled Salama (https://www.linkedin.com/in/5aledsalama/)
 *
 * @note         This header file provides definitions and configurations
 *               for the GPIO peripheral on the STM32F103C6 microcontroller.
 */

#ifndef STM32_F103C6_GPIO_H_
#define STM32_F103C6_GPIO_H_
#include "Stm32_F103xx.h"


//config structure

typedef struct{
	//specify the pin to be configered
	uint16_t GPIO_pinNumber;		//this parameter can be value of @ref GPIO_PINS_define

	//specify the operating mode for selected pin
	uint8_t  GPIO_mode;				//this parameter can be value of @ref GPIO_MODE_define

	//specify the speed of selected pins
	uint8_t  GPIO_outputSpeed;		//this parameter can be value of @ref GPIO_SPEED_define
}GPIO_pinConfig_typeDef;

//-----------------------------
//Macros Configuration References
//-----------------------------


//********************* @ref  GPIO_PINs_define***********************
#define GPIO_PIN_0			((uint16_t)0x0001)
#define GPIO_PIN_1			((uint16_t)0x0002)
#define GPIO_PIN_2			((uint16_t)0x0004)
#define GPIO_PIN_3			((uint16_t)0x0008)
#define GPIO_PIN_4			((uint16_t)0x0010)
#define GPIO_PIN_5			((uint16_t)0x0020)
#define GPIO_PIN_6			((uint16_t)0x0040)
#define GPIO_PIN_7			((uint16_t)0x0080)
#define GPIO_PIN_8			((uint16_t)0x0100)
#define GPIO_PIN_9			((uint16_t)0x0200)
#define GPIO_PIN_10			((uint16_t)0x0400)
#define GPIO_PIN_11			((uint16_t)0x0800)
#define GPIO_PIN_12			((uint16_t)0x1000)
#define GPIO_PIN_13			((uint16_t)0x2000)
#define GPIO_PIN_14			((uint16_t)0x4000)
#define GPIO_PIN_15			((uint16_t)0x8000)

#define GPIO_PIN_ALL    	((uint16_t)0xFFFF)
#define GPIO_PIN_MASK    	0x0000FFFFu


//********************@ref  GPIO_MODE_define************************
//0: Analog mode
//1: Floating input (reset state)
//2: pull-up
//3: pull-down
//4: General purpose output push-pull
//5: General purpose output Open-drain
//6: Alternate function output Push-pull
//7: Alternate function output Open-drain
//8: Alternative function input


#define GPIO_MODE_INPUT_ANALOG							0x00000000u
#define GPIO_MODE_INPUT_FLOATING						0x00000001u
#define GPIO_MODE_INPUT_PULL_UP							0x00000002u
#define GPIO_MODE_INPUT_PULL_DOWN						0x00000003u


#define GPIO_MODE_OUTPUT_PUSH_PULL						0x00000004u
#define GPIO_MODE_OUTPUT_OPEN_DRAIN						0x00000005u
#define GPIO_MODE_OUTPUT_ALTERNATE_PUSH_PULL			0x00000006u
#define GPIO_MODE_OUTPUT_ALTERNATE_OPEN_DRAIN			0x00000007u
#define GPIO_MODE_INPUT_ALTERNATE						0x00000008u

//********************@ref  GPIO_SPEED_define************************
//1: Output mode, max speed 10 MHz.
//2: Output mode, max speed 2 MHz.
//3: Output mode, max speed 50 MHz
#define GPIO_SPEED_OUTPUT_10M							0x00000001u
#define GPIO_SPEED_OUTPUT_2M							0x00000002u
#define GPIO_SPEED_OUTPUT_50M							0x00000003u

//********************@ref  GPIO_Pin_state************************
#define GPIO_PIN_SET									1
#define GPIO_PIN_RESET									0

//********************@ref  GPIO_LOCK_PIN************************
#define GPIO_PIN_LOCK_Active							1
#define GPIO_PIN_LOCK_Disabled							0

//*******************@ref GPIO_Return_defines************************

#define OK 						     1
#define ERROR 						 0

/*
* ===============================================
* APIs Supported by "MCAL GPIO DRIVER"
* ===============================================
*/

//initalize
void MCAL_GPIO_Init(GPIO_typeDef *GPIOx ,GPIO_pinConfig_typeDef *PINx);
void MCAL_GPIO_Dinit(GPIO_typeDef *GPIOx);
//Read
uint8_t MCAL_GPIO_READ_Pin(GPIO_typeDef *GPIOx, uint16_t pinNumber);
uint16_t MCAL_GPIO_READ_Port(GPIO_typeDef *GPIOx);
//Write
void MCAL_GPIO_WRITE_Pin(GPIO_typeDef* GPIOx,uint16_t pinNumber, uint8_t value);
void MCAL_GPIO_WRITE_Port(GPIO_typeDef* GPIOx, uint16_t value);

void MCAL_GPIO_TOGGLE_Pin(GPIO_typeDef* GPIOx,uint16_t pinNumber);
uint8_t MCAL_GPIO_LOCK_Pin(GPIO_typeDef* GPIOx,uint16_t pinNumber);
#endif /* STM32_F103C6_GPIO_H_ */

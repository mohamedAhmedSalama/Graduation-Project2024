/**================================================================
 * @file         Stm32_F103xx.h
 * @brief        STM32 F103xx Series Peripheral Definitions
 * @version      1.0
 * @date         12/07/2023
 * @author        Khaled Salama (https://www.linkedin.com/in/5aledsalama/)
 *
 * @note         This header file provides base addresses, structures,
 *               and macros for various peripherals of the STM32 F103xx series.
 */
#ifndef STM32_F103XX_H_
#define STM32_F103XX_H_

//-----------------------------
//Includes
//-----------------------------

#include"stdlib.h"
#include<stdint.h>
//-----------------------------
//Base addresses for Memories
//-----------------------------
#define FLASH_MEMORY_BASE				0x08000000UL
#define SYSTEM_MEMORY_BASE				0x1FFFF000UL
#define SRAM_BASE						0x20000000UL

#define PERIPHERALS_BASE 				0x40000000UL
#define CORTEX_M3_PERIPHERALS_BASE 	 	0xE0000000UL

//-----------------------------
//Base addresses for BUS Peripherals
//-----------------------------
//RCC
#define RCC_BASE						0x40021000UL

//***************************
//APB2 Peripheral Base address
//**************************

//******************GPIO***********************
//A,B fully included
#define GPIOA_BASE					0x40010800UL
#define GPIOB_BASE					0x40010C00UL

//C,D partial included
#define GPIOC_BASE					0x40011000UL
#define GPIOD_BASE					0x40011400UL

//E not included
#define GPIOE_BASE					0x40011800UL

//*****************External interrupt************
#define EXTI_BASE					0x40010400UL
//*****************Alternative function***********
#define AFIO_BASE					0x40010000UL


//-*-*-*-*-*-*-*-*-*-*-*-
//Peripheral register:
//-*-*-*-*-*-*-*-*-*-*-*

//GPIO Registers
typedef struct {
	volatile uint32_t CRL;
	volatile uint32_t CRH;
	volatile uint32_t IDR;
	volatile uint32_t ODR;
	volatile uint32_t BSRR;
	volatile uint32_t BRR;
	volatile uint32_t LCKR;
} GPIO_typeDef;

//RCC Registers
typedef struct {
	volatile uint32_t CR;
	volatile uint32_t CFGR;
	volatile uint32_t CIR;
	volatile uint32_t APB2RSTR;
	volatile uint32_t APB1RSTR;
	volatile uint32_t AHBENR;
	volatile uint32_t APB2ENR;
	volatile uint32_t APB1ENR;
	volatile uint32_t BDCR;
	volatile uint32_t CSR;

} RCC_typeDef;

//EXTI Registers
typedef struct {
	volatile uint32_t IMR;
	volatile uint32_t EMR;
	volatile uint32_t RTSR;
	volatile uint32_t FTSR;
	volatile uint32_t SWIER;
	volatile uint32_t PR;

} EXTI_typeDef;

//AFIO Registers
typedef struct {
	volatile uint32_t EVCR;
	volatile uint32_t MAPR;
	volatile uint32_t EXTICR1;
	volatile uint32_t EXTICR2;
	volatile uint32_t EXTICR3;
	volatile uint32_t EXTICR4;
	volatile uint32_t RESERVED; // hasn't address in register
	volatile uint32_t MAPR2;

} AFIO_typeDef;

//-*-*-*-*-*-*-*-*-*-*-*-
//Peripheral Instants:
//-*-*-*-*-*-*-*-*-*-*-*
#define GPIOA				((GPIO_typeDef*) GPIOA_BASE)
#define GPIOB				((GPIO_typeDef*) GPIOB_BASE)
#define GPIOC				((GPIO_typeDef*) GPIOC_BASE)
#define GPIOD				((GPIO_typeDef*) GPIOD_BASE)
#define GPIOE				((GPIO_typeDef*) GPIOE_BASE)

#define RCC					((RCC_typeDef*) RCC_BASE)

#define EXTI				((EXTI_typeDef*) EXTI_BASE)
#define AFIO				((AFIO_typeDef*) AFIO_BASE)

//-*-*-*-*-*-*-*-*-*-*-*-
//clock enable Macros:
//-*-*-*-*-*-*-*-*-*-*-*

#define RCC_GPIOA_CLK_EN   	(RCC->APB2ENR |=1<<2)	//Enable clock GPIOA
#define RCC_GPIOB_CLK_EN   	(RCC->APB2ENR |=1<<3)	//Enable clock GPIOB
#define RCC_GPIOC_CLK_EN  	(RCC->APB2ENR |=1<<4)	//Enable clock GPIOC
#define RCC_GPIOD_CLK_EN  	(RCC->APB2ENR |=1<<5)	//Enable clock GPIOD
#define RCC_GPIOE_CLK_EN  	(RCC->APB2ENR |=1<<6)	//Enable clock GPIOE

#define RCC_AFIO_CLK_EN  	(RCC->APB2ENR |=1<<0)	//Enable clock AFIO

//-*-*-*-*-*-*-*-*-*-*-*-
//Generic Macros:
//-*-*-*-*-*-*-*-*-*-*-*

//EXTI macros
#define EXTI0_IRQ			0
#define EXTI1_IRQ			1
#define EXTI2_IRQ			2
#define EXTI3_IRQ			3
#define EXTI4_IRQ			4
#define EXTI5_IRQ			5
#define EXTI6_IRQ			6
#define EXTI7_IRQ			7
#define EXTI8_IRQ			8
#define EXTI9_IRQ			9
#define EXTI10_IRQ			10
#define EXTI11_IRQ			11
#define EXTI12_IRQ			12
#define EXTI13_IRQ			13
#define EXTI14_IRQ			14
#define EXTI15_IRQ			15


#endif /* STM32_F103XX_H_ */


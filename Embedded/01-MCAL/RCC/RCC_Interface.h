/*
 *
 * Author	    :	Mohamed Ahmed
 * Date		    :	29 SEP 2023
 * Version		:	V01
 * Description  : 	RCC Interface header file
 *
 **/

#ifndef RCC_INTERFACE_H_
#define RCC_INTERFACE_H_

#include "../Inc/LIB/STD_TYPES.h"

/******************Clock sources************/
#define  HSI 0
#define  HSE 1
#define  PLL 2


/**************HSE Divided or Not**********/
#define HSE_NOT_DIVIDED 1
#define HSE_DIVIDED 	2

/**********Peripheral buses**************/
#define AHB  0
#define APB1 1
#define APB2 2

/*AHB peripherals*/
#define DMA1T		0
#define DMA2		1
#define SRAM		2
#define FLITF		4
#define CRCEN		6
#define FSMC		8
#define SDIO		10

/*APB1 peripheral*/
#define TIM2		0
#define TIM3		1
#define TIM4		2
#define TIM5		3
#define TIM6		4
#define TIM7		5
#define TIM12		6
#define TIM13		7
#define TIM14		8
#define WWDG		11
#define SPI2		14
#define SPI3		15
#define USART2		17
#define USART3		18
#define UART4		19
#define UART5		20
#define I2C1		21
#define I2C2		22
#define USB			23
#define CAN			25
#define BKP			27
#define PWR			28
#define DAC			29

/*APB2 peripheral*/
#define AFIO   		0
#define IOPA   		2
#define IOPB   		3
#define IOPC   		4
#define IOPD   		5
#define IOPE   		6
#define IOPF  		7
#define IOPG   		8
#define ADC1   		9
#define ADC2  		10
#define TIM1  		11
#define SPI1  		12
#define TIM8  		13
#define USART1		14
#define ADC3   		15
#define TIM9   		19
#define TIM10  		20
#define TIM11  		21


typedef enum{
	RCC_NotReady,
	RCC_Ready
}RCC_Status_t;

/*
 * @brief MRCC_voidInit :
 *  		this function used to initialize RCC
 */
void MRCC_voidInit(void);

/*
 * @brief MRCC_voidClkEnable :
 *          this function used to Enable the selected clock source
 * @param A_uint8ClkSource :  (HSI - HSE - PLL)
 */
void MRCC_voidClkEnable(uint8 A_uint8ClkSource);

/*
 * @brief MRCC_voidClkDisable :
 *          this function used to Disable the selected clock source
 * @param A_uint8ClkSource :  (HSI - HSE - PLL)
 */
void MRCC_voidClkDisable(uint8 A_uint8ClkSource);

/**
 * @brief  MRCC_RCCS_tatus_tCheckClockReady :
 *                  this fuction used to check the clock source is ready or not
 * @param A_uint8ClkSource :  (HSI - HSE - PLL)
 * @return     return RCC_Ready if the clock source is ready
 *             return RCC_NotReady if the clock source does not ready
 */
RCC_Status_t MRCC_RCCStatus_tCheckClockReady (uint8 A_uint8ClkSource);

/**
 * @brief  MRCC_voidSetClkSource
 *              this function is used to set the enabled clock source
 * @param A_u8ClkSource  :  (HSI - HSE - PLL)
 */
void MRCC_voidSetClkSource(uint8 A_uint8ClkSource);

/*
 * @brief MRCC_voidSetBusesPrescaler :
 *          this function used to set the prescaller for
 *              (AHB - APB1 - APB2)
 * @param A_uint8AHBPrescaler     AHB_PRESCALER   "setted by configuration"
 * @param A_uint8APB1Prescaler    ABP1_PRESCALER  "setted by configuration"
 * @param A_uint8APB2Prescaler    ABP2_PRESCALER  "setted by configuration"
 */
void MRCC_voidSetBusesPrescaler (uint8 A_uint8AHBPrescaler, uint8 A_uint8APB1Prescaler, uint8 A_uint8APB2Prescaler);

/**
 * @brief this function used to select the clock source for PLL
 *          and select the prescaler for the selected source
 * @param A_uint8ClkSource  PLL_SOURCE     "setted by configuration"
 * @param A_uint8Prescaler  PLL_HSE_FACTOR "setted by configuration"
 */
void MRCC_voidSetPLLSource(uint8 A_uint8ClkSource, uint8 A_uint8Prescaler);

/**
 * @brief MRCC_voidSetPLLMulFactor :
 *          this function used to select the multiplication factor for PLL input
 * @param A_uint8MulFactor PLL_MULTIPLICATION_FACTOR   "setted by configurations"
 */
void MRCC_voidSetPLLMulFactor(uint8 A_uint8MulFactor);

/**
 * @brief MRCC_voidPreipheralEnable
 *          this function is used to select the Bus and enable one of its peripherals
 * @param A_uint8BusID         BUS_ID      	   "AHB - APB1 - APB2"
 * @param A_uint8PrephieralID  PERIPHERAL_ID    "selected from above"
 */
void MRCC_voidPreipheralEnable (uint8 A_uint8BusID, uint8 A_uint8PrephieralID);

/**
 * @brief MRCC_voidPreipheralDisable
 *          this function is used to select the Bus and disable one of its peripherals
 * @param A_uint8BusID         BUS_ID      	   "AHB - APB1 - APB2"
 * @param A_uint8PrephieralID  PERIPHERAL_ID   "selected from above"
 */
void MRCC_voidPreipheralDisable (uint8 A_uint8BusID, uint8 A_uint8PrephieralID);

#endif

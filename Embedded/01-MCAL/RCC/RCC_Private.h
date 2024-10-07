/*
 *
 * Author	    :	Mohamed Ahmed
 * Date		    :	29 SEP 2023
 * Version		:	V01
 * Description  : 	RCC Private header file
 *
 **/

#ifndef RCC_PRIVATE_H_
#define RCC_PRIVATE_H_

#include "../Inc/LIB/STD_TYPES.h"

// RCC Base address
#define RCC_BASE	0x40021000

// RCC Registers
typedef struct{
	volatile uint32 CR;
	volatile uint32 CFGR;
	volatile uint32 CIR;
	volatile uint32 APB2RSTR;
	volatile uint32 APB1RSTR;
	volatile uint32 AHBENR;
	volatile uint32 APB2ENR;
	volatile uint32 APB1ENR;
	volatile uint32 BDCR;
	volatile uint32 CSR;
}RCC_t;

#define RCC ((volatile RCC_t*)(RCC_BASE))

/*********************************************************************
 * 																	 *
 * 					Registers Description							 *
 * 																	 *
 *********************************************************************/

/********************  Bits definition for RCC_CR register  **********/

// bits (26:31)  & (20:23) are reserved

#define RCC_CR_HSION                           0            /*!< Internal High Speed clock enable */
#define RCC_CR_HSIRDY                          1            /*!< Internal High Speed clock ready flag */
#define RCC_CR_HSITRIM_0                       3            /*!< Internal High Speed clock trimming */
#define RCC_CR_HSITRIM_1                       4
#define RCC_CR_HSITRIM_2                       5
#define RCC_CR_HSITRIM_3                       6
#define RCC_CR_HSITRIM_4                       7
#define RCC_CR_HSICAL_0                        8            /*!< Internal High Speed clock Calibration */
#define RCC_CR_HSICAL_1                        9
#define RCC_CR_HSICAL_2                        10
#define RCC_CR_HSICAL_3                        11
#define RCC_CR_HSICAL_4                        12
#define RCC_CR_HSICAL_5                        13
#define RCC_CR_HSICAL_6                        14
#define RCC_CR_HSICAL_7                        15
#define RCC_CR_HSEON                           16          /*!< External High Speed clock enable */
#define RCC_CR_HSERDY                          17          /*!< External High Speed clock ready flag */
#define RCC_CR_HSEBYP                          18          /*!< External High Speed clock Bypass */
#define RCC_CR_CSSON                           19          /*!< Clock Security System enable */
#define RCC_CR_PLLON                           24          /*!< PLL enable */
#define RCC_CR_PLLRDY                          25          /*!< PLL clock ready flag */


/********************  Bits definition for RCC_CFGR register  **********/

#define RCC_CFGR_SW_0                          0           /*!< SW[1:0] bits (System clock Switch) */
#define RCC_CFGR_SW_1                          1
#define RCC_CFGR_SWS_0                         2           /*!< SWS[1:0] bits (System Clock Switch Status) */
#define RCC_CFGR_SWS_1                         3
#define RCC_CFGR_HPRE_0                        4           /*!< HPRE[3:0] bits (AHB prescaler) */
#define RCC_CFGR_HPRE_2                        5
#define RCC_CFGR_HPRE_3                        6
#define RCC_CFGR_HPRE_4                        7
#define RCC_CFGR_PPRE1_0                       8           /*!< PRE1[2:0] bits (APB1 prescaler) */
#define RCC_CFGR_PPRE1_1                       9
#define RCC_CFGR_PPRE1_2                       10
#define RCC_CFGR_PPRE2_0                       11          /*!< PRE2[2:0] bits (APB2 prescaler) */
#define RCC_CFGR_PPRE2_1                       12
#define RCC_CFGR_PPRE2_2                       13
#define RCC_CFGR_ADCPRE_0                      14          /*!< ADCPRE[1:0] bits (ADC prescaler) */
#define RCC_CFGR_ADCPRE_1                      15
#define RCC_CFGR_PLLSRC                        16          /*!< PLL entry clock source */
#define RCC_CFGR_PLLXTPRE                      17          /*!< HSE divider for PLL entry */
#define RCC_CFGR_PLLMUL_0                      18          /*!< PLLMUL[3:0] bits (PLL multiplication factor) */
#define RCC_CFGR_PLLMUL_1                      19
#define RCC_CFGR_PLLMUL_2                      20
#define RCC_CFGR_PLLMUL_3                      21
#define RCC_CFGR_USBPRE                        22          /*!< USB OTG FS prescaler */
#define RCC_CFGR_MCO_0                         24          /*!< MCO[3:0] bits (Microcontroller Clock Output) */
#define RCC_CFGR_MCO_1                         25
#define RCC_CFGR_MCO_2                         26

/********************  Bits definition for RCC_CIR register  **********/

#define RCC_CIR_LSIRDYF							0	// LSI ready interrupt flag
#define RCC_CIR_LSERDYF							1	//LSE ready interrupt flag
#define RCC_CIR_HSIRDYF							2	//HSI ready interrupt flag
#define RCC_CIR_HSERDYF							3	//HSE ready interrupt flag
#define RCC_CIR_PLLRDYF							4	//PLL ready interrupt flag
#define RCC_CIR_CSSF							7	//Clock security system interrupt flag
#define RCC_CIR_LSIRDYIE						8	// LSI ready interrupt enable
#define RCC_CIR_LSERDYIE						9	// LSE ready interrupt enable
#define RCC_CIR_HSIRDYIE						10	//HSI ready interrupt enable
#define RCC_CIR_HSERDYIE						11	//HSE ready interrupt enable
#define RCC_CIR_PLLRDYIE						12	//PLL ready interrupt enable
#define RCC_CIR_LSIRDYC							16	//LSI ready interrupt clear
#define RCC_CIR_LSERDYC							17	//LSE ready interrupt clear
#define RCC_CIR_HSIRDYC							18	//HSI ready interrupt clear
#define RCC_CIR_HSERDYC							19	//HSE ready interrupt clear
#define RCC_CIR_PLLRDYC							20	//PLL ready interrupt clear
#define RCC_CIR_CSSC							23	//Clock security system interrupt clear

/********************  Bits definition for RCC_APB2RSTR register  **********
					   (APB2 peripheral reset register)					  */
#define RCC_APB2RSTR_AFIORST					0	//Alternate function IO reset
#define RCC_APB2RSTR_IOPARST					2	//IO port A reset
#define RCC_APB2RSTR_IOPBRST					3	//IO port B reset
#define RCC_APB2RSTR_IOPCRST					4	//IO port C reset
#define RCC_APB2RSTR_IOPDRST					5	//IO port D reset
#define RCC_APB2RSTR_IOPERST					6	//IO port E reset
#define RCC_APB2RSTR_IOPFRST					7	//IO port F reset
#define RCC_APB2RSTR_IOPGRST					8	//IO port G reset
#define RCC_APB2RSTR_ADC1RST					9	//ADC 1 interface reset
#define RCC_APB2RSTR_ADC2RST					10	//ADC 2 interface reset
#define RCC_APB2RSTR_TIM1RST					11	//TIM1 timer reset
#define RCC_APB2RSTR_SPI1RST					12	//SPI1 reset
#define RCC_APB2RSTR_TIM8RST					13	//TIM8 timer reset
#define RCC_APB2RSTR_USART1RST					14	//USART1 reset
#define RCC_APB2RSTR_ADC3RST					15	//ADC3 interface reset
#define RCC_APB2RSTR_TIM9RST					19	//TIM9 timer reset
#define RCC_APB2RSTR_TIM11RST					20	//TIM10 timer reset
#define RCC_APB2RSTR_TIM10RST					21	// TIM11 timer reset

/********************  Bits definition for RCC_APB1RSTR register  **********
					   (APB1 peripheral reset register)					  */

#define RCC_APB1RSTR_TIM2RST					0	//TIM2 timer reset
#define RCC_APB1RSTR_TIM3RST					1	//TIM3 timer reset
#define RCC_APB1RSTR_TIM4RST					2	//TIM4 timer reset
#define RCC_APB1RSTR_TIM5RST					3	//TIM5 timer reset
#define RCC_APB1RSTR_TIM6RST					4	//TIM6 timer reset
#define RCC_APB1RSTR_TIM7RST					5	//TIM7 timer reset
#define RCC_APB1RSTR_TIM12RST					6	//TIM12 timer reset
#define RCC_APB1RSTR_TIM13RST					7	//TIM13 timer reset
#define RCC_APB1RSTR_TIM14RST					8	//TIM14 timer reset
#define RCC_APB1RSTR_WWDGRST					11	//Window watchdog reset
#define RCC_APB1RSTR_SPI2RST					14	//SPI2 reset
#define RCC_APB1RSTR_SPI3RST					15	// SPI3 reset
#define RCC_APB1RSTR_USART2RST					17	//USART2 reset
#define RCC_APB1RSTR_USART3RST					18	//USART3 reset
#define RCC_APB1RSTR_UART4RST					19	// USART4 reset
#define RCC_APB1RSTR_UART5RST					20	// USART5 reset
#define RCC_APB1RSTR_I2C1RST					21	//I2C1 reset
#define RCC_APB1RSTR_I2C2RST					22	//I2C2 reset
#define RCC_APB1RSTR_USBRST						23	//USB reset
#define RCC_APB1RSTR_CANRST						25	//CAN reset
#define RCC_APB1RSTR_BKPRST						27	// Backup interface reset
#define RCC_APB1RSTR_PWRRST						28	// Power interface reset
#define RCC_APB1RSTR_DACRST						29	// DAC interface reset

/********************  Bits definition for RCC_AHBENR register  **********
					   (AHB peripheral clock enable register)			*/

#define RCC_AHBENR_DMA1EN						0	//DMA1 clock enable
#define RCC_AHBENR_DMA2EN						1	//DMA2 clock enable
#define RCC_AHBENR_SRAMEN						2	//SRAM interface clock enable
#define RCC_AHBENR_FLITFEN						4	//FLITF clock enable
#define RCC_AHBENR_CRCEN						6	//CRC clock enable
#define RCC_AHBENR_FSMCEN						8	//FSMC clock enable
#define RCC_AHBENR_SDIOEN						10	//SDIO clock enable

/********************  Bits definition for RCC_APB2ENR register  ***********
					   (APB2 peripheral clock enable register)			  */

#define RCC_APB2ENR_AFIOEN						0	//Alternate function IO clock enable
#define RCC_APB2ENR_IOPAEN						2	//IO port A clock enable
#define RCC_APB2ENR_IOPBEN						3	//IO port B clock enable
#define RCC_APB2ENR_IOPCEN 						4	//IO port C clock enable
#define RCC_APB2ENR_IOPDEN						5	//IO port D clock enable
#define RCC_APB2ENR_IOPEEN	 					6	//IO port E clock enable
#define RCC_APB2ENR_IOPFEN				 		7	//IO port F clock enable
#define RCC_APB2ENR_IOPGEN	 					8	//IO port G clock enable
#define RCC_APB2ENR_ADC1EN				 		9	//ADC 1 interface clock enable
#define RCC_APB2ENR_ADC2EN			 			10	//ADC 2 interface clock enable
#define RCC_APB2ENR_TIM1EN						11	//TIM1 timer clock enable
#define RCC_APB2ENR_SPI1EN		 				12	//SPI1 clock enable
#define RCC_APB2ENR_TIM8EN					 	13	//TIM8 Timer clock enable
#define RCC_APB2ENR_USART1EN		 			14	//USART1 clock enable
#define RCC_APB2ENR_ADC3EN				 		15	//ADC3 interface clock enable
#define RCC_APB2ENR_TIM9EN 						19	//TIM9 timer clock enable
#define RCC_APB2ENR_TIM10EN 					20	//TIM10 timer clock enable
#define RCC_APB2ENR_TIM11EN					 	21	//TIM11 timer clock enable

/********************  Bits definition for RCC_APB1ENR register  ***********
					   (APB1 peripheral clock enable register)			  */

#define RCC_APB1ENR_TIM2EN 							0	//TIM2 timer clock enable
#define RCC_APB1ENR_TIM3EN			 				1	//TIM3 timer clock enable
#define RCC_APB1ENR_TIM4EN 							2	//TIM4 timer clock enable
#define RCC_APB1ENR_TIM5EN 							3	//TIM5 timer clock enable
#define RCC_APB1ENR_TIM6EN		 					4	//TIM6 timer clock enable
#define RCC_APB1ENR_TIM7EN 							5	//TIM7 timer clock enable
#define RCC_APB1ENR_TIM12EN 						6	//TIM12 timer clock enable
#define RCC_APB1ENR_TIM13EN 						7	//TIM13 timer clock enable
#define RCC_APB1ENR_TIM14EN		 					8	//TIM14 timer clock enable
#define RCC_APB1ENR_WWDGEN 							11	//Window watchdog clock enable
#define RCC_APB1ENR_SPI2EN 							14	//SPI2 clock enable
#define RCC_APB1ENR_SPI3EN		 					15	//SPI 3 clock enable
#define RCC_APB1ENR_USART2EN 						17	//USART2 clock enable
#define RCC_APB1ENR_USART3EN 						18	//USART3 clock enable
#define RCC_APB1ENR_UART4EN 						19	//USART4 clock enable
#define RCC_APB1ENR_UART5EN						 	20	//USART5 clock enable
#define RCC_APB1ENR_I2C1EN 							21	//I2C1 clock enable
#define RCC_APB1ENR_I2C2EN 							22	//I2C2 clock enable
#define RCC_APB1ENR_USBEN			 				23	//USB clock enable
#define RCC_APB1ENR_CANEN 							25	//CAN clock enable
#define RCC_APB1ENR_BKPEN				 			27	//Backup interface clock enable
#define RCC_APB1ENR_PWREN	 						28	//Power interface clock enable
#define RCC_APB1ENR_DACEN 							29	//DAC interface clock enable

/********************  Bits definition for RCC_BDCR register  ***********
					   (Backup domain control register)			  	   */

#define RCC_BDCR_LSEON		 						0	//External low-speed oscillator enable
#define RCC_BDCR_LSERDY 							1	//External low-speed oscillator ready
#define RCC_BDCR_LSEBYP 							2	//External low-speed oscillator bypass
#define RCC_BDCR_RTCSEL0			 				8	//RTC clock source selection
#define RCC_BDCR_RTCSEL1			 				9	//RTC clock source selection
#define RCC_BDCR_RTCEN 								15	//RTC clock enable
#define RCC_BDCR_BDRST 								16	//Backup domain software reset

/********************  Bits definition for RCC_CSR register  ***********
					   (Control/status register)			  	      */

#define	RCC_CSR_LSION 								0	//Internal low-speed oscillator enable
#define	RCC_CSR_LSIRDY 								1	//Internal low-speed oscillator ready
#define	RCC_CSR_RMVF 								24	//Remove reset flag
#define	RCC_CSR_PINRSTF 							26	//PIN reset flag
#define	RCC_CSR_PORRSTF 							27	//POR/PDR reset flag
#define	RCC_CSR_SFTRSTF		 						28	//Software reset flag
#define	RCC_CSR_IWDGRSTF 							29	//Independent watchdog reset flag
#define	RCC_CSR_WWDGRSTF 							30	//Window watchdog reset flag
#define	RCC_CSR_LPWRRSTF	 						31	//Low-power reset flag


/*********************	Masking macros ***********************************/

#define BUSES_PRESCALER_RESET_MASK 			1023<<RCC_CFGR_HPRE_0
#define MULTIPLICATION_FACTOR_RESET_MASK 	0b1111 << RCC_CFGR_PLLMUL_0

#endif

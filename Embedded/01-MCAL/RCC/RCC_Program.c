/*
 *
 * Author	    :	Mohamed Ahmed
 * Date		    :	29 SEP 2023
 * Version		:	V01
 * Description  : 	RCC Program file
 *
 **/
#include"../Inc/LIB/BIT_MATH.h"
#include"../Inc/LIB/STD_TYPES.h"

#include"../Inc/MCAL/RCC/RCC_Interface.h"
#include"../Inc/MCAL/RCC/RCC_Private.h"
#include"../Inc/MCAL/RCC/RCC_Config.h"

void MRCC_voidInit(void)
{
#if CLK_SOURCE == HSI

	/*step (1): Turn on HSI*/
	MRCC_voidClkEnable(HSI);

	/*step (2): check HSI is ready*/
	while(MRCC_RCCStatus_tCheckClockReady(HSI) == RCC_NotReady);

	/*step (3): set buses prescaler*/
	MRCC_voidSetBusesPrescaler(AHB_PRESCALER, ABP1_PRESCALER, ABP2_PRESCALER);

	/*step (4): switch to HSI clock*/
	MRCC_voidSetClkSource(HSI);

	/*step (5): turn off HSE and PLL*/
	MRCC_voidClkDisable(HSE);
	MRCC_voidClkDisable(PLL);

#elif CLK_SOURCE == HSE

	/*step (1): Turn on HSE*/
	MRCC_voidClkEnable(HSE);

	/*step (2): check HSE is ready*/
	while(MRCC_RCCStatus_tCheckClockReady(HSE) == RCC_NotReady);

	/*step (3): set buses prescaler*/
	MRCC_voidSetBusesPrescaler(AHB_PRESCALER, ABP1_PRESCALER, ABP2_PRESCALER);

	/*step (4): switch to HSE clock*/
	MRCC_voidSetClkSource(HSE);

	/*step (5): turn off HSI and PLL*/
	MRCC_voidClkDisable(HSI);
	MRCC_voidClkDisable(PLL);

#elif CLK_SOURCE == PLL

	#if PLL_SOURCE == HSE

		/*step(1): set PLL source*/
		MRCC_voidSetPLLSource(PLL_SOURCE, PLL_HSE_FACTOR);
		/*step (2): Turn on HSE*/
		MRCC_voidClkEnable(HSE);
		/*step (3): check HSE is ready*/
		while(MRCC_RCCStatus_tCheckClockReady(HSE) == RCC_NotReady);
		/*step(4): turn on HSI*/
		MRCC_voidClkEnable(HSI);
		/*step(5): check HSI is ready*/
		while (MRCC_RCCStatus_tCheckClockReady(HSI) == RCC_NotReady);
		/*step(6): switch to HSI clock*/
		MRCC_voidSetClkSource(HSI);
	#elif PLL_SOURCE == HSI

		/*step(1): set PLL source*/
		MRCC_voidSetPLLSource(PLL_SOURCE, PLL_HSE_FACTOR);
		/*step (2): Turn on HSI*/
		MRCC_voidClkEnable(HSI);
		/*step (3): check HSI is ready*/
		while(MRCC_RCCStatus_tCheckClockReady(HSI) == RCC_NotReady);
		/*step(4): turn on HSE*/
		MRCC_voidClkEnable(HSE);
		/*step(5): check HSE is ready*/
		while (MRCC_u8CheckClockReady(HSE) == RCC_NotReady);
		/*step(6): switch to HSE clock*/
		MRCC_voidSetClkSource(HSE);


	#else
	#error Wrong PLL Configurations
	#endif /*PLL_SOURCE*/

		/*step(7):  set PLL multiplication factor*/
		MRCC_voidSetPLLMulFactor(PLL_MULTIPLICATION_FACTOR);

		/*step(8):  set buses prescaler*/
		MRCC_voidSetBusesPrescaler(AHB_PRESCALER, ABP1_PRESCALER, ABP2_PRESCALER);

		/*step(9):  turn on PLL*/
		MRCC_voidClkEnable(PLL);
		/*step(10): check PLL is ready*/
		while (MRCC_RCCStatus_tCheckClockReady(PLL) == RCC_NotReady);

		/*step(11): switch to HSI clock*/
		MRCC_voidSetClkSource(HSI);

#if PLL_SOURCE == HSE
		/*step(12): turn off HSI*/
		MRCC_voidClkDisable(HSI);
#elif PLL_SOURCE == HSI
		/*step(12): turn off HSI*/
		MRCC_voidClkDisable(HSE);
#endif

#endif /*CLK_SOURCE*/
}

void MRCC_voidClkEnable(uint8 A_uint8ClkSource)
{
	switch(A_uint8ClkSource)
	{
		case HSI:
			SET_BIT(RCC->CR,RCC_CR_HSION);
			break;
		case  HSE:
			SET_BIT(RCC->CR,RCC_CR_HSEON);
			break;
		case PLL:
			SET_BIT(RCC->CR,RCC_CR_PLLON);
			break;
		default:
			/*TODO: Return Error Code*/
			break;

	}
}

void MRCC_voidClkDisable(uint8 A_uint8ClkSource)
{
	switch(A_uint8ClkSource)
	{
		case HSI:
			CLR_BIT(RCC->CR,RCC_CR_HSION);
			break;
		case  HSE:
			CLR_BIT(RCC->CR,RCC_CR_HSEON);
			break;
		case PLL:
			CLR_BIT(RCC->CR,RCC_CR_PLLON);
			break;
		default:
			/*TODO: Return Error Code*/
			break;

	}
}

RCC_Status_t MRCC_RCCStatus_tCheckClockReady (uint8 A_uint8ClkSource)
{
	RCC_Status_t local_RCC_Status_tReadyFlag = RCC_NotReady;

	switch(A_uint8ClkSource)
	{
		case HSI:
			local_RCC_Status_tReadyFlag = READ_BIT(RCC->CR,RCC_CR_HSIRDY);
			break;
		case HSE:
			local_RCC_Status_tReadyFlag = READ_BIT(RCC->CR,RCC_CR_HSERDY);
			break;
		case PLL:
			local_RCC_Status_tReadyFlag = READ_BIT(RCC->CR,RCC_CR_PLLRDY);
			break;
		default:
			/*TODO: Return Error Code*/
			break;
	}

	return local_RCC_Status_tReadyFlag;
}

void MRCC_voidSetClkSource(uint8 A_uint8ClkSource)
{
	switch(A_uint8ClkSource)
	{
		case HSI:
			CLR_BIT(RCC->CFGR,RCC_CFGR_SW_0);
			CLR_BIT(RCC->CFGR,RCC_CFGR_SW_1);
			break;
		case HSE:
			SET_BIT(RCC->CFGR,RCC_CFGR_SW_0);
			CLR_BIT(RCC->CFGR,RCC_CFGR_SW_1);
			break;
		case PLL:
			CLR_BIT(RCC->CFGR,RCC_CFGR_SW_0);
			SET_BIT(RCC->CFGR,RCC_CFGR_SW_1);
			break;
		default:
			/*TODO: Return Error Code*/
			break;
	}
}

void MRCC_voidSetBusesPrescaler (uint8 A_uint8AHBPrescaler, uint8 A_uint8APB1Prescaler, uint8 A_uint8APB2Prescaler)
{
	/* BUSES_PRESCALER_RESET_MASK: is a mask to clear only bits used in prescaler set for AHB - APB1 - APB2 */
	RCC->CFGR &= ~(BUSES_PRESCALER_RESET_MASK);

	RCC->CFGR |=  (A_uint8AHBPrescaler << RCC_CFGR_HPRE_0);

	RCC->CFGR |=  (A_uint8APB1Prescaler << RCC_CFGR_PPRE1_0);

	RCC->CFGR |=  (A_uint8APB2Prescaler << RCC_CFGR_PPRE2_0);

}

void MRCC_voidSetPLLSource(uint8 A_uint8ClkSource, uint8 A_uint8Prescaler)
{
	switch(A_uint8ClkSource)
	{
		case HSI:
			CLR_BIT(RCC->CFGR,RCC_CFGR_PLLSRC);
			break;
		case HSE:
			SET_BIT(RCC->CFGR,RCC_CFGR_PLLSRC);
			switch(A_uint8Prescaler)
			{
				case HSE_NOT_DIVIDED:
					CLR_BIT(RCC->CFGR,RCC_CFGR_PLLXTPRE);
					break;
				case HSE_DIVIDED:
					SET_BIT(RCC->CFGR,RCC_CFGR_PLLXTPRE);
					break;
				default:
					/*TODO: Return Error Code*/
					break;
			}
			break;
		default:
			/*TODO: Return Error Code*/
			break;

	}
}

void MRCC_voidSetPLLMulFactor(uint8 A_uint8MulFactor)
{
	/*MULTIPLICATION_FACTOR_RESET_MASK: is a mask to clear 4 bit for multiplication factor at CFGR register started from bit 18*/
	RCC->CFGR &= ~(MULTIPLICATION_FACTOR_RESET_MASK);

	RCC->CFGR |= (A_uint8MulFactor << RCC_CFGR_PLLMUL_0);
}

void MRCC_voidPreipheralEnable (uint8 A_uint8BusID, uint8 A_uint8PrephieralID)
{
	if(A_uint8PrephieralID < 31)
	{
		switch(A_uint8BusID)
		{
		case AHB:
			SET_BIT(RCC->AHBENR, A_uint8PrephieralID);
			break;
		case APB1:
			SET_BIT(RCC->APB1ENR, A_uint8PrephieralID);
			break;
		case APB2:
			SET_BIT(RCC->APB2ENR, A_uint8PrephieralID);
			break;
		default:
			/*TODO: Return Error Code*/
			break;
		}
	}
	else
	{
		/*TODO: Return Error Code*/
	}
}

void MRCC_voidPreipheralDisable (uint8 A_uint8BusID, uint8 A_uint8PrephieralID)
{
	if(A_uint8PrephieralID < 31)
	{
		switch(A_uint8BusID)
		{
		case AHB:
			CLR_BIT(RCC->AHBENR, A_uint8PrephieralID);
			break;
		case APB1:
			CLR_BIT(RCC->APB1ENR, A_uint8PrephieralID);
			break;
		case APB2:
			CLR_BIT(RCC->APB2ENR, A_uint8PrephieralID);
			break;
		default:
			/*TODO: Return Error Code*/
			break;
		}
	}
	else
	{
		/*TODO: Return Error Code*/
	}
}

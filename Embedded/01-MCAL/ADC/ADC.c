/*
 * ADC.c
 *
 *  Created on: Aug 16, 2022
 *      Author: Mohamed Salama
 */
* Includes
*******************************************************************************/	

#include "../inc/LIB/Std_Types.h"
#include "../inc/LIB/BIT_MATH.h"

#include "../inc/MCAL/ADC.h"
#include "../inc/MCAL/ADC_Cfg.h"
#include "../inc/MCAL/ADC_Private.h"

/******************************************************************************
* Module Preprocessor Constants
*******************************************************************************/
#define WAIT_FOR_CONVERSION (GET_BIT(AdcChannel[Cpy_PeripheralNumber]->SR, EOC) == FLAG_NOT_SET)
/******************************************************************************
* Module Preprocessor Macros
*******************************************************************************/

/******************************************************************************
* Module Typedefs
*******************************************************************************/

/******************************************************************************
* Module Variable Definitions
*******************************************************************************/
PtrToFunction CallBackFunction;
/******************************************************************************
* Function Prototypes
*******************************************************************************/

/******************************************************************************
* Function Definitions
*******************************************************************************/

Std_ReturnType MADC_u8InitializeAdc(void)
{
   // Configure adc that enabled by user.
	// Loop on adcs to find which enabled.
	for(uint8 Local_u8AdcNumber = ADC1;Local_u8AdcNumber < NUMBER_OF_ADC_PERIPHERALS;Local_u8AdcNumber++)
	{
		if(Static_AdcConfig[Local_u8AdcNumber].ModuleState == ENABLE_ADC)
		{
			// Clear registers
         AdcChannel[Local_u8AdcNumber]->CR1   = CLR_REGISTER;
         AdcChannel[Local_u8AdcNumber]->CR2   = CLR_REGISTER;
         AdcChannel[Local_u8AdcNumber]->SMPR1 = CLR_REGISTER;
         AdcChannel[Local_u8AdcNumber]->SMPR2 = CLR_REGISTER;
         AdcChannel[Local_u8AdcNumber]->SQR1  = CLR_REGISTER;
         AdcChannel[Local_u8AdcNumber]->SQR2  = CLR_REGISTER;
         AdcChannel[Local_u8AdcNumber]->SQR3  = CLR_REGISTER;
         // Configurations
         // Specify Data Alignment
         AdcChannel[Local_u8AdcNumber]->CR2  |= ((Static_AdcConfig[Local_u8AdcNumber].DataAlignment) << ALIGN);
         // Specify Calibration
         AdcChannel[Local_u8AdcNumber]->CR2  |= ((Static_AdcConfig[Local_u8AdcNumber].CalibrationState) << CAL);
         // Turn on Adc
         SET_BIT(AdcChannel[Local_u8AdcNumber]->CR2, ADON);
		}
	} 
}

Std_ReturnType MADC_u8SetConversionMode(AdcPeripherals_t Cpy_PeripheralNumber, AdcConversionMode_t Cpy_Mode,
                                        uint8 Cpy_u8NumberOfConversions)
{
   switch(Cpy_Mode)
   {
      case SINGLE_CONVERSION          :
         // Apply Single conversion Mode
         CLR_BIT(AdcChannel[Cpy_PeripheralNumber]->CR2, CONT);
         // Just for removing warning.
         (uint8)Cpy_u8NumberOfConversions;
      break;
      case CONTINUOUS_CONVERSION      :
         // Apply continuous conversion Mode
         SET_BIT(AdcChannel[Cpy_PeripheralNumber]->CR2, CONT);
         (uint8)Cpy_u8NumberOfConversions;
      break;
      case SCAN_SINGLE_CONVERSION     :
         // Apply scan single conversion Mode
         CLR_BIT(AdcChannel[Cpy_PeripheralNumber]->CR2, CONT);
         SET_BIT(AdcChannel[Cpy_PeripheralNumber]->CR1, SCAN);
         SET_BIT(AdcChannel[Cpy_PeripheralNumber]->CR2, DMA); 
         (uint8)Cpy_u8NumberOfConversions;
      break;
      case SCAN_CONTINUOUS_CONVERSION :
         // Apply scan continuous conversion Mode
         SET_BIT(AdcChannel[Cpy_PeripheralNumber]->CR2, CONT);
         SET_BIT(AdcChannel[Cpy_PeripheralNumber]->CR1, SCAN);
         SET_BIT(AdcChannel[Cpy_PeripheralNumber]->CR2, DMA);
         (uint8)Cpy_u8NumberOfConversions;
      break;
      case DISCONTINUOUS_CONVERSION   :
      // Apply scan discontinuous conversion Mode
         SET_BIT(AdcChannel[Cpy_PeripheralNumber]->CR1, DISCEN);
         AdcChannel[Cpy_PeripheralNumber]->CR1 |= (Cpy_u8NumberOfConversions << DISCNUM0);
      break;
   }
}

Std_ReturnType MADC_u8SetRegularChannelOrder(AdcPeripherals_t Cpy_PeripheralNumber,AdcChannels_t Cpy_u8Channel,
            AdcChannelOrder_t Cpy_u8ConvertionOrder)
{
   
   if(Cpy_u8Channel <= END_OF_SQR3)
   {
      AdcChannel[Cpy_PeripheralNumber]->SQR3 |= (Cpy_u8Channel) << (Cpy_u8ConvertionOrder);
   }
   else if(Cpy_u8Channel <= END_OF_SQR2)
   {
      AdcChannel[Cpy_PeripheralNumber]->SQR2 |= (Cpy_u8Channel) << (Cpy_u8ConvertionOrder);
   }
   else if(Cpy_u8Channel <= END_OF_SQR1)
   {
      AdcChannel[Cpy_PeripheralNumber]->SQR1 |= (Cpy_u8Channel) << (Cpy_u8ConvertionOrder);
   }
   else
   {
      /*!<TODO: Handle error*/
   }
}

Std_ReturnType MADC_u8SetSamplingTime(AdcPeripherals_t Cpy_PeripheralNumber, AdcChannels_t Cpy_u8Channel,
                                      AdcSampleTime_t Cpy_u8SamplingTime)
{
   if(Cpy_u8Channel <= END_OF_SMPR2)
   {
      AdcChannel[Cpy_PeripheralNumber]->SMPR2 |= (Cpy_u8SamplingTime) << (Cpy_u8Channel * OFFSET);
   }
   else if(Cpy_u8Channel <= END_OF_SMPR1)
   {
      Cpy_u8Channel -= ADJUST_CHANNEL;
      AdcChannel[Cpy_PeripheralNumber]->SMPR1 |= (Cpy_u8SamplingTime) << (Cpy_u8Channel * OFFSET);
   }
   else
   {
      /*!<TODO: Handle error*/
   }
}

Std_ReturnType MADC_u8ReadResultBlocking(AdcPeripherals_t Cpy_PeripheralNumber, AdcChannels_t Cpy_u8Channel,
                              AdcRegularChannelSquanceLength_t Cpy_NumberOfChannels, uint16 * Cpy_u16Result)
{
   AdcChannel[Cpy_PeripheralNumber]->SQR3  = CLR_REGISTER;
   // Specify Regular channel sequence length
   AdcChannel[Cpy_PeripheralNumber]->SQR3 |= (Cpy_NumberOfChannels) << L0;
   // Make the passsed channel is the first conversion
   AdcChannel[Cpy_PeripheralNumber]->SQR3 |= (Cpy_u8Channel) << (FIRST_ORDER);
   // Start Conversion
   SET_BIT(AdcChannel[Cpy_PeripheralNumber]->CR2, ADON);
   SET_BIT(AdcChannel[Cpy_PeripheralNumber]->CR2, SWSTART);
   // Wait conversion
   while(WAIT_FOR_CONVERSION);
   // Get Data
   *Cpy_u16Result = ((AdcChannel[Cpy_PeripheralNumber]->DR) & GET_RIGHT_ALIGNED_DATA);
   // Clear flag
   CLR_BIT(AdcChannel[Cpy_PeripheralNumber]->SR, EOC);
   CLR_BIT(AdcChannel[Cpy_PeripheralNumber]->SR, STRT);
}

Std_ReturnType MADC_u8ReadResultNonBlocking(AdcPeripherals_t Cpy_PeripheralNumber, AdcChannels_t Cpy_u8Channel,
      AdcRegularChannelSquanceLength_t Cpy_NumberOfChannels, uint16 * Cpy_u16Result)
{
   AdcChannel[Cpy_PeripheralNumber]->SQR3  = CLR_REGISTER;
   // Specify Regular channel sequence length
   AdcChannel[Cpy_PeripheralNumber]->SQR3 |= (Cpy_NumberOfChannels) << L0;
   // Make the passsed channel is the first conversion
   AdcChannel[Cpy_PeripheralNumber]->SQR3 |= (Cpy_u8Channel) << (FIRST_ORDER);
   // Start Conversion
   SET_BIT(AdcChannel[Cpy_PeripheralNumber]->CR2, ADON);
   SET_BIT(AdcChannel[Cpy_PeripheralNumber]->CR2, SWSTART);
   if(GET_BIT(AdcChannel[Cpy_PeripheralNumber]->SR, EOC) == FLAG_SET)
   {
      // Get Data
      *Cpy_u16Result = ((AdcChannel[Cpy_PeripheralNumber]->DR) & GET_RIGHT_ALIGNED_DATA);
      // Clear flag
      CLR_BIT(AdcChannel[Cpy_PeripheralNumber]->SR, EOC);
      CLR_BIT(AdcChannel[Cpy_PeripheralNumber]->SR, STRT);
   }
}
Std_ReturnType MADC_u8ReadDigitalAsynch(AdcPeripherals_t Cpy_PeripheralNumber, PtrToFunction CallBack)
{
   CallBackFunction = CallBack;
   SET_BIT(AdcChannel[Cpy_PeripheralNumber]->CR1, EOCIE);
   SET_BIT(AdcChannel[Cpy_PeripheralNumber]->CR2, ADON);
   SET_BIT(AdcChannel[Cpy_PeripheralNumber]->CR2, SWSTART);
}

void ADC1_2_IRQHandler(void)
{
   CallBackFunction((AdcChannel[0]->DR) & GET_RIGHT_ALIGNED_DATA);
   CLR_BIT(AdcChannel[0]->SR, EOC);
   CLR_BIT(AdcChannel[0]->SR, STRT);
}


/*************** END OF FUNCTIONS ***************************************************************************/

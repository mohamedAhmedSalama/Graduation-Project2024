/**================================================================
 * @file         Stm32_F103C6_GPIO.c
 * @brief        GPIO Peripheral Abstraction Layer Implementation
 * @version      1.0
 * @date         12/07/2023
 * @author       Khaled Salama (https://www.linkedin.com/in/5aledsalama/)
 *
 * @note         This file contains the implementation of the GPIO
 *               Peripheral Abstraction Layer (MCAL) for STM32
 *               microcontrollers. It provides functions for GPIO
 *               pin initialization, deinitialization, reading,
 *               writing, toggling, and pin locking.
 */
#include "Stm32_F103C6.GPIO.h"
/**================================================================
 * @Fn           get_GPIO_CRLH_pinPosition
 * @brief        Get the bit position offset for a GPIO pin in CRL or CRH register.
 * @param [in]   pinNumber: The GPIO pin number.
 * @retval       The bit position offset for the specified pin in CRL or CRH register.
 * @note         This function returns the bit position offset for a given GPIO pin number in
 *               the Configuration Register Low (CRL) or Configuration Register High (CRH) based
 *               on the pin number. It is designed for STM32 microcontrollers and assumes that
 *               the pinNumber parameter corresponds to a valid GPIO pin. Adjust the comments
 *               based on the specific details of your implementation.
 */

uint8_t get_GPIO_CRLH_pinPosition(uint16_t pinNumber){
	switch(pinNumber)
	{
	//CRL
	case GPIO_PIN_0:
		return 0;
		break;
	case GPIO_PIN_1:
		return 4;
		break;

	case GPIO_PIN_2:
		return 8;
		break;

	case GPIO_PIN_3:
		return 12;
		break;
	case GPIO_PIN_4:
		return 16;
		break;
	case GPIO_PIN_5:
		return 20;
		break;

	case GPIO_PIN_6:
		return 24;
		break;

	case GPIO_PIN_7:
		return 28;
		break;
		//CRH
	case GPIO_PIN_8:
		return 0;
		break;
	case GPIO_PIN_9:
		return 4;
		break;

	case GPIO_PIN_10:
		return 8;
		break;

	case GPIO_PIN_11:
		return 12;
		break;
	case GPIO_PIN_12:
		return 16;
		break;
	case GPIO_PIN_13:
		return 20;
		break;

	case GPIO_PIN_14:
		return 24;
		break;

	case GPIO_PIN_15:
		return 28;
		break;


	}
	return 0;

}
/**================================================================
 * @Fn           MCAL_GPIO_Init
 * @brief        Initialize the GPIO pin based on the provided configuration.
 * @param [in]   GPIOx: Pointer to the GPIO peripheral instance (e.g., GPIOA, GPIOB, etc.).
 * @param [in]   PINx: Pointer to a structure containing GPIO pin configuration settings.
 * @retval       None
 * @note         This function configures the specified GPIO pin based on the provided settings
 *               in the GPIO_pinConfig_typeDef structure. It initializes the pin mode, output speed,
 *               and, in the case of input modes, configures pull-up or pull-down resistors.
 *               The function is designed for STM32 microcontrollers and assumes that the GPIOx
 *               and PINx parameters are correctly initialized.
 */
void MCAL_GPIO_Init(GPIO_typeDef *GPIOx ,GPIO_pinConfig_typeDef *PINx){

	volatile uint32_t *regConfig=NULL;
	uint8_t pinConfig;
	 // Pointer to the configuration register (CRL or CRH) based on pin number
	regConfig=(PINx->GPIO_pinNumber < GPIO_PIN_8)? &GPIOx->CRL: &GPIOx->CRH;

    // Clear the configuration bits for the selected pin

	(*regConfig)&=~(0xf<<get_GPIO_CRLH_pinPosition(PINx->GPIO_pinNumber));

	switch(PINx->GPIO_mode){
	  // Output modes
	case GPIO_MODE_OUTPUT_PUSH_PULL:
	case GPIO_MODE_OUTPUT_OPEN_DRAIN:
	case GPIO_MODE_OUTPUT_ALTERNATE_PUSH_PULL:
	case GPIO_MODE_OUTPUT_ALTERNATE_OPEN_DRAIN:
		pinConfig=( ((((PINx->GPIO_mode)-4) << 2) |(PINx->GPIO_outputSpeed)) & 0x0F);
		break;

		// Input modes
	case GPIO_MODE_INPUT_ANALOG:
	case GPIO_MODE_INPUT_FLOATING:
		pinConfig=(((PINx->GPIO_mode) << 2) & 0x0F);
		break;

		// Input alternate mode
	case GPIO_MODE_INPUT_ALTERNATE:
		pinConfig=(((GPIO_MODE_INPUT_FLOATING) << 2)& 0x0F);
		break;

		// Input pull-up mode
	case GPIO_MODE_INPUT_PULL_UP:
		pinConfig=(((GPIO_MODE_INPUT_PULL_UP) << 2) & 0x0F);
		GPIOx->ODR |= PINx->GPIO_pinNumber;
		break;

		// Input pull-down mode
	case GPIO_MODE_INPUT_PULL_DOWN:
		pinConfig=(((GPIO_MODE_INPUT_PULL_UP) << 2) & 0x0F);
		GPIOx->ODR &=~(PINx->GPIO_pinNumber);

		break;
	}
	(*regConfig)|=(pinConfig<<get_GPIO_CRLH_pinPosition(PINx->GPIO_pinNumber));
}
/**================================================================
 * @Fn           MCAL_GPIO_Dinit
 * @brief        Deinitialize (reset) the GPIO peripheral and its configuration.
 * @param [in]   GPIOx: Pointer to the GPIO peripheral instance (e.g., GPIOA, GPIOB, etc.).
 * @retval       None
 * @note         This function resets the specified GPIO peripheral, clearing all configurations
 *               and returning the peripheral to its default state. It is designed for STM32
 *               microcontrollers and assumes that the GPIOx parameter is correctly initialized.
 *               If there is no reset controller, default configuration values are applied to
 *               GPIO control registers (CRL, CRH). If a reset controller is present, the function
 *               utilizes the RCC (Reset and Clock Control) peripheral to perform a reset on the
 *               specified GPIO peripheral. Adjust the comments based on the specific details of
 *               your implementation.
 */
void MCAL_GPIO_Dinit(GPIO_typeDef *GPIOx){
	//****** if there is no rest controller we use:
	//	GPIOx->CRL=0x44444444;
	//	GPIOx->CRH=0x44444444;
	//	//IDR = 0x0000XXXX  Read only
	//	GPIOx->ODR=0x00000000;
	//	GPIOx->BSRR=0x00000000;
	//	GPIOx->BRR=0x00000000;
	//	GPIOx->LCKR=0x00000000;

	// else if there is rest controller

	if(GPIOx==GPIOA)
	{
		RCC->APB2RSTR|=(1<<2);
		RCC->APB2RSTR &=~(1<<2);
	}
	else if(GPIOx==GPIOB)
	{
		RCC->APB2RSTR|=(1<<3);
		RCC->APB2RSTR &=~(1<<3);
	}
	else if(GPIOx==GPIOC)
	{
		RCC->APB2RSTR|=(1<<4);
		RCC->APB2RSTR &=~(1<<4);
	}
	else if(GPIOx==GPIOD)
	{
		RCC->APB2RSTR|=(1<<5);
		RCC->APB2RSTR &=~(1<<5);
	}
	else if(GPIOx==GPIOE)
	{
		RCC->APB2RSTR|=(1<<6);
		RCC->APB2RSTR &=~(1<<6);
	}


}

/**================================================================
 * @Fn           MCAL_GPIO_READ_Pin
 * @brief        Read the logic level of a specified GPIO pin.
 * @param [in]   GPIOx: Pointer to the GPIO peripheral instance (e.g., GPIOA, GPIOB, etc.).
 * @param [in]   pinNumber: The number of the GPIO pin to be read.
 * @retval       GPIO_PIN_SET if the pin is high (logic level 1), GPIO_PIN_RESET if the pin is low (logic level 0).
 * @note         This function reads the logic level of the specified GPIO pin in the input data register (IDR).
 *               The result is returned as GPIO_PIN_SET if the pin is high and GPIO_PIN_RESET if the pin is low.
 *               It is designed for STM32 microcontrollers and assumes that the GPIOx parameter is correctly initialized.
 *               The pinNumber parameter should be the pin number (0 to 15) of the GPIO port.
 *               Adjust the comments based on the specific details of your implementation.
 */

uint8_t MCAL_GPIO_READ_Pin(GPIO_typeDef *GPIOx, uint16_t pinNumber){
	uint8_t pinStatus;
	// Check if the specified pin is high or low in the Input Data Register (IDR)
	if((GPIOx->IDR & pinNumber)!=(uint32_t)GPIO_PIN_RESET){
		pinStatus=GPIO_PIN_SET;
	}else{
		pinStatus=GPIO_PIN_RESET;
	}
	return pinStatus;
}

/**================================================================
 * @Fn           MCAL_GPIO_READ_Port
 * @brief        Read the current status of all GPIO pins in a specified port.
 * @param [in]   GPIOx: Pointer to the GPIO peripheral instance (e.g., GPIOA, GPIOB, etc.).
 * @retval       A 16-bit value representing the current status of all GPIO pins in the specified port.
 * @note         This function reads the status of all GPIO pins in the specified port by
 *               accessing the Input Data Register (IDR) of the GPIO peripheral. It is designed
 *               for STM32 microcontrollers and assumes that the GPIOx parameter is correctly
 *               initialized. The 16-bit value returned represents the current logic levels of
 *               all pins in the port, where each bit corresponds to a specific pin. Adjust the
 *               comments based on the specific details of your implementation.
 */
uint16_t MCAL_GPIO_READ_Port(GPIO_typeDef *GPIOx){
	uint16_t portValue;
	// Read the status of all GPIO pins in the specified port from the Input Data Register (IDR)
	portValue=(uint16_t)GPIOx->IDR;
	return portValue;
}

/**================================================================
 * @Fn           MCAL_GPIO_WRITE_Pin
 * @brief        Set or reset the specified GPIO pin to the specified logic level.
 * @param [in]   GPIOx: Pointer to the GPIO peripheral instance (e.g., GPIOA, GPIOB, etc.).
 * @param [in]   pinNumber: The pin number to set or reset.
 * @param [in]   value: The desired logic level for the specified pin (GPIO_PIN_SET or GPIO_PIN_RESET).
 * @retval       None
 * @note         This function sets or resets the specified GPIO pin to the specified logic level.
 *               It is designed for STM32 microcontrollers and assumes that the GPIOx parameter is
 *               correctly initialized. The function uses the Bit Set Reset Register (BSRR) to
 *               efficiently set or reset the specified pin based on the provided logic level.
 *               Adjust the comments based on the specific details of your implementation.
 */

void MCAL_GPIO_WRITE_Pin(GPIO_typeDef* GPIOx,uint16_t pinNumber, uint8_t value){
	if(value==GPIO_PIN_SET){
		 // Set the specified pin to logic high using the Bit Set Reset Register (BSRR)
		GPIOx->BSRR=pinNumber;
	}else
	{
		 // Reset the specified pin to logic low using the Bit Reset Register (BRR)
		GPIOx->BRR=pinNumber;
	}

}

/**================================================================
 * @Fn           MCAL_GPIO_WRITE_Port
 * @brief        Write a 16-bit value to all GPIO pins in a specified port.
 * @param [in]   GPIOx: Pointer to the GPIO peripheral instance (e.g., GPIOA, GPIOB, etc.).
 * @param [in]   value: A 16-bit value representing the desired logic levels for all pins in the port.
 * @retval       None
 * @note         This function writes a 16-bit value to the Output Data Register (ODR) of the specified
 *               GPIO peripheral, setting or resetting all pins in the port based on the provided value.
 *               It is designed for STM32 microcontrollers and assumes that the GPIOx parameter is
 *               correctly initialized. Each bit in the 16-bit value corresponds to a specific pin,
 *               setting the pin to logic high if the corresponding bit is set, and logic low if it is clear.
 *               Adjust the comments based on the specific details of your implementation.
 */
void MCAL_GPIO_WRITE_Port(GPIO_typeDef* GPIOx, uint16_t value){
	GPIOx->ODR=(uint32_t) value; // Write the 16-bit value to the Output Data Register (ODR) of the specified GPIO peripheral
}

/**================================================================
 * @Fn           MCAL_GPIO_TOGGLE_Pin
 * @brief        Toggle the logic level of the specified GPIO pin.
 * @param [in]   GPIOx: Pointer to the GPIO peripheral instance (e.g., GPIOA, GPIOB, etc.).
 * @param [in]   pinNumber: The pin number to toggle.
 * @retval       None
 * @note         This function toggles the logic level of the specified GPIO pin by using the XOR
 *               operation on the corresponding bit in the Output Data Register (ODR) of the GPIO
 *               peripheral. It is designed for STM32 microcontrollers and assumes that the GPIOx
 *               parameter is correctly initialized. The function effectively inverts the current
 *               logic level of the specified pin. Adjust the comments based on the specific details
 *               of your implementation.
 */

void MCAL_GPIO_TOGGLE_Pin(GPIO_typeDef* GPIOx,uint16_t pinNumber){

	GPIOx->ODR ^=pinNumber; // Toggle the logic level of the specified pin using the XOR operation on the ODR
}

/**================================================================
 * @Fn           MCAL_GPIO_LOCK_Pin
 * @brief        Lock or unlock the configuration of the specified GPIO pin.
 * @param [in]   GPIOx: Pointer to the GPIO peripheral instance (e.g., GPIOA, GPIOB, etc.).
 * @param [in]   pinNumber: The pin number to lock or unlock.
 * @retval       GPIO_PIN_LOCK_Active if the pin is locked, GPIO_PIN_LOCK_Disabled if the pin is unlocked.
 * @note         This function locks or unlocks the configuration of the specified GPIO pin by using
 *               the Lock Register (LCKR) of the GPIO peripheral. It is designed for STM32
 *               microcontrollers and assumes that the GPIOx parameter is correctly initialized.
 *               The function follows the procedure specified in the reference manual to lock or
 *               unlock the pin configuration. After the operation, it checks whether the lock is
 *               active and returns the corresponding status. Adjust the comments based on the
 *               specific details of your implementation.
 */
uint8_t MCAL_GPIO_LOCK_Pin(GPIO_typeDef* GPIOx,uint16_t pinNumber){
	volatile uint32_t tmp=1<<16;
	tmp |=pinNumber;
	GPIOx->LCKR=tmp;
	GPIOx->LCKR=pinNumber;
	GPIOx->LCKR=tmp;
	tmp=GPIOx->LCKR;
	if((uint32_t)(GPIOx->LCKR &1<<16)){
		return GPIO_PIN_LOCK_Active;
	}else{
		return GPIO_PIN_LOCK_Disabled;
	}

}

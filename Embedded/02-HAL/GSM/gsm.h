#ifndef GSM_H_
#define GSM_H_

#include "../Stm32_F103C6_Drivers/include/uart.h"
#include "RCC_Interface.h"


void GSM_Init(void);
void GSM_SendSMS(const char* phoneNumber, const char* message);
void delay_ms(uint32 time);

#endif /* GSM_H_ */

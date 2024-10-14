#include "gsm.h"

#define USART_CHANNEL    USART2
#define GSM_UART_CHANNEL    UART2

void GSM_Init(void) {
    // Initialize UART for GSM communication
	MRCC_voidPreipheralEnable(APB1, USART_CHANNEL);
    MUART_voidInit(GSM_UART_CHANNEL);
}

void GSM_SendSMS(const char* phoneNumber, const char* message) {
    // Send AT command to initialize communication
    MUART_voidTransmitSynch(GSM_UART_CHANNEL, "AT\r\n");
    delay_ms(1000);

    // Set SMS text mode
    MUART_voidTransmitSynch(GSM_UART_CHANNEL, "AT+CMGF=1\r");
    delay_ms(1000);

    // Specify recipient phone number
    char command[50];
    sprintf(command, "AT+CMGS=\"%s\"\r", phoneNumber);
    MUART_voidTransmitSynch(GSM_UART_CHANNEL, command);
    delay_ms(1000);

    // Send message
    MUART_voidTransmitSynch(GSM_UART_CHANNEL, message);
    delay_ms(1000);

    // Send Ctrl+Z to indicate end of message
    MUART_voidTransmitByteSynch(GSM_UART_CHANNEL, (char)26);
}


void delay_ms(uint32 time) {
    uint32 i, j;
    for (i = 0; i < time; i++) {
        for (j = 0; j < 510; j++) { // Double the loop count
            // Adding some dummy operations to prevent optimization
            __asm("NOP");
        }
    }
}

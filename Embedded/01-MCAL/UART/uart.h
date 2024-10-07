
#ifndef UART_INTERFACE_H_
#define UART_INTERFACE_H_

/******************************************************************************
* Includes
*******************************************************************************/
#include "STD_TYPES.h"
#include "BIT_MATH.h"
//#include "GPIO_interface.h"

#include "uart_config.h"
#include "uart_private.h"
/******************************************************************************
* Preprocessor Constants
*******************************************************************************/
//UART Characterstics
#define UART_NUMBER_OF_CHANNELS    5
#define UART_1                     0
#define UART_2                     1
#define UART_3                     2
#define UART_4                     3
#define UART_5                     4
//UART Pins
#define UART_1_TX                  PINA9
#define UART_1_RX                  PINA10
#define UART_2_TX                  PINA2
#define UART_2_RX                  PINA3
#define UART_3_TX                  PINB10
#define UART_3_RX                  PINB11

/******************************************************************************
* Configuration Constants
*******************************************************************************/

/******************************************************************************
* Macros
*******************************************************************************/

/******************************************************************************
* Typedefs
*******************************************************************************/

/******************************************************************************
* Variables
*******************************************************************************/

/******************************************************************************
* Function Prototypes
*******************************************************************************/
void MUART_voidInit(uint8 Copy_u8UartNumber);
void MUART_voidTransmitSynch(uint8 Copy_u8UartNumber, uint8 Copy_u8DataArray[]);
uint8   MUART_u8ReceiveByteSynch(uint8 Copy_u8UartNumber);
uint8   MUART_u8ReceiveSynch(uint8 Copy_u8UartNumber, uint8 * Copy_u8Data);
void MUART_voidReceiveASynch(uint8 Copy_u8UartNumber, void (*CallBackFuncRx)(uint8));

#endif /*File_H_*/

/*** End of File **************************************************************/

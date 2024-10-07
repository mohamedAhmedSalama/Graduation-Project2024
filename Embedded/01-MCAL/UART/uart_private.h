/*
 * uart_private.h
 *
 *  Created on: Dec 2, 2023
 *      Author: moham
 */

#ifndef SRC_UART_PRIVATE_H_
#define SRC_UART_PRIVATE_H_

#ifndef UART_PRIVATE_H_
#define UART_PRIVATE_H_

/******************************************************************************
* Includes
*******************************************************************************/
#include "uart.h"
/******************************************************************************
* Typedefs
*******************************************************************************/

/**
* Defines seven variables which specify the UART registers.
*/
typedef struct
{
    volatile unsigned int SR;    /**<Status register */
    volatile unsigned int DR;    /**<Data register */
    volatile unsigned int BRR;   /**<BaudRate register */
    volatile unsigned int CR1;   /**<Control register number 1 */
    volatile unsigned int CR2;   /**<Control register number 2 */
    volatile unsigned int CR3;   /**<Control register number 3 */
    volatile unsigned int GTPR;
}UART_t;

/******************************************************************************
* Preprocessor Constants
*******************************************************************************/
// Some auxilary constants.
// UARTS base address.
#define UART_1_BASE_ADDRESS   0x40013800
#define UART_2_BASE_ADDRESS   0x40004400
#define UART_3_BASE_ADDRESS   0x40004800
#define UART_4_BASE_ADDRESS   0x40004C00
#define UART_5_BASE_ADDRESS   0x40005000
// Other constants.
#define CLR_REGISTER          0X00000000
#define ONE_BYTE              0xFF
/******************************************************************************
* Configuration Constants
*******************************************************************************/
// Register bits definition.

// SR bits register definition.
#define PE                    0
#define FE                    1
#define OREE                  2
#define NE                    3
#define IDLE                  4
#define RXNE                  5
#define TC                    6
#define TXE                   7
#define LDB                   8
#define CTS                   9
// CR1 bits register definition.
#define SPK                   0
#define RWU                   1
#define RE                    2
#define TE                    3
#define IDLEIE                4
#define RXNEIE                5
#define TCIE                  6
#define TXEIE                 7
#define PEIE                  8
#define PS                    9
#define PCE                   10
#define WAKE                  11
#define M                     12
#define UE                    13
// CR2 bits register definition.
#define ADD                   0
#define LBDL                  5
#define LBDIE                 6
#define LBCL                  8
#define CPHA                  9
#define CPOL                  10
#define CLKEN                 11
#define STOP                  12
#define LINEN                 14
// CR3 bits register definition.
#define EIE                   0
#define IREN                  1
#define IRLP                  2
#define HDSEL                 3
#define NACK                  4
#define SCEN                  5
#define DMAR                  6
#define DMAT                  7
#define RTSE                  8
#define CTSE                  9
#define CTSIE                 10
// GTPR bits register definition.
#define PSC                   0
#define GT                    1
/******************************************************************************
* Module Variable Definitions
*******************************************************************************/
// Array of UART channels that exist on MC.
static volatile UART_t * const UARTChannel[5] =
{
    ((volatile UART_t * const)(UART_1_BASE_ADDRESS)),
    ((volatile UART_t * const)(UART_2_BASE_ADDRESS)),
    ((volatile UART_t * const)(UART_3_BASE_ADDRESS)),
    ((volatile UART_t * const)(UART_4_BASE_ADDRESS)),
    ((volatile UART_t * const)(UART_5_BASE_ADDRESS))
};
/******************************************************************************
* Function Prototypes
*******************************************************************************/

#endif
/*** End of File **************************************************************/


#endif /* SRC_UART_PRIVATE_H_ */

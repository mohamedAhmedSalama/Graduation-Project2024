/*
 * DMA_private.h
 *
 *  Created on: Aug 24, 2022
 *      Author: ELKHOLY
 */

#ifndef MCAL_DMA_DMA_PRIVATE_H_
#define MCAL_DMA_DMA_PRIVATE_H_
#include "../../LIB/BIT_MATH.h"
#include "../../LIB/STD_TYPES.h"

typedef struct
{
	volatile uint32 CCR ;
	volatile uint32 CNDTR ;
	volatile uint32 CPAR ;
	volatile uint32 CMAR ;
	volatile uint32 Reserved ;
}DMA_Channel_T;

typedef struct
{
	volatile uint32     ISR ;
	volatile uint32     IFCR ;
	DMA_Channel_T    channel[7];
}DMA_T;


typedef enum
{
	CH_1 ,
	CH_2 ,
	CH_3,
	CH_4,
	CH_5,
	CH_6,
	CH_7
}Channel_T;

typedef enum {
	GIF,
	TCIF,
	HTIF,
	TEIF
}Flag_T;

typedef enum
{
	TransferComplete = 1 ,
	HalfTransferComplete = 2,
	TransferError = 3
}Interrupt_T;

typedef enum
{
	channel_enable,
	channel_disable
}status_t;

#define DMA1  (( DMA_T *) 0x40020000)

#define Very_High  0b11
#define High       0b10
#define Medium     0b01
#define Low        0b00

#define _32_Bit    0b10
#define _16_Bit    0b01
#define _8_Bit     0b00

#define Enable     0b01
#define Disable    0b00

#define RdFromMem  0b01
#define RdFromPer  0b00



#endif /* MCAL_DMA_DMA_PRIVATE_H_ */

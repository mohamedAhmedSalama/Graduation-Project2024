/*
 * DMA_interface.h
 *
 *  Created on: Aug 24, 2022
 *      Author: ELKHOLY
 */

#ifndef MCAL_DMA_DMA_INTERFACE_H_
#define MCAL_DMA_DMA_INTERFACE_H_

#include "../Inc/LIB/STD_TYPES.h"
#include "../Inc/MCAL/DMA/DMA_private.h"


void MDMA_voidChannelInit (Channel_T Copy_uint8DMA_Channel);
void MDMA1_voidChannel_Start (Channel_T channelNum, uint32 *Copy_uint32Source_Address, uint32 *Copy_uint32Destination_Address, uint16 Copy_uint16Block_Length);
void MDMA_voidSetChannelStatus (Channel_T Copy_uint8ChannelNum, status_t status);
void MDMA_voidSetSource_Dest_Address (Channel_T Copy_uint8ChannelNum,uint32 *Copy_uint32Source_Address, uint32 *Copy_uint32Destination_Address, uint16 Copy_uint16Block_Length);

void DMA_voidInterruptEnable ( Channel_T Copy_uint8ChannelNum, Interrupt_T Copy_uint8DMAIntType);
void DMA_voidInterruptDisable ( Channel_T Copy_uint8ChannelNum, Interrupt_T Copy_uint8DMAIntType);

void DMA_voidClearFlag(Channel_T Copy_uint8DMA_Channel , Flag_T Copy_uint8Flag );
uint8   DMA_uint8ReadFlag(Channel_T Copy_uint8DMA_Channel , Flag_T Copy_uint8Flag );

void DMA_SetCallBack(Channel_T Copy_uint8DMA_Channel , void (*pf)(void) );

#endif /* MCAL_DMA_DMA_INTERFACE_H_ */

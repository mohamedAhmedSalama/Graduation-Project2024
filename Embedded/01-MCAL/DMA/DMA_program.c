/*
 * DMA_program.c
 *
 *  Created on: Aug 24, 2022
 *      Author: ELHOSSENI
 */

#include <stdio.h>

#include "../Inc/LIB/BIT_MATH.h"
#include "../Inc/LIB/STD_TYPES.h"
#include "../Inc/MCAL/DMA/DMA_interface.h"
#include "../Inc/MCAL/DMA/DMA_private.h"
#include "../Inc/MCAL/DMA/DMA_configuration.h"

static void	(* DMA_CH_CallBack[7])	(void);

void MDMA_voidChannelInit (Channel_T Copy_uint8DMA_Channel)
{

	switch(Copy_uint8DMA_Channel)
	{
	case CH_1:
	DMA1 -> channel[Copy_uint8DMA_Channel].CCR |= ((DataDir_1<<4)|(CircularMode_1<<5)|(MemIncMode_1<<7)|(PerIncMode_1<<6)
											    |(Peripheral_Size_1 <<8)|(Memory_Size_1<<10)|(Periority_Level_1<<12)
												|(Mem2Mem_1<<14)); break;
	case CH_2:
    DMA1 -> channel[Copy_uint8DMA_Channel].CCR |= ((DataDir_2<<4)|(CircularMode_2<<5)|(MemIncMode_2<<7)|(PerIncMode_2<<6)
											    |(Peripheral_Size_2 <<8)|(Memory_Size_2<<10)|(Periority_Level_2<<12)
											    |(Mem2Mem_2<<14));	break;
	case CH_3:
    DMA1 -> channel[Copy_uint8DMA_Channel].CCR |= ((DataDir_3<<4)|(CircularMode_3<<5)|(MemIncMode_3<<7)|(PerIncMode_3<<6)
											    |(Peripheral_Size_3 <<8)|(Memory_Size_3<<10)|(Periority_Level_3<<12)
											    |(Mem2Mem_3<<14));	break;
	case CH_4:
    DMA1 -> channel[Copy_uint8DMA_Channel].CCR |= ((DataDir_4<<4)|(CircularMode_4<<5)|(MemIncMode_4<<7)|(PerIncMode_4<<6)
											    |(Peripheral_Size_4 <<8)|(Memory_Size_4<<10)|(Periority_Level_4<<12)
											    |(Mem2Mem_4<<14));	break;
	case CH_5:
    DMA1 -> channel[Copy_uint8DMA_Channel].CCR |= ((DataDir_5<<4)|(CircularMode_5<<5)|(MemIncMode_5<<7)|(PerIncMode_5<<6)
											    |(Peripheral_Size_5 <<8)|(Memory_Size_5<<10)|(Periority_Level_5<<12)
											    |(Mem2Mem_5<<14));	break;
	case CH_6:
    DMA1 -> channel[Copy_uint8DMA_Channel].CCR |= ((DataDir_6<<4)|(CircularMode_6<<5)|(MemIncMode_6<<7)|(PerIncMode_6<<6)
											    |(Peripheral_Size_6 <<8)|(Memory_Size_6<<10)|(Periority_Level_6<<12)
											    |(Mem2Mem_6<<14));	break;
	case CH_7:
    DMA1 -> channel[Copy_uint8DMA_Channel].CCR |= ((DataDir_7<<4)|(CircularMode_7<<5)|(MemIncMode_7<<7)|(PerIncMode_7<<6)
											    |(Peripheral_Size_7 <<8)|(Memory_Size_7<<10)|(Periority_Level_7<<12)
											    |(Mem2Mem_7<<14));	break;
	}
    DMA_voidInterruptDisable(Copy_uint8DMA_Channel, HalfTransferComplete);
    DMA_voidInterruptDisable(Copy_uint8DMA_Channel, TransferError);
    DMA_voidInterruptEnable(Copy_uint8DMA_Channel, TransferComplete);

    MDMA_voidSetChannelStatus (Copy_uint8DMA_Channel,channel_disable);

}

void MDMA1_voidChannel_Start (Channel_T Copy_uint8ChannelNum, uint32 *Copy_uint32Source_Address, uint32 *Copy_uint32Destination_Address, uint16 Copy_uint16Block_Length)
{
	/*make sure channel is disabled */
	MDMA_voidSetChannelStatus(Copy_uint8ChannelNum,channel_disable);

	/*Set Source and destination address
	 * load block length*/
	MDMA_voidSetSource_Dest_Address (Copy_uint8ChannelNum, Copy_uint32Source_Address, Copy_uint32Destination_Address, Copy_uint16Block_Length);

	/*enable channel*/
	MDMA_voidSetChannelStatus(Copy_uint8ChannelNum,channel_enable);

}
void MDMA_voidSetChannelStatus (Channel_T Copy_uint8ChannelNum, status_t status)
{
	if (status == channel_enable)
	{
		SET_BIT(DMA1 -> channel[Copy_uint8ChannelNum].CCR, 0);
	}
	else if ( status == channel_disable)
	{
		CLR_BIT(DMA1 -> channel[Copy_uint8ChannelNum].CCR , 0);
	}
}
void MDMA_voidSetSource_Dest_Address (Channel_T Copy_uint8ChannelNum,uint32 *Copy_uint32Source_Address, uint32 *Copy_uint32Destination_Address, uint16 Copy_uint16Block_Length)
{

	DMA1 -> channel [Copy_uint8ChannelNum].CPAR = Copy_uint32Source_Address;
	DMA1 -> channel [Copy_uint8ChannelNum].CMAR = Copy_uint32Destination_Address;
	DMA1 -> channel [Copy_uint8ChannelNum].CNDTR = Copy_uint16Block_Length;
}

void DMA_voidInterruptEnable ( Channel_T Copy_uint8ChannelNum, Interrupt_T Copy_uint8DMAIntType)
{
	SET_BIT(DMA1->channel[Copy_uint8ChannelNum].CCR ,Copy_uint8DMAIntType );

}

void DMA_voidInterruptDisable ( Channel_T Copy_uint8ChannelNum, Interrupt_T Copy_uint8DMAIntType)
{
	CLR_BIT(DMA1->channel[Copy_uint8ChannelNum].CCR ,Copy_uint8DMAIntType );

}

void DMA_voidClearFlag(Channel_T Copy_uint8DMA_Channel , Flag_T Copy_uint8Flag )
{
	SET_BIT(DMA1 -> IFCR , ((Copy_uint8DMA_Channel*4)+ Copy_uint8Flag));
}

uint8   DMA_uint8ReadFlag(Channel_T Copy_uint8DMA_Channel , Flag_T Copy_uint8Flag )
{
   return READ_BIT(DMA1 -> ISR , ((Copy_uint8DMA_Channel*4)+ Copy_uint8Flag));
}

void DMA_SetCallBack(Channel_T Copy_uint8DMA_Channel , void (*pf)(void) )
{
	if(pf != NULL)
	{
		DMA_CH_CallBack [Copy_uint8DMA_Channel] = pf;
	}
}



void DMA1_Channel1_IRQHandler()
{
	DMA_voidClearFlag(CH_1, GIF);
	DMA_voidClearFlag(CH_1, HTIF);
	DMA_voidClearFlag(CH_1, TCIF);
	DMA_voidClearFlag(CH_1, TEIF);
	DMA_CH_CallBack[CH_1]();
}

void DMA1_Channel2_IRQHandler()
{
	DMA_voidClearFlag(CH_2, GIF);
	DMA_voidClearFlag(CH_2, HTIF);
	DMA_voidClearFlag(CH_2, TCIF);
	DMA_voidClearFlag(CH_2, TEIF);
	DMA_CH_CallBack[CH_2]();
}

void DMA1_Channel3_IRQHandler()
{
	DMA_voidClearFlag(CH_3, GIF);
	DMA_voidClearFlag(CH_3, HTIF);
	DMA_voidClearFlag(CH_3, TCIF);
	DMA_voidClearFlag(CH_3, TEIF);
	DMA_CH_CallBack[CH_3]();
}

void DMA1_Channel4_IRQHandler()
{
	DMA_voidClearFlag(CH_4, GIF);
	DMA_voidClearFlag(CH_4, HTIF);
	DMA_voidClearFlag(CH_4, TCIF);
	DMA_voidClearFlag(CH_4, TEIF);
	DMA_CH_CallBack[CH_4]();
}

void DMA1_Channel5_IRQHandler()
{
	DMA_voidClearFlag(CH_5, GIF);
	DMA_voidClearFlag(CH_5, HTIF);
	DMA_voidClearFlag(CH_5, TCIF);
	DMA_voidClearFlag(CH_5, TEIF);
	DMA_CH_CallBack[CH_5]();
}

void DMA1_Channel6_IRQHandler()
{
	DMA_voidClearFlag(CH_6, GIF);
	DMA_voidClearFlag(CH_6, HTIF);
	DMA_voidClearFlag(CH_6, TCIF);
	DMA_voidClearFlag(CH_6, TEIF);
	DMA_CH_CallBack[CH_6]();
}

void DMA_Channel7_IRQHandler()
{
	DMA_voidClearFlag(CH_7, GIF);
	DMA_voidClearFlag(CH_7, HTIF);
	DMA_voidClearFlag(CH_7, TCIF);
	DMA_voidClearFlag(CH_7, TEIF);
	DMA_CH_CallBack[CH_7]();
}



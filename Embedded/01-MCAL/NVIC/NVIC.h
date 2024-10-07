#ifndef NVIC_H_
#define NVIC_H_
/*---------------------Includes------------------------------*/
#include "STD_TYPES.h"
/*---------------------Macro Declaration---------------------*/
#define NVIC_base       (0xE000E100UL)
#define NVIC            ((NVIC_Type *)NVIC_base)
#define NVIC_Prio_Bits  4U
/*---------------------Macro Fucntion Declaration------------------*/

/*---------------------Data Type Declaration-----------------*/
typedef struct
{
    volatile uint32 ISER[8U];
    uint32 RESERVED0[24U];
    volatile uint32 ICER[8U];
    uint32 RESERVED1[24U];
    volatile uint32 ISPR[8U];
    uint32 RESERVED2[24U];
    volatile uint32 ICPR[8U];
    uint32 RESERVED3[24U];
    volatile uint32 IABR[8U];
    uint32 RESERVED4[56U];
    volatile uint8 IP[240U];
    uint32 RESERVED5[644U];
    volatile uint32 STIR;
}NVIC_Type;

typedef enum{
    EXTI0_Num_From_VT 	      =   6 ,
    EXTI1_Num_From_VT 		  =   7 ,
    EXTI2_Num_From_VT         =   8 ,
    EXTI3_Num_From_VT         =   9 ,
    EXTI4_Num_From_VT         =   10,
    DMA1_Channel1_Num_From_VT =   11,
    DMA1_Channel2_Num_From_VT =   12,
    DMA1_Channel3_Num_From_VT =   13,
    DMA1_Channel4_Num_From_VT =   14,
    DMA1_Channel5_Num_From_VT =   15,
    DMA1_Channel6_Num_From_VT =   16,
    DMA1_Channel7_Num_From_VT =   17,
    ADC1_2_Num_From_VT		  =   18,
    USB_HP_CAN_TX_Num_From_VT =   19,
    USB_LP_CAN_RX_Num_From_VT =   20,
    CAN_RX1_Num_From_VT       =   21,
    CAN_SCE_Num_From_VT       =   22,
    EXTI9_5_Num_From_VT		  =   23,
    TIM1_BRK_Num_From_VT      =   24,
    TIM1_UP_Num_From_VT	      =   25,
    TIM1_TRG_COM_Num_From_VT  =   26,
    TIM1_CC_Num_From_VT	      =   27,
    TIM2_Num_From_VT		  =   28,
    TIM3_Num_From_VT		  =   29,
    TIM4_Num_From_VT		  =   30,
    I2C1_EV_Num_From_VT		  =   31,
    I2C1_ER_Num_From_VT		  =   32,
    I2C2_EV_Num_From_VT		  =   33,
    I2C2_ER_Num_From_VT		  =   34,
    SPI1_Num_From_VT		  =   35,
    SPI2_Num_From_VT		  =   36,
    USART1_Num_From_VT		  =   37,
    USART2_Num_From_VT		  =   38,
    USART3_Num_From_VT		  =   39,
    EXTI15_10_Num_From_VT	  =   40,
    RTCAlarm_Num_From_VT	  =	  41,
    USBWakeup_Num_From_VT	  =	  42,
    TIM8_BRK_Num_From_VT	  =	  43,
    TIM8_UP_Num_From_VT		  =   44,
    TIM8_TRG_COM_Num_From_VT  =   45,
    TIM8_CC_Num_From_VT	 	  =   46,
    ADC3_Num_From_VT	   	  =   47,
    FSMC_Num_From_VT	   	  =   48,
    SDIO_Num_From_VT	   	  =   49,
    TIM5_Num_From_VT	   	  =   50,
    SPI3_Num_From_VT	   	  =   51,
    UART4_Num_From_VT	   	  =   52,
    UART5_Num_From_VT	   	  =   53,
    TIM6_Num_From_VT		  =   54,
    TIM7_Num_From_VT		  =   55,
    DMA2_Channel1_Num_From_VT =	  56,
    DMA2_Channel2_Num_From_VT =	  57,
    DMA2_Channel3_Num_From_VT =   58,
    DMA2_Channel4_5           =   59
}IRQn_type;
/*---------------------Includes Declaration------------------*/
void NVIC_EnableIRQ(IRQn_type IRQn);
void NVIC_DisableIRQ(IRQn_type IRQn);
void NVIC_SetPendingIRQ(IRQn_type IRQn);
void NVIC_ClearPendingIRQ(IRQn_type IRQn);
uint32 NVIC_GetActive(IRQn_type IRQn);

void NVIC_SetPriority(IRQn_type IRQn, uint32 priority);
uint32 NVIC_GetPrioriy(IRQn_type IRQn);
#endif
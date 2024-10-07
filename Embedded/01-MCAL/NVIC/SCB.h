#ifndef SCB_H_
#define SCB_H_
/*---------------------Includes------------------------------*/
#include "STD_TYPES.h"
/*---------------------Macro Declaration---------------------*/
#define SCB_BASE        (0xE000ED00UL)
#define SCB             ((SCB_Type *)SCB_BASE)

#define SCB_PRIORITY_GROUP_0       0x00000007U  /*NVIC_0_GROUP_16_SUB*/
#define SCB_PRIORITY_GROUP_1       0x00000006U  /*NVIC_2_GROUP_8_SUB */
#define SCB_PRIORITY_GROUP_2       0x00000005U  /*NVIC_4_GROUP_4_SUB */
#define SCB_PRIORITY_GROUP_3       0x00000004U  /*NVIC_8_GROUP_2_SUB */
#define SCB_PRIORITY_GROUP_4       0x00000003U  /*NVIC_16_GROUP_0_SUB*/

#define SCB_AIRCR_PRIGROUP_pos     8U
#define SCB_AIRCR_PRIGROUP_MSK     (7UL << SCB_AIRCR_PRIGROUP_pos)

#define SCB_AIRCR_VECTKEYSTAT_pos  16U
#define SCB_AIRCR_VECTKEYSTAT_MSK  (0xFFFFUL << SCB_AIRCR_VECTKEYSTAT_pos)
/*---------------------Macro Fucntion Declaration------------------*/

/*---------------------Data Type Declaration-----------------*/
typedef struct
{
    volatile uint32 CPUID;
    volatile uint32 ICSR;
    volatile uint32 VTOR;
    volatile uint32 AIRCR;
    volatile uint32 SCR;
    volatile uint32 CCR;
    volatile uint32 SHPR1;
    volatile uint32 SHPR2;
    volatile uint32 SHPR3; 
    volatile uint32 SHCSR;
    volatile uint32 CFSR;
}SCB_Type;

/*---------------------Includes Declaration------------------*/
void SCB_SetPriorityGrouping (uint32 PriorityGroup);
uint32 SCB_GetPriorityGrouping (void);

#endif
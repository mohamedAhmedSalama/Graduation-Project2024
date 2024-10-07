#include "SCB.h"

void SCB_SetPriorityGrouping (uint32 PriorityGroup){
    uint32 Register_value = 0;
    PriorityGroup &= (uint32)0x07;
    Register_value = SCB->AIRCR;
    Register_value &= ~((uint32)SCB_AIRCR_PRIGROUP_MSK | (uint32)SCB_AIRCR_VECTKEYSTAT_MSK);
    Register_value = (Register_value | ((uint32)0x05FA << SCB_AIRCR_VECTKEYSTAT_pos) | (PriorityGroup << SCB_AIRCR_PRIGROUP_pos));
    SCB->AIRCR = Register_value;
}

uint32 SCB_GetPriorityGrouping(void)
{
    return (((uint32)SCB->AIRCR & (uint32)SCB_AIRCR_PRIGROUP_MSK) >> SCB_AIRCR_PRIGROUP_pos);
}
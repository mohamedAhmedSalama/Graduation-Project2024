#include "NVIC.h"

void NVIC_EnableIRQ(IRQn_type IRQn){
    if ((uint32)IRQn >= 0)
    {
        NVIC->ISER[((uint32)IRQn >> 5)] = (1UL << (((uint32)IRQn) & 0x1F));
    }    
}
void NVIC_DisableIRQ(IRQn_type IRQn){
    if ((uint32)IRQn >= 0)
    {
        NVIC->ICER[((uint32)IRQn >> 5)] = (1UL << (((uint32)IRQn) & 0x1F));
    } 
}
void NVIC_SetPendingIRQ(IRQn_type IRQn){
    if ((uint32)IRQn >= 0)
    {
        NVIC->ISPR[((uint32)IRQn >> 5)] = (1UL << (((uint32)IRQn) & 0x1F));
    } 
}
void NVIC_ClearPendingIRQ(IRQn_type IRQn){
    if ((uint32)IRQn >= 0)
    {
        NVIC->ICPR[((uint32)IRQn >> 5)] = (1UL << (((uint32)IRQn) & 0x1F));
    } 
}
uint32 NVIC_GetActive(IRQn_type IRQn){
    if ((uint32)IRQn >= 0)
    {
        return (NVIC->IABR[((uint32)IRQn >> 5)] & (1UL << (((uint32)IRQn) & 0x1F)) != (uint32)0 ? 1UL : 0UL) ;
    }
    else
    {
        return 0UL ;
    }    
}

void NVIC_SetPriority(IRQn_type IRQn, uint32 priority){
    if ((uint32)IRQn >= 0) 
    {
        NVIC->IP[(uint32)IRQn] = (uint8)((priority << (8U - NVIC_Prio_Bits)) & (uint32)0xFF); 
    }
    else
    {
        /*Nothing*/
    }
}
uint32 NVIC_GetPrioriy(IRQn_type IRQn){
    if ((uint32)IRQn >= 0)
    {
        return ((NVIC->IP[(uint32)IRQn]) >> (8U - NVIC_Prio_Bits));
    }
    else
    {
        /*Nothing*/
    }
}
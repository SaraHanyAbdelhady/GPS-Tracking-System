#ifndef SYSTICK_H
#define SYSTICK_H

#include "../../../Services/STD_TYPES.h"
void SYSTICKTIMER_init(void);
void Systick_Wait(u32 d); 
void delay_m(u64 delay);

#endif 

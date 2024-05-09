#ifndef SYSTICK_H
#define SYSTICK_H

#include "../../../Services/STD_TYPES.h"
extern void Systick_Init(void);
extern void Systick_Wait(u32 delay);
extern void delay (u32 delay);

#endif 

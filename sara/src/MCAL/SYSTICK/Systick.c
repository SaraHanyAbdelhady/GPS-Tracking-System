#include "../../../Services/tm4c123gh6pm.h"
#include "../../../Services/Bit_Utilities.h"
#include "../../../Services/STD_TYPES.h"


void SYSTICKTIMER_init(void){
	NVIC_ST_CTRL_R = 0;
	NVIC_ST_RELOAD_R = 0XFFFFFF;
	NVIC_ST_CURRENT_R = 0;
	NVIC_ST_CTRL_R = 0X05 ;
}

void Systick_Wait(u32 d){
		NVIC_ST_CTRL_R=0;
    NVIC_ST_RELOAD_R=d-1;
    NVIC_ST_CURRENT_R=0;
		NVIC_ST_CTRL_R=0x00000005;
    while((NVIC_ST_CTRL_R&0x00010000)==0);  
}

void delay_m (u64 delay){
		u32 i ;
		for(i=0;i<delay;i++){
			Systick_Wait(16000);
		}
}

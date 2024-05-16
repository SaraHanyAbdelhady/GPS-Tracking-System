#include "../../../Services/tm4c123gh6pm.h"
#include "../../../Services/Bit_Utilities.h"
#include "../../../Services/STD_TYPES.h"
#include "../../../Headers/HAL/Push Button/Push button.h"
void Button_Init(){ 
	CLR_BIT(GPIO_PORTF_DIR_R, SW_1);
	CLR_BIT(GPIO_PORTF_DIR_R, SW_2);
	SET_BIT(GPIO_PORTF_PUR_R, SW_1);
	SET_BIT(GPIO_PORTF_PUR_R, SW_2);
}  
u8 Button_Pressed(void){
	if(READ_BIT(GPIO_PORTF_DATA_R,SW_1) == 0)
	return 1;
	else return 0;
}

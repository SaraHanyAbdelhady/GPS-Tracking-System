#include "../../../Services/tm4c123gh6pm.h"
#include "../../../Services/Bit_Utilities.h"
#include "../../../Services/STD_TYPES.h"
#include "../../../Headers/HAL/LED/LED.h"
#include "../../../Headers/MCAL/GPIO/GPIO.h"


void LEDInit(){
	SET_BIT(GPIO_PORTF_DIR_R,LED_RED);
	SET_BIT(GPIO_PORTF_DIR_R,LED_BLUE);
	SET_BIT(GPIO_PORTF_DIR_R,LED_GREEN);
}
void LED_On(u8 copy_u8LedColour){
	switch(copy_u8LedColour)
    {
    case LED_RED:
        SET_BIT(GPIO_PORTF_DATA_R,LED_RED);
        break;
    case LED_BLUE:
        SET_BIT(GPIO_PORTF_DATA_R,LED_BLUE);
        break;
    case LED_GREEN:
        SET_BIT(GPIO_PORTF_DATA_R,LED_GREEN);
        break;
    }
}
void LED_Off(u8 copy_u8LedColour){
	switch(copy_u8LedColour)
    {
    case LED_RED:
        CLR_BIT(GPIO_PORTF_DATA_R,LED_RED);
        break;
    case LED_BLUE:
        CLR_BIT(GPIO_PORTF_DATA_R,LED_BLUE);
        break;
    case LED_GREEN:
        CLR_BIT(GPIO_PORTF_DATA_R,LED_GREEN);
        break;
    }
}
	

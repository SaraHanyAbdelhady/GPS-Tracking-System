#ifndef __HAL_LED_INTERFACE_H__
#define __HAL_LED_INTERFACE_H__



#define LED_RED  	 	1
#define LED_BLUE 		2
#define LED_GREEN	  3



#define LED_TIME_ON			1000

void LEDInit(void);
void LED_On(u8 copy_u8LedColour);
void LED_Off(u8 copy_u8LedColour);

#endif 
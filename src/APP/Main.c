#include "../../Services/tm4c123gh6pm.h"
#include "../../Services/Bit_Utilities.h"
#include "../../Services/STD_TYPES.h"
#include "../../Headers/MCAL/UART/UART.h"
#include "../../Headers/MCAL/GPIO/GPIO.h"
#include "../../Headers/HAL/GPS/GPS.h"
#include "../../Headers/HAL/LED/LED.h"
#include "../../Headers/HAL/Push button/Push button.h"
#include "../../Headers/APP/APP.h"
#include "../../Services/STD_TYPES.h"

u8 GPS_u8SpeedArr[5];

u8 push_button;

int main() {
	// intiallize portf for leds & switches
    PortF_Init();
	// intiallize portB for LCD
	PortB_Init();
	// intiallize uart2 for gps
	UART2_Init();
	// intiallize uart0 for bluetooth or serial inter face between laptop&tiva c
	UART0_Init();
	Button_Init();
	LEDInit();
	while(1){
		
		push_button = Button_Pressed();	
		
		while(!push_button && Distance(f32 longStart, f32 latStart, f32 longEnd, f32 latEnd) < 100){
			//Put trajectories
		}
		LED_On(LED_RED);
	}
}

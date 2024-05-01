#include "../../Services/tm4c123gh6pm.h"
#include "../../Services/Bit_Utilities.h"
#include "../../Services/STD_TYPES.h"
#include "../../Headers/MCAL/UART/UART.h"
#include "../../Headers/MCAL/UART/UART_private.h"
#include "../../Headers/MCAL/GPIO.h"
#include "../../Headers/HAL/GPS/GPS.h"
#include "../../Headers/HAL/LED/LED.h"
#include "../../Headers/HAL/Push button/Push button.h"



unsigned char SW1_input(void){
return GPIO_PORTF_DATA_R & 0x10;
}
unsigned char SW2_input(void){
return GPIO_PORTF_DATA_R & 0x01;
}
void LEDs_output(unsigned char data){
GPIO_PORTF_DATA_R &= ~0x0E; //clearing bits
GPIO_PORTF_DATA_R |= data;
}



unsigned char push_button;

int main() {
	// intiallize portf for leds & switches
	// intiallize portA for LCD
	// intiallize uart0 for gps
	// intiallize uart5 for bluetooth or serial inter face between laptop&tiva c
	Button_Init();
	LEDInit();
	while(1){
		
		push_button = Button_Pressed();	
		
		while(!push_button){
			//Put trajectories
		}
		LED_On(LED_RED);
	}
}

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
#include "../../Headers/HAL/LCD/LCD.h"
#include "../../Headers/MCAL/SYSTICK/Systick.h"
#include "../../Headers/MCAL/EEPROM/EEPROM.h"
#include <string.h>



u8 GPS_u8SpeedArr[5];

u8 push_button;

u32 address;





int main() {
	
	//declaration of variables that store the start points of the trajectory 
	f32 longStart = 0, latStart = 0;
	
	//declaration of variables that store the current points in the trajectory at a specific point of time
	f32 longEnd = 0, latEnd = 0 ;
	
	f32 totalDistance =0;
	f32 distance =0;
  f32 currentLatitude =0;
	f32 currentlongitude =0;
	f32 previousLatitude =0;
	f32 previousLongitude =0;
	
	// intiallize portf for leds & switches
    PortF_Init();
	
	// intiallize portB for LCD
	PortB_Init();
	PortE_Init();
	// intiallize uart2 for gps
	UART2_Init();
	
	// intiallize uart0 for bluetooth or serial inter face between laptop&tiva c
	UART0_Init();
	Button_Init();
	LEDInit();
  u8 Local_u8Speed = 0;
	
	GPS_voidReceiveSentence(& latStart, & longStart, & Local_u8Speed );
	previousLatitude =latStart;
	previousLongitude=longStart;
	 
	//	displaying on LCD
	  LCD_voidSendString("Total Dist:");
    LCD_voidGoToXYPos(0, 14);
    LCD_voidSendString(" m");
    LCD_voidGoToXYPos(1, 0);
    LCD_voidSendString("SPEED:");
    LCD_voidGoToXYPos(1, 12);
    LCD_voidSendString("knot");
		
	//	start of interface between laptop and tiva
	UART0_SendString ("ENTER \n");
	address=EEPROM_START_ADDR;	
		
	while(1){
		const int lengthLap = 2; //For Recieving U
		
		push_button = Button_Pressed();	
		
		while(!push_button &&  totalDistance < 100){
			//Put trajectories
			GPS_voidReceiveSentence(& currentLatitude, & currentlongitude, & Local_u8Speed );
		  distance =Distance( previousLongitude, previousLatitude, currentlongitude, currentLatitude); 
			totalDistance+= distance ;
			LCD_voidGoToXYPos(1, 6);
      LCD_voidSendString(GPS_u8SpeedArr);	
			
			
			//	Saving to memory
			eeprom_write(currentLatitude,address);
			address+=4;
			eeprom_write(currentlongitude,address);
			address+=4;
			
		}
		LED_On(LED_BLUE );
		LCD_voidGoToXYPos(0, 11); /**< New Line in LCD @ position:(1,0) */
    LCD_voidSendNumber(totalDistance);
	}
	//	for receiving U
  const int length=3;
  char command[length]={0};

	UART0_RecieveString(command,length);
	if(strcmp(command, "U") == 0)
		{
  while(address>EEPROM_START_ADDR){
		f32 longitude=0;
		f32 latitude=0;
		
		// to be seen isa
					//longitude = eeprom_read(address);
				//	address-=4;
			// UART0_SendString (longitude);
	  // to be seen isa
				// latitude = eeprom_read(address);
				//address-=4;
				//UART0_SendString (latitude);
	
	
	}
		
	
	
}



}
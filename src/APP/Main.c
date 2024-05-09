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
#include <stdint.h>



char GPS_u8SpeedArr[5];
u8 push_button;

u32 address;

const int length=3;					//	for receiving U
char command[length]={0}; 	//	for receiving U
//declaration of variables that store the start points of the trajectory 
f32 longStart = 0, latStart = 0;
	
//declaration of variables that store the End points of the trajectory 
f32 longEnd = 0, latEnd = 0 ;
int main() {


	f32 totalDistance =0;
	f32 distance =0;
  f32 currentLatitude =0;
	f32 currentlongitude =0;
	f32 previousLatitude =0;
	f32 previousLongitude =0;
	u8 Local_u8Speed = 0;
	
	// intiallize portf for leds & switches
    PortF_Init();
	
	// intiallize portB for LCD
	PortB_Init();
	PortE_Init();
	// intiallize uart2 for gps
	UART2_Init();
	
	// intiallize uart0 for bluetooth or serial interface between laptop&tiva c
	UART0_Init();
	Button_Init();
	LEDInit();
	LCD_voidInit();
  
	
	GPS_voidReceiveSentence(& latStart, & longStart, & Local_u8Speed );
	eeprom_write(latStart,address);
			address+=4;
			eeprom_write(longStart,address);
			address+=4;
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
	
	address=EEPROM_START_ADDR;	
		
	while(1){

		push_button = Button_Pressed();	
		
		while(!push_button){ //&&  totalDistance < 100
			//Put trajectories
			GPS_voidReceiveSentence(& currentLatitude, & currentlongitude, & Local_u8Speed );
		  distance =Distance( previousLongitude, previousLatitude, currentlongitude, currentLatitude); 
			previousLongitude=currentlongitude;
			previousLatitude=currentLatitude;
			totalDistance+= distance ;
			LCD_voidGoToXYPos(1, 6);
      LCD_voidSendString(GPS_u8SpeedArr);	
			
			
			//	Saving to memory
			eeprom_write(currentLatitude,address);
			address+=4;
			eeprom_write(currentlongitude,address);
			address+=4;
			
		}
		
		longEnd = currentlongitude;
		latEnd =currentLatitude;
		LED_On(LED_BLUE );
		LCD_voidGoToXYPos(0, 11); /**< New Line in LCD @ position:(1,0) */
    Print_Distance_To_LCD(totalDistance);
	

	UART0_SendString ("ENTER: \n");
 

	UART0_RecieveString(command,length);
	if(strcmp(command, "U") == 0)
		{
  while(address>EEPROM_START_ADDR){
		f32 longitude=0;
		char str_longitude[20]={0};
		f32 latitude=0;
		char str_latitude[20]={0};
		
		longitude = eeprom_read(address);
		ConvertFloatToStr(longitude,str_longitude);
		UART0_SendString (str_longitude);
		address-=4;
		UART0_SendString ("   ");
		latitude = eeprom_read(address);
		ConvertFloatToStr(latitude,str_latitude);
		UART0_SendString (str_latitude);
		address-=4;
		UART0_SendString ("\n");
	}
}
}


}
	

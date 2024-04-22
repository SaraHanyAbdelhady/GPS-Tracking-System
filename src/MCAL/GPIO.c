<<<<<<< HEAD
#include "../../Services/Bit_Utilities.h"
#include "../../Services/STD_TYPES.h"
#include  "../../Services/tm4c123gh6pm.h"
=======
#include"../Services/tm4c123gh6pm.h"
#include"../Services/STD_TYPES.h"
#include"../Services/Bit_Utilities.h"



void Set_vPinDirection(u8 port_name,u8 pin_number, u8 pin_direction){ // a fn that specifiec whether the pin is input or output
	
	switch(port_name)
	{
		case 'A':
		case 'a':
		{
			if(pin_direction==0) //input
				CLEAR_BIT(GPIO_PORTA_DIR_R,pin_number);
			else //output
				SET_BIT(GPIO_PORTA_DIR_R,pin_number);
		}
		break;
		
		case 'B':
		case 'b':
		{
			if(pin_direction==0) //input
				CLEAR_BIT(GPIO_PORTB_DIR_R,pin_number);
			else //output
				SET_BIT(GPIO_PORTB_DIR_R,pin_number);
		}
		break;
		
		case 'C':
		case 'c':
		{
			if(pin_direction==0) //input
				CLEAR_BIT(GPIO_PORTC_DIR_R,pin_number);
			else
				SET_BIT(GPIO_PORTC_DIR_R,pin_number);
		}
		break;
		
		case 'D':
		case 'd':
		{
			if(pin_direction==0) //input
				CLEAR_BIT(GPIO_PORTD_DIR_R,pin_number);
			else //output
				SET_BIT(GPIO_PORTD_DIR_R,pin_number);
		}
		break;
		
		case 'E':
		case 'e':
		{
			if(pin_direction==0) //input
				CLEAR_BIT(GPIO_PORTE_DIR_R,pin_number);
			else //output
				SET_BIT(GPIO_PORTE_DIR_R,pin_number);
		}
		break;
		
		case 'F':
		case 'f':
		{
			if(pin_direction==0) //input
				CLEAR_BIT(GPIO_PORTF_DIR_R,pin_number);
			else //output
				SET_BIT(GPIO_PORTF_DIR_R,pin_number);
		}
		//???? a7ot default case wala la2 ?	
	}
}
	
	
	u8 Get_u8PinValue(u8 port_name,u8 pin_number, u8 pin_direction)
	{ // a fn that reads the data of a specific pin
		switch(port_name)
	{
		case 'A':
		case 'a':
		{
			return GET_BIT(GPIO_PORTA_DATA_R,pin_number);
		}
		break;
		
		case 'B':
		case 'b':
		{
			return GET_BIT(GPIO_PORTB_DATA_R,pin_number);
		}
		break;
		
		case 'C':
		case 'c':
		{
			return GET_BIT(GPIO_PORTC_DATA_R,pin_number);
		}
		break;
		
		case 'D':
		case 'd':
		{
			return GET_BIT(GPIO_PORTD_DATA_R,pin_number);
		}
		break;
		
		case 'E':
		case 'e':
		{
			return GET_BIT(GPIO_PORTE_DATA_R,pin_number);
		}
		break;
		
		case 'F':
		case 'f':
		{
			return GET_BIT(GPIO_PORTF_DATA_R,pin_number);
		}
		//???? a7ot default case wala la2 ?	
	}	
	}
	
	void Set_vPortValue(u8 port_name, u8 PortValue){ // a fn the writes data on the port
		
		switch(port_name)
	{
		case 'A':
		case 'a':
		{
			GPIO_PORTA_DATA_R=PortValue;
		}
		break;
		
		case 'B':
		case 'b':
		{
			GPIO_PORTB_DATA_R=PortValue;
		}
		break;
		
		case 'C':
		case 'c':
		{
			GPIO_PORTC_DATA_R=PortValue;
		}
		break;
		
		case 'D':
		case 'd':
		{
			GPIO_PORTD_DATA_R=PortValue;
		}
		break;
		
		case 'E':
		case 'e':
		{
			GPIO_PORTE_DATA_R=PortValue;
		}
		break;
		
		case 'F':
		case 'f':
		{
			GPIO_PORTF_DATA_R=PortValue;
		}
		//???? a7ot default case wala la2 ?	
	}	
	}
	
	void Toggle_vPinValue(u8 port_name,u8 pin_number) { // a fn that flips the value of a specific pin
		switch(port_name)
	{
		case 'A':
		case 'a':
		{
			TOG_BIT(GPIO_PORTA_DATA_R,pin_number);
		}
		break;
		
		case 'B':
		case 'b':
		{
			TOG_BIT(GPIO_PORTB_DATA_R,pin_number);
		}
		break;
		
		case 'C':
		case 'c':
		{
			TOG_BIT(GPIO_PORTC_DATA_R,pin_number);
		}
		break;
		
		case 'D':
		case 'd':
		{
			TOG_BIT(GPIO_PORTD_DATA_R,pin_number);
		}
		break;
		
		case 'E':
		case 'e':
		{
			TOG_BIT(GPIO_PORTE_DATA_R,pin_number);
		}
		break;
		
		case 'F':
		case 'f':
		{
			TOG_BIT(GPIO_PORTF_DATA_R,pin_number);
		}
		//???? a7ot default case wala la2 ?	
	}	
	
		
	}
	
	
	
	

>>>>>>> c3212b4fcc3c62c984655ea289dee5509b21b42c

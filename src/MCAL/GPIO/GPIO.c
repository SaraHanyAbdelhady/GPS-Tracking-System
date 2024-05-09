#include "../../../Services/Bit_Utilities.h"
#include "../../../Services/STD_TYPES.h"
#include  "../../../Services/tm4c123gh6pm.h"
#include "../../../Headers/MCAL/GPIO/GPIO.h"

	// Port F initialization as GPIO for switches and LEDs
 void PortF_Init(void){ 
	SET_BIT(SYSCTL_RCGCGPIO_R,5);
			while(READ_BIT(SYSCTL_PRGPIO_R,5)==0);
			GPIO_PORTF_LOCK_R =GPIO_LOCK_KEY;
			GPIO_PORTF_CR_R=0xFF;
			GPIO_PORTF_AFSEL_R = 0x00;
			GPIO_PORTF_DEN_R = 0xFF;
			GPIO_PORTF_PCTL_R = 0x00;
			GPIO_PORTF_AMSEL_R = 0x00;
          // Set the direction of bits 1,2,3 as output and the rest remains zeros (inputs)
			SET_BIT(GPIO_PORTF_DIR_R,1);
			SET_BIT(GPIO_PORTF_DIR_R,2);
			SET_BIT(GPIO_PORTF_DIR_R,3);
			CLR_BIT(GPIO_PORTF_DATA_R,0);
		    CLR_BIT(GPIO_PORTF_DATA_R,4);
		// initialize pins 1-3 with zeros (LEDs are off at the beginning)
		CLR_BIT(GPIO_PORTF_DATA_R,1);
		CLR_BIT(GPIO_PORTF_DATA_R,2);
		CLR_BIT(GPIO_PORTF_DATA_R,3);
 }

 // Port A initialization as UART
  
  void PortA_Init(void){
	SET_BIT(SYSCTL_RCGCGPIO_R,0);
			while(READ_BIT(SYSCTL_PRGPIO_R,0)==0);
			GPIO_PORTA_LOCK_R =GPIO_LOCK_KEY;
		  GPIO_PORTA_AFSEL_R = 0x01;
			GPIO_PORTA_PCTL_R = 0x11;
			GPIO_PORTA_DEN_R = 0xFF;
			GPIO_PORTA_AMSEL_R = 0x00;
			GPIO_PORTA_CR_R=0xFF;

  }

  // Port B initialization as GPIO for LCD

  void PortB_Init(void){
	SET_BIT(SYSCTL_RCGCGPIO_R,1);
			while(READ_BIT(SYSCTL_PRGPIO_R,1)==0);
			GPIO_PORTB_LOCK_R =GPIO_LOCK_KEY;
			GPIO_PORTB_CR_R=0xFF;
		  GPIO_PORTB_AFSEL_R = 0x00;
			GPIO_PORTB_PCTL_R = 0x00;
			GPIO_PORTB_DEN_R = 0xFF;
			GPIO_PORTB_AMSEL_R = 0x00;

  }

  // Port D initialization as GPIO 

  void PortD_Init(void){
	SET_BIT(SYSCTL_RCGCGPIO_R,3);
			while(READ_BIT(SYSCTL_PRGPIO_R,3)==0);
			GPIO_PORTD_LOCK_R =GPIO_LOCK_KEY;
			GPIO_PORTD_CR_R=0xFF;
			GPIO_PORTD_AFSEL_R = 0x00;
			GPIO_PORTD_DEN_R = 0xFF;
			GPIO_PORTD_PCTL_R = 0x00;
			GPIO_PORTD_AMSEL_R = 0x00;
  }
   void PortE_Init(void){
	SET_BIT(SYSCTL_RCGCGPIO_R,4);
			while(READ_BIT(SYSCTL_PRGPIO_R,4)==0);
			GPIO_PORTE_LOCK_R =GPIO_LOCK_KEY;
		    GPIO_PORTE_AFSEL_R = 0x00;
			GPIO_PORTE_PCTL_R = 0x00;
			GPIO_PORTE_DEN_R = 0xFF;
			GPIO_PORTE_AMSEL_R = 0x00;
			GPIO_PORTE_CR_R=0xFF;
			// Set the direction of bits 1,2,3 as output and the rest remains zeros (inputs)
			SET_BIT(GPIO_PORTE_DIR_R,1);
			SET_BIT(GPIO_PORTE_DIR_R,2);
			SET_BIT(GPIO_PORTE_DIR_R,3);
		    // initialize pins 1-3 with zeros 
		CLR_BIT(GPIO_PORTE_DATA_R,1);
		CLR_BIT(GPIO_PORTE_DATA_R,2);
		CLR_BIT(GPIO_PORTE_DATA_R,3);
 }


  
  u8 Set_vPinValue(u8 Port_ID,u8 Pin_Number,u8 Pin_Value){ // a fn that writes a value on a specific pin
	u8 status=STD_TYPES_OK; // a variable to store the status of the function wether it's written the value or not
	if(((Port_ID>='A' && Port_ID<='F')||(Port_ID>='a' && Port_ID<='f'))&&((Pin_Number>=0)&&(Pin_Number<=7))&&((Pin_Value==0)||(Pin_Value==1)))
	{
		switch(Port_ID){
		case 'A':
		case 'a':
		{
			if(Pin_Value==0)
				CLR_BIT(GPIO_PORTA_DATA_R,Pin_Number);
			else
				SET_BIT(GPIO_PORTA_DATA_R,Pin_Number);
		}
		break;
		case 'B':
		case 'b':
		{
			if(Pin_Value==0)
				CLR_BIT(GPIO_PORTB_DATA_R,Pin_Number);
			else
				SET_BIT(GPIO_PORTB_DATA_R,Pin_Number);
		}
		break;
		case 'C':
		case 'c':
		{
			if(Pin_Value==0)
				CLR_BIT(GPIO_PORTC_DATA_R,Pin_Number);
			else
				SET_BIT(GPIO_PORTC_DATA_R,Pin_Number);
		}
		break;
		case 'D':
		case 'd':
		{
			if(Pin_Value==0)
				CLR_BIT(GPIO_PORTD_DATA_R,Pin_Number);
			else
				SET_BIT(GPIO_PORTD_DATA_R,Pin_Number);
		}
		break;
		case 'E':
		case 'e':
		{
			if((Pin_Number>=0)&&(Pin_Number<=5)){
			if(Pin_Value==0)
				CLR_BIT(GPIO_PORTE_DATA_R,Pin_Number);
			else
				SET_BIT(GPIO_PORTE_DATA_R,Pin_Number);
		}else{
			status=STD_TYPES_NOK;
		}
		}
		break;
		case 'F':
		case 'f':
		{
			if((Pin_Number>=0)&&(Pin_Number<=4)){
			if(Pin_Value==0)
				CLR_BIT(GPIO_PORTF_DATA_R,Pin_Number);
			else
				SET_BIT(GPIO_PORTF_DATA_R,Pin_Number);
		}else{
			status=STD_TYPES_NOK;
		}
		}
		break;
		default:
			status=STD_TYPES_NOK;
		}
	}
	else{
		status=STD_TYPES_NOK;
	}
	return status;
}
u8 Get_Port_Value(u8 Port_ID){ // a fn that reads the data of the port
	if((Port_ID>='A' && Port_ID<='F')||(Port_ID>='a' && Port_ID<='f'))
	{
		switch(Port_ID){
		case 'A':
		case 'a':
		{
			return GPIO_PORTA_DATA_R;
		}

		case 'B':
		case 'b':
		{
			return GPIO_PORTB_DATA_R;
		}
	
		case 'C':
		case 'c':
		{
			return GPIO_PORTC_DATA_R;
		}

		case 'D':
		case 'd':
		{
			return GPIO_PORTD_DATA_R;
		}
		
		case 'E':
		case 'e':
		{
		   return GPIO_PORTE_DATA_R;
		}
		
		case 'F':
		case 'f':
		{
			return GPIO_PORTF_DATA_R;
		}

		default:
			return 0;
		}
	}
	else{
		return 0;
	}}

	s8 Get_u8PinValue(u8 port_name,u8 pin_number, u8 pin_direction)
	{ // a fn that reads the data of a specific pin
		if(((port_name>='A' && port_name<='F')||(port_name>='a' && port_name<='f'))&&((pin_number>=0)&&(pin_number<=7))&&((pin_direction==0)||(pin_direction==1)))
	{	switch(port_name)
	{
		case 'A':
		case 'a':
		{
			return CLR_BIT(GPIO_PORTA_DATA_R,pin_number);
		}

		
		case 'B':
		case 'b':
		{
			return READ_BIT(GPIO_PORTB_DATA_R,pin_number);
		}

		
		case 'C':
		case 'c':
		{
			return READ_BIT(GPIO_PORTC_DATA_R,pin_number);
		}

		
		case 'D':
		case 'd':
		{
			return READ_BIT(GPIO_PORTD_DATA_R,pin_number);
		}

		
		case 'E':
		case 'e':
		{
			if((pin_number>=0)&&(pin_number<=5)){
			return READ_BIT(GPIO_PORTE_DATA_R,pin_number);
			}else{
				return -1;

			}
		}

		
		case 'F':
		case 'f':
		{
			if((pin_number>=0)&&(pin_number<=4)){
			return READ_BIT(GPIO_PORTF_DATA_R,pin_number);
			}else{
				return -1;
			}
		}

		default:
			return -1;
	}}else{
		return -1;
	}
	}	
	u8 Set_vPortValue(u8 port_name, u8 PortValue){ // a fn the writes data on the port
		u8 status=STD_TYPES_OK; // a variable to store the status of the function wether it's set the Port value or not
	if(((port_name>='A' && port_name<='F')||(port_name>='a' && port_name<='f'))&&((PortValue==0)||(PortValue==1)))
	{switch(port_name)
	{
		case 'A':
		case 'a':
		{
			GPIO_PORTA_DATA_R=PortValue;
			return status;
		}
		
		case 'B':
		case 'b':
		{
			GPIO_PORTB_DATA_R=PortValue;
				return status;
		}

		
		case 'C':
		case 'c':
		{
			GPIO_PORTC_DATA_R=PortValue;
				return status;
		}

		
		case 'D':
		case 'd':
		{
			GPIO_PORTD_DATA_R=PortValue;
				return status;
		}

		case 'E':
		case 'e':
		{
			GPIO_PORTE_DATA_R=PortValue;
				return status;
		}
		
		case 'F':
		case 'f':
		{
			GPIO_PORTF_DATA_R=PortValue;
				return status;
		}
		default:
		{	status=STD_TYPES_NOK;
			return status;
		}}
	}else{
		status=STD_TYPES_NOK;
		return status;
	}
}
	
	

/* u8 Init_Port(u8 Port_ID){  // a fn that initializes the port
	switch(Port_ID){
		u8 status= STD_TYPES_OK; 	// a variable to store the status of the function wether it's initialized the port or not
		if((Port_ID>='A' && Port_ID<='F')||(Port_ID>='a' && Port_ID<='f'))
		{
		case 'A':
		case 'a':
		{
			SET_BIT(SYSCTL_RCGCGPIO_R,0);
			while(READ_BIT(SYSCTL_PRGPIO_R,0)==0);
			GPIO_PORTA_LOCK_R =GPIO_LOCK_KEY;
		    GPIO_PORTA_AFSEL_R = 0x00;
			GPIO_PORTA_PCTL_R = 0x00;
			GPIO_PORTA_DEN_R = 0xFF;
			GPIO_PORTA_AMSEL_R = 0x00;
			GPIO_PORTA_CR_R=0xFF;

		}
		break;
		case 'B':
		case 'b':
		{
			SET_BIT(SYSCTL_RCGCGPIO_R,1);
			while(READ_BIT(SYSCTL_PRGPIO_R,1)==0);
			GPIO_PORTB_LOCK_R =GPIO_LOCK_KEY;
			GPIO_PORTB_CR_R=0xFF;
		    GPIO_PORTB_AFSEL_R = 0x00;
			GPIO_PORTB_PCTL_R = 0x00;
			GPIO_PORTB_DEN_R = 0xFF;
			GPIO_PORTB_AMSEL_R = 0x00;

		}
		break;
		case 'C':
		case 'c':
		{
			SET_BIT(SYSCTL_RCGCGPIO_R,2);
			while(READ_BIT(SYSCTL_PRGPIO_R,2)==0);
			GPIO_PORTC_LOCK_R =GPIO_LOCK_KEY;
			GPIO_PORTC_CR_R=0xFF;
			GPIO_PORTC_AFSEL_R = 0x00;
			GPIO_PORTC_DEN_R = 0xFF;
			GPIO_PORTC_PCTL_R = 0x00;
			GPIO_PORTC_AMSEL_R = 0x00;
		}
		break;
		case 'D':
		case 'd':
		{
			SET_BIT(SYSCTL_RCGCGPIO_R,3);
			while(READ_BIT(SYSCTL_PRGPIO_R,3)==0);
			GPIO_PORTD_LOCK_R =GPIO_LOCK_KEY;
			GPIO_PORTD_CR_R=0xFF;
			GPIO_PORTD_AFSEL_R = 0x00;
			GPIO_PORTD_DEN_R = 0xFF;
			GPIO_PORTD_PCTL_R = 0x00;
			GPIO_PORTD_AMSEL_R = 0x00;
		}
		break;
		case 'E':
		case 'e':
		{
			SET_BIT(SYSCTL_RCGCGPIO_R,4);
			while(READ_BIT(SYSCTL_PRGPIO_R,4)==0);
			GPIO_PORTE_LOCK_R =GPIO_LOCK_KEY;
			GPIO_PORTE_CR_R=0xFF;
			GPIO_PORTE_AFSEL_R = 0x00;
			GPIO_PORTE_DEN_R = 0xFF;
			GPIO_PORTE_PCTL_R = 0x00;
			GPIO_PORTE_AMSEL_R = 0x00;


		}
		break;
		case 'F':
		case 'f':
		{
			SET_BIT(SYSCTL_RCGCGPIO_R,5);
			while(READ_BIT(SYSCTL_PRGPIO_R,5)==0);
			GPIO_PORTF_LOCK_R =GPIO_LOCK_KEY;
			GPIO_PORTF_CR_R=0xFF;
			GPIO_PORTF_AFSEL_R = 0x00;
			GPIO_PORTF_DEN_R = 0xFF;
			GPIO_PORTF_PCTL_R = 0x00;
			GPIO_PORTF_AMSEL_R = 0x00;

		}
		break;
		default:
			status=STD_TYPES_NOK;
		 

		}
		else{
			status=STD_TYPES_NOK;
		}
		return status;
	}

}

u8 Write_PIN_value(u8 Port_ID,u8 Pin_Number,u8 Pin_Value){ // a fn that writes a value on a specific pin
	u8 status=STD_TYPES_OK; // a variable to store the status of the function wether it's written the value or not
	if(((Port_ID>='A' && Port_ID<='F')||(Port_ID>='a' && Port_ID<='f'))&&((Pin_Number>=0)&&(Pin_Number<=7))&&((Pin_Value==0)||(Pin_Value==1)))
	{
		switch(Port_ID){
		case 'A':
		case 'a':
		{
			if(Pin_Value==0)
				CLR_BIT(GPIO_PORTA_DATA_R,Pin_Number);
			else
				SET_BIT(GPIO_PORTA_DATA_R,Pin_Number);
		}
		break;
		case 'B':
		case 'b':
		{
			if(Pin_Value==0)
				CLR_BIT(GPIO_PORTB_DATA_R,Pin_Number);
			else
				SET_BIT(GPIO_PORTB_DATA_R,Pin_Number);
		}
		break;
		case 'C':
		case 'c':
		{
			if(Pin_Value==0)
				CLR_BIT(GPIO_PORTC_DATA_R,Pin_Number);
			else
				SET_BIT(GPIO_PORTC_DATA_R,Pin_Number);
		}
		break;
		case 'D':
		case 'd':
		{
			if(Pin_Value==0)
				CLR_BIT(GPIO_PORTD_DATA_R,Pin_Number);
			else
				SET_BIT(GPIO_PORTD_DATA_R,Pin_Number);
		}
		break;
		case 'E':
		case 'e':
		{
			if((Pin_Number>=0)&&(Pin_Number<=5)){
			if(Pin_Value==0)
				CLR_BIT(GPIO_PORTE_DATA_R,Pin_Number);
			else
				SET_BIT(GPIO_PORTE_DATA_R,Pin_Number);
		}else{
			status=STD_TYPES_NOK;
		}
		}
		break;
		case 'F':
		case 'f':
		{
			if((Pin_Number>=0)&&(Pin_Number<=4)){
			if(Pin_Value==0)
				CLR_BIT(GPIO_PORTF_DATA_R,Pin_Number);
			else
				SET_BIT(GPIO_PORTF_DATA_R,Pin_Number);
		}else{
			status=STD_TYPES_NOK;
		}
		}
		break;
		default:
			status=STD_TYPES_NOK;
		}
	}
	else{
		status=STD_TYPES_NOK;
	}
	return status;
}

u8 Set_Port_Direction(u8 Port_ID,u8 Port_Direction){ // a fn that sets the direction of the port
	u8 status=STD_TYPES_OK; // a variable to store the status of the function wether it's set the direction or not
	if(((Port_ID>='A' && Port_ID<='F')||(Port_ID>='a' && Port_ID<='f'))&&((Port_Direction==0)||(Port_Direction==1)))
	{
		switch(Port_ID){
		case 'A':
		case 'a':
		{
			if(Port_Direction==0)
				GPIO_PORTA_DIR_R=0x00;
			else
				GPIO_PORTA_DIR_R=0xFF;
		}
		break;
		case 'B':
		case 'b':
		{
			if(Port_Direction==0)
				GPIO_PORTB_DIR_R=0x00;
			else
				GPIO_PORTB_DIR_R=0xFF;
		}
		break;
		case 'C':
		case 'c':
		{
			if(Port_Direction==0)
				GPIO_PORTC_DIR_R=0x00;
			else
				GPIO_PORTC_DIR_R=0xFF;
		}
		break;
		case 'D':
		case 'd':
		{
			if(Port_Direction==0)
				GPIO_PORTD_DIR_R=0x00;
			else
				GPIO_PORTD_DIR_R=0xFF;
		}
		break;
		case 'E':
		case 'e':
		{
			if(Port_Direction==0)
				GPIO_PORTE_DIR_R=0x00;
			else
				GPIO_PORTE_DIR_R=0xFF;
		}
		break;
		case 'F':
		case 'f':
		{
			if(Port_Direction==0)
				GPIO_PORTF_DIR_R=0x00;
			else
				GPIO_PORTF_DIR_R=0xFF;
		}
		break;
		default:
			status=STD_TYPES_NOK;
		}
	}
	else{
		status=STD_TYPES_NOK;
	}
	return status;
}

u8 Get_Port_Value(u8 Port_ID){ // a fn that reads the data of the port
	if((Port_ID>='A' && Port_ID<='F')||(Port_ID>='a' && Port_ID<='f'))
	{
		switch(Port_ID){
		case 'A':
		case 'a':
		{
			return GPIO_PORTA_DATA_R;
		}
		break;
		case 'B':
		case 'b':
		{
			return GPIO_PORTB_DATA_R;
		}
		break;
		case 'C':
		case 'c':
		{
			return GPIO_PORTC_DATA_R;
		}
		break;
		case 'D':
		case 'd':
		{
			return GPIO_PORTD_DATA_R;
		}
		break;
		case 'E':
		case 'e':
		{
		   return GPIO_PORTE_DATA_R;
		}
		break;
		case 'F':
		case 'f':
		{
			return GPIO_PORTF_DATA_R;
		}
		break;
		default:
			return 0;
		}
	}
	else{
		return 0;
	}}

	


u8 Set_vPinDirection(u8 port_name,u8 pin_number, u8 pin_direction){ // a fn that specifiec whether the pin is input or output
u8 status=STD_TYPES_OK; // a variable to store the status of the function wether it's set the direction or not
	if(((port_name>='A' && port_name<='F')||(port_name>='a' && port_name<='f'))&&((pin_number>=0)&&(pin_number<=7))&&((pin_direction==0)||(pin_direction==1)))
	{switch(port_name)
	{
		case 'A':
		case 'a':
		{
			if(pin_direction==0) //input
				CLR_BIT(GPIO_PORTA_DIR_R,pin_number);
			else //output
				SET_BIT(GPIO_PORTA_DIR_R,pin_number);
		}
		break;
		
		case 'B':
		case 'b':
		{
			if(pin_direction==0) //input
				CLR_BIT(GPIO_PORTB_DIR_R,pin_number);
			else //output
				SET_BIT(GPIO_PORTB_DIR_R,pin_number);
		}
		break;
		
		case 'C':
		case 'c':
		{
			if(pin_direction==0) //input
				CLR_BIT(GPIO_PORTC_DIR_R,pin_number);
			else
				SET_BIT(GPIO_PORTC_DIR_R,pin_number);
		}
		break;
		
		case 'D':
		case 'd':
		{
			if(pin_direction==0) //input
				CLR_BIT(GPIO_PORTD_DIR_R,pin_number);
			else //output
				SET_BIT(GPIO_PORTD_DIR_R,pin_number);
		}
		break;
		
		case 'E':
		case 'e':
		
		{
			if((pin_number>=0)&&(pin_number<=5)){
			if(pin_direction==0) //input
				CLR_BIT(GPIO_PORTE_DIR_R,pin_number);
			else //output
				SET_BIT(GPIO_PORTE_DIR_R,pin_number);
				}else{
			status=STD_TYPES_NOK;
		}
		}
		break;
		
		case 'F':
		case 'f':
		{
				if((pin_number>=0)&&(pin_number<=4)){
			if(pin_direction==0) //input
				CLR_BIT(GPIO_PORTF_DIR_R,pin_number);
			else //output
				SET_BIT(GPIO_PORTF_DIR_R,pin_number);
				}else{
			status=STD_TYPES_NOK;
		}}
				break;
		default:
			status=STD_TYPES_NOK;
		}
	}
	else{
		status=STD_TYPES_NOK;
	}
	return status;
	}

	
	
	u8 Get_u8PinValue(u8 port_name,u8 pin_number, u8 pin_direction)
	{ // a fn that reads the data of a specific pin
		if(((port_name>='A' && port_name<='F')||(port_name>='a' && port_name<='f'))&&((pin_number>=0)&&(pin_number<=7))&&((pin_direction==0)||(pin_direction==1)))
	{	switch(port_name)
	{
		case 'A':
		case 'a':
		{
			return CLR_BIT(GPIO_PORTA_DATA_R,pin_number);
		}
		break;
		
		case 'B':
		case 'b':
		{
			return READ_BIT(GPIO_PORTB_DATA_R,pin_number);
		}
		break;
		
		case 'C':
		case 'c':
		{
			return READ_BIT(GPIO_PORTC_DATA_R,pin_number);
		}
		break;
		
		case 'D':
		case 'd':
		{
			return READ_BIT(GPIO_PORTD_DATA_R,pin_number);
		}
		break;
		
		case 'E':
		case 'e':
		{
			if((pin_number>=0)&&(pin_number<=5)){
			return READ_BIT(GPIO_PORTE_DATA_R,pin_number);
			}else{
				return -1;
			}
		}
		break;
		
		case 'F':
		case 'f':
		{
			if((pin_number>=0)&&(pin_number<=4)){
			return READ_BIT(GPIO_PORTF_DATA_R,pin_number);
			}else{
				return -1;
			}
		}
		break;
		default:
			return -1;
	}}else{
		return -1;
	}
	}	
	
	
	u8 Set_vPortValue(u8 port_name, u8 PortValue){ // a fn the writes data on the port
		u8 status=STD_TYPES_OK; // a variable to store the status of the function wether it's set the Port value or not
	if(((port_name>='A' && port_name<='F')||(port_name>='a' && port_name<='f'))&&((PortValue==0)||(PortValue==1)))
	{switch(port_name)
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
		break;
		default:
			status=STD_TYPES_NOK;
		}
	}else{
		status=STD_TYPES_NOK;
	}
	}	
	
	
	u8 Toggle_vPinValue(u8 port_name,u8 pin_number) { // a fn that flips the value of a specific pin
	u8 status=STD_TYPES_OK; // a variable to store the status of the function wether it's toggled the pin value or not
	if(((port_name>='A' && port_name<='F')||(port_name>='a' && port_name<='f'))&&((pin_number>=0)&&(pin_number<=7)))
{ 	switch(port_name)
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
		if((pin_number>=0)&&(pin_number<=5))
		{ 
			TOG_BIT(GPIO_PORTE_DATA_R,pin_number);
		} else{
			status=STD_TYPES_NOK;}
		break;
		
		case 'F':
		case 'f':
		if ((pin_number>=0)&&(pin_number<=4))
		
		{ 
			TOG_BIT(GPIO_PORTF_DATA_R,pin_number);
		}
		else{
			status=STD_TYPES_NOK;
		}
		break;
		default:
			status=STD_TYPES_NOK;
		}
	}else{
		status=STD_TYPES_NOK;
	}
	}	 */




	




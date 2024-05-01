#include "../../../Services/tm4c123gh6pm.h"
#include "../../../Services/Bit_Utilities.h"
#include "../../../Services/STD_TYPES.h"
#include "../../../Headers/MCAL/UART/UART.h"



void UART0_Init (void){
	SYSCTL_RCGCUART_R |= 0x0001; 	//activate UART0
	SYSCTL_RCGCGPIO_R |= 0x0001;  //activate portA clk
	while((SYSCTL_PRGPIO_R & 0x01) == 0);
	UART0_CTL_R &= ~0x0001;				//disable UART
	UART0_IBRD_R = 0x208;					//IBRD = int(80000000/(16*9600)) = int(520.8333)
	UART0_FBRD_R = 0x35;					//FBRD = int (0.833*64 + 0.5)
	UART0_LCRH_R = 0x070;					//8-bits Data + enable FIFO
	UART0_CTL_R = 0x0301;					//activate RXE, TXE & UART
	GPIO_PORTA_AFSEL_R |= pinUart0; 	//enable alternate function PA0 & PA1
	GPIO_PORTA_PCTL_R = (GPIO_PORTA_PCTL_R & 0xFFFFFF00) + 0x00000011;
	GPIO_PORTA_DEN_R |= pinUart0;			//enable digtal I/O 
	GPIO_PORTA_AMSEL_R &= ~pinUart0;	//disable analog I/O
}


void UART2_Init (void){
	SYSCTL_RCGCUART_R |= 0x0004; 	//activate UARTD
	SYSCTL_RCGCGPIO_R |= 0x0008;  //activate portD clk
	while((SYSCTL_PRGPIO_R & 0x08) == 0);
	UART0_CTL_R &= ~0x0001;				//disable UART
	UART0_IBRD_R = 0x208;					//IBRD = int(80000000/(16*9600)) = int(520.8333)
	UART0_FBRD_R = 0x35;					//FBRD = int (0.833*64 + 0.5)
	UART0_LCRH_R = 0x070;					//8-bits Data + enable FIFO
	UART0_CTL_R = 0x0301;					//activate RXE, TXE & UART
	GPIO_PORTD_AFSEL_R |= pinUart2; 	//enable alternate function PD6 & PD7
	GPIO_PORTD_PCTL_R = (GPIO_PORTD_PCTL_R & 0x00FFFFFF) + 0x11000000;
	GPIO_PORTD_DEN_R |= pinUart2;			//enable digtal I/O 
	GPIO_PORTD_AMSEL_R &= ~pinUart2;	//disable analog I/O
}


void UART0_SendChar (u8 data){
		while ((UART0_FR_R & 0x20));
	UART0_DR_R = data;
}

void UART0_SendString (u8 *pt){
		while (*pt){
			UART0_SendChar(*pt);
			pt++;
		}
}

u8 UART0_Recievechar (){
		while ((UART0_FR_R & 0x10));
	return (char)UART0_DR_R;
}

void UART0_RecieveString (u8 *command, u32 length){
	char chararacter;
	int i;
	for(i =0;i<length;i++){
	  	chararacter = UART0_Recievechar();
			if(chararacter != END)
			{
				command[i] = chararacter;
				UART0_SendChar(command[i]);
			}
			else if (chararacter == END || i == length) break;
	}
}



void UART2_SendChar (u8 data){
		while ((UART2_FR_R & 0x20));
	UART2_DR_R = data;
}

void UART2_SendString (u8 *pt){
		while (*pt){
			UART2_SendChar(*pt);
			pt++;
		}
}

u8 UART2_Recievechar (){
		while ((UART2_FR_R & 0x10));
	return (char)UART2_DR_R;
}

void UART2_RecieveString (u8 *command, u32 length){
	char chararacter;
	int i;
	for(i =0;i<length;i++){
	  	chararacter = UART2_Recievechar();
			if(chararacter != END)
			{
				command[i] = chararacter;
				UART2_SendChar(command[i]);
			}
			else if (chararacter == END || i == length) break;
	}
}



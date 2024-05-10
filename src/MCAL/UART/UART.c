#include "../../../Services/tm4c123gh6pm.h"
#include "../../../Services/Bit_Utilities.h"
#include "../../../Services/STD_TYPES.h"
#include "../../../Headers/MCAL/UART/UART.h"
#include <string.h>
#include <stdint.h>


void UART0_Init (void){
	SYSCTL_RCGCUART_R |= 0x0001; 	//activate UART0
	SYSCTL_RCGCGPIO_R |= 0x0001;  //activate portA clk
	while((SYSCTL_PRGPIO_R & 0x01) == 0);
	UART0_CTL_R &= ~0x0001;				//disable UART
	UART0_IBRD_R = 0x68;					//IBRD = int(16000000/(16*9600)) = int(104.16667)
	UART0_FBRD_R = 0xB;					  //FBRD = int (0.16667*64 + 0.5)
	UART0_LCRH_R = 0x070;					//8-bits Data + enable FIFO
	UART0_CTL_R = 0x0301;					//activate RXE, TXE & UART
	GPIO_PORTA_AFSEL_R |= pinUart0; 	//enable alternate function PA0 & PA1
	GPIO_PORTA_PCTL_R = (GPIO_PORTA_PCTL_R & 0xFFFFFF00) + 0x00000011;
	GPIO_PORTA_DEN_R |= pinUart0;			//enable digtal I/O 
	GPIO_PORTA_AMSEL_R &= ~pinUart0;	//disable analog I/O
}


void UART5_Init (void){
	SYSCTL_RCGCUART_R |= 0x0020; 	//activate UARTD
	SYSCTL_RCGCGPIO_R |= 0x0010;  //activate portE clk
	while((SYSCTL_PRGPIO_R & 0x0010) == 0);
	UART5_CTL_R &= ~0x0001;				//disable UART
	UART5_IBRD_R = 0x68;					//IBRD = int(16000000/(16*9600)) = int(104.16667)
	UART5_FBRD_R = 0xB;					  //FBRD = int (0.16667*64 + 0.5)
	UART5_LCRH_R = 0x070;					//8-bits Data + enable FIFO
	UART5_CTL_R = 0x0301;					//activate RXE, TXE & UART
	GPIO_PORTE_AFSEL_R |= pinUart5; 	//enable alternate function PD4 & PD5
	GPIO_PORTE_PCTL_R = (GPIO_PORTD_PCTL_R & 0xFF00FFFF) + 0x00110000;
	GPIO_PORTE_DEN_R |= pinUart5;			//enable digtal I/O 
	GPIO_PORTE_AMSEL_R &= ~pinUart5;	//disable analog I/O
}


void UART0_SendChar (char data){
		while ((UART0_FR_R & 0x20));
	UART0_DR_R = data;
}

void UART0_SendString (char *pt){
		while (*pt){
			UART0_SendChar(*pt);
			pt++;
		}
}

char UART0_Recievechar (){
		while ((UART0_FR_R & 0x10));
	return (char)UART0_DR_R;
}

void UART0_RecieveString (char *command, u32 length){
	char chararacter;
	int i;
	for(i =0;i<length;i++){
	  	chararacter = UART0_Recievechar();
			if(chararacter != CR)
			{
				command[i] = chararacter;
				UART0_SendChar(command[i]);
			}
			else if (chararacter == CR || i == length) break;
	}
}



void UART5_SendChar (char data){
		while ((UART5_FR_R & 0x20));
	UART5_DR_R = data;
}

void UART5_SendString (char *pt){
		while (*pt){
			UART5_SendChar(*pt);
			pt++;
		}
}

char UART5_Recievechar (){
		while ((UART5_FR_R & 0x10));
	return (char)UART5_DR_R;
}

void UART5_RecieveString (char *command, u32 length){
	char chararacter;
	int i;
	for(i =0;i<length;i++){
	  	chararacter = UART5_Recievechar();
			if(chararacter != END)
			{
				command[i] = chararacter;
				UART5_SendChar(command[i]);
			}
			else if (chararacter == END || i == length) break;
	}
}



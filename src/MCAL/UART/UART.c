#include "../../../Services/tm4c123gh6pm.h"
#include "../../../Services/Bit_Utilities.h"
#include "../../../Services/STD_TYPES.h"
#include "../../../Headers/MCAL/UART/UART.h"
#include <string.h>
#include <stdint.h>


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


void UART5_Init (void){
	SYSCTL_RCGCUART_R |= 0x0020; 	//activate UARTE
	SYSCTL_RCGCGPIO_R |= 0x0010;  //activate portE clk
	while((SYSCTL_PRGPIO_R & 0x0010) == 0);
	UART5_CTL_R &= ~0x0001;				//disable UART
	UART5_IBRD_R = 0x68;					//IBRD = int(16000000/(16*9600)) = int(104.16667)
	UART5_FBRD_R = 0xB;					  //FBRD = int (0.16667*64 + 0.5)
	UART5_LCRH_R = 0x070;					//8-bits Data + enable FIFO
	UART5_CTL_R = 0x0301;					//activate RXE, TXE & UART
	GPIO_PORTE_AFSEL_R |= pinUart5; 	//enable alternate function PE4 & PE5
	GPIO_PORTE_PCTL_R = (GPIO_PORTD_PCTL_R & 0xFF00FFFF) + 0x00110000;
	GPIO_PORTE_DEN_R |= pinUart5;			//enable digtal I/O 
	GPIO_PORTE_AMSEL_R &= ~pinUart5;	//disable analog I/O
}


void UART2_SendChar (char data){
		while ((UART2_FR_R & 0x20));
	UART2_DR_R = data;
}

void UART2_SendString (char *pt){
		while (*pt){
			UART2_SendChar(*pt);
			pt++;
		}
}

char UART2_Recievechar (){
		while ((UART2_FR_R & 0x10));
	return (char)UART2_DR_R;
}

void UART2_RecieveString (char *command, u32 length){
	char chararacter;
	int i;
	for(i =0;i<length;i++){
	  	chararacter = UART2_Recievechar();
			if(chararacter != CR)
			{
				command[i] = chararacter;
				UART2_SendChar(command[i]);
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



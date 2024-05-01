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
	GPIO_PORTA_AFSEL_R |= 0x03; 	//enable alternate function PA0 & PA1
	GPIO_PORTA_PCTL_R = (GPIO_PORTA_PCTL_R & 0xFFFFFF00) + 0x00000011;
	GPIO_PORTA_DEN_R |= 0x03;			//enable digtal I/O 
	GPIO_PORTA_AMSEL_R &= ~0x03;	//disable analog I/O
}

void UART_SendChar (u8 data){
		while ((UART0_FR_R & 0x20));
	UART0_DR_R = data;
}

void UART_SendString (u8 *pt){
		while (*pt){
			UART_SendChar(*pt);
			pt++;
		}
}

u8 UART_Recievechar (){
		while ((UART0_FR_R & 0x10));
	return (char)UART0_DR_R;
}

void UART_RecieveString (u8 *command, u32 length){
	char chararacter;
	int i;
	for(i =0;i<length;i++){
	  	chararacter = UART_Recievechar();
			if(chararacter != END)
			{
				command[i] = chararacter;
				UART_SendChar(command[i]);
			}
			else if (chararacter == END || i == length) break;
	}
}

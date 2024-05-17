#include "../../../Services/tm4c123gh6pm.h"
#include "../../../Services/Bit_Utilities.h"
#include "../../../Services/STD_TYPES.h"
#include "../../../Headers/MCAL/UART/UART.h"
#include <string.h>
#include <stdint.h>
/*
void UART0_Init (void){
	SYSCTL_RCGCUART_R |= 0x0001; 	//activate UART0
	SYSCTL_RCGCGPIO_R |= 0x0001;  //activate portA clk
	while((SYSCTL_PRGPIO_R & 0x01) == 0);
	UART0_CTL_R &= ~0x0001;				//disable UART
	UART0_IBRD_R = 104;
	UART0_FBRD_R = 11;
	UART0_LCRH_R = 0x070;					//8-bits Data + enable FIFO
	UART0_CTL_R = 0x0301;					//activate RXE, TXE & UART
	GPIO_PORTA_AFSEL_R |= 0x03; 	//enable alternate function PA0 & PA1
	GPIO_PORTA_PCTL_R = (GPIO_PORTA_PCTL_R & 0xFFFFFF00) + 0x00000011;
	GPIO_PORTA_DEN_R |= 0x03;			//enable digtal I/O 
	GPIO_PORTA_AMSEL_R &= ~0x03;	//disable analog I/O
}

void UART2_Init (void){
	SYSCTL_RCGCUART_R |= 0x0004; 	//activate UARTD
	SYSCTL_RCGCGPIO_R |= 0x0008;  //activate portD clk
	while((SYSCTL_PRGPIO_R & 0x08) == 0);
	UART2_CTL_R &= ~0x0001;				//disable UART
	UART2_IBRD_R = 104;					//IBRD = int(16000000/(16*9600)) = int(104.667)
	UART2_FBRD_R = 11;					//FBRD = int (0.667*64 + 0.5)
	UART2_CC_R =0;
	UART2_LCRH_R = 0x070;					//8-bits Data + enable FIFO
	UART2_CTL_R = 0x0301;					//activate RXE, TXE & UART
	GPIO_PORTD_AFSEL_R |= pinUart2; 	//enable alternate function PD6 & PD7
	GPIO_PORTD_PCTL_R = (GPIO_PORTD_PCTL_R & 0x00FFFFFF) + 0x11000000;
	GPIO_PORTD_DEN_R |= pinUart2;			//enable digtal I/O 
	GPIO_PORTD_AMSEL_R &= ~pinUart2;	//disable analog I/O
}*/

void UART0_Init(){
 SYSCTL_RCGCUART_R |= SYSCTL_RCGCUART_R0;
 SYSCTL_RCGCGPIO_R |= SYSCTL_RCGCGPIO_R0;

UART0_CTL_R &= ~ UART_CTL_UARTEN;
UART0_IBRD_R = 104;  
UART0_FBRD_R = 11;
UART0_LCRH_R |= (UART_LCRH_WLEN_8 | UART_LCRH_FEN)  ;
UART0_CTL_R = (UART_CTL_RXE | UART_CTL_TXE | UART_CTL_UARTEN);
  
GPIO_PORTA_AFSEL_R |= 0x03;
GPIO_PORTA_PCTL_R = (GPIO_PORTA_PCTL_R &= ~0xFF)|(GPIO_PCTL_PA1_U0TX|GPIO_PCTL_PA0_U0RX);
GPIO_PORTA_DEN_R |= 0x03;
GPIO_PORTA_AMSEL_R &= ~0x03;  
}


void UART2_Init(){ // for gps
	  unsigned BRD;
	
	  SYSCTL_RCGCUART_R |= 0X04; // activate UART2
	  SYSCTL_RCGCGPIO_R |= 0X08; //  activate port D
	///////////////////// NO PRGPIO
	  UART2_CTL_R &= ~(0X0001);   // disable UART
	  UART2_IBRD_R = 104;  
		UART2_FBRD_R = 11;
	
	  GPIO_PORTD_LOCK_R = GPIO_LOCK_KEY;  // Unlock port D
    GPIO_PORTD_CR_R |= 0xC0;  // Allow changes to PD7-PD6
	  GPIO_PORTD_AFSEL_R |= 0XC0; // enable alt function PD7, PD6
	  GPIO_PORTD_PCTL_R = (GPIO_PORTD_PCTL_R & 0X00FFFFFF) | 0X11000000; // configure uart for pa0,pa1
	  
	  UART2_CC_R = 0; 	   // use system clock
	  UART2_LCRH_R = 0x60; // 8-bit word length, no Fifo , no parity, 1 stop bit ////////////////
	  UART2_CTL_R = 0X0301;  // enable RXE,TXE AND UART
	
	  GPIO_PORTD_DEN_R |= 0XC0;  // enable digital IO on PD6,PD7
	  GPIO_PORTD_AMSEL_R &= ~0XC0; // disable analog function on PD6, PD7
		
		delay_m(1);
		 
}


void UART5_Init (void){
	SYSCTL_RCGCUART_R |= 0x0020; 	//activate UARTE
	SYSCTL_RCGCGPIO_R |= 0x0010;  //activate portE clk
	while((SYSCTL_PRGPIO_R & 0x0010) == 0);
	UART5_CTL_R &= ~0x0001;				//disable UART
	UART5_IBRD_R = 104;					//IBRD = int(16000000/(16*9600)) = int(104.16667)
	UART5_FBRD_R = 11;					  //FBRD = int (0.16667*64 + 0.5)
	UART5_LCRH_R = 0x070;					//8-bits Data + enable FIFO
	UART5_CTL_R = 0x0301;					//activate RXE, TXE & UART
	GPIO_PORTE_AFSEL_R |= pinUart5; 	//enable alternate function PE4 & PE5
	GPIO_PORTE_PCTL_R = (GPIO_PORTE_PCTL_R & 0xFF00FFFF) + 0x00110000;
	GPIO_PORTE_DEN_R |= pinUart5;			//enable digtal I/O 
	GPIO_PORTE_AMSEL_R &= ~pinUart5;	//disable analog I/O
}


void UART0_SendChar (char data){
		while((UART0_FR_R & UART_FR_TXFF)==UART_FR_TXFF){};
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
			if(chararacter!=CR)
			{
				command[i] = chararacter;
				UART0_SendChar(command[i]);
			}
			else if (chararacter == CR || i == length) break;
	}
}

void UART2_SendChar (uint8_t data){
		while ((UART2_FR_R & 0x20)!=0);
		UART2_DR_R = data;
}

void UART2_SendString (char *pt){
		while (*pt){
			UART2_SendChar(*pt);
			pt++;
		}
}


uint8_t UART2_Receivechar(void)
{
	uint8_t c;
	
	while((UART2_FR_R & 0x10) != 0);  
	c = UART2_DR_R; 
	
	return c; 
}


void UART2_RecieveString (char *command, u32 length){
	char chararacter;
	int i;
	for(i =0;i<length;i++){
	  	chararacter = UART2_Receivechar();
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
		while ((UART5_FR_R & 0x10)!=0);
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


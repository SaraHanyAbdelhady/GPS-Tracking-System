/**************************** SYSTEM ****************************/
#include <stdio.h>
#include <string.h>
#include <Stdlib.h>
#include <math.h>
/***************************** LIB *****************************/
#include "../../../Services/STD_TYPES.h"
#include "../../../Services/BIT_UTILITIES.h"

/***************************** MCAL *****************************/
#include "../../../Headers/MCAL/UART/UART.h"
#include "../../../Headers/MCAL/SYSTICK/Systick.h"
/***************************** HAL *****************************/
#include "../../../Headers/HAL/GPS/GPS.h"
#include "../../../Headers/HAL/LED/LED.h"
/********************** GLOBAL VARIABLES **********************/
extern u8 GPS_u8SpeedArr[5];




int flag = 0;
u8 Local_u8ReceivedChar;
char GPS[300];
char header[] = "$GPRMC,";
int i;
unsigned long int check;


void GPS_Read()
{
	

	char i=0;
	short unsigned int counter=0;

	//wait till $GPRMC message
	
		LED_On(LED_BLUE);
	
		
		
	//extract GPRMC message content
	do{	
			GPS[counter]=UART2_Receivechar();
			UART0_SendChar(GPS[counter]);
			counter++;;
	  }while(GPS[counter-1]!= '*');
		LED_On(LED_GREEN);
}


	

void GPS_voidReceiveSentence(f32* Copy_f32Latitude, f32 *Copy_f32Longitude, u8 *Copy_u8Speed)
{
	//static u8 Local_u8UART_InitFlag = 0;
	//u8 Local_u8ReadCounter = 0;
	u8 Local_u8GPS_Sentence[100];

	/*if(Local_u8UART_InitFlag == 0)
	{
		UART5_Init();
		Local_u8UART_InitFlag++;
	}*/
	do 
	{
		GPS[i] = UART2_Receivechar();
		if(GPS[i]== header[check])
		{
			check++;
		}
		else 
			check = 0;
		i++;
		/*a[0] = UART2_Recievechar();
		delay_m(1);
		a[1] = UART2_Recievechar();
		delay_m(1);
		a[2] = UART2_Recievechar();
		delay_m(1);
		a[3] = UART2_Recievechar();
		delay_m(1);
		a[4] = UART2_Recievechar();
		delay_m(1);
		a[5] = UART2_Recievechar();
		delay_m(1);
		if(strcmp(a,Local_u8GPS_Check) == 0)
			flag = 1;
		
		//Local_u8ReceivedChar = UART5_Recievechar ();
		//sprintf(a,"%c",Local_u8ReceivedChar);
		
		//UART_OutChar(Local_u8ReceivedChar);
		if(Local_u8ReceivedChar == Local_u8GPS_Check[0])
		{
			Local_u8ReceivedChar = UART5_Recievechar ();
			if(Local_u8ReceivedChar == Local_u8GPS_Check[1])
			{
				Local_u8ReceivedChar = UART5_Recievechar ();
				if(Local_u8ReceivedChar == Local_u8GPS_Check[2])
				{
					Local_u8ReceivedChar = UART5_Recievechar ();
					if(Local_u8ReceivedChar == Local_u8GPS_Check[3])
					{
						Local_u8ReceivedChar = UART5_Recievechar ();
						if(Local_u8ReceivedChar == Local_u8GPS_Check[4])
						{
							Local_u8ReceivedChar = UART5_Recievechar ();
							if(Local_u8ReceivedChar == Local_u8GPS_Check[5])
							{
								Local_u8ReceivedChar = UART5_Recievechar ();
								if(Local_u8ReceivedChar == Local_u8GPS_Check[6])
								{
									Local_u8ReceivedChar = UART5_Recievechar ();
									while(Local_u8ReceivedChar != '*')
									{
										Local_u8GPS_Sentence[Local_u8ReadCounter] = Local_u8ReceivedChar;
										Local_u8ReceivedChar = UART5_Recievechar ();
										Local_u8ReadCounter++;
									}
									GPS_voidExtractCoordinates(Local_u8GPS_Sentence,Copy_f32Latitude,Copy_f32Longitude,Copy_u8Speed);
								}
							}
						}
					}
				}
			}
		}*/
	}while (check!=7);
}


void GPS_voidExtractCoordinates(u8 *Copy_pu8sentence,f32 *Copy_f32Latitude,f32 *Copy_f32Longitude,u8 *Copy_u8Speed)
{
	f32 Deg,Min,Sec;
	char latitudeARR[15]={0};
	char longARR[15]={0};
	char SpeedARR[10];
	u8 j=0;
	u8 k=0;
	u8 l=0;
	u8 i=0;
	u8 Local_u8_CommaCount =0;
	while (Local_u8_CommaCount<7)
	{
		if (Copy_pu8sentence[i]==',')
		{
			Local_u8_CommaCount++;
			i++;
		}
		if (Local_u8_CommaCount==1)
		{
			if (Copy_pu8sentence[i]!='A')
			{
				GPS_voidReceiveSentence(Copy_f32Latitude, Copy_f32Longitude,Copy_u8Speed);
			}
		}
	    if (Local_u8_CommaCount==2)
		{
           latitudeARR[j++]=Copy_pu8sentence[i];
		}
	    if (Local_u8_CommaCount==4)
		{
           longARR[k++]=Copy_pu8sentence[i];
		}
		if (Local_u8_CommaCount==6)
		{
           SpeedARR[l++]=Copy_pu8sentence[i];
		}
		i++;
	}
	*Copy_f32Latitude=atof(latitudeARR);
	Deg=*Copy_f32Latitude/100;
	Min=*Copy_f32Latitude-(f32)(Deg*100);
	Sec=Min/60.0;
	*Copy_f32Latitude= Deg+Sec;


	*Copy_f32Longitude=atof(longARR);
	Deg=*Copy_f32Longitude/100;
	Min=*Copy_f32Longitude-(f32)(Deg*100);
	Sec=Min/60.0;
	*Copy_f32Longitude= Deg+Sec;
	//int i;
	for ( i =0;i<4;i++)
	{
		GPS_u8SpeedArr[i]=SpeedARR[i];
	}
    SpeedARR[i]='\0';
	*Copy_u8Speed=atof(SpeedARR);
}




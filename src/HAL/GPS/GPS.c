/**************************** SYSTEM ****************************/
#include <stdio.h>
#include <string.h>
#include <Stdlib.h>

/***************************** LIB *****************************/
#include "../../../Services/STD_TYPES.h"
#include "../../../Services/BIT_UTILITIES.h"

/***************************** MCAL *****************************/
#include "../../../Headers/MCAL/UART/UART.h"

/***************************** HAL *****************************/
#include "../../../Headers/HAL/GPS/GPS.h"

/********************** GLOBAL VARIABLES **********************/
extern char GPS_u8SpeedArr[5];


void GPS_voidReceiveSentence(f64* Copy_f64Latitude, f64 *Copy_f64Longitude, u8 *Copy_u8Speed)
{
	static u8 Local_u8UART_InitFlag = 0;
	u8 Local_u8ReadCounter = 0;
	u8 Local_u8GPS_Sentence[100];
	u8 Local_u8GPS_Check[] = "$GNRMC,";
	u8 Local_u8ReceivedChar;
	if(Local_u8UART_InitFlag == 0)
	{
		UART_voidInit(UART2, UART_BDR_9600, UART_DATA_8, UART_PARITY_NONE, UART_STOP_BIT_1);
		Local_u8UART_InitFlag++;
	}
	do 
	{
		UART_voidReceiveByte(UART2,&Local_u8ReceivedChar);
		if(Local_u8ReceivedChar == Local_u8GPS_Check[0])
		{
			UART_voidReceiveByte(UART2,&Local_u8ReceivedChar);
			if(Local_u8ReceivedChar == Local_u8GPS_Check[1])
			{
				UART_voidReceiveByte(UART2,&Local_u8ReceivedChar);
				if(Local_u8ReceivedChar == Local_u8GPS_Check[2])
				{
					UART_voidReceiveByte(UART2,&Local_u8ReceivedChar);
					if(Local_u8ReceivedChar == Local_u8GPS_Check[3])
					{
						UART_voidReceiveByte(UART2,&Local_u8ReceivedChar);
						if(Local_u8ReceivedChar == Local_u8GPS_Check[4])
						{
							UART_voidReceiveByte(UART2,&Local_u8ReceivedChar);
							if(Local_u8ReceivedChar == Local_u8GPS_Check[5])
							{
								UART_voidReceiveByte(UART2,&Local_u8ReceivedChar);
								if(Local_u8ReceivedChar == Local_u8GPS_Check[6])
								{
									UART_voidReceiveByte(UART2,&Local_u8ReceivedChar);
									while(Local_u8ReceivedChar != '*')
									{
										Local_u8GPS_Sentence[Local_u8ReadCounter] = Local_u8ReceivedChar;
										Local_u8ReadCounter++;
									}
									GPS_voidExtractCoordinates(Local_u8GPS_Sentence,Copy_f64Latitude,Copy_f64Longitude);
								}
							}
						}
					}
				}
			}
		}
	} while (Local_u8ReadCounter == 0);
}
void GPS_voidExtractCoordinates(u8 *Copy_pu8Sentence,f64 *Copy_f64Latitude,f64 *Copy_f64Longitude, u8 *Copy_u8Speed){
	f32 Local_f32Deg,Local_f32Min, Local_f32Sec;
	u8 Local_u8CommaCount =0;
	u8 j=0;
	u8 k =0;
	u8 l=0;
	char longARR[15]={0};
	char altitudeARR[15]={0};
	u8 i=0;
	char speedArr[10];
	while (Local_u8CommaCount <7)
	{
		if (Copy_pu8Sentence[i]==',')
		{
			Local_u8CommaCount++;
			i++;
		}
		if (Local_u8CommaCount==1)
		{
			if (Copy_pu8Sentence[i]!='A')
			{
				GPS_voidReceiveSentence(Copy_f64Latitude,Copy_f64Longitude,Copy_u8Speed);
			}
		}
		if(Local_u8CommaCount==2)
		{
			altitudeARR[j++]=Copy_pu8Sentence[i];
		}
		if(Local_u8CommaCount==4)
		{
			longARR[k++]=Copy_pu8Sentence[i];
		}
		if(Local_u8CommaCount==6)
		{
			speedArr[l++]=Copy_pu8Sentence[i];
		}
		i++;
	}
	*Copy_f64Latitude=atof(altitudeARR);
	Local_f32Deg=*Copy_f64Latitude/100;
	Local_f32Min=*Copy_f64Latitude-(f32)(Local_f32Deg*100);
	Local_f32Sec=Local_f32Min/60.0;
	*Copy_f64Latitude=Local_f32Deg + Local_f32Sec;


	*Copy_f64Longitude=atof(longARR);
	Local_f32Deg=*Copy_f64Longitude/100;
	Local_f32Min=*Copy_f64Longitude-(f32)(Local_f32Deg*100);
	Local_f32Sec=Local_f32Min/60.0;
	*Copy_f64Longitude=Local_f32Deg + Local_f32Sec;

	for(int i =0;i<4;i++)
	{
		GPS_u8SpeedArr[i]=speedArr[i];
	}
    speedArr[i]='\0';
	*Copy_u8Speed=atof(speedArr);
}



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



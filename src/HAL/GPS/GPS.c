/**************************** SYSTEM ****************************/
#include <stdio.h>
#include <string.h>
#include <Stdlib.h>
#include <math.h>
/***************************** LIB *****************************/
#include "../../../Services/STD_TYPES.h"
#include "../../../Services/BIT_UTILITIES.h"
#include "../../../Services/tm4c123gh6pm.h"
/***************************** MCAL *****************************/
#include "../../../Headers/MCAL/UART/UART.h"
#include "../../../Headers/MCAL/SYSTICK/Systick.h"
/***************************** HAL *****************************/
#include "../../../Headers/HAL/GPS/GPS.h"
#include "../../../Headers/HAL/LED/LED.h"
/********************** GLOBAL VARIABLES **********************/




char GPS_logname[] = "$GPRMC";
char GPS[80];
char GPS_formated[12][20];
char* token;
float currentLat;
float currentLong;
/////////////////////////////////////////////////////////////////////////////////////////////////////
float allLats[200];
int latscount=0;
float allLongs[200];
int longscount=0;


// extract $GPRMC message content
void GPS_read(void) {
    char i = 0;
    char counter = 0;

    // wait till $GPRMC message
    do {
        while (UART2_Recievechar() != GPS_logname[i]) {
            i = 0;
        }
        i++;
    } while (i != 6);

    // extract GPRMC message content
    do {
        GPS[counter] = UART2_Recievechar();
        counter++;
    } while (GPS[counter - 1] != '*');
}

// extract Latitude  and Longitude of the $GPRMC message
void GPS_format(void) {
    char noofStrings = 0;
    token = strtok(GPS, ",");

    do {
        strcpy(GPS_formated[noofStrings], token);
        token = strtok(NULL, ",");
        noofStrings++;
    } while (token != NULL);

    if (strcmp(GPS_formated[1], "A") == 0) {
        if (strcmp(GPS_formated[3], "N") == 0){
            currentLat = atof(GPS_formated[2]);
				    allLats[latscount++]= currentLat;}
        else{
            currentLat = -(atof(GPS_formated[2]));
				    allLats[latscount++]= currentLat;}

        if (strcmp(GPS_formated[5], "E") == 0){
            currentLong = atof(GPS_formated[4]);
					  allLongs[longscount++]= currentLong;
				}
        else{
            currentLong = -(atof(GPS_formated[4]));
					  allLongs[longscount++]= currentLong;
				}
    }
}

/************* PREVIOUS APPROACH *************/
/*

int flag = 0;
u8 Received_Char, Counter;
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
	u8 Local_u8GPS_Sentence[100];
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

		if(Received_Char == header[0])
		{
			Received_Char = UART5_Recievechar ();
			if(Received_Char == header[1])
			{
				Received_Char = UART5_Recievechar ();
				if(Received_Char == header[2])
				{
					Received_Char = UART5_Recievechar ();
					if(Received_Char == header[3])
					{
						Received_Char = UART5_Recievechar ();
						if(Received_Char == header[4])
						{
							Received_Char = UART5_Recievechar ();
							if(Received_Char == header[5])
							{
								Received_Char = UART5_Recievechar ();
								if(Received_Char == header[6])
								{
									Received_Char = UART5_Recievechar ();
									while(Received_Char != '*')
									{
										Local_u8GPS_Sentence[Counter] = Received_Char;
										Received_Char = UART5_Recievechar ();
										Counter++;
									}
									GPS_voidExtractCoordinates(Local_u8GPS_Sentence,Copy_f32Latitude,Copy_f32Longitude,Copy_u8Speed);
								}
							}
						}
					}
				}
			}
		}
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




*******************************************/


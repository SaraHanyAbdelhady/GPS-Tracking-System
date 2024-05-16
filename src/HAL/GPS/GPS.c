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

// extract $GPRMC message content
void GPS_read(void) {
    char i = 0;
    char counter = 0;

    // wait till $GPRMC message
    do {
        while (UART2_Receivechar() != GPS_logname[i]) {
            i = 0;
        }
        i++;
    } while (i != 6);

    // extract GPRMC message content
    do {
        GPS[counter] = UART2_Receivechar();
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
        if (strcmp(GPS_formated[3], "N") == 0)
            currentLat = atof(GPS_formated[2]);
        else
            currentLat = -(atof(GPS_formated[2]));

        if (strcmp(GPS_formated[5], "E") == 0)
            currentLong = atof(GPS_formated[4]);
        else
            currentLong = -(atof(GPS_formated[4]));
    }
}




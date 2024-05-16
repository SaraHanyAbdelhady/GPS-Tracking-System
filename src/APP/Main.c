#include "../../Services/tm4c123gh6pm.h"
#include "../../Services/Bit_Utilities.h"
#include "../../Services/STD_TYPES.h"
#include "../../Headers/MCAL/UART/UART.h"
#include "../../Headers/MCAL/GPIO/GPIO.h"
#include "../../Headers/HAL/GPS/GPS.h"
#include "../../Headers/HAL/LED/LED.h"
#include "../../Headers/HAL/Push button/Push button.h"
#include "../../Headers/APP/APP.h"
#include "../../Services/STD_TYPES.h"
#include "../../Headers/HAL/LCD/LCD.h"
#include "../../Headers/MCAL/SYSTICK/Systick.h"
#include "../../Headers/MCAL/EEPROM/EEPROM.h"
#include <string.h>
#include <stdint.h>

#include <math.h>
#include <stdlib.h>
#include <string.h>




#define RADIUS 6371000  // radius of earth in meters

double tot_distance = 0;

// points coordinates
double lat1 = 0;
double long1 = 0;
extern float currentLat;
extern float currentLong;


double to_degree(float raw_degree);
double to_radians(double degrees);
double distance(double lat1, double lon1, double lat2, double lon2);
double approximate(double a, float d);



	int main(void) {
    SYSTICKTIMER_init();
    PortF_Init();
   UART2_Init();
	 UART5_Init();
		LEDInit();
   LED_On(LED_RED);
    delay_m(3000);
    
    delay_m(1000 * 20);
   LED_Off(LED_RED);
	 LED_Off(LED_BLUE);
	 LED_Off(LED_GREEN);
    delay_m(3000);
    LED_Off(LED_RED);
	 LED_Off(LED_BLUE);
	 LED_Off(LED_GREEN);
 LED_On(LED_RED);

    // get start point
    GPS_read();
    GPS_format();
    lat1 = to_degree(currentLat);
    long1 = to_degree(currentLong);

    while (1) {
        GPS_read();
        GPS_format();

        currentLat = to_degree(currentLat);
        currentLong = to_degree(currentLong);

        tot_distance += distance(lat1, long1, currentLat, currentLong);
        lat1 = currentLat;
        long1 = currentLong;

        if ( tot_distance >=100.0) {
            LED_On(LED_GREEN);
            break;
        }
		UART2_RecieveString(command,length);
		if(strcmp(command, "U") == 0)
			{ int k;
		for(k=0;k<sizeof(allLats);k++){
			f32 longitude=0;
			char str_longitude[20]={0};
			f32 latitude=0;
			char str_latitude[20]={0};
		
			longitude = allLongs[k] ;
			ConvertFloatToStr(longitude,str_longitude);
			UART2_SendString (str_longitude);
			
			UART2_SendString ("   ");
			latitude = allLats[k] ;
			ConvertFloatToStr(latitude,str_latitude);
			UART2_SendString (str_latitude);
			
			UART2_SendString ("\n");
		}
	
	}
    }
}



double to_degree(float raw_degree) {  // gps output to degrees
    int dd = (int)(raw_degree / 100);
    double mm = raw_degree - (dd * 100);
    double degree = dd + (mm / 60);
    return degree;
}

double to_radians(double degrees) {  // degree to rad
    return degrees * M_PI / 180.0;
}

double distance(double lat1, double lon1, double lat2, double lon2) {  // calc distance between 2 coordinates in M
    double dlat = to_radians(lat2 - lat1);
    double dlon = to_radians(lon2 - lon1);
    double a = pow(sin(dlat / 2), 2) + cos(to_radians(lat1)) * cos(to_radians(lat2)) * pow(sin(dlon / 2), 2);
    double c = 2 * atan2(sqrt(a), sqrt(1 - a));
    return RADIUS * c;
}

double approximate(double a, float d) { return (int)(a / d + 0.5) * d; }

	

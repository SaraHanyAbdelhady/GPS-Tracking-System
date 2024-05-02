#ifndef GPS_H
#define GPS_H

/***************************** LIB *****************************/
#include "../../../Services/STD_TYPES.h"

/**************************** MACROS ***************************/
#define M_PI            3.1415926


void GPS_voidReceiveSentence(f64 *copy_f64Latitude,f64 *copy_f64Longitude, u8 *copy_u8Speed);

void GPS_voidExtractCoordinates(u8 *copy_pu8Sentence,f64 *copy_f64Latitude,f64 *copy_f64Longitude, u8 *copy_u8Speed);

#endif
#ifndef GPS_H
#define GPS_H

/***************************** LIB *****************************/
#include "../../../Services/STD_TYPES.h"

/**************************** MACROS ***************************/
#define M_PI            3.1415926


extern void GPS_voidReceiveSentence(f32 *copy_f32Latitude,f32 *copy_f32Longitude, u8 *copy_u8Speed);

extern void GPS_voidExtractCoordinates(u8 *copy_pu8Sentence,f32 *copy_f32Latitude,f32*copy_f32Longitude, u8 *copy_u8Speed);

#endif

#ifndef GPS_H
#define GPS_H

/***************************** LIB *****************************/
#include "../../../Services/STD_TYPES.h"

/**************************** MACROS ***************************/
#define M_PI            3.1415926


extern void GPS_read(void);

extern void GPS_format(void);

extern float allLats[200];
extern float allLongs[200];

#endif
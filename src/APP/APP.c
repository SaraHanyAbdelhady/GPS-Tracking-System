#include "../../Headers/HAL/GPS/GPS.h"
#include "../../Headers/APP/APP.h"
#include "../../Services/Bit_Utilities.h"
#include "../../Services/STD_TYPES.h"
#include <math.h>
//#include "TM4C123.h"						//hardware arch layer

//GPS file is to calculate the distance using latitude and longtude

//Takes the lat and convert it into degree
f32 Todegree(f32 angle){
	s32 degree = (int)angle / 100;
	f32 minutes = angle - (f32)degree * 100;
	return(degree + minutes/60);
}
//takes the degree and convert it into rad
f32 ToRad(f32 angle){
return angle*M_PI/180;
}

//We have two points' longitude and latitude to calculate the distance between them
f32 Distance(f32 longStart, f32 latStart, f32 longEnd, f32 latEnd){
//calc radian angle
	f32 longStartRad = ToRad(Todegree(longStart));
	f32 latStartRad = ToRad(Todegree(latStart));
	f32 longEndRad = ToRad(Todegree(longEnd));
	f32 latEndRad = ToRad(Todegree(latEnd));
	
//calc A-B
	f32 Longitude = longEndRad - longStartRad;
	f32 latitude = latEndRad - latStartRad;
	
	//calc distance from distance rule:
f32 a = pow(sin(latitude/2), 2) + cos(latStartRad) * cos(latEndRad) * pow(sin(Longitude/2), 2);
f64 c = 2 * atan2(sqrt(a), sqrt(a-1));
return Earth_Radius * c;
}

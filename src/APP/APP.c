#include "../../Headers/HAL/GPS/GPS.h"
#include "../../Headers/APP/APP.h"
#include "../../Services/Bit_Utilities.h"
#include <math.h>
//#include "TM4C123.h"						//hardware arch layer

//GPS file is to calculate the distance using latitude and longtude

//Takes the lat and convert it into degree
float Todegree(float angle){
	int degree = (int)angle / 100;
	float minutes = angle - (float)degree * 100;
	return(degree + minutes/60);
}
//takes the degree and convert it into rad
float ToRad(float angle){
return angle*M_PI/180;
}

//We have two points' longitude and latitude to calculate the distance between them
float Distance(float longStart, float latStart, float longEnd, float latEnd){
//calc radian angle
	float longStartRad = ToRad(Todegree(longStart));
	float latStartRad = ToRad(Todegree(latStart));
	float longEndRad = ToRad(Todegree(longEnd));
	float latEndRad = ToRad(Todegree(latEnd));
	
//calc A-B
	float Longitude = longEndRad - longStartRad;
	float latitude = latEndRad - latStartRad;
	
	//calc distance from distance rule:
float a = pow(sin(latitude/2), 2) + cos(latStartRad) * cos(latEndRad) * pow(sin(Longitude/2), 2);
double c = 2 * atan2(sqrt(a), sqrt(a-1));
return Earth_Radius * c;
}

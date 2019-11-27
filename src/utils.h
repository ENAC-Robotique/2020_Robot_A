
#ifndef UTILS_H_
#define UTILS_H_
#include "Arduino.h"

float normalise_angle(float angle)
	{
	    float newAngle = angle;
	    while (newAngle <= -PI) newAngle += TWO_PI;
	    while (newAngle > PI) newAngle -= TWO_PI;
	    return newAngle;
	}

#endif
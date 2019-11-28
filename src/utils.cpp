#include "Arduino.h"
#include "utils.h"

float normalise_angle(float angle){
	float newAngle = angle;
	while (newAngle <= -PI) newAngle += TWO_PI;
	while (newAngle > PI) newAngle -= TWO_PI;
	return newAngle;
}

int sign(float x){
	return (int) (x/abs(x));
}
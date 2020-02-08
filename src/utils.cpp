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

float scalaire(float x1, float y1, float x2, float y2){
	return x1*x2 + y1*y2;
}
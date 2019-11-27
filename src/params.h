
#ifndef PARAMS_H_
#define PARAMS_H_
#include "Arduino.h"


const unsigned long TIME_RACE = 100000;

const int ENCODER_R_A = 21;
const int ENCODER_R_B = 20;
const int ENCODER_L_A = 17;
const int ENCODER_L_B = 16;


const int MOT_R_PWM = 5;
const int MOT_R_DIR = 6;
const int MOT_L_PWM = 29;
const int MOT_L_DIR = 28;

const float WHEEL_DIAMETER = 54.0;
const float WHEELBASE = 230.0;

const float INCR_TO_MM = PI*WHEEL_DIAMETER/2500;

const float CONTROL_PERIOD = 0.02;
#endif
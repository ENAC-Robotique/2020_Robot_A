
#ifndef PARAMS_H_
#define PARAMS_H_
#include "Arduino.h"


const unsigned long TIME_RACE = 100000;

const int ENCODER_R_A = 2;
const int ENCODER_R_B = 3;
const int ENCODER_L_A = 31;
const int ENCODER_L_B = 30;


const int MOT_R_PWM = 5;
const int MOT_R_DIR = 6;
const int MOT_L_PWM = 29;
const int MOT_L_DIR = 28;

const float WHEEL_DIAMETER = 54.0;
const float WHEELBASE = 230.0;

const float INCR_TO_MM = PI*WHEEL_DIAMETER/2500;

const float CONTROL_PERIOD = 0.02;


//à déterminer
const float ACCEL_OMEGA_MAX = 2;
const float OMEGA_MAX = 2.5;
const float ADMITTED_OMEGA_ERROR = 0.03;
const float ADMITTED_SPEED_ERROR = 5;
const float ADMITTED_POSITION_ERROR = 5;
const float ADMITTED_ANGLE_ERROR = 0.01;
const int ACCEL_MAX = 800;
const int SPEED_MAX = 500;
const int EMERGENCY_BRAKE = 2500;
//à déterminer
const float NAVIGATOR_TIME_PERIOD = 0.05;
#endif
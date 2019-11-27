#include "odometry.h"
#include "Arduino.h"
#include "params.h"
#include "utils.h"

namespace Odometry{
    volatile float incr_R_temp;
	volatile float incr_L_temp;
    float pos_x, pos_y, pos_theta;
	float speed, omega;


    void init(){
        pinMode(ENCODER_R_A, INPUT);
        pinMode(ENCODER_R_B, INPUT);
        attachInterrupt(ENCODER_R_A, incrementator_R, RISING);

        pinMode(ENCODER_L_A, INPUT);
        pinMode(ENCODER_L_B, INPUT);
        attachInterrupt(ENCODER_L_A, incrementator_L, RISING);

        incr_R_temp = 0;
        incr_L_temp = 0;
    }

    void incrementator_R(){
        if (digitalRead(ENCODER_R_B)){
            incr_R_temp--;
          }
        else{
            incr_R_temp++;
        }
    }
    void incrementator_L(){
        if (digitalRead(ENCODER_L_B)){
            incr_L_temp++;
        }
        else{
            incr_L_temp--;
        }
    }

    float get_pos_x(){
		return pos_x;
	}

	float get_pos_y(){
		return pos_y;
	}

	float get_pos_theta(){
		return normalise_angle(pos_theta);
	}

	float get_speed(){
		return speed;
	}

	float get_omega(){
		return omega;
	}

	void set_pos(float x, float y, float theta){
		pos_x = x;
		pos_y = y;
		pos_theta = PI*theta/180;
	}



	void update() {
		cli();
		int incr_L = incr_L_temp;
		int incr_R = incr_R_temp;
		incr_L_temp = 0;
        incr_R_temp = 0;
		sei();

		float length = ((float)(incr_L+incr_R)/2.0)*INCR_TO_MM;
		float angle = ((float)(incr_R-incr_L)*INCR_TO_MM)/WHEELBASE;
		
        pos_x = pos_x + length*cos(pos_theta + angle/2.0);
		pos_y = pos_y + length*sin(pos_theta + angle/2.0);
		pos_theta = pos_theta + angle;
		
        speed = length / CONTROL_PERIOD;
		omega = angle / CONTROL_PERIOD;
	}
}









}
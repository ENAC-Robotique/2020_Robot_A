#include "motorControl.h"
#include "Arduino.h"
#include "params.h"
#include "odometry.h"

int clamp(int inf, int sup, float x) {
	return min(sup, max(inf, x));
}

int direction_sign(int nb){
    return nb<=0;
}

namespace MotorControl {

	float cons_speed;
	float cons_omega;
	float Ki_speed = 0.175;//0.2;
	float Kp_speed = 0.5;//0.5;
	float Kd_speed = 0;
	float Ki_omega = 17.5;//20;
	float Kp_omega = 30;//30;
	float Kd_omega = 0;

	float error_integrale_speed;
	float error_integrale_omega;

	float delta_speed;
	float delta_omega;
	float prev_speed_error;
	float prev_omega_error;

	void set_cons(float speed, float omega) {
		cons_speed = speed;
		cons_omega = omega;
	}

	float get_cons_speed(){
		return cons_speed;
	}

	float get_cons_omega(){
		return cons_omega;
	}

	void init() {
		pinMode(MOT_R_DIR, OUTPUT);
		pinMode(MOT_R_PWM, OUTPUT);
		pinMode(MOT_L_DIR, OUTPUT);
		pinMode(MOT_L_PWM, OUTPUT);
		cons_omega = cons_speed = 0;
		error_integrale_omega = error_integrale_speed = 0;
		prev_omega_error = prev_speed_error = 0;


	}

	void update(){

		float error_speed = cons_speed - Odometry::get_speed();
		error_integrale_speed += error_speed;
		delta_speed = error_speed - prev_speed_error;
		prev_speed_error = error_integrale_speed;
		float cmd_speed = Kp_speed * error_speed + Ki_speed * error_integrale_speed + Kd_speed * delta_speed;

		float error_omega = cons_omega - Odometry::get_omega();
		error_integrale_omega += error_omega;
		delta_omega = error_omega - prev_omega_error;
		prev_omega_error = error_omega;
		float cmd_omega = Kp_omega * error_omega + Ki_omega * error_integrale_omega + Kd_omega * delta_omega;

		int cmd_mot_R = clamp(-255, 255, cmd_speed - cmd_omega); //à revoir
		int cmd_mot_L = -clamp(-255, 255, cmd_speed + cmd_omega);

		analogWrite(MOT_R_PWM, abs(cmd_mot_R));
		digitalWrite(MOT_R_DIR, direction_sign(cmd_mot_R));
		analogWrite(MOT_L_PWM, abs(cmd_mot_L));
		digitalWrite(MOT_L_DIR, direction_sign(cmd_mot_L));
    }

}
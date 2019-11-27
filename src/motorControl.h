#ifndef MOTORCONTROL_H_
#define MOTORCONTROL_H_

namespace MotorControl {
	void update();
	void init();

	float get_cons_speed();
	float get_cons_omega();

	void set_cons(float speed, float omega);
}


#endif
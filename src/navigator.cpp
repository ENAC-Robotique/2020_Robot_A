#include "navigator.h"
#include "params.h"
#include "odometry.h"
#include "motorControl.h"
#include "math.h"

#include "utils.h"


Navigator navigator = Navigator();

Navigator::Navigator(){
    x_target = 0;
    y_target = 0;
    theta_target = 0;
    move_dir = FORWARD;
}

void Navigator::move_to(float x, float y, float theta, Move_dir dir){
    x_target = x;
    y_target = y;
    theta_target = theta;
    theta_initial = theta;
	move_type = DISPLACEMENT;
	move_state = INITIAL_TURN;
	stage = INIT;
}

void Navigator::turn_to(float theta){
	theta_target = theta;
	move_type = DISPLACEMENT;
	move_state = FINAL_TURN;
	stage = INIT;
}

float Navigator::compute_cons_omega(float theta){
  float omega_cons;
  float t_rotation_stop = abs(Odometry::get_omega())/ACCEL_OMEGA_MAX;
	float angle_fore = Odometry::get_pos_theta() + abs(Odometry::get_omega())*t_rotation_stop -1/2*ACCEL_OMEGA_MAX*pow(t_rotation_stop,2);
	int sgn = sign(theta - Odometry::get_pos_theta());
  if(abs(angle_fore - theta) < ADMITTED_ANGLE_ERROR){
		omega_cons = sgn * max(0, abs(Odometry::get_omega()) - NAVIGATOR_TIME_PERIOD*ACCEL_OMEGA_MAX);
	}
	else{
    
		if((theta - angle_fore) > 0){
			omega_cons = sgn * min(OMEGA_MAX, abs(Odometry::get_omega()) + NAVIGATOR_TIME_PERIOD*ACCEL_OMEGA_MAX);
		}
		else{
			omega_cons = sgn * max(0, abs(Odometry::get_omega()) - NAVIGATOR_TIME_PERIOD*ACCEL_OMEGA_MAX);
		}
	}
	return omega_cons;
}

float Navigator::compute_cons_speed(float x, float y){
    float speed_cons, dist_fore, t_stop, dist_objective;
    int	sgn = scalaire(cos(Odometry::get_pos_theta()),sin(Odometry::get_pos_theta()), x_target - Odometry::get_pos_x(), y_target - Odometry::get_pos_y());
    t_stop = Odometry::get_speed()/ACCEL_MAX;
    dist_fore = (Odometry::get_speed()*t_stop-1/2*ACCEL_MAX*pow(t_stop,2));
	dist_objective = sqrt(pow(x_target - Odometry::get_pos_x(),2) + pow(y_target - Odometry::get_pos_y(),2));

	if(abs( dist_fore - dist_objective ) < ADMITTED_POSITION_ERROR){
		speed_cons = sgn*max(0,-ACCEL_MAX*NAVIGATOR_TIME_PERIOD + abs(Odometry::get_speed()));
	}
	else{
		if(dist_fore - dist_objective > 0){
			speed_cons = sgn*max(0,abs(Odometry::get_speed()) - ACCEL_MAX*NAVIGATOR_TIME_PERIOD);
		}
		else{
			speed_cons = sgn*min(SPEED_MAX,abs(Odometry::get_speed()) + ACCEL_MAX*NAVIGATOR_TIME_PERIOD);
		}
	}
    return speed_cons;
}

void Navigator::update(){
    switch(move_type){
        case DISPLACEMENT:
         	 switch (move_state)
          	{
			case INITIAL_TURN:
				switch (stage)
				{
					case INIT:
					theta_initial = normalise_angle(atan2((-y_target+Odometry::get_pos_y()),(-x_target+Odometry::get_pos_x())));
					if (move_dir == BACKWARD){
						theta_initial = normalise_angle(theta_initial + PI);
					} 
					/*else if (move_dir == FORWARD){
						// NOTHING HAPPENS...
					}*/
					stage = ON_GOING;
					//break; //always ON_GOING after INIT
					
					case ON_GOING:
						if ((theta_initial - Odometry::get_pos_theta()) > ADMITTED_ANGLE_ERROR){
							compute_cons_omega(theta_initial);
						}
						else{
							stage = INIT;
							move_state = CRUISE;
						}
						break;
				}
				
				break;
			
			case CRUISE:
				switch (stage)
				{
				case INIT:
				stage = ON_GOING;
				//break; //always ON_GOING after INIT
		
				case ON_GOING:
					if (abs(scalaire(cos(Odometry::get_pos_theta()), sin(Odometry::get_pos_theta()), x_target - Odometry::get_pos_x(), y_target - Odometry::get_pos_y())) > ADMITTED_POSITION_ERROR ){
						compute_cons_omega(theta_initial);
						compute_cons_speed(x_target, y_target);
					}
					else{
						stage = INIT;
						move_state = FINAL_TURN;
					}
				break;
				}
				break;

			case FINAL_TURN:
				switch(stage){
					case INIT:
						stage = ON_GOING;
						//break; //always ON_GOING after INIT
					case ON_GOING:
						if ((theta_target - Odometry::get_pos_theta()) > ADMITTED_ANGLE_ERROR){
							compute_cons_omega(theta_target);
						}
						else{
							stage = INIT;
							move_state = STOPPED;
							break;
						}
					break;
				}

			case STOPPED:
				break;

			}
			break;
	
        case BRAKE:
			int sgn = scalaire(cos(Odometry::get_pos_theta()), sin(Odometry::get_pos_theta()), x_target - Odometry::get_pos_x(), y_target - Odometry::get_pos_y());
			float speed_cons = sgn*max(0,abs(Odometry::get_speed()) - EMERGENCY_BRAKE*NAVIGATOR_TIME_PERIOD);
			if(abs(Odometry::get_speed()) < ADMITTED_SPEED_ERROR){
				move_state = STOPPED;
				speed_cons = 0;
			}
			MotorControl::set_cons(speed_cons,0);
			MotorControl::set_cons(speed_cons,0);
            break;
        }
		


}
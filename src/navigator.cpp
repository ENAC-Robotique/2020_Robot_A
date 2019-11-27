#include "params.h"
#include "odometry.h"
#include "motorControl.h"
#include "math.h"
#include "navigator.h"
#include "utils.h"

Navigator navigator = Navigator();

Navigator::Navigator(){
    x_target = 0;
    y_target = 0;
    theta_target = 0;
    move_dir = FORWARD;
}

void Navigator::move_to(float x, float y, float theta, Move_dir dir){
    int sign = 1;
    if (dir == BACKWARD){
        sign = -1;
    }
    x_target = x;
    y_target = y;
    theta_target = theta;
    //theta intermediaire (initial turn)
}

void Navigator::update(){
    float omega_cons_speed_cons, distance, theta_initial;
    switch(move_type){
        case DISPLACEMENT:
          switch (move_state)
          {
          case INITIAL_TURN:
            theta_initial = normalise_angle(atan2((-y_target+Odometry::get_pos_y()),(-x_target+Odometry::get_pos_x())));
            if (move_dir == FORWARD){
                // NOTHING HAPPENS...
            }
            else { // if (move_dir == BACKWARD)
                theta_initial = normalise_angle(theta_initial + PI);
            } 

            break;
          
          case CRUISE:

            break;

          case FINAL_TURN:
            
            break;
            

          case STOPPED:

                break;

          }
        break;

        //travel
        case BRAKE:
            break;
        }


}
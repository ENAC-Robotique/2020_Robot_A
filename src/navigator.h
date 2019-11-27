
#ifndef NAVIGATOR_H_
#define NAVIGATOR_H_

typedef enum {DISPLACEMENT,
		      BRAKE}Move_type;

typedef enum {FORWARD,
              BACKWARD}Move_dir;


typedef enum {INITIAL_TURN,
              FINAL_TURN,
			  CRUISE,
			  STOPPED}Move_state;

class Navigator{
public:
	Navigator();
	void move_to(float x, float y, float theta, Move_dir dir);
	void update();

    /*------------------*/

	void turn_to(float theta);
	void throw_to(float x, float y, float theta);
	float compute_cons_speed();
	float compute_cons_omega();
	void forceStop();
	bool isTrajectoryFinished();
	bool moveForward();
	Move_state get_move_state();

private:
	float x_target;
	float y_target;
	float theta_target;
    Move_dir move_dir;
    
    /*--------------*/
    
    bool turn_done;
	bool displacement_done;
	bool trajectory_done;
	
	Move_type move_type;
	Move_state move_state;

	float center_axes(float angle);
	float center_radian(float angle);
	int scalaire(float x,float y,float x2,float y2);
};

extern Navigator navigator;

#endif
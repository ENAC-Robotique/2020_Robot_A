#include <Arduino.h>
#include "params.h"
#include "odometry.h"
#include "motorControl.h"
#include "navigator.h"
#include "Metro.h"

Metro controlTime = Metro((unsigned long)(CONTROL_PERIOD * 1000));
Metro navigatorTime = Metro(NAVIGATOR_TIME_PERIOD * 1000);

void setup() {
  // put your setup code here, to run once:
  Odometry::init();
	MotorControl::init();
  Odometry::set_pos(0, 0, 0);

  Serial.begin(115200);
  while(!Serial);
}

int i = 0;

void loop() {

  if (i == 0){
    //navigator.move_to(0, 0, 3, FORWARD);
    navigator.turn_to(3);
    i++;
  }

  if(controlTime.check()) {
		Odometry::update();
    Serial.println(Odometry::get_pos_theta());
		MotorControl::update();
	}

	if(navigatorTime.check()) {
		navigator.update();
	}
}
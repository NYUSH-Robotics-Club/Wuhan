#include "vex.h"
#include "robot-config.h"

motor_group adm = motor_group(L1, R1, L2, R2, L3, R3, L4, R4);
motor_group intake = motor_group(roller, conveyor);
motor_group wallStake = motor_group(wallStake1, wallStake2);


float autoRingColor, autoConveyorPosition;

//autoIsRed = True means we are sorting OUT blue, meaning we are on the red alliance.
bool autoIsRed = false;

/*void autoColorSort() {
  while (1) {
    wait(20, msec);
    
    // colorDetect.setLight(ledState::on);
    // colorDetect.setLightPower(100, percent);
  

  //print distance away on brain screen
  // Brain.Screen.setCursor(1, 30);
  // Brain.Screen.print(ringDist.objectDistance(inches));

  if ((ringDist.objectDistance(inches) < 2)) {

    //print ringColor on controller screen (removed bc printing to controller screen takes 200ms)
    autoRingColor = colorDetect.hue();
    // Controller1.Screen.setCursor(3, 14);
    // Controller1.Screen.print(autoRingColor);

    autoConveyorPosition = conveyor.position(degrees);
    
    if(autoIsRed && (autoRingColor > 360 || 20 > autoRingColor)) {
      //wait(.09, sec);
      conveyor.spin(forward, 12, volt);
      waitUntil(conveyor.position(degrees) > autoConveyorPosition + 100);
      conveyor.spin(reverse, 12 ,volt);
      wait(.2, sec);
      conveyor.spin(forward, 12, volt);
      //Controller1.rumble(".");
    }
    else if (!autoIsRed && (autoRingColor > 180 && 260 > autoRingColor)) {
      //wait(.09, sec);
      conveyor.spin(forward, 12, volt);
      waitUntil(conveyor.position(degrees) > autoConveyorPosition + 162);
      conveyor.spin(reverse, 12 ,volt);
      wait(.2, sec);
      conveyor.spin(forward, 12, volt);
      //Controller1.rumble(".");
    }
  }
  }
}*/

void drive_for_time(int timeMs, directionType direction, int maxVoltage) 
{
  adm.spin(direction, maxVoltage, volt);
  wait(timeMs, msec);
  adm.stop();
}

void drive_for_time(int timeMs, directionType direction) 
{
  drive_for_time(timeMs, direction, 7);
}

void drive_for_time(int timeMs) 
{
  drive_for_time(timeMs, fwd, 7);
}

void default_constants(){
  chassis.set_drive_constants(10, 1.5, 0, 10, 0);
  chassis.set_heading_constants(6, .4, 0, 1, 0);
  chassis.set_turn_constants(12, .4, 0.01, 3.1, 15);
  //chassis.set_swing_constants(12, .35, .002, 2, 15);
  chassis.set_swing_constants(12, .3, .001, 2, 15);
  chassis.set_drive_exit_conditions(1.5, 100, 3000);
  chassis.set_turn_exit_conditions(2, 100, 1000);
  chassis.set_swing_exit_conditions(2, 300, 1400);

  

  //Calibrate inertial sensor
  chassis.Gyro.calibrate();
  while (chassis.Gyro.isCalibrating()) {
    wait(10, msec);
  }
  wait(100, msec);
  Controller1.rumble("--");

  wallStake.setVelocity(100, percent);

  /*chassis.set_drive_constants(10, 1.5, 0, 10, 0);
  chassis.set_heading_constants(6, .4, 0, 1, 0);
  chassis.set_turn_constants(12, .4, .03, 3, 15);
  chassis.set_swing_constants(12, .3, .001, 2, 15);
  chassis.set_drive_exit_conditions(1.5, 300, 1000);
  chassis.set_turn_exit_conditions(1, 300, 3000);
  chassis.set_swing_exit_conditions(1, 300, 3000);*/
}

void odom_constants(){
  default_constants();
  chassis.drive_max_voltage = 8;
  chassis.drive_settle_error = 3;
}


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void leftAutonCenter(){
  //GREENGREENGREENGREENGREENGREENGREENGREENGREEN
  //Red left auton
  //score alliance stake

  //default_constants();
  
  //rush to the center mogo
  //chassis.set_coordinates()
  chassis.drive_to_point(0, 1.5);
  //chassis.turn_to_angle(30);
  doinker.set(true); // clamp mogo
  wait(.5, sec);


}

void leftAutonLeft(){
  //GREENGREENGREENGREENGREENGREENGREENGREENGREEN
  //Red left auton
  //score alliance stake
  
  //rush to the left mogo

}

void rightAuton(){
  //GOLDGOLDGOLDGOLDGOLDGOLDGOLDGOLDGOLDGOLD
  //Red right auton
  wait(.5, sec);
  chassis.set_heading(-90);

  //turn to the right mogo

  /*
  wait(1, sec);
  chassis.set_heading(-90);
  chassis.turn_to_angle(-127.5);
  chassis.drive_distance(5.5);
  wallStake.spin(fwd, 12, volt);
  wait(.5, sec);
  chassis.drive_distance(-15.25);
  wallStake.spin(reverse, 12, volt);
  chassis.turn_to_angle(-180);
  chassis.drive_distance(-22); // 17.5 bare minimum to reach goal
  wallStake.stop();
  mogoMech.set(true);
  chassis.turn_to_angle(90);
  intake.spin(fwd, 12, volt);
  chassis.drive_distance(17);
  chassis.turn_to_angle(-180);
  chassis.drive_distance(19);
  chassis.turn_to_angle(135);
  // chassis.drive_distance(24);
  drive_for_time(900, fwd, 8);
  wait(200, msec);
  chassis.drive_distance(-15);
  chassis.turn_to_angle(-90);
  chassis.drive_distance(60);
  chassis.drive_distance(-40);
  */
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////


void AWP_Plus_One(){
  //Just RED Allince stake
  //wait(20, seconds);
  chassis.drive_distance(10);
  chassis.turn_to_angle(90);
  roller.spin(fwd, 12, volt);
  chassis.drive_distance(24);
  chassis.turn_to_angle(0);
  drive_for_time(1000, reverse);
  chassis.drive_distance(1.8);
  intake.spin(fwd, 12, volt);
  wait(2, sec);
  conveyor.spin(reverse, 12, volt);
  drive_for_time(2000);
  intake.stop();


}

void Prog_Skills(){
  //Prog Skills

  //grab 1 ring
  chassis.set_drive_constants(4, 1.5, 0, 10, 0);
  roller.spin(forward, 12, volt);
  chassis.drive_distance(40);
  //grab mogo
  chassis.turn_to_angle(-90);
  chassis.drive_distance(-25);
  mogoMech.set(true);
  wait(.3, seconds);
  intake.spin(forward, 12, volt);
  //grab 3 extra rings
  chassis.drive_distance(6);
  chassis.turn_to_angle(0);
  chassis.drive_distance(24);
  chassis.turn_to_angle(90);
  chassis.drive_distance(14);
  chassis.drive_distance(-5);
  chassis.turn_to_angle(-180);
  wait(1, seconds);
  // conveyor.stop();
  chassis.drive_distance(50);
  // conveyor.spin(forward);
  // waitUntil(ringDist.objectDistance(inches) < 2);
  // drive_for_time(500, fwd, 4);
  // wallStake.spin(fwd, 12, volt);
  // wait(1, seconds);
  // wallStake.spin(reverse, 12, volt);
  // wait(1, sec);
  // chassis.drive_distance(-10);
  //grab ring in corner
  chassis.turn_to_angle(135);
  drive_for_time(1000, forward);
  wait(1.5, seconds);
  conveyor.spin(reverse, 12, volt);
  wait(.5, seconds);
  conveyor.spin(forward, 12, volt);
  //put goal in corner
  chassis.drive_distance(-10);
  chassis.turn_to_angle(-45);
  drive_for_time(1000, reverse);
  conveyor.spin(reverse, 12, volt);
  mogoMech.set(false);
  //get robot out or corner
  chassis.drive_distance(15);
  wait(5, sec);

  // push goal into corner
  intake.spin(fwd, 12, volt);
  chassis.set_drive_exit_conditions(1.5, 100, 4000);
  chassis.set_drive_constants(6, 1.5, 0, 10, 0);
  chassis.drive_distance(80);
  intake.stop();
  chassis.turn_to_angle(130);
  chassis.drive_distance(-40);
  mogoMech.set(true);
  wait(.2, sec);
  intake.spin(fwd, 12 ,volt);
  chassis.turn_to_angle(-45);
  chassis.drive_distance(12);
  wait(1, sec);
  chassis.turn_to_angle(135);
  intake.stop();
  chassis.drive_distance(-40);
  mogoMech.set(false);
  chassis.set_drive_exit_conditions(1.5, 100, 1000);
  chassis.drive_distance(19);
  chassis.drive_distance(-20);
  chassis.drive_distance(20);


}

void odom_test(){
  //RED Alliance HS auton Neg corner

  autoIsRed = true;

  chassis.set_drive_constants(4.5, 1.5, 0, 10, 0);
  chassis.set_heading(90);
  chassis.turn_to_angle(127.5);
  chassis.drive_distance(5.5);
  wallStake.spin(fwd, 12, volt);
  wait(.5, sec);
  chassis.drive_distance(-15.25);
  wallStake.spin(reverse, 12, volt);
  chassis.turn_to_angle(180);
  chassis.drive_distance(-22); // 17.5 bare minimum to reach goal
  wallStake.stop();
  mogoMech.set(true);
  chassis.turn_to_angle(-90);
  intake.spin(fwd, 12, volt);
  chassis.drive_distance(17);
  chassis.turn_to_angle(180);
  chassis.drive_distance(19);
  chassis.turn_to_angle(-135);
  chassis.drive_distance(24);
  wait(200, msec);
  chassis.drive_distance(-15);
  chassis.turn_to_angle(90);
  chassis.drive_distance(60);

}



void worlds_auton(){
  //Worlds Auton

  //AWP + score some form the middle and cross the bar to start on the far side

  

}

void safe_worlds_auton(){
  //Safe worlds auton
  //Maybe use for safe auton where we shave a few seconds off


}




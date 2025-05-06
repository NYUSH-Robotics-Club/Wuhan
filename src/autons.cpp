#include "vex.h"
#include "robot-config.h"
#include "main.h"

motor_group adm = motor_group(L1, R1, L2, R2, L3, R3, L4, R4);
motor_group intake = motor_group(roller, conveyor);
motor_group wallStake = motor_group(wallStake1, wallStake2);


float autoRingColor, autoConveyorPosition;

//autoIsRed = True means we are sorting OUT blue, meaning we are on the red alliance.
bool autoIsRed = false;


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
  chassis.set_drive_constants(12, 1.5, 0.0, 10, 0);
  chassis.set_heading_constants(6, .5, 0, 1.2, 0);
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
void preRedGreenAutonCenter(){
  isRed = true;
  ringSortDisable = false;
  wallStakeFeedFwdDis = true;
  
  chassis.set_coordinates(24, -48, 0);
}

void redGreenAutonCenter(){
  double startTime = Brain.timer(msec);


  chassis.drive_max_voltage = 12;
  chassis.heading_max_voltage = 12;

  //chassis.set_heading(-30);
  roller.spin(fwd, 12, volt);
  doinker_left.set(true); //extend doinker
  // chassis.drive_to_point(14.2, -13.3);
  chassis.drive_distance(35);//switched to drive_distance for better consistency
  doinker_left.set(false); //clamp doinker
  roller.spin(reverse, 12, volt);

  // chassis.drive_to_point(30.1, -42.3);
  chassis.drive_to_point(30, -48);
  
  chassis.drive_stop(hold);
  
  chassis.drive_max_voltage = 8;
  chassis.heading_max_voltage = 4;
  chassis.drive_distance(3);
  doinker_left.set(true); //unclamp doinker
  wait(.5, sec);
  chassis.drive_distance(-7);
  doinker_left.set(false); //retract doinker
  chassis.turn_to_angle(chassis.get_absolute_heading() + 165);
  
  chassis.drive_min_voltage = 3;
  chassis.drive_max_voltage = 4;
  chassis.drive_distance(-23);
  mogoMech.set(true);
  wait(.1, sec); //grab mogo
  roller.spin(fwd, 12, volt);
  conveyor.spin(fwd, 9, volt);
  
  chassis.drive_min_voltage = 0;
  chassis.drive_max_voltage = 8;

  
  wait(1, sec);

  // chassis.turn_to_point(24, -24);
  // chassis.drive_to_point(24, -24);//grab red blue stack

  chassis.turn_to_angle(90.0);

  chassis.drive_max_voltage = 3.5;
  chassis.drive_to_point(57, -24);


  chassis.turn_to_point(60, 0);
  chassis.drive_to_point(60, -7);
  chassis.drive_distance(-6);
  wait(.5, sec);//wait for ring to flip over the top


  chassis.drive_max_voltage = 9;
  chassis.turn_to_point(48, -47);

  chassis.drive_to_point(48, -47);
  wait(.5, sec); //wait for ring to score on goal (non-essential)
  
  //drop off goal near + corner
  chassis.turn_to_point(55, -46, 180);
  chassis.drive_to_point(55, -46);
  mogoMech.set(false);
  wait(.1, sec);

  chassis.turn_to_point(0, -60);
  chassis.drive_to_point(0,-60);

  wsState = 0;
  onR1Pressed();
  
  // chassis.drive_to_point(8,-56);
  // chassis.turn_to_angle(-135);
  wait(400,msec);
  chassis.turn_to_point(-1, -72);
  drive_for_time(500, fwd, 4);//align with alliance stake
  chassis.drive_distance(-9);
  chassis.turn_to_point(-2, -72);
  conveyor.spin(reverse, 4, volt);
  wait(100,msec);
  wallStake.spin(forward, 12, volt);//score on alliance stake
  wait(1000,msec);
  wallStake.stop();

  //touch the ladder near goal that gold bot left behind
  drive_for_time(200, reverse, 7);
  intake.spin(fwd, 12 ,volt);
  wallStake.spin(reverse, 12, volt);
  chassis.heading_max_voltage = 12;
  chassis.drive_to_point(-24, -18);
  chassis.heading_max_voltage = 4;
  chassis.turn_to_point(0, 0);
  wallStake.stop();
  chassis.drive_distance(10);
  chassis.turn_to_point(-24, -68, 180);



  //leave at end of auton
  chassis.drive_stop(vex::coast);

  double endTime = Brain.timer(msec);

  printf("Autonomous finished in %.2f seconds\n", (endTime - startTime)/1000);
}

void blueGreenAutonCenter(){

  

  //ringSortDisable = false;


    
  /*
  

  chassis.drive_max_voltage = 8;
  chassis.drive_to_point(24, -24);
  doinker_left.set(true); // unclamp doinker
  chassis.drive_distance(-6, 335);
  doinker_left.set(false); // retract doinker

  

  chassis.turn_to_angle(chassis.get_absolute_heading() + 180);
  */
  //chassis.turn_to_angle(-30);
  
  
  
}

void redGreenAutonOther(){
  
  //score alliance stake
  
  //rush to the left mogo
}

void blueGreenAutonOther(){
 
  //score alliance stake
  
  //rush to the left mogo
}

void redGoldAuton(){
  
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

void blueGoldAuton() {
  chassis.drive_max_voltage = 12;
  chassis.heading_max_voltage = 12;
  doinker_right.set(true); // put doinker down
  chassis.drive_distance(39);
  doinker_right.set(false);  // grab mogo with doinker
  chassis.drive_to_point(21, -50);

  chassis.drive_stop(hold);

  chassis.drive_max_voltage = 9;
  chassis.heading_max_voltage = 4;

  chassis.turn_to_point(24, -72);
  doinker_right.set(true);  // let go of mogo
  chassis.drive_distance(3);
  wait(.5, sec);
  chassis.drive_distance(-7);
  doinker_right.set(false); // put doinker up
  // chassis.turn_to_angle(chassis.get_absolute_heading() - 165);
  // chassis.drive_distance(-10);
  // chassis.drive_min_voltage = 3;
  // chassis.drive_max_voltage = 4;
  // chassis.drive_distance(-15);
  // mogoMech.set(true);
  // wait(.1, sec); //grab mogo
  // roller.spin(fwd, 12, volt);
  // conveyor.spin(fwd, 9, volt);
  // chassis.drive_distance(4);
  
  // //drop mogo near driver station wall
  // chassis.turn_to_point(24, -72, 180);
  // chassis.drive_distance(-12);
  // mogoMech.set(false);
  // wait(.1, sec);

  //gab our side mogo
  chassis.turn_to_point(-3, -49, 180);
  chassis.drive_min_voltage = 3;
  chassis.drive_max_voltage = 7;
  chassis.drive_to_point(-3, -49);
  mogoMech.set(true);


  chassis.drive_min_voltage = 0;
  chassis.drive_max_voltage = 10;
  chassis.turn_max_voltage = 7;

  //get 2 double stacks of rings
  chassis.turn_to_point(38, -31);
  roller.spin(fwd, 12, volt);
  conveyor.spin(fwd, 9, volt);
  chassis.drive_to_point(38, -31);
  chassis.drive_max_voltage = 4;
  // chassis.turn_to_point(56, -19);
  chassis.drive_to_point(56, -19);
  chassis.drive_max_voltage = 9;
  chassis.turn_to_point(48, -48);
  chassis.drive_to_point(48, -48);
  
  //grab 4 stack in corner & ram 3 times
  chassis.turn_to_point(72, -72);
  drive_for_time(700, forward, 6);
  chassis.drive_distance(-5);
  chassis.turn_to_point(72, -72);
  drive_for_time(400, forward, 10);
  chassis.drive_distance(-7);
  chassis.turn_to_point(72, -72);
  drive_for_time(300, forward, 10);
  chassis.drive_distance(-7);
  chassis.turn_to_point(72, -72);
  drive_for_time(300, forward, 10);
  chassis.drive_distance(-10);
  chassis.turn_to_point(-46, -48);

  chassis.drive_max_voltage = 12;
  //cross the field to pos corner to clear rings and put mogo in corner
  chassis.drive_to_point(-46, -48);
  chassis.drive_max_voltage = 10;


  //grab 4 stack in + corner & ram 3 times
  chassis.turn_to_point(-72, -72);
  drive_for_time(700, forward, 7);
  chassis.drive_distance(-5);
  chassis.turn_to_point(-72, -72);
  drive_for_time(400, forward, 10);
  chassis.drive_distance(-7);
  chassis.turn_to_point(-72, -72);
  drive_for_time(300, forward, 10);
  chassis.drive_distance(-7);
  chassis.turn_to_point(-72, -72);
  drive_for_time(300, forward, 10);
  //sweep corner
  
  chassis.drive_distance(-10);
  chassis.turn_to_point(-36, -60, 180);
  chassis.drive_to_point(-36, -60);
  chassis.turn_max_voltage = 12;
  doinker_left.set(true);
  chassis.turn_max_voltage = 9;
  chassis.turn_to_point(-72, -70);
  drive_for_time(500, fwd, 10);
  chassis.drive_distance(-5);
  // chassis.turn_to_point(-72, -48);
  chassis.turn_to_point(0, 0);
  doinker_left.set(false);

  //put goal in + corner
  mogoMech.set(false);
  drive_for_time(500, reverse, 8);
  chassis.drive_distance(10);

  //line up to grab goal green dropped off
  // chassis.drive_to_point(-56, -56);
  chassis.turn_to_angle(135);
  //get off auton line for AWP
  chassis.drive_max_voltage = 9;
  chassis.drive_distance(-6);


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




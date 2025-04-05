#include "auto/utils.h"

void auton_skills() {
  // Prog Skills

  // grab 1 ring
  chassis.set_drive_constants(4, 1.5, 0, 10, 0);
  roller.spin(forward, 12, volt);
  chassis.drive_distance(40);
  // grab mogo
  chassis.turn_to_angle(-90);
  chassis.drive_distance(-25);
  mogoMech.set(true);
  wait(.3, seconds);
  intakeMotors.spin(forward, 12, volt);
  // grab 3 extra rings
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
  // grab ring in corner
  chassis.turn_to_angle(135);
  drive_for_time(1000, forward);
  wait(1.5, seconds);
  conveyor.spin(reverse, 12, volt);
  wait(.5, seconds);
  conveyor.spin(forward, 12, volt);
  // put goal in corner
  chassis.drive_distance(-10);
  chassis.turn_to_angle(-45);
  drive_for_time(1000, reverse);
  conveyor.spin(reverse, 12, volt);
  mogoMech.set(false);
  // get robot out or corner
  chassis.drive_distance(15);
  wait(5, sec);

  // push goal into corner
  intakeMotors.spin(fwd, 12, volt);
  chassis.set_drive_exit_conditions(1.5, 100, 4000);
  chassis.set_drive_constants(6, 1.5, 0, 10, 0);
  chassis.drive_distance(80);
  intakeMotors.stop();
  chassis.turn_to_angle(130);
  chassis.drive_distance(-40);
  mogoMech.set(true);
  wait(.2, sec);
  intakeMotors.spin(fwd, 12, volt);
  chassis.turn_to_angle(-45);
  chassis.drive_distance(12);
  wait(1, sec);
  chassis.turn_to_angle(135);
  intakeMotors.stop();
  chassis.drive_distance(-40);
  mogoMech.set(false);
  chassis.set_drive_exit_conditions(1.5, 100, 1000);
  chassis.drive_distance(19);
  chassis.drive_distance(-20);
  chassis.drive_distance(20);
}
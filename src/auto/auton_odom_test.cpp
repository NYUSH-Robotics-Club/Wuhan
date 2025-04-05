#include "auto/utils.h"

void auton_odom_test() {
  // BLUE Alliance Stake

  // Just BLUE Allince stake
  wait(20, seconds);
  chassis.drive_distance(10);
  chassis.turn_to_angle(-90);
  roller.spin(fwd, 12, volt);
  chassis.drive_distance(24);
  chassis.turn_to_angle(0);
  drive_for_time(1000, reverse);
  chassis.drive_distance(2.5);
  intakeMotors.spin(fwd, 12, volt);
  wait(2, sec);
  drive_for_time(2000);

  // turn test
  //  chassis.turn_to_angle(15);
  //  chassis.turn_to_angle(90);
  //  chassis.turn_to_angle(270);
  //  chassis.turn_to_angle(0);
  //  Controller1.rumble("--");

  /*chassis.drive_distance(24);
  wait(.5, seconds);
  chassis.drive_distance(3);
  wait(.5, seconds);
  chassis.drive_distance(20);
  wait(.5, seconds);
  chassis.drive_distance(-31.25);
  Controller1.rumble("--");*/

  // swing test
  chassis.right_swing_to_angle(45);
  chassis.left_swing_to_angle(0);
  chassis.right_swing_to_angle(90);
  chassis.left_swing_to_angle(0);
}
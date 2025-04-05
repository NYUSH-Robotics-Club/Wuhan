#include "auto/utils.h"

void auton_blue() {
  // HS AWP BLUE

  // prep for rush
  roller.spin(forward, 12, volt);
  doinker.set(true);
  chassis.drive_distance(35, -60);
  chassis.drive_distance(3);
  // Rush
  // wait(.1, seconds);
  doinker.set(false);
  // wait(.1, seconds);
  chassis.drive_distance(-37, -35);
  // chassis.left_swing_to_angle(30);
  chassis.turn_to_angle(-2);
  // chassis.turn_to_angle(5);
  doinker.set(true);
  // chassis.drive_distance(3);
  chassis.turn_to_angle(-10);
  chassis.turn_to_angle(0);
  // zero against wall
  drive_for_time(1500, reverse);
  doinker.set(false);
  chassis.set_heading(0);
  chassis.turn_to_angle(0);
  wait(.1, seconds);
  // grab mogo
  chassis.drive_distance(30);
  chassis.turn_to_angle(180);
  chassis.set_drive_constants(4, 1.5, 0, 10, 0);
  chassis.drive_distance(-18);
  mogoMech.set(true);
  wait(.1, seconds);
  chassis.drive_distance(9);
  mogoMech.set(false);
  // wait(.2, seconds);
  chassis.drive_distance(-4);
  mogoMech.set(true);
  wait(.2, seconds);
  intakeMotors.spin(forward, 12, volt);
  // pick up both 2-ring stackes
  chassis.turn_to_angle(90);
  chassis.set_drive_constants(4, 1.5, 0, 10, 0);
  chassis.drive_distance(23);
  chassis.drive_distance(-9);
  chassis.turn_to_angle(180);
  chassis.drive_distance(35);
  chassis.drive_distance(-5);
  // unjam conveyor if it's jammed
  //  intake.spin(reverse, 12, volt);
  //  wait(.3, seconds);
  //  intake.spin(forward, 12, volt);
  // grab bottom ring from neg corner
  chassis.turn_to_angle(130);
  drive_for_time(750, forward);
  chassis.drive_distance(-2);
  wait(.6, seconds);
  chassis.drive_distance(-10);
  // zero against side wall
  chassis.turn_to_angle(90);
  drive_for_time(750, fwd, 5);
  wait(.1, sec);
  chassis.set_heading(90);
  chassis.turn_to_angle(90);
  chassis.drive_distance(-20);
  // grab ring to put on alliance stake with fish mech
  chassis.turn_to_angle(-98);
  chassis.drive_distance(42);
  float autoConveyorPosition = conveyor.position(degrees);
  waitUntil(
      (colorDetect.isNearObject() && ringDist.objectDistance(inches) < 2.5) ||
      (conveyor.position(degrees) == autoConveyorPosition + 6000));
  intakeMotors.stop();
  // put ring on alliance stake
  chassis.turn_to_angle(180);
  chassis.drive_distance(-4.5);
  wallStake.spin(fwd, 12, volt);
  wait(.8, seconds);
  wallStake.spin(reverse, 12, volt);
  wait(.9, sec);
  chassis.set_drive_constants(10, 1.5, 0, 10, 0);
  // touch the ladder
  chassis.turn_to_angle(0);
  roller.spin(forward, 12, volt);
  drive_for_time(2000, fwd, 4);
}

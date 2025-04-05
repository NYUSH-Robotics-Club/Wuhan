#include "auto/utils.h"

void auton_awp() {
  // Just RED Allince stake
  // wait(20, seconds);
  chassis.drive_distance(10);
  chassis.turn_to_angle(90);
  roller.spin(fwd, 12, volt);
  chassis.drive_distance(24);
  chassis.turn_to_angle(0);
  drive_for_time(1000, reverse);
  chassis.drive_distance(1.8);
  intakeMotors.spin(fwd, 12, volt);
  wait(2, sec);
  conveyor.spin(reverse, 12, volt);
  drive_for_time(2000);
  intakeMotors.stop();
}
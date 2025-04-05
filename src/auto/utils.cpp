#include "auto/utils.h"

void auto_color_sort(bool autoIsRed) {
  while (1) {
    wait(20, msec);

    // colorDetect.setLight(ledState::on);
    // colorDetect.setLightPower(100, percent);

    // print distance away on brain screen
    //  Brain.Screen.setCursor(1, 30);
    //  Brain.Screen.print(ringDist.objectDistance(inches));

    if ((ringDist.objectDistance(inches) < 2)) {

      // print ringColor on controller screen (removed bc printing to controller
      // screen takes 200ms)
      float autoRingColor = colorDetect.hue();
      // Controller1.Screen.setCursor(3, 14);
      // Controller1.Screen.print(autoRingColor);

      float autoConveyorPosition = conveyor.position(degrees);

      if (autoIsRed && (autoRingColor > 360 || 20 > autoRingColor)) {
        // wait(.09, sec);
        conveyor.spin(forward, 12, volt);
        waitUntil(conveyor.position(degrees) > autoConveyorPosition + 100);
        conveyor.spin(reverse, 12, volt);
        wait(.2, sec);
        conveyor.spin(forward, 12, volt);
        // Controller1.rumble(".");
      } else if (!autoIsRed && (autoRingColor > 180 && 260 > autoRingColor)) {
        // wait(.09, sec);
        conveyor.spin(forward, 12, volt);
        waitUntil(conveyor.position(degrees) > autoConveyorPosition + 162);
        conveyor.spin(reverse, 12, volt);
        wait(.2, sec);
        conveyor.spin(forward, 12, volt);
        // Controller1.rumble(".");
      }
    }
  }
}

void drive_for_time(int timeMs, directionType direction, int maxVoltage) {
  allDriveMotors.spin(direction, maxVoltage, volt);
  wait(timeMs, msec);
  allDriveMotors.stop();
}

void drive_for_time(int timeMs, directionType direction) {
  drive_for_time(timeMs, direction, 7);
}

void drive_for_time(int timeMs) { drive_for_time(timeMs, fwd, 7); }

void default_constants() {
  chassis.set_drive_constants(10, 1.5, 0, 10, 0);
  chassis.set_heading_constants(6, .4, 0, 1, 0);
  chassis.set_turn_constants(12, .4, 0.01, 3.1, 15);
  // chassis.set_swing_constants(12, .35, .002, 2, 15);
  chassis.set_swing_constants(12, .3, .001, 2, 15);
  chassis.set_drive_exit_conditions(1.5, 100, 3000);
  chassis.set_turn_exit_conditions(2, 100, 1000);
  chassis.set_swing_exit_conditions(2, 300, 1400);

  // Calibrate inertial sensor
  inertialSensor.calibrate();
  wait(2000, msec);
  Controller1.rumble("-..");

  wallStake.setVelocity(100, percent);

  /*
  chassis.set_drive_constants(10, 1.5, 0, 10, 0);
  chassis.set_heading_constants(6, .4, 0, 1, 0);
  chassis.set_turn_constants(12, .4, .03, 3, 15);
  chassis.set_swing_constants(12, .3, .001, 2, 15);
  chassis.set_drive_exit_conditions(1.5, 300, 1000);
  chassis.set_turn_exit_conditions(1, 300, 3000);
  chassis.set_swing_exit_conditions(1, 300, 3000);
  */
}

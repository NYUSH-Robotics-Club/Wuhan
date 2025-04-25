#include "robot/ring_sort.h"
#include "globals.h"
#include "vex.h"

float ringColor;

#define is_blue_alliance !isRed
#define is_red_alliance isRed

int conveyorPosition = 0;

//**RING SORTING**
void colorSort() {

  while (1) {
    wait(10, msec);

    // print distance away on brain screen
    Brain.Screen.setCursor(1, 30);
    Brain.Screen.print(ringDist.objectDistance(inches));

    if (ringDist.objectDistance(inches) > 1.5 || ringSortDisable)
      continue;

    // print ringColor on controller screen (removed bc printing to controller
    // screen takes 200ms)
    ringColor = colorDetect.hue();
    // Controller1.Screen.setCursor(3, 14);
    // Controller1.Screen.print(ringColor);

    conveyorPosition = conveyor.position(degrees);

    if (is_blue_alliance && (ringColor > 360 || 20 > ringColor)) {
      // wait(.09, sec);
      // printf("Launching red\n");
      conveyor.spin(forward, 12, volt);
      waitUntil(conveyor.position(degrees) > conveyorPosition + 100);
      // wait(10 * conveyor.current(amp), msec);
      conveyor.spin(reverse, 12, volt);
      wait(.2, sec);
      conveyor.spin(forward, 9, volt);
      Controller1.rumble("..");
      wait(200, msec);
    } else if (is_red_alliance && (ringColor > 180 && 260 > ringColor)) {
      // wait(.09, sec);
      // printf("Launching blue\n");
      conveyor.spin(forward, 12, volt);
      waitUntil(conveyor.position(degrees) > conveyorPosition + 100);
      // wait(10 * conveyor.current(amp), msec);
      conveyor.spin(reverse, 12, volt);
      wait(.2, sec);
      conveyor.spin(forward, 9, volt);
      Controller1.rumble(".");
      wait(200, msec);
    }

    // Controller1.Screen.setCursor(3, 14);
    // Controller1.Screen.print(ringColor);
  }
}

void loadRing() {
  ringDetectOverride = false;
  Controller1.rumble("-");
  while (!(((ringDist.objectDistance(inches) < 2)) || ringDetectOverride)) {
    roller.spin(forward, 12, volt);
    conveyor.spin(forward, 7, volt);
    wait(10, msec);
  }

  if (!ringDetectOverride) {
    intakeMotors.stop();
    conveyor.stop();
  }
  roller.spin(fwd, 8, volt);
}

void enableRingDetectOverride() { ringDetectOverride = true; }

void throwRed() {
  ringSortDisable = false;
  isRed = false;
  Controller1.Screen.setCursor(3, 1);
  Controller1.Screen.print("chuck red ");
}

void throwBlue() {

  ringSortDisable = false;
  isRed = true;
  Controller1.Screen.setCursor(3, 1);
  Controller1.Screen.print("chuck blue");
}

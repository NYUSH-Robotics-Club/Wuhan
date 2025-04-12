#include "auto/autons.h"
#include "auto/utils.h"
#include "robot.h"
#include "vex.h"
#include "globals.h"
#include "robot/ring_sort.h"

// What I changed since the last version of code:

// lb code + one button mogo mech

// ---- START VEXCODE CONFIGURED DEVICES ----
// Robot Configuration ****SMALL BOT****:
// [Name]               [Type]        [Port(s)]
// Controller1          controller
// L1                   motor         6
// L2                   motor         7
// L3                   motor         8
// R1                   motor         1
// R2                   motor         2
// R3                   motor         3
// roller               motor         5
// conveyor             motor         4
// wallStake            motor         9
// doinker              digital_out   B
// ringChuck            digital_out   C
// mogoMech             digital_out   D
// colorDetect          optical       21
// ---- END VEXCODE CONFIGURED DEVICES ----

competition Competition;



bool wallStakeFeedFwdDis, antijamDisable = true;


#define is_blue_alliance !isRed
#define is_red_alliance isRed

thread wsThread;

#define LOADING 1
#define PRESCORING 2
#define SCORING 3
#define LOWER_SCORING 0

int current_auton_selection = 0, wallStakeState = 0;
bool auto_started = false;

void pre_auton(void) {
  default_constants();

  while (auto_started == false) {
    Brain.Screen.clearScreen();
    switch (current_auton_selection) {
    case 0:
      Brain.Screen.printAt(50, 50, "Red Auton");
      // Brain.Screen.setFillColor();
      // Brain.Screen.drawRectangle(0, 0, 100, 100);
      break;
    case 1:
      Brain.Screen.printAt(50, 50, "Blue Auton");
      break;
    case 2:
      Brain.Screen.printAt(50, 50, "Red Alliance Stake");
      break;
    case 3:
      Brain.Screen.printAt(50, 50, "Prog Skills");
      break;
    case 4:
      Brain.Screen.printAt(50, 50, "TEST DO NOT USE - Empty Slot");
      break;
    case 5:
      Brain.Screen.printAt(50, 50, "DO NOT USE - Empty Slot");
      break;
    case 6:
      Brain.Screen.printAt(50, 50, "Blue Auto v2");
      break;
    case 7:
      Brain.Screen.printAt(50, 50, "Red Auto v2");
      break;
    }
    if (Brain.Screen.pressing()) {
      while (Brain.Screen.pressing()) {
        wait(10, msec);
      }
      current_auton_selection++;
    } else if (current_auton_selection == 8) {
      current_auton_selection = 0;
    }
    task::sleep(10);
  }
}

void autonomous(void) {
  auto_started = true;
  switch (current_auton_selection) {
  case 0:
    isRed = true;
    ringSortDisable = false;
    wallStakeFeedFwdDis = true;
    auton_red();
    break;
  case 1:
    isRed = false;
    wallStakeFeedFwdDis = true;
    ringSortDisable = false;
    auton_blue();

    break;
  case 2:
    auton_awp();
    break;
  case 3:
    auton_skills();
    isRed = true;
    ringSortDisable = false;

    break;
  case 4:
    auton_odom_test();
    break;
  case 5:
    // TODO implement this auton
    break;
  case 6:
    // TODO implement this auton
    break;
  }
}



void usercontrol(void) {
  ringSortDisable = true;
  antijamDisable = true;
  allDriveMotors.setStopping(coast);
}

// intake control
void enableConveyor() {
  // intakeMain.spin(forward, 9, volt);
  conveyor.spin(fwd, 9, volt);
  roller.spin(fwd, 12, volt);
}

void reverseConveyor() { intakeMotors.spin(reverse, 12, volt); }

void stopConveyor() { intakeMotors.stop(); }

void toggleDoinker() { doinker.toggle(); }

void toggleMogo() { mogo.toggle(); }

void enableMogo() { mogo.clamp(); }
void disableMogo() { mogo.clamp(); }

void wsSpinToPosition(int position, double kP, double kD, double tolerance) {
  // double kP = 200;
  // double kD = 1000;

  rotationWallStake.resetPosition();

  double startPos = rotationWallStake.position(deg);
  double target = startPos + position;

  double error = target - rotationWallStake.position(deg);
  double lastError = 0;

  while (fabs(error) > tolerance) {
    error = target - rotationWallStake.position(deg);
    wallStake.spin(fwd, (error * kP) + ((error - lastError) * kD),
                   vex::voltageUnits::mV);
    lastError = error;
    wait(10, msec);
  }

  wallStake.stop(hold);
}

int wsState = 0;

void scoreLB() {
  wsState = ++wsState & 3;

  wsThread.interrupt();

  if (wsState == LOADING) {
    wsThread = thread([]() {
      wsSpinToPosition(21, 200, 0, 1);
      waitUntil(conveyor.current(amp) > 2.3 && conveyor.velocity(rpm) < 2);
      conveyor.spin(fwd, 2, volt);
      wallStake.stop(coast);
    });

    roller.spin(fwd, 12, volt);
    conveyor.spin(fwd, 9, volt);
  } else if (wsState == PRESCORING) {
    wsThread = thread([]() {
      conveyor.spin(reverse, 4, volt);
      wsSpinToPosition(100, 250, 0, 3);
      conveyor.stop();
      if (Controller1.ButtonY.pressing()) {
        wsSpinToPosition(90, 200, 0, 2);
        wallStake.spin(reverse, 12, volt);
        wait(500, msec);
        wallStake.stop(coast);
        wsState = 0;
      }
    });
  } else if (wsState == SCORING) {
    wsThread = thread([]() {
      wsState = 0;
      wsSpinToPosition(55, 200, 0, 5);
      wallStake.spin(reverse, 12, volt);
      wait(400, msec);
      wallStake.stop(coast);
    });
  }

  antijamDisable = false;
}

void manualWallstakeCtrl() {
  int position = Controller1.Axis2.position();
  if (abs(position) < 50) {
    wallStakeFeedFwdDis = false;
    wallStake.stop(brake);
    return;
  }
  wsThread.interrupt();
  wsState = LOWER_SCORING;
  conveyor.stop();
  wallStakeFeedFwdDis = true;
  wallStake.spin(fwd, position * 0.12, volt);
}

void wallStakeAutoHold() {
  colorDetect.setLight(ledState::on);
  colorDetect.setLightPower(100, percent);
  wallStake.setVelocity(100, percent);
  wallStake.setStopping(hold);
  wallStakeFeedFwdDis = false;
  // Set drive motor stopping to coast
  allDriveMotors.setStopping(coast);

  while (1) {
    Brain.Screen.setCursor(1, 1);
    Brain.Screen.print(wallStake.position(degrees));
    Brain.Screen.print("   ");
    if (Controller1.ButtonDown.pressing()) {
      wallStake.setPosition(0, degrees);
    }

    // if (!wallStakeFeedFwdDis && wallStake.position(degrees) < 100) {
    //   wallStake.spin(reverse, 1, volt);
    // }

    wait(20, msec);
  }
}



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




int main() {
  thread colorSortThread = thread(colorSort);
  thread wsAutoHold = thread(wallStakeAutoHold);

  rotationWallStake.setPosition(0, degrees);

  colorDetect.integrationTime(5);

#ifdef GREEN
  Controller1.ButtonL1.pressed(enableConveyor);
  Controller1.ButtonL2.pressed(reverseConveyor);
  Controller1.ButtonL2.released(stopConveyor);

  // Unwrapped updateDrivetrainVelocity logic
  Controller1.Axis1.changed([]() {
    chassis.control_arcade();
  });
  Controller1.Axis3.changed([]() {
    chassis.control_arcade();
  });

  Controller1.Axis2.changed(manualWallstakeCtrl);
  Controller1.ButtonB.pressed(toggleDoinker);
  Controller1.ButtonL1.pressed(enableRingDetectOverride);
  Controller1.ButtonL2.pressed(enableRingDetectOverride);
  Controller1.ButtonLeft.pressed(throwBlue);
  Controller1.ButtonRight.pressed(throwRed);
#ifdef LADY_BROWN
  Controller1.ButtonR1.pressed(scoreLB);
#endif


  Controller1.ButtonR2.pressed(toggleMogo);
  Controller1.ButtonA.pressed(loadRing);
#endif

#ifdef GOLD
  Controller1.ButtonL1.pressed(enableConveyor);
  Controller1.ButtonL2.pressed(reverseConveyor);
  Controller1.ButtonL2.released(stopConveyor);
  Controller1.Axis1.changed(updateDrivetrainVelocity);
  Controller1.Axis3.changed(updateDrivetrainVelocity);
  Controller1.Axis2.changed(manualWallstakeCtrl);
  Controller1.ButtonB.pressed(toggleDoinker);
  Controller1.ButtonL1.pressed(enableRingDetectOverride);
  Controller1.ButtonL2.pressed(enableRingDetectOverride);
  Controller1.ButtonLeft.pressed(throwBlue);
  Controller1.ButtonRight.pressed(throwRed);
  // Controller1.ButtonR1.pressed(scoreLB);
  // Controller1.ButtonR2.pressed(toggleMogo);
  Controller1.ButtonR1.pressed(enableMogo);
  Controller1.ButtonR2.pressed(disableMogo);
#ifdef LADY_BROWN
  Controller1.ButtonY.pressed(scoreLB);
#endif
  Controller1.ButtonA.pressed(loadRing);
#endif

  Competition.drivercontrol(usercontrol);
  Competition.autonomous(autonomous);
  pre_auton();
}
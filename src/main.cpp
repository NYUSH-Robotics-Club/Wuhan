#include "vex.h"

// What I changed since the last version of code:

// Changes in code since last time:

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

using namespace vex;
competition Competition;

motor_group leftDriveMotors = motor_group(L1, L2, L3);
motor_group rightDriveMotors = motor_group(R1, R2, R3);

float ringColor;

bool wallStakeFeedFwdDis, isRed, ringSortDisable = true, ringDetectOverride;

Drive chassis(
    ZERO_TRACKER_NO_ODOM,
    leftDriveMotors,
    rightDriveMotors,
    //inertial port
    PORT14,
    3.25,
    0.75,
    360, 

    PORT1, -PORT2,
    PORT3, -PORT4,
    3,
    2.75,
    -2,
    1,
    -2.75,
    5.5

);

motor_group intakeMain = motor_group(roller, conveyor);
motor_group admMain = motor_group(L1, R1, L2, R2, L3, R3);
// motor wallStake = motor(PORT1, ratio18_1, false);

int current_auton_selection = 0, conveyorPosition;
bool auto_started = false;

void pre_auton(void) {
  // Initializing Robot Configuration. DO NOT REMOVE!
  vexcodeInit();
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
    redAuto();
    break;
  case 1:
    isRed = false;
    wallStakeFeedFwdDis = true;
    ringSortDisable = false;
    blueAuto();

    break;
  case 2:
    AWP_Plus_One();
    break;
  case 3:
    Prog_Skills();
      isRed = true;
      ringSortDisable = false;

    break;
  case 4:
    odom_test();
    break;
  case 5:
    safe_worlds_auton();
    break;
  case 6:
    worlds_auton();
    break;
  }
}

/*---------------------------------------------------------------------------*/
/*                                                                           */
/*                              User Control Task                            */
/*                                                                           */
/*  This task is used to control your robot during the user control phase of */
/*  a VEX Competition.                                                       */
/*                                                                           */
/*  You must modify the code to add your own robot specific commands here.   */
/*---------------------------------------------------------------------------*/



int whenStarted1() {
  // Zero wallStake
  wallStake.setStopping(hold);
  wallStakeFeedFwdDis = false;
  wallStake.setVelocity(80, rpm);
  while (!(wallStake.current(amp) > 1.4)) {
    wallStake.spin(reverse);
    wait(10, msec);
  }
  wallStake.setPosition(0, degrees);
  wallStake.stop();
  // Set drive motor stopping to coast
  admMain.setStopping(coast);

  colorDetect.setLight(ledState::on);
  colorDetect.setLightPower(100, percent);
  wallStake.setVelocity(100, percent);

  return 0;
}


//**RING SORTING**
void colorSort() {
   
   //ANTI-JAM ANTIJAM ANTI JAM
   while(1){
      wait(10, msec);
  
      if((conveyor.velocity(rpm) == 0) && (conveyor.current(amp) > 2.1)) {
      conveyor.spin(reverse, 12, volt);
      wait(.2, seconds);
      conveyor.spin(forward, 9, volt);
      wait(.2, seconds);
    }


  //print distance away on brain screen
  Brain.Screen.setCursor(1, 30);
  Brain.Screen.print(ringDist.objectDistance(inches));

  if (ringDist.objectDistance(inches) > 1.5 || ringSortDisable) continue;

    //print ringColor on controller screen (removed bc printing to controller screen takes 200ms)
    ringColor = colorDetect.hue();
    // Controller1.Screen.setCursor(3, 14);
    // Controller1.Screen.print(ringColor);

    conveyorPosition = conveyor.position(degrees);
    
    if(!isRed && (ringColor > 360 || 20 > ringColor)) {
      //wait(.09, sec);
      //printf("Launching red\n");
      conveyor.spin(forward, 12, volt);
      waitUntil(conveyor.position(degrees) > conveyorPosition + 250);
      //wait(10 * conveyor.current(amp), msec);
      conveyor.spin(reverse, 12 ,volt);
      wait(.2, sec);
      conveyor.spin(forward, 9, volt);
      Controller1.rumble("..");
      wait(200, msec);
    }
    else if (isRed && (ringColor > 180 && 260 > ringColor)) {
      //wait(.09, sec);
      //printf("Launching blue\n");
      conveyor.spin(forward, 12, volt);
      waitUntil(conveyor.position(degrees) > conveyorPosition + 250);
      //wait(10 * conveyor.current(amp), msec);
      conveyor.spin(reverse, 12 ,volt);
      wait(.2, sec);
      conveyor.spin(forward, 9, volt);
      Controller1.rumble(".");
      wait(200, msec);
    }

    // Controller1.Screen.setCursor(3, 14);
    // Controller1.Screen.print(ringColor);
    
  }
}


void wallStakeAutoHold() {
  colorDetect.setLight(ledState::on);
  colorDetect.setLightPower(100, percent);
  wallStake.setVelocity(100, percent);
  // Zero wallStake
  wallStake.setStopping(hold);
  wallStakeFeedFwdDis = false;
  wallStake.setVelocity(80, rpm);
  while (!(wallStake.current(amp) > 1.4)) {
    wallStake.spin(reverse);
    wait(10, msec);
  }
  wallStake.setPosition(0, degrees);
  wallStake.stop();
  // Set drive motor stopping to coast
  admMain.setStopping(coast);
  
  while (1) {
    Brain.Screen.setCursor(1, 1);
    Brain.Screen.print(wallStake.position(degrees));
    Brain.Screen.print("   ");

    if (!wallStakeFeedFwdDis && wallStake.position(degrees) < 100) {
      wallStake.spin(reverse, 1, volt);
    }

    wait(20, msec);
  }
}

void usercontrol(void) {
  ringSortDisable = true;
  admMain.setStopping(coast);
}

void updateDrivetrainVelocity() {
  int leftVelocity =
      (Controller1.Axis3.position() + (Controller1.Axis1.position() / 1)) * 120;
  int rightVelocity =
      (Controller1.Axis3.position() - (Controller1.Axis1.position() / 1)) * 120;

  motor_group(L1, L2, L3)
      .spin(vex::forward, leftVelocity, vex::voltageUnits::mV);
  motor_group(R1, R2, R3)
      .spin(vex::forward, rightVelocity, vex::voltageUnits::mV);
}

// intake control
void onevent_Controller1ButtonL1_pressed_0() {
  //intakeMain.spin(forward, 9, volt);
  conveyor.spin(fwd, 9, volt);
  roller.spin(fwd, 12, volt);
}

void onevent_Controller1ButtonL2_pressed_0() {
  intakeMain.spin(reverse, 12, volt);
}

void onevent_Controller1ButtonL2_released_0() { intakeMain.stop(); }

void toggleDoinker() { doinker.set(!doinker.value()); }

void onR2Pressed() { mogoMech.set(true); }

void onR1Pressed() {
  mogoMech.set(false);
  conveyor.spinFor(reverse, 100, degrees);
}

void onYPressed() {
  wallStakeFeedFwdDis = true;
  wallStake.setVelocity(100, percent);
  wallStake.spinToPosition(210, degrees, true);
  wait(0.2, seconds);
  wallStake.spinToPosition(-5, degrees, true);
  wallStakeFeedFwdDis = false;
}

void onRightPressed() {
  ringSortDisable = false;
  isRed = false;
  Controller1.Screen.setCursor(3, 1);
  Controller1.Screen.print("chuck red ");
}

void onLeftPressed() {

  ringSortDisable = false;
  isRed = true;
  Controller1.Screen.setCursor(3, 1);
  Controller1.Screen.print("chuck blue");
}

void onAPressed() {
  ringDetectOverride = false;
  Controller1.rumble("-");
  while (!(((ringDist.objectDistance(inches) < 2.5) && colorDetect.isNearObject()) || ringDetectOverride)) {
    roller.spin(forward, 12, volt);
    conveyor.spin(forward, 9, volt);
    wait(10, msec);
  }

  
  if (!ringDetectOverride) {
    intakeMain.stop();
    conveyor.stop();
  }
  roller.spin(fwd, 8, volt);
}

void enableRingDetectOverride() { ringDetectOverride = true; }

void onAxis2Changed() {
  int position = Controller1.Axis2.position();
  if (abs(position) < 50) {
    wallStake.stop(hold);
    wallStakeFeedFwdDis = false;
    return;
  }
  wallStakeFeedFwdDis = true;
  wallStake.spin(fwd, position * 0.12, volt);
}

//void autonomousRoutine() {
  // Code here
//}

int main() {
  thread colorSortThread = thread(colorSort);
  thread wsAutoHold = thread(wallStakeAutoHold);

  colorDetect.integrationTime(5);

  Controller1.ButtonL1.pressed(onevent_Controller1ButtonL1_pressed_0);
  Controller1.ButtonL2.pressed(onevent_Controller1ButtonL2_pressed_0);
  Controller1.ButtonL2.released(onevent_Controller1ButtonL2_released_0);
  Controller1.Axis1.changed(updateDrivetrainVelocity);
  Controller1.Axis3.changed(updateDrivetrainVelocity);
  Controller1.Axis2.changed(onAxis2Changed);
  Controller1.ButtonY.pressed(onYPressed);
  Controller1.ButtonB.pressed(toggleDoinker);
  Controller1.ButtonL1.pressed(enableRingDetectOverride);
  Controller1.ButtonL2.pressed(enableRingDetectOverride);
  Controller1.ButtonLeft.pressed(onLeftPressed);
  Controller1.ButtonRight.pressed(onRightPressed);
  Controller1.ButtonR1.pressed(onR1Pressed);
  Controller1.ButtonR2.pressed(onR2Pressed);
  Controller1.ButtonA.pressed(onAPressed);

  Competition.drivercontrol(usercontrol);
  Competition.autonomous(autonomous);
  pre_auton();
}
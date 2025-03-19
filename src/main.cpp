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

#define CONTROLLER_L_Y_AXIS Controller1.Axis3.position()
#define CONTROLLER_L_X_AXIS Controller1.Axis4.position()
#define CONTROLLER_R_Y_AXIS Controller1.Axis2.position()
#define CONTROLLER_R_X_AXIS Controller1.Axis1.position()

float ringColor;

bool wallStakeFeedFwdDis, isRed, ringSortDisable = true, ringDetectOverride;

#define is_on_red_alliance isRed
#define is_on_blue_alliance !isRed
#define DRIVE_SCALAR 120

motor_group conveyorAndRoller = motor_group(roller, conveyor);
motor_group all_drive_motors = motor_group(L1, R1, L2, R2, L3, R3);
// motor wallStake = motor(PORT1, ratio18_1, false);

int current_auton_selection = 0, conveyorPositionPrev;
bool auto_started = false;

//fn protos
bool has_red_ring();
bool has_blue_ring();



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
    } else if (current_auton_selection > 7) { // wrap
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

mutex wallStakeMutex = mutex();

int initialize() {
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
  all_drive_motors.setStopping(coast);

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
  
    if((conveyor.velocity(rpm) == 0) && (conveyor.current(amp) > 2.1)) { // dejamming
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
    //(it was a blocking routine)
    ringColor = colorDetect.hue(); //update ringcolor
    // Controller1.Screen.setCursor(3, 14);
    // Controller1.Screen.print(ringColor);
    
    conveyorPositionPrev = conveyor.position(degrees);
    
    if(is_on_blue_alliance && has_red_ring()) { // throw a red ring
      //wait(.09, sec);
      //printf("Launching red\n");
      conveyor.spin(forward, 12, volt);
      waitUntil(conveyor.position(degrees) > conveyorPositionPrev + 250);
      //wait(10 * conveyor.current(amp), msec);
      conveyor.spin(reverse, 12 ,volt);
      wait(.2, sec);
      conveyor.spin(forward, 9, volt);
      Controller1.rumble("..");
      wait(200, msec);
    }
    else if (is_on_red_alliance && has_blue_ring()) { // throw a blue ring
      //wait(.09, sec);
      //printf("Launching blue\n");
      conveyor.spin(forward, 12, volt);
      waitUntil(conveyor.position(degrees) > conveyorPositionPrev + 250);
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

bool has_red_ring() {
  ringColor = colorDetect.hue(); //TODO MAKE THIS CRGB
  return (ringColor > 360 || 20 > ringColor);
}

bool has_blue_ring() {
  ringColor = colorDetect.hue(); //TODO MAKE THIS CRGB
  return (ringColor > 180 && 260 > ringColor);
}

void wallStakeAutoHold() { //TODO RENAME
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
  all_drive_motors.setStopping(coast);
  
  while (1) { // TODO MUTEX
    wallStakeMutex.lock();
    Brain.Screen.setCursor(1, 1);
    Brain.Screen.print(wallStake.position(degrees));
    Brain.Screen.print("   ");

    if (!wallStakeFeedFwdDis && wallStake.position(degrees) < 100) {
      wallStake.spin(reverse, 1, volt);
    } else {
      
    }
    wallStakeMutex.unlock();

    wait(20, msec);
    
  }
}

void usercontrol(void) {
  ringSortDisable = true;
  all_drive_motors.setStopping(coast);
}

void updateDrivetrainVelocity() {
  int leftVelocity =
      (CONTROLLER_L_Y_AXIS + CONTROLLER_R_X_AXIS) * DRIVE_SCALAR;
  int rightVelocity =
      (CONTROLLER_L_Y_AXIS - CONTROLLER_R_X_AXIS) * DRIVE_SCALAR;

  motor_group(L1, L2, L3)
      .spin(vex::forward, leftVelocity, vex::voltageUnits::mV);
  motor_group(R1, R2, R3)
      .spin(vex::forward, rightVelocity, vex::voltageUnits::mV);
}

// intake control
void enableConveyor() {
  //conveyorAndRoller.spin(forward, 9, volt);
  conveyor.spin(fwd, 9, volt);
  roller.spin(fwd, 12, volt);
}

void reverseConveyor() {
  conveyorAndRoller.spin(reverse, 12, volt);
}

void disableConveyor() { conveyorAndRoller.stop(); }

void toggleDoinker() { doinker.set(!doinker.value()); }

void grabMogo() { mogoMech.set(true); }

void releaseMogo() {
  mogoMech.set(false);
  conveyor.spinFor(reverse, 100, degrees);
}

void scoreWallstake() { //TODO MUTEX
  wallStakeMutex.lock();
  
  wallStakeFeedFwdDis = true;
  wallStake.setVelocity(100, percent);
  wallStake.spinToPosition(210, degrees, true);
  
  wallStakeMutex.unlock();

  wait(0.2, seconds);

  wallStakeMutex.lock();
  
  wallStake.spinToPosition(-5, degrees, true);
  wallStakeFeedFwdDis = false;
  
  wallStakeMutex.unlock();
  
}

void switchToBlueAlliance() {
  ringSortDisable = false;
  isRed = false;
  Controller1.Screen.setCursor(3, 1);
  Controller1.Screen.print("chuck red");
}

void switchToRedAlliance() {

  ringSortDisable = false;
  isRed = true;
  Controller1.Screen.setCursor(3, 1);
  Controller1.Screen.print("chuck blue");
}

void loadRing() {
  ringDetectOverride = false;
  Controller1.rumble("-");
  while (!(((ringDist.objectDistance(inches) < 2.0)) || ringDetectOverride)) {
    roller.spin(forward, 12, volt);
    conveyor.spin(forward, 9, volt);
    wait(10, msec);
  }

  
  if (!ringDetectOverride) {
    conveyorAndRoller.stop();
    conveyor.stop();
  }
  roller.spin(fwd, 8, volt);
}

void enableRingDetectOverride() { ringDetectOverride = true; }

void manualWallstake() { //TODO MUTEX
  wallStakeMutex.lock();
  int position = CONTROLLER_R_Y_AXIS;
  if (abs(position) < 50) {
    wallStake.stop(hold);
    wallStakeFeedFwdDis = false;
    return;
  } else {
    wallStakeMutex.unlock();
  }
  wallStakeFeedFwdDis = true;
  wallStake.spin(fwd, position * 0.12, volt);
}

//void autonomousRoutine() {
  // Code here
//}

int main() {
  initialize();
  thread colorSortThread = thread(colorSort);
  thread wsAutoHold = thread(wallStakeAutoHold);

  colorDetect.integrationTime(5);

  Controller1.ButtonL1.pressed(enableConveyor);
  Controller1.ButtonL2.pressed(reverseConveyor);
  Controller1.ButtonL2.released(disableConveyor);
  Controller1.Axis1.changed(updateDrivetrainVelocity);
  Controller1.Axis3.changed(updateDrivetrainVelocity);
  Controller1.Axis2.changed(manualWallstake);
  Controller1.ButtonY.pressed(scoreWallstake);
  Controller1.ButtonB.pressed(toggleDoinker);
  Controller1.ButtonL1.pressed(enableRingDetectOverride);
  Controller1.ButtonL2.pressed(enableRingDetectOverride);
  Controller1.ButtonLeft.pressed(switchToRedAlliance);
  Controller1.ButtonRight.pressed(switchToBlueAlliance);
  Controller1.ButtonR1.pressed(releaseMogo);
  Controller1.ButtonR2.pressed(grabMogo);
  Controller1.ButtonA.pressed(loadRing);

  Competition.drivercontrol(usercontrol);
  Competition.autonomous(autonomous);
  pre_auton();

  // Prevent main from exiting with an infinite loop.
  while (true) {
    wait(100, msec);
  }

}
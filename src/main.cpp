#include "vex.h"
#include "robot_type.h"
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

using namespace vex;
competition Competition;



float ringColor;

bool wallStakeFeedFwdDis, isRed, ringSortDisable = true, ringDetectOverride, antijamDisable = true;

thread wsThread;

#define LOADING 1
#define PRESCORING 2
#define SCORING 3
///*

motor_group leftDriveMotors = motor_group(L1, L2, L3);
motor_group rightDriveMotors = motor_group(R1, R2, R3);

Drive chassis(
    ZERO_TRACKER_NO_ODOM,
    leftDriveMotors,
    rightDriveMotors,
    PORT14, //inertial port
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
//*/

motor_group intakeMain = motor_group(roller, conveyor);
motor_group admMain = motor_group(L1, R1, L2, R2, L3, R3);
// motor wallStake = motor(PORT1, ratio18_1, false);

int current_auton_selection = 0, conveyorPosition, wallStakeState = 0;
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


//**RING SORTING**
void colorSort() {
   
  //  ANTI-JAM ANTIJAM ANTI JAM
  //  while(!antijamDisable){
  //     wait(10, msec);

  //     if((conveyor.velocity(rpm) == 0) && (conveyor.current(amp) > 2.1)) {
  //     conveyor.spin(reverse, 12, volt);
  //     wait(.2, seconds);
  //     conveyor.spin(forward, 9, volt);
  //     wait(.2, seconds);
  //   }
  while(1){
    wait(10, msec);
  
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
      waitUntil(conveyor.position(degrees) > conveyorPosition + 100);
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
      waitUntil(conveyor.position(degrees) > conveyorPosition + 100);
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
  wallStake.setStopping(hold);
  wallStakeFeedFwdDis = false;
  // Set drive motor stopping to coast
  admMain.setStopping(coast);
  
  while (1) {
    Brain.Screen.setCursor(1, 1);
    Brain.Screen.print(wallStake.position(degrees));
    Brain.Screen.print("   ");
    if(Controller1.ButtonDown.pressing()){
      wallStake.setPosition(0, degrees);
    }

    // if (!wallStakeFeedFwdDis && wallStake.position(degrees) < 100) {
    //   wallStake.spin(reverse, 1, volt);
    // }

    wait(20, msec);
  }
}

void usercontrol(void) {
  ringSortDisable = true;
  antijamDisable = true;
  admMain.setStopping(coast);
}

void updateDrivetrainVelocity() {
  /*
  int leftVelocity =
      (Controller1.Axis3.position() + (Controller1.Axis1.position() / 1)) * 120;
  int rightVelocity =
      (Controller1.Axis3.position() - (Controller1.Axis1.position() / 1)) * 120;

  */

  chassis.control_arcade();
  
  
  /*
  motor_group(L1, L2, L3)
      .spin(vex::forward, leftVelocity, vex::voltageUnits::mV);
  motor_group(R1, R2, R3)
      .spin(vex::forward, rightVelocity, vex::voltageUnits::mV);
      */
}

// intake control
void enableConveyor() {
  //intakeMain.spin(forward, 9, volt);
  conveyor.spin(fwd, 9, volt);
  roller.spin(fwd, 12, volt);
}

void reverseConveyor() {
  intakeMain.spin(reverse, 12, volt);
}

void stopConveyor() { intakeMain.stop(); }

void toggleDoinker() { doinker.set(!doinker.value()); }

void toggleMogo()
{ 
  mogoMech.set(!mogoMech.value()); 
}

void wsSpinToPosition(int position, double kP, double kD, double tolerance)
{  
  // double kP = 200;
  // double kD = 1000;

  rotationWallStake.resetPosition();

  double startPos = rotationWallStake.position(deg);
  double target = startPos + position;

  double error = target - rotationWallStake.position(deg);
  double lastError = 0;

  while(fabs(error) > tolerance)
  {
    error = target - rotationWallStake.position(deg);
    wallStake.spin(fwd, (error * kP) + ((error - lastError) * kD), vex::voltageUnits::mV);
    lastError = error;
    wait(10, msec);
  }

  wallStake.stop(hold);
}

int wsState = 0;

void scoreLB() {
  wsState = ++wsState & 3;

  wsThread.interrupt();

  
  if (wsState == LOADING)
  {
    wsThread = thread([](){
      wsSpinToPosition(21, 200, 0, 1);
      waitUntil(conveyor.current(amp) > 2.3 && conveyor.velocity(rpm) < 2);
      conveyor.spin(fwd, 2, volt);
      wallStake.stop(coast);
    });
  
    roller.spin(fwd, 12, volt);
    conveyor.spin(fwd, 9, volt);
  } else if (wsState == PRESCORING)
  {
    wsThread = thread([](){
      conveyor.spin(reverse, 4, volt);
      wsSpinToPosition(100, 250, 0, 3);
      conveyor.stop();
      if (Controller1.ButtonY.pressing())
      {
        wsSpinToPosition(90, 200, 0, 2);
        wallStake.spin(reverse, 12, volt);
        wait(500, msec);
        wallStake.stop(coast);
        wsState = 0;
      }
      
    });
  } else if (wsState == SCORING)
  {
    wsThread = thread([](){
      wsState = 0;
      wsSpinToPosition(55, 200, 0, 5);
      wallStake.spin(reverse, 12, volt);
      wait(400, msec);
      wallStake.stop(coast);
    });
    
  }
  
  antijamDisable = false;
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

void loadRing() {
  ringDetectOverride = false;
  Controller1.rumble("-");
  while (!(((ringDist.objectDistance(inches) < 2)) || ringDetectOverride)) {
    roller.spin(forward, 12, volt);
    conveyor.spin(forward, 7, volt);
    wait(10, msec);
  }

  
  if (!ringDetectOverride) {
    intakeMain.stop();
    conveyor.stop();
  }
  roller.spin(fwd, 8, volt);
}

void enableRingDetectOverride() { ringDetectOverride = true; }

void manualWallstakeCtrl() {
  int position = Controller1.Axis2.position();
  if (abs(position) < 50) {
    wallStakeFeedFwdDis = false;
    wallStake.stop(brake);
    return;
  }
  wsThread.interrupt();
  wsState = 0;
  conveyor.stop();
  wallStakeFeedFwdDis = true;
  wallStake.spin(fwd, position * 0.12, volt);
}

void enableMogo(){
  mogoMech.set(true);
}
void disableMogo(){
  mogoMech.set(false);
}


//void autonomousRoutine() {
  // Code here
//}

int main() {
  //vexcodeInit();
  thread colorSortThread = thread(colorSort);
  thread wsAutoHold = thread(wallStakeAutoHold);

  rotationWallStake.setPosition(0, degrees);

  colorDetect.integrationTime(5);
  
  #ifdef GREEN
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
  Controller1.ButtonR1.pressed(scoreLB);
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
  //Controller1.ButtonR1.pressed(scoreLB);
  //Controller1.ButtonR2.pressed(toggleMogo);
  Controller1.ButtonR1.pressed(enableMogo);
  Controller1.ButtonR2.pressed(disableMogo);
  Controller1.ButtonY.pressed(scoreLB);
  Controller1.ButtonA.pressed(loadRing);
  #endif

  Competition.drivercontrol(usercontrol);
  Competition.autonomous(autonomous);
  pre_auton();
}
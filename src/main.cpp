#include "vex.h"
#include "main.h"
#include "robot-config.h"

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

#define DEBUG_ODOM

//#define ENABLE_DRIVE

using namespace vex;
competition Competition;

motor_group leftDriveMotors = motor_group(L1, L2, L3);
motor_group rightDriveMotors = motor_group(R1, R2, R3);
motor_group wallStakeMain = motor_group(wallStake1, wallStake2);


float ringColor;

bool wallStakeFeedFwdDis, isRed = true, ringSortDisable = false, ringDetectOverride, antijamDisable = true;

thread wsThread;

#define LOADING 1
#define PRESCORING 2
#define SCORING 3

// Note: Updated green ports since they were wrong, I think gold is wrong too but not 100% sure
#ifdef GOLD
#define VERT PORT5
#define HORI PORT6
#define INERTIAL PORT21
#define RING_SORT_DELAY 40
#endif

#ifdef GREEN
#define VERT PORT6
#define HORI PORT8
#define INERTIAL PORT9
#define RING_SORT_DELAY 200
#endif


Drive chassis(

  //Pick your drive setup from the list below:
  //ZERO_TRACKER_NO_ODOM
  //ZERO_TRACKER_ODOM
  //TANK_ONE_FORWARD_ENCODER
  //TANK_ONE_FORWARD_ROTATION
  //TANK_ONE_SIDEWAYS_ENCODER
  //TANK_ONE_SIDEWAYS_ROTATION
  //TANK_TWO_ENCODER
  //TANK_TWO_ROTATION
  //HOLONOMIC_TWO_ENCODER
  //HOLONOMIC_TWO_ROTATION
  //
  //Write it here:
  TANK_TWO_ROTATION,
  
  //Add the names of your Drive motors into the motor groups below, separated by commas, i.e. motor_group(Motor1,Motor2,Motor3).
  //You will input whatever motor names you chose when you configured your robot using the sidebar configurer, they don't have to be "Motor1" and "Motor2".
  
  //Left Motors:
  leftDriveMotors,
  
  //Right Motors:
  rightDriveMotors,
  
  //Specify the PORT NUMBER of your inertial sensor, in PORT format (i.e. "PORT1", not simply "1"):
  INERTIAL,
  
  //Input your wheel diameter. (4" omnis are actually closer to 4.125"):
  2.75,
  
  //External ratio, must be in decimal, in the format of input teeth/output teeth.
  //If your motor has an 84-tooth gear and your wheel has a 60-tooth gear, this value will be 1.4.
  //If the motor drives the wheel directly, this value is 1:
  (float) (0.94736842),
  
  //Gyro scale, this is what your gyro reads when you spin the robot 360 degrees.
  //For most cases 360 will do fine here, but this scale factor can be very helpful when precision is necessary.
  360,
  
  /*---------------------------------------------------------------------------*/
  /*                                  PAUSE!                                   */
  /*                                                                           */
  /*  The rest of the drive constructor is for robots using POSITION TRACKING. */
  /*  If you are not using position tracking, leave the rest of the values as  */
  /*  they are.                                                                */
  /*---------------------------------------------------------------------------*/
  
  //If you are using ZERO_TRACKER_ODOM, you ONLY need to adjust the FORWARD TRACKER CENTER DISTANCE.
  
  //FOR HOLONOMIC DRIVES ONLY: Input your drive motors by position. This is only necessary for holonomic drives, otherwise this section can be left alone.
  //LF:      //RF:    
  PORT22,     PORT22,
  
  //LB:      //RB: 
  PORT22,     PORT22,
  
  //If you are using position tracking, this is the Forward Tracker port (the tracker which runs parallel to the direction of the chassis).
  //If this is a rotation sensor, enter it in "PORT1" format, inputting the port below.
  //If this is an encoder, enter the port as an integer. Triport A will be a "1", Triport B will be a "2", etc.
  VERT,
  
  //Input the Forward Tracker diameter (reverse it to make the direction switch):
  #ifdef GREEN
  -2.0259270425f,
  #endif
  #ifdef GOLD
  -2.038463892801825f,
  #endif
  //Input Forward Tracker center distance (a positive distance corresponds to a tracker on the right side of the robot, negative is left.)
  //For a zero tracker tank drive with odom, put the positive distance from the center of the robot to the right side of the drive.
  //This distance is in inches:
  0.0,
  
  //Input the Sideways Tracker Port, following the same steps as the Forward Tracker Port:
  HORI,
  
  //Sideways tracker diameter (reverse to make the direction switch):
  
  #ifdef GREEN
  2.008662356412027f,
  #endif
  #ifdef GOLD
  -2.0063045333426217f,
  #endif
  //Sideways tracker center distance (positive distance is behind the center of the robot, negative is in front):
  0.0
  
  );

motor_group intakeMain = motor_group(roller, conveyor);
motor_group admMain = motor_group(L1, R1, L2, R2, L3, R3, L4, R4);
// motor wallStake = motor(PORT1, ratio18_1, false);

int current_auton_selection = 0;
int conveyorPosition, wallStakeState = 0;
bool auto_started = false;

void pre_auton(void) {
  // Initializing Robot Configuration. DO NOT REMOVE!
  vexcodeInit();

  odom_constants();
  
  //chassis.set_drive_constants(5.5, 1.5, 0, 10, 0);
}

void autonomous(void) {

  auto_started = true;
  switch (current_auton_selection) {
  case 0:
    isRed = true;
    ringSortDisable = false;
    wallStakeFeedFwdDis = true;


    chassis.set_coordinates(24, -48, 0);
    redGreenAutonCenter();
    break;
  case 1:
    isRed = true;
    ringSortDisable = false;
    wallStakeFeedFwdDis = true;
    
    redGreenAutonOther();
    break;
  case 2:
    isRed = true;
    ringSortDisable = false;
    wallStakeFeedFwdDis = true;
    
    redGoldAuton();
    break;
  case 3:
    isRed = false;
    wallStakeFeedFwdDis = true; // BLUE GREEN CENTER
    ringSortDisable = false;
    
    chassis.set_coordinates(24, -48, 0);
    blueGreenAutonCenter();
    break;
  case 4:
    isRed = false;
    wallStakeFeedFwdDis = true;
    ringSortDisable = false;
    
    blueGreenAutonOther();
    break;
  case 5:
    isRed = false;
    wallStakeFeedFwdDis = true;
    ringSortDisable = false;
    
    blueGoldAuton();
    break;
  case 6:
    odom_test();
    break;
  case 7:
    safe_worlds_auton();
    break;
  case 8:
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


//**RING SORTING**
void colorSort() {
  while (1) {
    wait(10, msec);

    // Print distance away on brain screen
    Brain.Screen.setCursor(1, 30);
    Brain.Screen.print(ringDist.objectDistance(inches));

    if (ringDist.objectDistance(inches) > 2.5 || ringSortDisable) continue;
    
    #ifdef GOLD
    wait(90, msec);
    #endif

    // Get ring color hue
    ringColor = colorDetect.hue();
    printf("hue = %.2f\n", ringColor);
    conveyorPosition = conveyor.position(degrees);

    printf("detected ring\n");
    if (!isRed && (ringColor > 360 || ringColor < 20)) {
      //Brain.Screen.printAt()
      printf("yeeting red\n");
      // Launch red ring
      conveyor.spin(forward, 12, volt);
      waitUntil(conveyor.position(degrees) > conveyorPosition + RING_SORT_DELAY);
      conveyor.spin(reverse, 12, volt);
      wait(0.2, sec);
      conveyor.spin(forward, 12, volt);
      Controller1.rumble("..");
      wait(200, msec);
    } else if (isRed && (ringColor > 180 && ringColor < 260)) {
      printf("yeeting blue\n");
      // Launch blue ring
      conveyor.spin(forward, 12, volt);
      waitUntil(conveyor.position(degrees) > conveyorPosition + RING_SORT_DELAY);
      conveyor.spin(reverse, 12, volt);
      wait(0.2, sec);
      conveyor.spin(forward, 12, volt);
      Controller1.rumble(".");
      wait(200, msec);
    }
  }
}



void wallStakeAutoHold() {
  
  wallStakeMain.setVelocity(100, percent);
  wallStakeMain.setStopping(hold);
  wallStakeFeedFwdDis = false;
  // Set drive motor stopping to coast
  admMain.setStopping(coast);
  
  while (1) {
    Brain.Screen.setCursor(1, 1);
    Brain.Screen.print(wallStakeMain.position(degrees));
    Brain.Screen.print("   ");
    if(Controller1.ButtonDown.pressing()){
      wallStakeMain.setPosition(0, degrees);
    }

    // if (!wallStakeFeedFwdDis && wallStake.position(degrees) < 100) {
    //   wallStake.spin(reverse, 1, volt);
    // }

    wait(200, msec);
  }
}

void usercontrol(void) {
  //ringSortDisable = true;
  antijamDisable = true;
  admMain.setStopping(coast);
  
}


// intake control
void onevent_Controller1ButtonL1_pressed_0() {
  //intakeMain.spin(forward, 9, volt);
  conveyor.spin(fwd, 12, volt);
  roller.spin(fwd, 12, volt);
}

void onevent_Controller1ButtonL2_pressed_0() {
  intakeMain.spin(reverse, 12, volt);
}

void onevent_Controller1ButtonL2_released_0() { intakeMain.stop(); }

void toggleDoinker() { doinker_right.set(!doinker_right.value()); }

void onR2Pressed()
//add later**** Make controller rumble once when clamped, rumble twice when released******
{ 
  // mogoMech.set(!mogoMech.value());
  bool newState = !mogoMech.value();
  if (mogoMech.value() == true) {
    Controller1.rumble("..");
  }

  mogoMech.set(newState);
}

void onRightPressed()
{
  
  tipper.set(!tipper.value());
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
    wallStakeMain.spin(fwd, (error * kP) + ((error - lastError) * kD), vex::voltageUnits::mV);
    lastError = error;
    wait(10, msec);
  }

  wallStakeMain.stop(hold);
}

int wsState = 0;

void onR1Pressed() {
  wsState = ++wsState & 3;

  wsThread.interrupt();

  
  if (wsState == LOADING)
  {
    wsThread = thread([](){
      wsSpinToPosition(14, 300, 0, 1);
      waitUntil(conveyor.current(amp) > 2.1 && conveyor.velocity(rpm) < 2);
      conveyor.spin(fwd, 2, volt);
      wallStakeMain.stop(coast);
    });
  
    roller.spin(fwd, 12, volt);
    conveyor.spin(fwd, 12, volt);
  } else if (wsState == PRESCORING)
  {
    wsThread = thread([](){
      conveyor.spin(reverse, 4, volt);
      wsSpinToPosition(68, 250, 0, 3);
      conveyor.stop();
      if (Controller1.ButtonY.pressing())
      {
        wsSpinToPosition(59, 200, 0, 2);
        wallStakeMain.spin(reverse, 12, volt);
        wait(500, msec);
        wallStakeMain.stop(coast);
        wsState = 0;
      }
      
    });
  } else if (wsState == SCORING)
  {
    wsThread = thread([](){
      wsState = 0;
      wsSpinToPosition(60, 200, 0, 5);
      wallStakeMain.spin(reverse, 12, volt);
      wait(400, msec);
      wallStakeMain.stop(coast);
    });
    
  }
  
  antijamDisable = false;
}

void onUpPressed() {
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
  while (!((ringDist.objectDistance(inches) < 2.5) || ringDetectOverride)) {
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


void onDownPressed() {
  doinker_left.set(!doinker_left.value());
}

void enableRingDetectOverride() { ringDetectOverride = true; }

void onAxis2Changed() {
  int position = Controller1.Axis2.position();
  if (abs(position) < 50) {
    wallStakeFeedFwdDis = false;
    wallStake1.stop(brake);
    wallStake2.stop(hold);
    return;
  }
  wsThread.interrupt();
  wsState = 0;
  conveyor.stop();
  wallStakeFeedFwdDis = true;
  wallStakeMain.spin(fwd, position * 0.12, volt);
}



int main() {
  //leftDriveMotors.setStopping(vex::coast);
  //rightDriveMotors.setStopping(vex::coast);
  
  thread colorSortThread = thread(colorSort);
  thread wsAutoHold = thread(wallStakeAutoHold);
  
  //

  rotationWallStake.resetPosition();
  //default_constants();
  
  //wait(500, msec);

  #ifdef DEBUG_ODOM
    odom_constants();
    //default_constants();
    
    chassis.set_coordinates(24, -48, 0);

    //chassis.set_coordinates(0, 0, 0);
    //chassis.drive_timeout = 20000;
    //wait(100, msec); // let thread initialize
    
    
    //wait(100, msec); // let thread initialize
    thread odom_thread = thread([]() {
      float startingX = 22.6;
      float startingY = -50.85;
      float startingHeading = 20.2;

      while (1) {
        wait(200, msec);
        float xPos = chassis.get_X_position();
        float yPos = chassis.get_Y_position();
        float heading = chassis.get_absolute_heading();

        Brain.Screen.setCursor(5, 1);
        Brain.Screen.print("Y = %.2f, expected %.2f", yPos, startingY);
        Brain.Screen.setCursor(4, 1);
        Brain.Screen.print("X = %.2f, expected %.2f", xPos, startingX);
        Brain.Screen.setCursor(6, 1);
        Brain.Screen.print("H = %.2f, expected %.2f", heading, startingHeading);

        float xDiff = startingX - xPos;
        float yDiff = startingY - yPos;
        float headingDiff = startingHeading - heading;

        Brain.Screen.setCursor(7, 1);
        Brain.Screen.print("Y error: %.2f", yDiff);
        Brain.Screen.setCursor(8, 1);
        Brain.Screen.print("X error: %.2f", xDiff);
        Brain.Screen.setCursor(9, 1);
        Brain.Screen.print("Heading error: %.2f", headingDiff);

        Brain.Screen.setCursor(10, 1);

        if (xDiff < 0.5 && xDiff > -0.5 && yDiff < 0.5 && yDiff > -0.5) {
          Brain.Screen.print("Correct position");
        } else {
          Brain.Screen.print("Wrong position!");
        }

        // 22.6, -50.85, 20.2
        //Brain.Screen.setCursor(4, 1);
        //Brain.Screen.print("Chassis Position: X = %.2f, Y = %.2f, H = %.2f", chassis.get_X_position(), chassis.get_Y_position(), chassis.get_absolute_heading());
        
      }
    });
    wait(100, msec); // let thread initialize
    
    Controller1.ButtonX.pressed([] {
      isRed = false;
      ringSortDisable = true;
      admMain.setStopping(coast);
      blueGoldAuton();
    });
    // Controller1.ButtonX.pressed([] {
    //   chassis.turn_to_angle(chassis.get_absolute_heading() + 90);
    // });
    //chassis.turn_to_angle(90);
    /*
    Controller1.ButtonX.pressed([] {
      isRed = true;
      redGreenAutonCenter();
      admMain.setStopping(coast);
    });
    */
    //chassis.drive_max_voltage = 3.0;
    //chassis.turn_max_voltage = 2.0;
    //chassis.drive_to_point(0.0, 96.0);
    chassis.drive_stop(coast);
    //isRed = false;
  #endif


  Controller1.ButtonL1.pressed(onevent_Controller1ButtonL1_pressed_0);
  Controller1.ButtonL2.pressed(onevent_Controller1ButtonL2_pressed_0);
  Controller1.ButtonL2.released(onevent_Controller1ButtonL2_released_0);

  #ifdef ENABLE_DRIVE
  Controller1.Axis1.changed([] { 
    chassis.control_arcade();
  });
  Controller1.Axis3.changed([] { 
    chassis.control_arcade();
  });
  #endif

  Controller1.Axis2.changed(onAxis2Changed);
  Controller1.ButtonB.pressed(toggleDoinker);
  Controller1.ButtonL1.pressed(enableRingDetectOverride);
  Controller1.ButtonL2.pressed(enableRingDetectOverride);
  Controller1.ButtonLeft.pressed(onLeftPressed);
  //Controller1.ButtonRight.pressed(onRightPressed);
  Controller1.ButtonR1.pressed(onR1Pressed);
  Controller1.ButtonR2.pressed(onR2Pressed);
  Controller1.ButtonUp.pressed(onUpPressed);
  Controller1.ButtonRight.pressed(onRightPressed);
  Controller1.ButtonDown.pressed(onDownPressed);
  Controller1.ButtonA.pressed(onAPressed);

  #ifndef DEBUG_ODOM
    pre_auton();
  #endif
  
  Competition.drivercontrol(usercontrol);
  Competition.autonomous(autonomous);

  colorDetect.integrationTime(5);
  colorDetect.setLight(ledState::on);
  colorDetect.setLightPower(100, percent);
  
  
}
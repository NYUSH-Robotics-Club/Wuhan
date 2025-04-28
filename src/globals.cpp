#include "robot.h"
#include "vex.h"

using signature = vision::signature;
using code = vision::code;

// A global instance of brain used for printing to the V5 Brain screen
brain Brain;

// VEXcode device constructors
controller Controller1(primary);

#ifdef GREEN

motor roller(PORT5, ratio6_1, true);
motor conveyor(PORT7, ratio6_1, true);
motor wSMotor1(PORT17, ratio36_1, true);
motor wSMotor2(PORT16, ratio36_1, false);
motor L1(PORT1, ratio6_1, true);
motor L2(PORT2, ratio6_1, false);
motor L3(PORT4, ratio6_1, false);
motor L4(PORT20, ratio6_1, true);
motor R1(PORT11, ratio6_1, false);
motor R2(PORT12, ratio6_1, true);
motor R3(PORT13, ratio6_1, false);
motor R4(PORT14, ratio6_1, true);

rotation rotationWallStake(PORT15); //reverse
// rotation verticalTraker = rotation(PORT6); //reverse
// rotation horizontalTraker = rotation(PORT8); 



// vex::motor_group leftDriveMotors = motor_group(L1,L2,L3);
// vex::motor_group rightDriveMotors = motor_group(R1,R2,R3);
// vex::motor_group allDriveMotors = motor_group(L1, R1, L2, R2, L3, R3);

distance ringDist(PORT18);
optical colorDetect(PORT19);
inertial inertialSensor(PORT9);
digital_out mogoPort(Brain.ThreeWirePort.B);
digital_out doinkerPort(Brain.ThreeWirePort.C);
digital_out tipper(Brain.ThreeWirePort.D);

//digital_out ringChuck = digital_out(Brain.ThreeWirePort.D); //not used
//digital_in ringSwitch = digital_in(Brain.ThreeWirePort.H);//not used

#define HORIZ_TRACKER PORT6
#define VERT_TRACKER PORT5

#endif

#ifdef GOLD
motor roller(PORT20, ratio6_1, true);

motor conveyor(PORT18, ratio6_1, true);
motor wallStake1(PORT11, ratio36_1, true);
motor wallStake2(PORT12, ratio36_1, false);

motor L1(PORT7, ratio6_1, false);
motor L2(PORT8, ratio6_1, true);
motor L3(PORT9, ratio6_1, false);
motor L4(PORT10, ratio6_1, true);

motor R1(PORT1, ratio6_1, false);
motor R2(PORT2, ratio6_1, false);
motor R3(PORT3, ratio6_1, true);
motor R4(PORT4, ratio6_1, true);

optical colorDetect(PORT16);
distance ringDist(PORT17);

inertial inertialSensor(PORT21);
rotation rotationWallStake(PORT15);

digital_in ringSwitch(Brain.ThreeWirePort.E);//not used
digital_out ringChuck(Brain.ThreeWirePort.C); //not used

digital_out doinkerPort(Brain.ThreeWirePort.B);
digital_out mogoPort(Brain.ThreeWirePort.D);

digital_out tipper(Brain.ThreeWirePort.A);

#define HORIZ_TRACKER PORT8
#define VERT_TRACKER PORT6


//digital_out tipper = digital_out(Brain.ThreeWirePort.D);

#endif

motor_group leftDriveMotors(L1, L2, L3, L4);
motor_group rightDriveMotors(R1, R2, R3, R4);
motor_group allDriveMotors(L1, R1, L2, R2, L3, R3, L4, R4);
motor_group intakeMotors(roller, conveyor);



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
  PORT21,
  
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
  PORT16,     PORT16,
  
  //LB:      //RB: 
  PORT16,     PORT16,
  
  //If you are using position tracking, this is the Forward Tracker port (the tracker which runs parallel to the direction of the chassis).
  //If this is a rotation sensor, enter it in "PORT1" format, inputting the port below.
  //If this is an encoder, enter the port as an integer. Triport A will be a "1", Triport B will be a "2", etc.
  VERT_TRACKER,
  
  //Input the Forward Tracker diameter (reverse it to make the direction switch):
  -2.00,
  
  //Input Forward Tracker center distance (a positive distance corresponds to a tracker on the right side of the robot, negative is left.)
  //For a zero tracker tank drive with odom, put the positive distance from the center of the robot to the right side of the drive.
  //This distance is in inches:
  0.0,
  
  //Input the Sideways Tracker Port, following the same steps as the Forward Tracker Port:
  HORIZ_TRACKER,
  
  //Sideways tracker diameter (reverse to make the direction switch):
  2.0,
  
  //Sideways tracker center distance (positive distance is behind the center of the robot, negative is in front):
  -0.75
  
  );

Doinker doinker(&doinkerPort);
Mogo mogo(&mogoPort);

motor_group wallStake(wSMotor1, wSMotor2);

bool isRed = true;

bool ringSortDisable = true;
bool ringDetectOverride = false;
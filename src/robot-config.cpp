#include "vex.h"

using namespace vex;
using signature = vision::signature;
using code = vision::code;

// A global instance of brain used for printing to the V5 Brain screen
brain  Brain;

// VEXcode device constructors
controller Controller1 = controller(primary);

#ifdef GREEN
// Drive motors - updated to match Python code configuration
motor L1 = motor(PORT1, ratio6_1, false);  // motor1
motor L2 = motor(PORT2, ratio6_1, true);   // motor2
motor L3 = motor(PORT3, ratio6_1, false);  // motor3
motor L4 = motor(PORT4, ratio6_1, true);   // motor4
motor R1 = motor(PORT5, ratio6_1, true);   // motor5
motor R2 = motor(PORT6, ratio6_1, false);  // motor6
motor R3 = motor(PORT7, ratio6_1, true);   // motor7
motor R4 = motor(PORT8, ratio6_1, false);  // motor8

// Intake system - updated to match Python code
motor roller = motor(PORT11, ratio18_1, true);    // roller
motor conveyor = motor(PORT12, ratio18_1, true);  // conveyor

// Wall stake system - updated to match Python code
motor wallStake1 = motor(PORT13, ratio36_1, true);   // wall_stake_left
motor wallStake2 = motor(PORT14, ratio36_1, false);  // wall_stake_right
rotation rotationWallStake = rotation(PORT15);       // wall_stake_rotation

// Digital outputs - updated to match Python DigitalOutDevice ports
digital_out mogoMech = digital_out(Brain.ThreeWirePort.H);     // mogo_mech
digital_out doinker_right = digital_out(Brain.ThreeWirePort.G); // arm_grip 
digital_out doinker_left = digital_out(Brain.ThreeWirePort.F);  // arm_extend
digital_out tipper = digital_out(Brain.ThreeWirePort.D);

digital_in doinkerSwitches = digital_in(Brain.ThreeWirePort.A);

// Sensors
distance ringDist = distance(PORT18);
optical colorDetect = optical(PORT19);
inertial inertialSensor = inertial(PORT21);

// Tracking wheels for odometry
rotation verticalTracker = rotation(PORT9);    // 垂直追踪轮（前后位移）
rotation horizontalTracker = rotation(PORT10);  // 水平追踪轮（左右位移）

// Unused devices
digital_out ringChuck = digital_out(Brain.ThreeWirePort.C); //not used
digital_in ringSwitch = digital_in(Brain.ThreeWirePort.E);//not used
#endif

#ifdef GOLD
motor roller = motor(PORT20, ratio6_1, true);
motor conveyor = motor(PORT18, ratio18_1, true);
motor wallStake1 = motor(PORT11, ratio36_1, true);
motor wallStake2 = motor(PORT12, ratio36_1, false);
motor L1 = motor(PORT7, ratio6_1, true);
motor L2 = motor(PORT8, ratio6_1, false);
motor L3 = motor(PORT6, ratio6_1, true);  // 移动到PORT6避免冲突
motor L4 = motor(PORT10, ratio6_1, false);
motor R1 = motor(PORT1, ratio6_1, false);
motor R2 = motor(PORT2, ratio6_1, true);
motor R3 = motor(PORT3, ratio6_1, false);
motor R4 = motor(PORT4, ratio6_1, true);

rotation rotationWallStake = rotation(PORT15); //reverse
// rotation verticalTraker = rotation(PORT6); //reverse
// rotation horizontalTraker = rotation(PORT8); 

// Tracking wheels for odometry
rotation horizontalTracker = rotation(PORT9);  // 水平追踪轮（左右位移）

// vex::motor_group leftDriveMotors = motor_group(L1,L2,L3);
// vex::motor_group rightDriveMotors = motor_group(R1,R2,R3);
// vex::motor_group allDriveMotors = motor_group(L1, R1, L2, R2, L3, R3);

distance ringDist = distance(PORT16);
optical colorDetect = optical(PORT19);
inertial inertialSensor = inertial(PORT21);

digital_out doinker_left = digital_out(Brain.ThreeWirePort.D);

digital_out mogoMech = digital_out(Brain.ThreeWirePort.B);
digital_out doinker_right = digital_out(Brain.ThreeWirePort.C);
digital_out tipper = digital_out(Brain.ThreeWirePort.A);

digital_in doinkerSwitches = digital_in(Brain.ThreeWirePort.H); // DEFAULT HIGH

digital_out ringChuck = digital_out(Brain.ThreeWirePort.C); //not used
digital_in ringSwitch = digital_in(Brain.ThreeWirePort.H);//not used
#endif



// VEXcode generated functions
// define variable for remote controller enable/disable
bool RemoteControlCodeEnabled = true;

/**
 * Used to initialize code/tasks/devices added using tools in VEXcode Pro.
 * 
 * This should be called at the start of your int main function.
 */
void vexcodeInit( void ) {
  // nothing to initialize
}
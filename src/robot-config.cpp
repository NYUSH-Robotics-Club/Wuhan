#include "vex.h"
#include "robot_type.h"

using namespace vex;
using signature = vision::signature;
using code = vision::code;

// A global instance of brain used for printing to the V5 Brain screen
brain  Brain;

// VEXcode device constructors
controller Controller1 = controller(primary);

#ifdef GREEN
motor roller = motor(PORT5, ratio6_1, true);
motor conveyor = motor(PORT4, ratio6_1, true);
motor wallStake = motor(PORT9, ratio36_1, true);
motor L1 = motor(PORT6, ratio6_1, true);
motor L2 = motor(PORT7, ratio6_1, false);
motor L3 = motor(PORT8, ratio6_1, true);
//motor L4 = motor(PORT5, ratio6_1, false);
motor R1 = motor(PORT1, ratio6_1, false);
motor R2 = motor(PORT2, ratio6_1, true);
motor R3 = motor(PORT13, ratio6_1, false);
//motor R4 = motor(PORT15, ratio6_1, true);

// vex::motor_group leftDriveMotors = motor_group(L1,L2,L3);
// vex::motor_group rightDriveMotors = motor_group(R1,R2,R3);
// vex::motor_group allDriveMotors = motor_group(L1, R1, L2, R2, L3, R3);

optical colorDetect = optical(PORT21);
distance ringDist = distance(PORT12);
inertial inertialSensor = inertial(PORT11);
digital_out mogoMech = digital_out(Brain.ThreeWirePort.D);
digital_out doinker = digital_out(Brain.ThreeWirePort.B);
digital_out ringChuck = digital_out(Brain.ThreeWirePort.C);
digital_in ringSwitch1 = digital_in(Brain.ThreeWirePort.E);
#endif



#ifdef GOLD
motor roller = motor(PORT5, ratio6_1, true);
motor conveyor = motor(PORT4, ratio6_1, true);
motor wallStake = motor(PORT9, ratio36_1, true);
motor L1 = motor(PORT6, ratio6_1, true);
motor L2 = motor(PORT7, ratio6_1, false);
motor L3 = motor(PORT8, ratio6_1, true);
//motor L4 = motor(PORT5, ratio6_1, false);
motor R1 = motor(PORT1, ratio6_1, false);
motor R2 = motor(PORT2, ratio6_1, true);
motor R3 = motor(PORT13, ratio6_1, false);
//motor R4 = motor(PORT15, ratio6_1, true);

// vex::motor_group leftDriveMotors = motor_group(L1,L2,L3);
// vex::motor_group rightDriveMotors = motor_group(R1,R2,R3);
// vex::motor_group allDriveMotors = motor_group(L1, R1, L2, R2, L3, R3);

optical colorDetect = optical(PORT21);
distance ringDist = distance(PORT12);
inertial inertialSensor = inertial(PORT11);
digital_out mogoMech = digital_out(Brain.ThreeWirePort.D);
digital_out doinker = digital_out(Brain.ThreeWirePort.B);
digital_out ringChuck = digital_out(Brain.ThreeWirePort.C);
digital_in ringSwitch1 = digital_in(Brain.ThreeWirePort.E);
#endif

motor_group leftDriveMotors = motor_group(L1, L2, L3);
motor_group rightDriveMotors = motor_group(R1, R2, R3);

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
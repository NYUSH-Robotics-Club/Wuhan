#include "vex.h"

using namespace vex;
using signature = vision::signature;
using code = vision::code;

// A global instance of brain used for printing to the V5 Brain screen
brain Brain;

// VEXcode device constructors
controller Controller1 = controller(primary);

#ifdef GREEN
motor roller = motor(PORT11, ratio6_1, true);
motor conveyor = motor(PORT12, ratio18_1, true);
motor wallStake1 = motor(PORT13, ratio36_1, true);
motor wallStake2 = motor(PORT14, ratio36_1, false);
motor L1 = motor(PORT1, ratio6_1, false);
motor L2 = motor(PORT2, ratio6_1, true);
motor L3 = motor(PORT3, ratio6_1, false);
motor L4 = motor(PORT4, ratio6_1, true);
motor R1 = motor(PORT5, ratio6_1, true);
motor R2 = motor(PORT6, ratio6_1, false);
motor R3 = motor(PORT7, ratio6_1, true);
motor R4 = motor(PORT8, ratio6_1, false);

rotation rotationWallStake = rotation(PORT15); // reverse

// vex::motor_group leftDriveMotors = motor_group(L1,L2,L3);
// vex::motor_group rightDriveMotors = motor_group(R1,R2,R3);
// vex::motor_group allDriveMotors = motor_group(L1, R1, L2, R2, L3, R3);

distance ringDist = distance(PORT18);
optical colorDetect = optical(PORT19);
inertial inertialSensor = inertial(PORT21);

digital_out mogoMech = digital_out(Brain.ThreeWirePort.H);
digital_out doinker_right = digital_out(Brain.ThreeWirePort.G);
digital_out doinker_left = digital_out(Brain.ThreeWirePort.F);
digital_out tipper = digital_out(Brain.ThreeWirePort.D);

digital_in doinkerSwitches = digital_in(Brain.ThreeWirePort.A);

digital_out ringChuck = digital_out(Brain.ThreeWirePort.C); // not used
digital_in ringSwitch = digital_in(Brain.ThreeWirePort.E);  // not used
#endif

#ifdef GOLD
motor roller = motor(PORT20, ratio6_1, true);
motor conveyor = motor(PORT18, ratio18_1, true);
motor wallStake1 = motor(PORT11, ratio36_1, true);
motor wallStake2 = motor(PORT12, ratio36_1, false);
motor L1 = motor(PORT7, ratio6_1, true);
motor L2 = motor(PORT8, ratio6_1, false);
motor L3 = motor(PORT9, ratio6_1, true);
motor L4 = motor(PORT10, ratio6_1, false);
motor R1 = motor(PORT1, ratio6_1, false);
motor R2 = motor(PORT2, ratio6_1, true);
motor R3 = motor(PORT3, ratio6_1, false);
motor R4 = motor(PORT4, ratio6_1, true);

rotation rotationWallStake = rotation(PORT15); // reverse
// rotation verticalTraker = rotation(PORT6); //reverse
// rotation horizontalTraker = rotation(PORT8);

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

digital_out ringChuck = digital_out(Brain.ThreeWirePort.C); // not used
digital_in ringSwitch = digital_in(Brain.ThreeWirePort.H);  // not used
#endif

// VEXcode generated functions
// define variable for remote controller enable/disable
bool RemoteControlCodeEnabled = true;

/**
 * Used to initialize code/tasks/devices added using tools in VEXcode Pro.
 *
 * This should be called at the start of your int main function.
 */
void vexcodeInit(void)
{
  // nothing to initialize
}
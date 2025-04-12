#include "robot.h"
#include "vex.h"

using namespace vex;
using signature = vision::signature;
using code = vision::code;

// A global instance of brain used for printing to the V5 Brain screen
brain Brain;

// VEXcode device constructors
controller Controller1(primary);

#ifdef GREEN
motor roller(PORT5, ratio6_1, true);
motor conveyor(PORT4, ratio6_1, true);
motor wallStake(PORT9, ratio36_1, true);

motor L1(PORT6, ratio6_1, true);
motor L2(PORT7, ratio6_1, false);
motor L3(PORT8, ratio6_1, true);
// motor L4(PORT5, ratio6_1, false);
motor R1(PORT1, ratio6_1, false);
motor R2(PORT2, ratio6_1, true);
motor R3(PORT13, ratio6_1, false);
// motor R4(PORT15, ratio6_1, true);

optical colorDetect(PORT21);
distance ringDist(PORT12);
inertial inertialSensor(PORT11);
digital_out mogoMech(Brain.ThreeWirePort.D);
digital_out ringChuck(Brain.ThreeWirePort.C);
digital_in ringSwitch1(Brain.ThreeWirePort.E);
rotation rotationWallStake(PORT20);

Doinker doinker(Brain.ThreeWirePort.B);

#endif

#ifdef GOLD
motor roller(PORT5, ratio6_1, true);
motor conveyor(PORT4, ratio6_1, true);
motor wallStake(PORT9, ratio36_1, true);
motor L1(PORT6, ratio6_1, true);
motor L2(PORT7, ratio6_1, false);
motor L3(PORT8, ratio6_1, true);
// motor L4(PORT5, ratio6_1, false);
motor R1(PORT1, ratio6_1, false);
motor R2(PORT2, ratio6_1, true);
motor R3(PORT13, ratio6_1, false);
// motor R4(PORT15, ratio6_1, true);

optical colorDetect(PORT21);
distance ringDist(PORT12);
inertial inertialSensor(PORT11);
digital_out mogoMech(Brain.ThreeWirePort.D);
digital_out ringChuck(Brain.ThreeWirePort.C);
digital_in ringSwitch1(Brain.ThreeWirePort.E);

Doinker doinker(Brain.ThreeWirePort.B);
#endif

motor_group leftDriveMotors(L1, L2, L3);
motor_group rightDriveMotors(R1, R2, R3);
motor_group allDriveMotors(L1, R1, L2, R2, L3, R3);
motor_group intakeMotors(roller, conveyor);

Drive chassis(ZERO_TRACKER_NO_ODOM, leftDriveMotors, rightDriveMotors,
              // inertial port
              PORT14, 3.25, 0.75, 360, PORT1, -PORT2, PORT3, -PORT4, 3, 2.75,
              -2, 1, -2.75, 5.5);

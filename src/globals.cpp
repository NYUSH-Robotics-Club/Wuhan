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
digital_out ringChuck(Brain.ThreeWirePort.C);
digital_in ringSwitch1(Brain.ThreeWirePort.E);
rotation rotationWallStake(PORT20);

digital_out doinkerPort(Brain.ThreeWirePort.B);
digital_out mogoPort(Brain.ThreeWirePort.D);

#endif

#ifdef GOLD
motor roller(PORT20, ratio6_1, true);

motor conveyor(PORT18, ratio6_1, true);
motor wallStake1(PORT11, ratio36_1, true);
motor wallStake2(PORT12, ratio36_1, false);

motor L1(PORT7, ratio6_1, true);
motor L2(PORT8, ratio6_1, false);
motor L3(PORT9, ratio6_1, true);
motor L4(PORT10, ratio6_1, false);

motor R1(PORT1, ratio6_1, false);
motor R2(PORT2, ratio6_1, true);
motor R3(PORT3, ratio6_1, false);
motor R4(PORT4, ratio6_1, true);

optical colorDetect(PORT16);
distance ringDist(PORT17);

inertial inertialSensor(PORT21);
rotation rotationWallStake(PORT15);

digital_in ringSwitch1(Brain.ThreeWirePort.E);
digital_out ringChuck(Brain.ThreeWirePort.C);
digital_out doinkerPort(Brain.ThreeWirePort.B);
digital_out mogoPort(Brain.ThreeWirePort.D);



#endif

motor_group leftDriveMotors(L1, L2, L3, L4);
motor_group rightDriveMotors(R1, R2, R3, R4);
motor_group allDriveMotors(L1, R1, L2, R2, L3, R3, L4, R4);
motor_group intakeMotors(roller, conveyor);


Doinker doinker(&doinkerPort);
Mogo mogo(&mogoPort);

bool isRed = true;

bool ringSortDisable = true;
bool ringDetectOverride = false;
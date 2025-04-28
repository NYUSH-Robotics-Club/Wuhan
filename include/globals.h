#pragma once
#include "JAR-Template/drive.h"

#include "robot/doinker.h"
#include "robot/mogo.h"

extern brain Brain;

// VEXcode devices
extern controller Controller1;
extern motor roller;
extern motor conveyor;
extern motor wallStake1;
extern motor wallStake2;

extern motor L1;
extern motor L2;
extern motor L3;
extern motor L4;

extern motor R1;
extern motor R2;
extern motor R3;
extern motor R4;

extern inertial inertialSensor;
extern optical colorDetect;
extern distance ringDist;
extern digital_out mogoMech;
extern digital_out ringChuck;
extern digital_in ringSwitch;
extern rotation rotationWallStake;

extern digital_out tipper;

extern Doinker doinker;

extern Mogo mogo;

extern motor_group leftDriveMotors;
extern motor_group rightDriveMotors;
extern motor_group allDriveMotors;
extern motor_group intakeMotors;

extern Drive chassis;
extern bool isRed;

extern bool ringSortDisable;
extern bool ringDetectOverride;
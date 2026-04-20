#ifndef ARM_MACRO_H
#define ARM_MACRO_H

#include "vex.h"  // this includes vex::thread and all VEX classes

extern volatile bool armMacroRunning;
extern volatile bool armMacroCancel;
extern volatile int armMacroID;
extern vex::thread armThread;  // use vex::thread
extern int currentArmPower;


int armMacroTask();

#endif // ARM_MACRO_H

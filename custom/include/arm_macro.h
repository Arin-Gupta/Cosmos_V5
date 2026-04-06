#ifndef ARM_MACRO_H
#define ARM_MACRO_H

#include "vex.h"  // this includes vex::thread and all VEX classes

extern bool armMacroRunning;
extern bool armMacroCancel;
extern int armMacroID;
extern vex::thread armThread;  // use vex::thread

int armMacroTask();

#endif // ARM_MACRO_H

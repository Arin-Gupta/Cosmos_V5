#include "../custom/include/arm_macro.h"

bool armMacroRunning = false;
bool armMacroCancel = false;
int armMacroID = 0;
vex::thread armThread;  // use vex::thread

int armMacroTask() {
    armMacroRunning = true;
    armMacroCancel = false;

    int speed = 100;          // default fast macro
    int reverseTime = 600;    // default fast reverse time

    if (armMacroID == 2) {    // slow macro
        speed = 30;
        reverseTime = 1000;   // longer reverse time when slow
    }

    blockStopper.set(true);

    arm.spin(forward, speed, percent);
    wait(1000, msec);

    arm.spin(reverse, speed, percent);
    wait(reverseTime, msec);  // <-- now dynamic

    blockStopper.set(false);
    arm.stop();

    armMacroRunning = false;
    armMacroID = 0;

    return 0;
}
#include "../custom/include/arm_macro.h"

volatile bool armMacroRunning = false;
volatile bool armMacroCancel = false;
volatile int armMacroID = 0;
vex::thread armThread;  // use vex::thread

int armMacroTask() {
    armMacroRunning = true;
    armMacroCancel  = false;

    int speed = 100;
    int reverseTime = 600;

    if (armMacroID == 2) {
        speed = 30;
        reverseTime = 1000;
    }

    blockStopper.set(true);

    // Phase 1: spin forward for up to 1000ms
    arm.spin(forward, speed, percent);
    for (int i = 0; i < 100; i++) {       // 100 x 10ms = 1000ms
        if (armMacroCancel) {
            arm.stop();
            blockStopper.set(false);
            armMacroRunning = false;
            return 0;                       // exit immediately
        }
        wait(10, msec);
    }

    // Phase 2: spin reverse
    arm.spin(reverse, speed, percent);
    for (int i = 0; i < reverseTime / 10; i++) {
        if (armMacroCancel) {
            arm.stop();
            blockStopper.set(false);
            armMacroRunning = false;
            return 0;
        }
        wait(10, msec);
    }

    // Completed normally
    blockStopper.set(false);
    arm.stop();
    armMacroRunning = false;
    armMacroID = 0;

    return 0;
}
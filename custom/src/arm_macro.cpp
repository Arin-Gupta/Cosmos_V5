#include "../custom/include/arm_macro.h"
#include "../custom/include/arm.h"

volatile bool armMacroRunning = false;
volatile bool armMacroCancel = false;
volatile int armMacroID = 0;
vex::thread armThread;

int armMacroTask() {
    armMacroRunning = true;
    armMacroCancel  = false;

    if (armMacroID == 2) {
        // ---- Slow shot (lever down) ----
        blockStopper.set(true);

        arm.spin(forward, 45, percent);
        for (int i = 0; i < 100; i++) {
            if (armMacroCancel) { arm.stop(); armMacroRunning = false; return 0; }
            wait(10, msec);
        }

        arm.spin(reverse, 45, percent);
        for (int i = 0; i < 100; i++) {
            if (armMacroCancel) { arm.stop(); armMacroRunning = false; return 0; }
            wait(10, msec);
    
        }
    } 
    
    else {
        // ---- Fast shot (lever up) ----
        blockStopper.set(true);

        arm.spin(forward, 100, percent);
        for (int i = 0; i < 100; i++) {
            if (armMacroCancel) { arm.stop(); armMacroRunning = false; return 0; }
            wait(10, msec);
        }

        arm.spin(reverse, 100, percent);
        for (int i = 0; i < 60; i++) {
            if (armMacroCancel) { arm.stop(); armMacroRunning = false; return 0; }
            wait(10, msec);
        }
    }

    arm.stop();
    armMacroRunning = false;
    armMacroID = 0;

    return 0;
}
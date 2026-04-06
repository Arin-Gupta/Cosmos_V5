#include "../custom/include/arm_macro.h"
#include "../custom/include/arm.h"

const int LAUNCH_RAMP_STEP = 5;
int currentArmPower = 0;

volatile bool armMacroRunning = false;
volatile bool armMacroCancel = false;
volatile int armMacroID = 0;
vex::thread armThread;  // use vex::thread

int armMacroTask() {
    armMacroRunning = true;
    armMacroCancel  = false;

    if (armMacroID == 2) {
        // ---- Slow shot (lever down) ----
        int speed = 30;
        int reverseTime = 1000;

        blockStopper.set(true);

        arm.spin(forward, speed, percent);
        for (int i = 0; i < 100; i++) {
            if (armMacroCancel) { arm.stop(); blockStopper.set(false); armMacroRunning = false; return 0; }
            wait(10, msec);
        }

        arm.spin(reverse, speed, percent);
        for (int i = 0; i < reverseTime / 10; i++) {
            if (armMacroCancel) { arm.stop(); blockStopper.set(false); armMacroRunning = false; return 0; }
            wait(10, msec);
        }

    } else {
        // ---- Fast shot with ramp (lever up) ----
        // Tune LAUNCH_RAMP_STEP in arm.cpp to control how fast it accelerates
        int power = 0;
        blockStopper.set(true);

        // Ramp up to 100%
        while (power < 100) {
            if (armMacroCancel) { arm.stop(); blockStopper.set(false); armMacroRunning = false; return 0; }
            power += LAUNCH_RAMP_STEP;
            if (power > 100) power = 100;
            arm.spin(forward, power, percent);
            wait(10, msec);
        }

        // Hold at 100% for remainder of 1000ms
        // ramp took (100 / LAUNCH_RAMP_STEP) * 10ms, so wait the rest
        int rampTime = (100 / LAUNCH_RAMP_STEP) * 10;
        int holdTime = 1000 - rampTime;
        for (int i = 0; i < holdTime / 10; i++) {
            if (armMacroCancel) { arm.stop(); blockStopper.set(false); armMacroRunning = false; return 0; }
            wait(10, msec);
        }

        arm.spin(reverse, 100, percent);
        for (int i = 0; i < 60; i++) {  // 600ms reverse
            if (armMacroCancel) { arm.stop(); blockStopper.set(false); armMacroRunning = false; return 0; }
            wait(10, msec);
        }
    }

    blockStopper.set(false);
    arm.stop();
    armMacroRunning = false;
    armMacroID = 0;

    return 0;
}
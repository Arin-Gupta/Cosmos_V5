#include "vex.h"
#include "motor-control.h"
#include "../custom/include/pid_tuner.h"
#include "../custom/include/robot-config.h"

bool turnToggle = false;

extern bool prevR1;
int selected = 0;
int mode = 0;
bool tuning = true;

const char* modeNames[] = { "Distance", "Turn", "Heading" };
double* kp = nullptr;
double* ki = nullptr;
double* kd = nullptr;

void pidTunerLoop() {
    tuning = true;
    while (true) {
        if (!tuning) {
            wait(50, msec);
            continue;
        }

        if (controller_1.ButtonX.pressing()) mode = (mode + 1) % 3;
        if (controller_1.ButtonY.pressing()) selected = (selected + 1) % 3;

        if (mode == 0) {
            kp = &distance_kp;
            ki = &distance_ki;
            kd = &distance_kd;
        } else if (mode == 1) {
            kp = &turn_kp;
            ki = &turn_ki;
            kd = &turn_kd;
        } else {
            kp = &heading_correction_kp;
            ki = &heading_correction_ki;
            kd = &heading_correction_kd;
        }

        if (controller_1.ButtonUp.pressing()) {
            if (selected == 0) *kp += 0.1;
            if (selected == 1) *ki += 0.01;
            if (selected == 2) *kd += 0.1;
        }
        if (controller_1.ButtonDown.pressing()) {
            if (selected == 0) *kp -= 0.1;
            if (selected == 1) *ki -= 0.01;
            if (selected == 2) *kd -= 0.1;
        }

        if (controller_1.ButtonR1.pressing() && !prevR1) {

// inside pidTunerLoop, replace the R1 block:
if (controller_1.ButtonR1.pressing() && !prevR1) {
    if (turnToggle) {
        turnToAngle(0, 3000, true, 6);
    } else {
        turnToAngle(180, 3000, true, 6);
    }
    turnToggle = !turnToggle;
}
            wait(500, msec);
        }
        prevR1 = controller_1.ButtonR1.pressing();

        wait(200, msec);
    }
}
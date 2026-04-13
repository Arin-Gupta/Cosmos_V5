#include "vex.h"
#include "motor-control.h"
#include "../custom/include/pid_tuner.h"
#include "../custom/include/robot-config.h"

extern bool prevR1;
int selected = 0; // 0=P, 1=I, 2=D
int mode = 0;     // 0=distance, 1=turn, 2=heading
bool tuning = false;

void pidTunerLoop() {
tuning = true;
  while (true) {

    if (!tuning) {
      wait(50, msec);
      continue;
    }

    // SWITCH WHICH CONSTANT YOU'RE EDITING
    if (controller_1.ButtonX.pressing()) mode = (mode + 1) % 3;
    if (controller_1.ButtonY.pressing()) selected = (selected + 1) % 3;

    double* kp;
    double* ki;
    double* kd;

    // POINT to the correct PID set
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

    // ADJUST VALUES
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

    // PRINT TO SCREEN
    Brain.Screen.clearScreen();
    Brain.Screen.setCursor(1,1);

    Brain.Screen.print("Mode: %d", mode);
    Brain.Screen.newLine();

    Brain.Screen.print("kP: %.2f", *kp);
    Brain.Screen.newLine();
    Brain.Screen.print("kI: %.2f", *ki);
    Brain.Screen.newLine();
    Brain.Screen.print("kD: %.2f", *kd);

    if (controller_1.ButtonR1.pressing() && !prevR1) {
        driveTo(48, 10000, true, 12);
        wait(500, msec);
        driveTo(0, 10000, true, 12);
    }

    prevR1 = controller_1.ButtonR1.pressing();

    wait(200, msec);
  }
}
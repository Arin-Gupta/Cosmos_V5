#include "vex.h"
#include "../custom/include/arm.h"
#include "../custom/include/intake.h"
#include "../custom/include/arm_macro.h"

// From user.cpp
extern bool button_a;
extern bool button_b;
extern bool l1;

extern bool prevL1;

extern volatile bool armMacroRunning;
extern volatile bool armMacroCancel;
extern volatile int  armMacroID;
extern vex::thread armThread;

extern bool LeverPos;  // true = lever down = slow shot mode

int armMacroTask();  // forward declaration

// Tunable accelerator — how much power is added per 10ms tick when ramping up
// e.g. 5 means it takes 20 ticks (200ms) to reach 100%


void armControl() {

  // ================= ARM MANUAL =================

  if (button_a || button_b) {

    // Cancel macro and wait for it to actually stop
    if (armMacroRunning) {
      armMacroCancel = true;
      int waitCount = 0;
      while (armMacroRunning && waitCount < 20) {
        wait(10, msec);
        waitCount++;
      }
    }

    currentArmPower = 0;  // reset ramp on manual override

    if (button_a)
      arm.spin(forward, 100, percent);
    else
      arm.spin(reverse, 100, percent);
  }
  else if (!armMacroRunning) {
    currentArmPower = 0;  // reset ramp when idle
    arm.spin(forward, 0, percent);
  }

  // ================= ARM MACROS =================

  if (l1 && !prevL1 && !armMacroRunning) {
    if (!LeverPos) {
      // Lever down — use slow shot
      armMacroID = 2;
    } else {
      // Lever up — use fast shot with ramp
      armMacroID = 1;
    }
    armThread = vex::thread(armMacroTask);
  }

  prevL1 = l1;

  // ================= BLOCK STOPPER =================
  // Keep block stopper open while L1 is held (even after macro finishes)
  // Close it as soon as L1 is released and no macro is running
  if (!armMacroRunning && !l1) {
    blockStopper.set(false);
  }
}
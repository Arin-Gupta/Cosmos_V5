#include "vex.h"
#include "../custom/include/arm.h"
#include "../custom/include/intake.h"
#include "../custom/include/arm_macro.h"

extern bool button_a;
extern bool button_b;
extern bool l1;
extern bool prevL1;
extern bool button_up_arrow;  
extern bool prevUp;

extern volatile bool armMacroRunning;
extern volatile bool armMacroCancel;
extern volatile int  armMacroID;
extern vex::thread armThread;

extern bool LeverPos;

int armMacroTask();

void armControl() {

  // ================= ARM MANUAL =================

  if (button_a || button_b) {
    if (armMacroRunning) {
      armMacroCancel = true;
      int waitCount = 0;
      while (armMacroRunning && waitCount < 20) {
        wait(10, msec);
        waitCount++;
      }
    }

    if (button_a)
      arm.spin(forward, 100, percent);
    else
      arm.spin(reverse, 100, percent);
  }
  else if (!armMacroRunning) {
    arm.spin(forward, 0, percent);
  }

// ================= ARM MACROS =================

  if (l1 && !prevL1 && !armMacroRunning) {
    armMacroID = 1;  // L1 = fast shot always
    armThread = vex::thread(armMacroTask);
  }

  if (button_up_arrow && !prevUp && !armMacroRunning) {
    armMacroID = 2;  // Up arrow = slow shot always
    armThread = vex::thread(armMacroTask);
  }

  prevL1 = l1;
  prevUp = button_up_arrow;

  // ================= BLOCK STOPPER =================
  if (!armMacroRunning && !l1) {
    blockStopper.set(false);
  }
}
#include "vex.h"
#include "../custom/include/arm.h"
#include "../custom/include/intake.h"

// From user.cpp
extern bool button_a;
extern bool button_b;
extern bool l1;
extern bool button_up_arrow;
extern int IntakeState();

extern bool prevL1;
extern bool prevUp;

extern bool armMacroRunning;
extern bool armMacroCancel;
extern int armMacroID;
extern vex::thread armThread;

bool armIdleUp = false;

int armMacroTask();  // forward declaration


void armControl() {

  // ================= ARM MANUAL =================

  if (button_a || button_b) {

    if (armMacroRunning) {
      armMacroCancel = true;
    }

    armMacroRunning = false;
    armMacroID = 0;

    if (button_a)
      arm.spin(forward,100,rpm);
    else
      arm.spin(reverse,100,rpm);
  }
else if (!armMacroRunning) {
  arm.spin(reverse,0,rpm);
}

  // ================= ARM MACROS =================

  if (l1 && !prevL1 && !armMacroRunning) {
    armMacroID = 1;
    armThread = thread(armMacroTask);
  }

  if (button_up_arrow && !prevUp && !armMacroRunning) {
    armMacroID = 2;
    armThread = thread(armMacroTask);
  }

  prevL1 = l1;
  prevUp = button_up_arrow;

}

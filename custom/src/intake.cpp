#include "vex.h"
#include "../custom/include/intake.h"

extern int IntakeState;
extern bool r1, r2;
extern bool prevR1, prevR2;

// new block unfaller
bool intakeHoldingRequest = false;

void intakeToggle() {

  if (r1 && !prevR1)
    IntakeState = (IntakeState == 1) ? 0 : 1;

  if (r2 && !prevR2)
    IntakeState = (IntakeState == -1) ? 0 : -1;

  if (IntakeState == 1)
    intake.spin(forward,600,rpm);
  else if (IntakeState == -1)
    intake.spin(reverse,300,rpm);
  else
    intake.spin(forward,0,rpm);

  prevR1 = r1;
  prevR2 = r2;
}
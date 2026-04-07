#include "vex.h"
#include "../custom/include/pneumatics.h"

// From user.cpp
extern bool WingPos;
extern bool ScraperPos;
extern bool LeverPos;

extern bool l2;
extern bool button_y;
extern bool button_x;

extern bool prevL2;
extern bool prevY;
extern bool prevX;


void pneumaticsControl() {

  // ================= OUTER WING =================
  // L2 held = outer wing down (false), otherwise up (true)
  outer_wing.set(!l2);


  // ================= INNER WING MANUAL TOGGLE =================
  static bool innerWingManual = false;
  static bool prevYLocal = false;

  // Toggle manual control with Y (edge detection)
  if (button_y && !prevYLocal) {
    innerWingManual = !innerWingManual;
  }
  prevYLocal = button_y;


  // ================= INNER WING FINAL LOGIC =================
  bool innerState;

  if (LeverPos) {
    // Lever UP → force inner wing UP
    innerState = true;
  } else {
    // Lever DOWN → allow manual toggle
    innerState = innerWingManual;
  }

  inner_wing.set(innerState);
}
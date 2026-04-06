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


  // ================= LEVER EDGE DETECTION =================
  static bool prevLeverPos = false;
  bool leverChanged = (LeverPos != prevLeverPos);


  // ================= INNER WING STATE SYSTEM =================
  static bool innerWingManual = false;
  static bool prevY = false;

  // toggle manual inner wing with Y
  if (button_y && !prevY) {
    innerWingManual = !innerWingManual;
  }
  prevY = button_y;


  // ================= LEVER OVERRIDE =================
  static bool leverOverrideActive = false;

  if (leverChanged) {
    leverOverrideActive = true;

    // force sync inner wing with lever
    inner_wing.set(LeverPos);
  }


  // once stable again, release override
  if (!leverChanged) {
    leverOverrideActive = false;
  }


  // ================= FINAL INNER WING OUTPUT =================
  bool innerState;

  if (leverOverrideActive) {
    innerState = LeverPos;          // safety forced state
  } else {
    innerState = innerWingManual;   // player control
  }

  inner_wing.set(innerState);


  // ================= UPDATE LEVER TRACKER =================
  prevLeverPos = LeverPos;
}
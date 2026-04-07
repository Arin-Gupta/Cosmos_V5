#include "vex.h"
#include "../custom/include/pneumatics.h"

// From user.cpp
extern bool l2;
extern bool button_y;
extern bool button_x;

void pneumaticsControl() {

  // ================= OUTER WING =================
  // Hold L2 → down, release → up
  outer_wing.set(!l2);


  // ================= LEVER (Y TOGGLE) =================
  static bool LeverPos = false;   // false = down, true = up
  static bool prevY = false;

  if (button_y && !prevY) {
    LeverPos = !LeverPos;
  }
  prevY = button_y;


  // ================= INNER WING =================
  // Always follows lever
  inner_wing.set(LeverPos);


  // ================= SCRAPER (X TOGGLE) =================
  static bool ScraperPos = false;
  static bool prevX = false;

  if (button_x && !prevX) {
    ScraperPos = !ScraperPos;
  }
  prevX = button_x;

  scraper.set(ScraperPos);


  // ================= OPTIONAL: LEVER PNEUMATIC =================
  // Uncomment if you have a physical piston for the lever
  lever.set(LeverPos);

  wait(20,msec);
}
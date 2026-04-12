#include "vex.h"
#include "../custom/include/pneumatics.h"

// From user.cpp
extern bool l2;
extern bool button_y;
extern bool button_x;

void pneumaticsControl() {

  // ================= LEVER (Y TOGGLE) =================
  static bool LeverPos = true;  // true = up, false = down
  static bool prevY = false;

  if (button_y && !prevY) {
    LeverPos = !LeverPos;
  }
  prevY = button_y;

  lever.set(!LeverPos);


  // ================= STATE MACHINE =================
  if (LeverPos) {
    // LEVER UP: L2 controls outer wing, inner wing always up
    outer_wing.set(!l2);
    inner_wing.set(true);

  } else {
    // LEVER DOWN: L2 controls inner wing, outer wing always down
    inner_wing.set(!l2);
    outer_wing.set(false);
  }


  // ================= SCRAPER (X TOGGLE) =================
  static bool ScraperPos = false;
  static bool prevX = false;

  if (button_x && !prevX) {
    ScraperPos = !ScraperPos;
  }
  prevX = button_x;

  scraper.set(ScraperPos);
}
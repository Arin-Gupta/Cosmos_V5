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

  // ================= WING TOGGLE =================

  if (l2 && !prevL2) {
    WingPos = !WingPos;
    wing.set(WingPos);
  }

  prevL2 = l2;


  // ================= SCRAPER TOGGLE =================

  if (button_x && !prevX) {
    ScraperPos = !ScraperPos;
    scraper.set(ScraperPos);

    
  }

  prevX = button_x;


  // ================= LEVER TOGGLE =================

  if (button_y && !prevY) {
    LeverPos = !LeverPos;
    lever.set(!LeverPos);

    if (LeverPos) {
      WingPos = true;
      wing.set(true);
    }
  }

  prevY = button_y;
}
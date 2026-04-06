#include "vex.h"
#include "../custom/include/controller.h"
#include "motor-control.h"


extern int ch1, ch3;
extern bool l1, l2, r1, r2;
extern bool button_a, button_b;
extern bool button_x, button_y;
extern bool button_up_arrow;
extern bool button_left_arrow;
extern bool button_right_arrow;

void controllerInput() {

  ch1 = controller_1.Axis1.value();
  ch3 = controller_1.Axis3.value();

  l1 = controller_1.ButtonL1.pressing();
  l2 = controller_1.ButtonL2.pressing();
  r1 = controller_1.ButtonR1.pressing();
  r2 = controller_1.ButtonR2.pressing();
  button_a = controller_1.ButtonA.pressing();
  button_b = controller_1.ButtonB.pressing();
  button_x = controller_1.ButtonX.pressing();
  button_y = controller_1.ButtonY.pressing();
  button_up_arrow = controller_1.ButtonUp.pressing();
  button_left_arrow = controller_1.ButtonLeft.pressing();
  button_right_arrow = controller_1.ButtonRight.pressing();
}
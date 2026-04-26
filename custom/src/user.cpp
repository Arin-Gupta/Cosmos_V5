#include "vex.h"
#include "motor-control.h"
#include "../custom/include/autonomous.h"
#include "../custom/include/robot-config.h"
#include "../custom/include/arm_macro.h"
#include "../custom/include/expo.h"
#include "../custom/include/controller.h"
#include "../custom/include/heading.h"
#include "../custom/include/intake.h"
#include "../custom/include/arm.h"
#include "../custom/include/pneumatics.h"
#include "../custom/include/brain_screen.h"
#include "../custom/include/pid_tuner.h"

// Modify autonomous, driver, or pre-auton code below
void runAutonomous() {
 // thread screen = thread(screenThread);
  int auton_selected = 1;
  switch(auton_selected) {
    case 1:
    _R4B();
      break;  
    case 2:
    _R4B2();
    break;  
    case 3:
    _L4B();
      break;
    case 4:
    _L4B2();
      break;
    case 5:
    ninety();
      break;
    case 6:
    Skills20();
      break;
    case 7:
    Skills15();
      break;
    case 8:
    nothing();
      break;
    case 9:
      break;
 
  }
}


// controller_1 input variables (snake_case)
int ch1, ch2, ch3, ch4;
bool l1, l2, r1, r2;
bool button_a, button_b, button_x, button_y;
bool button_up_arrow, button_down_arrow, button_left_arrow, button_right_arrow;
int chassis_flag = 0;

// ================= DRIVER STATE =================

// Heading hold
bool headingLocked = false;
double targetHeading = 0;

// Toggle states
int IntakeState = 0;
bool WingPos = false;
bool ScraperPos = false;
bool LeverPos = false;

// Edge detection
bool prevR1 = false, prevR2 = false, prevL1 = false;
bool prevUp = false, prevL2 = false, prevY = false, prevX = false;


void runDriver() {
  scraper.set(false);
    stopChassis(brake);
    intake.setStopping(brake);
    arm.setStopping(brake);
    heading_correction = false;

    thread cosmos(screenThread);

    if (tuning) {
        thread tuner(pidTunerLoop);
        tuner.detach();

        while (true) {
            wait(10, msec); // pidTunerLoop handles everything
        }
    }

    while (true) {
        controllerInput();
        headingHold();
        intakeToggle();
        armControl();
        pneumaticsControl();
        wait(10, msec);
    }
}
void runPreAutonomous() {
    // Initializing Robot Configuration. DO NOT REMOVE!
  vexcodeInit();
  wing.set(false);
  scraper.set(false);
  lever.set(false);

  // Calibrate inertial sensor
  inertial_sensor.calibrate();

  // Wait for the Inertial Sensor to calibrate
  while (inertial_sensor.isCalibrating()) {
    wait(10, msec);
  }

  //thread nova(screenThread);
  
  // odom tracking
  resetChassis();
  if(using_horizontal_tracker && using_vertical_tracker) {
    thread odom = thread(trackXYOdomWheel);
  } else if (using_horizontal_tracker) {
    thread odom = thread(trackXOdomWheel);
  } else if (using_vertical_tracker) {
    thread odom = thread(trackYOdomWheel);
  } else {
    thread odom = thread(trackNoOdomWheel);
  }

  stopChassis(brake);
  intake.setStopping(brake);
  arm.setStopping(brake);

}
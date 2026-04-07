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

// Modify autonomous, driver, or pre-auton code below

int screenThread() {
    Brain.Screen.clearScreen();
    Brain.Screen.setFillColor(vex::color(180,0,0));
    Brain.Screen.drawRectangle(0,0,480,240);
    Brain.Screen.setFillColor(black);
    Brain.Screen.setFont(fontType::mono20);

    // --- Draw Boxes ---
    Brain.Screen.setPenColor(white);
    Brain.Screen.drawRectangle(30,25,180,120);      // Inertial
    Brain.Screen.drawRectangle(30,155,180,60);      // Team ID
    Brain.Screen.drawRectangle(225,30,230,180);     // Motor temps

    // --- Labels ---
    Brain.Screen.printAt(40,50,"X:");
    Brain.Screen.printAt(40,85,"Y:");
    Brain.Screen.printAt(40,120,"Heading:");
    Brain.Screen.printAt(40,190,"  20785X NOVA");

    Brain.Screen.printAt(265,55,"L1:");
    Brain.Screen.printAt(265,75,"L2:");
    Brain.Screen.printAt(265,95,"L3:");
    Brain.Screen.printAt(265,115,"R1:");
    Brain.Screen.printAt(265,135,"R2:");
    Brain.Screen.printAt(265,155,"R3:");
    Brain.Screen.printAt(265,175,"INT:");
    Brain.Screen.printAt(265,195,"ARM:");

    while(true){
        Brain.Screen.setPenColor(white);

        // --- X / Y ---
        Brain.Screen.printAt(140,50,"%6.2f",x_pos);
        Brain.Screen.printAt(140,85,"%6.2f",y_pos);

        // --- Heading normalized to ±180 ---
        double h = getInertialHeading();
        while(h > 180)  h -= 360;
        while(h <= -180) h += 360;

        Brain.Screen.printAt(140,120,"%6.2f",h);

        // --- Motor temps ---
        auto printTemp=[&](int y,motor&m){
            double t = m.temperature(celsius);
            Brain.Screen.setPenColor(t>=55?red:t>=40?yellow:green);
            Brain.Screen.printAt(350,y,"%5.1fC  ",t);
        };

        printTemp(55,left_chassis1);
        printTemp(75,left_chassis2);
        printTemp(95,left_chassis3);
        printTemp(115,right_chassis1);
        printTemp(135,right_chassis2);
        printTemp(155,right_chassis3);
        printTemp(175,intake);
        printTemp(195,arm);

        wait(100,msec);
    }
    return 0;
}


void runAutonomous() {
  int auton_selected = 1;
  switch(auton_selected) {
    case 1:
      R4BP();
      break;  
    case 2:
      break;  
    case 3:
      L4BP();
      break;
    case 4:
      break; 
    case 5:
      break;
    case 6:
      SAWP();
      break;
    case 7:
      break;
    case 8:
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
  stopChassis(brake);
  intake.setStopping(brake);
  arm.setStopping(brake);
  heading_correction = false;

  thread cosmos(screenThread);

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
  outer_wing.set(true);
  scraper.set(true);
  lever.set(true);

  // Calibrate inertial sensor
  inertial_sensor.calibrate();

  // Wait for the Inertial Sensor to calibrate
  while (inertial_sensor.isCalibrating()) {
    wait(10, msec);
  }

  thread nova(screenThread);
  
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
#include "vex.h"
#include "../custom/include/heading.h"
#include "motor-control.h"
#include "../custom/include/expo.h"

extern bool headingLocked;
extern double targetHeading;

extern bool button_left_arrow;
extern bool button_right_arrow;

extern int ch1, ch3;

void headingHold() {

  bool leftHeld  = button_left_arrow;
  bool rightHeld = button_right_arrow;

  if (leftHeld || rightHeld) {

    if (!headingLocked) {
      targetHeading = inertial_sensor.heading();
      headingLocked = true;
    }

    double error = targetHeading - inertial_sensor.heading();

    if (error > 180) error -= 360;
    if (error < -180) error += 360;

    const double kP = 1.5;
    int turnCorrection = error * kP;

    if (turnCorrection > 40) turnCorrection = 40;
    if (turnCorrection < -40) turnCorrection = -40;

    int driveSpeed = leftHeld ? 100 : -100;

    double leftPower  = (driveSpeed + turnCorrection) * 0.12;
    double rightPower = (driveSpeed - turnCorrection) * 0.12;

    driveChassis(leftPower, rightPower);
  }
  else {

    headingLocked = false;

    double drive_power = applyExpo(ch3,
                                   drive_deadband,
                                   drive_min_output,
                                   drive_expo);

    double turn_power  = applyExpo(ch1,
                                   turn_deadband,
                                   turn_min_output,
                                   turn_expo);

    double left_power  = drive_power + turn_power;
    double right_power = drive_power - turn_power;

    if (left_power > 127) left_power = 127;
    if (left_power < -127) left_power = -127;
    if (right_power > 127) right_power = 127;
    if (right_power < -127) right_power = -127;

    driveChassis(left_power * 0.12,
                 right_power * 0.12);
  }
}
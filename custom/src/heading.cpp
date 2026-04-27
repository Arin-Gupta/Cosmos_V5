#include "vex.h"
#include "../custom/include/heading.h"
#include "motor-control.h"
#include "../custom/include/expo.h"
#include "../custom/include/slew.h"

extern int ch1, ch3;

static double left_output  = 0.0;
static double right_output = 0.0;
static double prev_drive = 0.0;

static int hold_ticks = 0;

const int REVERSAL_HOLD_TICKS = 1;

bool isReversing(double target, double previous) {
    return (target * previous < 0);
}

void headingHold() {

    double drive_power = applyExpo(ch3, drive_deadband, drive_min_output, drive_expo);
    double turn_power  = applyExpo(ch1, turn_deadband,  turn_min_output,  turn_expo);

    double left_target  = drive_power + turn_power;
    double right_target = drive_power - turn_power;

    if (left_target  >  127) left_target  =  127;
    if (left_target  < -127) left_target  = -127;
    if (right_target >  127) right_target =  127;
    if (right_target < -127) right_target = -127;

    if (isReversing(drive_power, prev_drive)) hold_ticks = REVERSAL_HOLD_TICKS;
    if (fabs(drive_power) > 0.5) prev_drive = drive_power;

    if (hold_ticks > 0) {
        left_target  = 0.0;
        right_target = 0.0;
        hold_ticks--;

        // Snap output to zero when hold expires so slew launches instantly
        if (hold_ticks == 0) {
            left_output  = 0.0;
            right_output = 0.0;
        }
    }

    left_output  = applySlewRate(left_target,  left_output);
    right_output = applySlewRate(right_target, right_output);

    driveChassis(left_output  * 0.12,
                 right_output * 0.12);
}
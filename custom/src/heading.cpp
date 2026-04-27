#include "vex.h"
#include "../custom/include/heading.h"
#include "motor-control.h"
#include "../custom/include/expo.h"
#include "../custom/include/slew.h"

extern int ch1, ch3;

// Persistent outputs — retained across loop ticks for slew calculation
static double left_output  = 0.0;
static double right_output = 0.0;

void headingHold() {

    // --- Compute raw expo-curved drive and turn values ---
    double drive_power = applyExpo(ch3,
                                   drive_deadband,
                                   drive_min_output,
                                   drive_expo);

    double turn_power  = applyExpo(ch1,
                                   turn_deadband,
                                   turn_min_output,
                                   turn_expo);

    // --- Mix into left/right targets ---
    double left_target  = drive_power + turn_power;
    double right_target = drive_power - turn_power;

    // Clamp targets to motor range
    if (left_target  >  127) left_target  =  127;
    if (left_target  < -127) left_target  = -127;
    if (right_target >  127) right_target =  127;
    if (right_target < -127) right_target = -127;

    // --- Apply direction-aware slew rate ---
    left_output  = applySlewRate(left_target,  left_output);
    right_output = applySlewRate(right_target, right_output);

    // --- Send to chassis (VEX expects roughly -1.0 to 1.0 range) ---
    driveChassis(left_output  * 0.12,
                 right_output * 0.12);
}
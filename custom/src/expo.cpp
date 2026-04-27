// expo.cpp
#include "../custom/include/expo.h"
#include <cmath>   // for pow()

// ====================
// Custom Expo Settings
// ====================

// Drive
int drive_deadband = 4;
int drive_min_output = 6;
double drive_expo = 0.6;

// Turn
int turn_deadband = 6;
int turn_min_output = 8.75;
double turn_expo = 0.67;


// =====================
// Custom Expo Function 
// =====================


double applyExpo(int input, int deadband, int min_output, double expo_gain) {
    // Clip input
    if (input > 127) input = 127;
    if (input < -127) input = -127;

    // Deadband
    if (abs(input) <= deadband) {
        return 0;
    }

    // Remove deadband and rescale
    double sign = (input > 0) ? 1 : -1;
    double adjusted = (abs(input) - deadband) / (double)(127 - deadband);

    // Apply expo curve
    double curved = (1 - expo_gain) * adjusted + expo_gain * pow(adjusted, 3);

    // Apply minimum output
    double output = min_output + (127 - min_output) * curved;

    return sign * output;

}

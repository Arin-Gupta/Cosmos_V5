// expo.h
#ifndef EXPO_H
#define EXPO_H

#include "vex.h"

// =====================
// Custom Expo Settings
// =====================

// Drive
extern int drive_deadband;
extern int drive_min_output;
extern double drive_expo;

// Turn
extern int turn_deadband;
extern int turn_min_output;
extern double turn_expo;

// =====================
// Function Declaration
// =====================

double applyExpo(int input, int deadband,
int min_output, double expo_gain);

#endif

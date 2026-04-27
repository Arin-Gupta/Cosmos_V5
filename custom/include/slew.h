// custom/include/slew.h
#pragma once

// Slew rate limiter for direction-aware motor control.
// Call applySlewRate() each loop tick for each motor channel.

// --- Tunable Parameters ---
// How much the output can change per loop when continuing in the same direction.
// 127 = effectively instant (no limiting). Lower = smoother acceleration.
const double SLEW_NORMAL = 127.0;

// How much the output can change per loop when reversing direction.
// Lower = slower/safer reversal. 6–12 is a good starting range.
const double SLEW_REVERSAL = 8.0;
// --------------------------

double applySlewRate(double target, double previous);
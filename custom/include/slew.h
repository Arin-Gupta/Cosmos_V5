// custom/include/slew.h
#pragma once
#include <cmath>

// --- Drive slew ---
const double SLEW_NORMAL   = 127.0;   // same-direction step limit (127 = instant)

// Reversal speed as a percentage of full output (0–100)
// e.g. 16 = the output can change by 16% of 127 per tick during a direction flip
const double SLEW_REVERSAL_PCT = 50.0;
const double SLEW_REVERSAL = (SLEW_REVERSAL_PCT / 100.0) * 127.0;

double applySlewRate(double target, double previous, double slew_normal, double slew_reversal);
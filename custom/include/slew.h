#pragma once
#include <cmath>

const double SLEW_NORMAL       = 127.0;
const double SLEW_REVERSAL_PCT = 50;
const double SLEW_REVERSAL     = (SLEW_REVERSAL_PCT / 100.0) * 127.0;

double applySlewRate(double target, double previous);
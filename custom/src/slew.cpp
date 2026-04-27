// slew.cpp
#include "../custom/include/slew.h"
#include <cmath>

// Apply a direction-aware slew rate limiter.
// target   : desired motor power this tick  (-127 to 127)
// previous : actual output from last tick   (-127 to 127)
// returns  : clamped output for this tick
double applySlewRate(double target, double previous) {

    // Detect a direction reversal: signs differ AND previous is not near zero
    bool reversing = (target * previous < 0) && (fabs(previous) > 1.0);

    double maxStep = reversing ? SLEW_REVERSAL : SLEW_NORMAL;

    double delta = target - previous;

    // Clamp the change to the allowed step size
    if (delta >  maxStep) delta =  maxStep;
    if (delta < -maxStep) delta = -maxStep;

    return previous + delta;
}
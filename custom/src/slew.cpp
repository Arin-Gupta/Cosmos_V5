#include "../custom/include/slew.h"

double applySlewRate(double target, double previous) {
    bool reversing = (target * previous < 0) && (fabs(previous) > 1.0);
    double maxStep = reversing ? SLEW_REVERSAL : SLEW_NORMAL;
    double delta = target - previous;
    if (delta >  maxStep) delta =  maxStep;
    if (delta < -maxStep) delta = -maxStep;
    return previous + delta;
}
#ifndef PID_TUNER_H
#define PID_TUNER_H

extern int selected; // 0=P, 1=I, 2=D
extern int mode;     // 0=distance, 1=turn, 2=heading
extern bool tuning;

void pidTunerLoop();

#endif // PID_TUNER_H
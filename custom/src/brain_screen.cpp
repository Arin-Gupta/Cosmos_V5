#include "vex.h"
#include "motor-control.h"
#include "../custom/include/brain_screen.h"
#include "../custom/include/pid_tuner.h"

int screenThread() {
    Brain.Screen.clearScreen();
    Brain.Screen.setFillColor(vex::color(180,0,0));
    Brain.Screen.drawRectangle(0,0,480,240);
    Brain.Screen.setFillColor(black);
    Brain.Screen.setFont(fontType::mono20);

    // --- Draw Boxes ---
    Brain.Screen.setPenColor(white);
    Brain.Screen.drawRectangle(30,25,180,120);
    Brain.Screen.drawRectangle(30,155,180,60);
    Brain.Screen.drawRectangle(225,30,230,180);

    // --- Labels ---
    Brain.Screen.printAt(40,50,"X:");
    Brain.Screen.printAt(40,85,"Y:");
    Brain.Screen.printAt(40,120,"Heading:");
    Brain.Screen.printAt(40,190,"  20785X NOVA");

    Brain.Screen.printAt(265,55,"L1:");
    Brain.Screen.printAt(265,75,"L2:");
    Brain.Screen.printAt(265,95,"L3:");
    Brain.Screen.printAt(265,115,"R1:");
    Brain.Screen.printAt(265,135,"R2:");
    Brain.Screen.printAt(265,155,"R3:");
    Brain.Screen.printAt(265,175,"INT:");
    Brain.Screen.printAt(265,195,"ARM:");

    while (true) {
        if (tuning) {
            Brain.Screen.clearScreen();
            Brain.Screen.setFont(fontType::mono20);
            Brain.Screen.setPenColor(white);
            char buf[32];

            snprintf(buf, sizeof(buf), "Mode: %s", modeNames[mode]);
            Brain.Screen.printAt(10, 40, buf);

            snprintf(buf, sizeof(buf), "%s kP: %.2f", selected == 0 ? ">" : " ", *kp);
            Brain.Screen.printAt(10, 80, buf);

            snprintf(buf, sizeof(buf), "%s kI: %.4f", selected == 1 ? ">" : " ", *ki);
            Brain.Screen.printAt(10, 120, buf);

            snprintf(buf, sizeof(buf), "%s kD: %.2f", selected == 2 ? ">" : " ", *kd);
            Brain.Screen.printAt(10, 160, buf);
            wait(200, msec);
            continue;
        }

        // --- Normal telemetry ---
        Brain.Screen.setPenColor(white);
        Brain.Screen.printAt(140,50,"%6.2f",x_pos);
        Brain.Screen.printAt(140,85,"%6.2f",y_pos);

        double h = getInertialHeading();
        while(h > 180)  h -= 360;
        while(h <= -180) h += 360;
        Brain.Screen.printAt(140,120,"%6.2f",h);

        auto printTemp=[&](int y, motor& m){
            double t = m.temperature(celsius);
            Brain.Screen.setPenColor(t>=55?red:t>=40?yellow:green);
            Brain.Screen.printAt(350,y,"%5.1fC  ",t);
        };

        printTemp(55,left_chassis1);
        printTemp(75,left_chassis2);
        printTemp(95,left_chassis3);
        printTemp(115,right_chassis1);
        printTemp(135,right_chassis2);
        printTemp(155,right_chassis3);
        printTemp(175,intake);
        printTemp(195,arm);

        wait(100, msec);
    }
    return 0;
}
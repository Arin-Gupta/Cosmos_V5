#include "vex.h"
#include "utils.h"
#include "pid.h"
#include <ctime>
#include <cmath>
#include <thread>

#include "../include/autonomous.h"
#include "motor-control.h"

void scraperthread() {
    wait(950, msec);
    scraper.set(true); wait(500, msec);
    scraper.set(false);
}

void _R4BP() {
    // Example of using the R4BP function to drive forward 24 inches while maintaining a heading of 0 degrees
    // and then turn to 90 degrees

    // Collect 4 Blocks
    thread meow = thread(scraperthread);
    intake.spin(forward, 100, percent);
    turnToAngle(14,500,true,10);
    moveToPoint(8,27,1,2000,true,10,false);
    lever.set(false);
    wait(200,msec);

    // Position in Front of Goal


    // Align


    // Shoot

    //turnToAngle(-73, 2000, true, 10);
    //driveTo(-48,500,true,12);
    
}
#include "vex.h"
#include "utils.h"
#include "pid.h"
#include <ctime>
#include <cmath>
#include <thread>

#include "../include/autonomous.h"
#include "motor-control.h"

void scraperthread() {
    wait(900, msec);
    scraper.set(true); wait(1000, msec);
    scraper.set(false);
}

void score() {
    blockStopper.set(true);
    arm.spin(forward, 100, percent);
    wait(1000, msec);
    arm.spin(reverse, 100, percent);
    wait(500, msec);
    arm.stop();
    blockStopper.set(false);
}

void _R4B() {
    // Example of using the R4BP function to drive forward 24 inches while maintaining a heading of 0 degrees
    // and then turn to 90 degrees

    // Collect 4 Blocks
    thread meow = thread(scraperthread);
    intake.spin(forward, 100, percent);
    turnToAngle(13,500,true,10);
    moveToPoint(6.5,29,1,2000,true,6,false);
    //moveToPoint(6.5,29,-1,2000,true,10,false);
    lever.set(false);
    wait(400,msec);
    turnToAngle(-75,1000,true,10);
    driveTo(-300,2000,true,12);
    score();
    arm.spin(forward, 100, percent);
    wait(1000, msec);
    arm.spin(reverse, 100, percent);
    wait(500, msec);
    arm.stop();
}

void _L4B() {
    // Example of using the R4BP function to drive forward 24 inches while maintaining a heading of 0 degrees
    // and then turn to 90 degrees

    // Collect 4 Blocks
    thread meow = thread(scraperthread);
    intake.spin(forward, 100, percent);
    turnToAngle(-13,500,true,10);
    moveToPoint(-6.5,29,1,2000,true,6,false);
    //moveToPoint(6.5,29,-1,2000,true,10,false);
    lever.set(false);
    wait(400,msec);
    turnToAngle(75,1000,true,10);
    driveTo(-300,2000,true,12);
    score();
    arm.spin(forward, 100, percent);
    wait(1000, msec);
    arm.spin(reverse, 100, percent);
    wait(500, msec);
    arm.stop();
}

void _R4B2() {
    // Example of using the R4BP function to drive forward 24 inches while maintaining a heading of 0 degrees
    // and then turn to 90 degrees

    // Collect 4 Blocks
    thread meow = thread(scraperthread);
    intake.spin(forward, 100, percent);
    turnToAngle(13,500,true,10);
    moveToPoint(6.5,29,1,2000,true,6,false);
    lever.set(false);
    wait(400,msec);

    // Collect 2 more blocks
    turnToAngle(50,1000,true,10);    thread woof = thread(scraperthread);
    moveToPoint(23,48,1,2000,true,6,false);
    wait(500,msec);

    // Score 2 blocks
    moveToPoint(6.5,29,-1,2000,true,6,false); wait(50, msec);
    turnToAngle(-40,1000,true,10);
    moveToPoint(-1.5,31,1,2000,true,6,false);
    intake.spin(reverse, 30, percent); wait(600, msec);
    intake.spin(forward, 100, percent);

    // Score 4 blocks
    moveToPoint(6.5,29,1,2000,true,6,false);
    wait(400,msec);
    turnToAngle(-75,1000,true,10);
    driveTo(-300,2000,true,12);
    score();
    arm.spin(forward, 100, percent);
    wait(1000, msec);
    arm.spin(reverse, 100, percent);
    wait(500, msec);
    arm.stop();
}
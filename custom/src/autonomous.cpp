#include "vex.h"
#include "utils.h"
#include "pid.h"
#include <ctime>
#include <cmath>
#include <thread>

#include "../include/autonomous.h"
#include "motor-control.h"

void scraperthread1() {
    wait(1100, msec);
    scraper.set(true); wait(750, msec);
    scraper.set(false);
}

void scraperthread2() {
    wait(900, msec);
    scraper.set(true); wait(750, msec);
    scraper.set(false);
}

void scraperthread() {

}


void score() {
    blockStopper.set(true);
    arm.spin(forward, 100, percent);
    wait(1000, msec);
    arm.spin(reverse, 100, percent);
    wait(500, msec);
    arm.stop();
}


void _R4B() {
    // Example of using the R4BP function to drive forward 24 inches while maintaining a heading of 0 degrees
    // and then turn to 90 degrees

    // Collect 4 Blocks

    // Start Scraper Thread and Intake
    thread meow = thread(scraperthread1);
    intake.spin(forward, 100, percent);
    turnToAngle(13,500,true,10);

    // Collect 3 Blocks
    moveToPoint(6.5,29,1,2000,true,6,false);

    // Let Robot Settle
    lever.set(true);
    wait(400,msec);

    // Turn towards Long Goal
    turnToAngle(-75,1000,true,10); wait(10,msec);

    // Align
    driveTo(-300,2000,true,12);

    // Safety Align
    driveTo(1,500,true,4);
    driveTo(-300,1000,true,12);
    turnToAngle(-180,1000,true,12);

    // Double Score for Safety
    score();
    arm.spin(forward, 100, percent);
    wait(1000, msec);
    arm.spin(reverse, 100, percent);
    wait(500, msec);
    arm.stop();
    blockStopper.set(false);

    wait(1000,msec);
    scraper.set(true);
    driveTo(45,3000,true,8);
    driveTo(-50,2000,true,9);
    score();

}


void _L4B() {
    // Example of using the R4BP function to drive forward 24 inches while maintaining a heading of 0 degrees
    // and then turn to 90 degrees

    // Collect 4 Blocks
    thread meow = thread(scraperthread1);
    intake.spin(forward, 100, percent);
    turnToAngle(-13,500,true,10);
    moveToPoint(-6.5,29,1,2000,true,6,false);
    //moveToPoint(6.5,29,-1,2000,true,10,false);
    lever.set(true);
    turnToAngle(50,1000,true,4);
    driveTo(-500,2000,true,12); wait(50,msec); driveTo(10,500,true,8); wait(50,msec);
    score(); 
    
        // Example of using the R4BP function to drive forward 24 inches while maintaining a heading of 0 degrees
    // and then turn to 90 degrees

    // Collect 4 Blocks

    // Start Scraper Thread and Intake
    thread dsjfld = thread(scraperthread1);
    intake.spin(forward, 100, percent);
    turnToAngle(-13,500,true,10);

    // Collect 3 Blocks
    moveToPoint(-6.5,29,1,2000,true,6,false);

    // Let Robot Settle
    lever.set(true);
    wait(400,msec);

    // Turn towards Long Goal
    turnToAngle(75,1000,true,10); wait(10,msec);

    // Align
    driveTo(-300,2000,true,12);

    // Safety Align
    driveTo(1,500,true,4);
    driveTo(-300,1000,true,12);
    turnToAngle(-180,1000,true,12);

    // Double Score for Safety
    score();
    arm.spin(forward, 100, percent);
    wait(1000, msec);
    arm.spin(reverse, 100, percent);
    wait(500, msec);
    arm.stop();
    blockStopper.set(false);

    wait(1000,msec);
    scraper.set(true);
    driveTo(45,3000,true,8); wait(500,msec);
    driveTo(-50,2000,true,9);
    score();

}

void Skills20() {

    scraper.set(true);
    intake.spin(forward, 100, percent);
    
    driveTo(3,3000,true,6); wait(100,msec); scraper.set(false);
    wait(1000,msec);
    driveTo(10,3000,true,12); wait(500,msec);
    //turnToAngle(180,2000,true,12);
    score();
    driveTo(5,2000,true,12);
    score();
}


void nothing() {
    //driveTo(-5,2000,true,8);
}
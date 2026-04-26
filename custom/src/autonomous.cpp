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

    // Double Score for Safety
    score();
    arm.spin(forward, 100, percent);
    wait(1000, msec);
    arm.spin(reverse, 100, percent);
    wait(500, msec);
    arm.stop();
    blockStopper.set(false);
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
    wait(400,msec);
    turnToAngle(45,1000,true,4);
    wait(3000, msec);
    driveTo(-500,2000,true,12); wait(50,msec); driveTo(10,500,true,8); wait(50,msec);
    score(); 
    /*
    driveTo(-300,2000,true,12);
    driveTo(10,1000,true,8);
    driveTo(-50,1000,true,12);
    score();
    arm.spin(forward, 100, percent);
    wait(1000, msec);
    arm.spin(reverse, 100, percent);
    wait(500, msec);
    arm.stop();
    */
}

void _L6B() {
    
    // Collect 4 Blocks
    thread meow = thread(scraperthread1);
    intake.spin(forward, 100, percent);
    turnToAngle(-13,500,true,10);
    moveToPoint(-6.5,29,1,2000,true,6,false);
    lever.set(true);
    wait(400,msec);

    // Collect 2 more blocks 
    turnToAngle(-50,1000,true,10);    thread woof = thread(scraperthread2);
    //moveToPoint(-23,48,1,2000,true,6,false);
    //wait(500,msec);

}
void _R4B2() {

    // Example of using the R4BP function to drive forward 24 inches while maintaining a heading of 0 degrees
    // and then turn to 90 degrees

    // Collect 4 Blocks
    thread meow = thread(scraperthread1);
    intake.spin(forward, 100, percent);
    turnToAngle(13,500,true,10);
    moveToPoint(6.5,29,1,2000,true,6,false);
    lever.set(true);
    wait(400,msec);

    // Collect 2 more blocks 
    turnToAngle(50,1000,true,10);    thread woof = thread(scraperthread2);
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

void _L4B2() {
    // Collect 4 Blocks
    thread meow = thread(scraperthread1);
    intake.spin(forward, 100, percent);
    //turnToAngle(-13,500,true,10);
    moveToPoint(-6.5,29,1,2000,true,6,false);
    //lever.set(true);
    wait(400,msec);

    
    // Collect 2 more blocks 
    turnToAngle(-69,1000,true,10);    
    thread woof = thread(scraperthread2);
    moveToPoint(-21.75,37,1,2000,true,6,false);
    wait(500,msec);

    // Score 2 blocks
    moveToPoint(3.6,23.5,-1,2000,true,6,false); wait(50, msec);


    turnToAngle(-145,1000,true,10);
    /*
    moveToPoint(1.5,31,1,2000,true,6,false);
    intake.spin(reverse, 30, percent); wait(600, msec);
    intake.spin(forward, 100, percent);

    // Score 4 blocks
    moveToPoint(-6.5,29,-1,2000,true,6,false);
    wait(400,msec);
    turnToAngle(75,1000,true,10);
    driveTo(-300,2000,true,12);
    score();
    */
}

void ninety() {
    turnToAngle(90,2000,true,12);
    turnToAngle(0,2000,true,12);
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
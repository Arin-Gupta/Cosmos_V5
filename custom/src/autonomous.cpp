#include "vex.h"
#include "utils.h"
#include "pid.h"
#include <ctime>
#include <cmath>
#include <thread>

#include "../include/autonomous.h"
#include "motor-control.h"

// IMPORTANT: Remember to add respective function declarations to custom/include/autonomous.h
// Call these functions from custom/include/user.cpp
// Format: returnType functionName() { code }

void ArmAuton() {
  blockStopper.set(true);

  arm.spin(forward, 90, percent);
  wait(1000, msec);

  arm.spin(reverse, 100, percent);
  wait(600, msec);

  blockStopper.set(false);
  arm.stop();
}

void Scraper4BP() {
  wait(900,msec);
  scraper.set(false);
  wait(300,msec);
  scraper.set(true);
}

void R4BP() {
  thread scr(Scraper4BP);
  intake.setVelocity(600, rpm); intake.spin(forward);
  lever.set(false);
  wing.set(false);

  boomerang(13,29,1,45,0.3,2000,true,6,false); wait(300,msec);

  wing.set(true);
  turnToAngle(135, 1000,true,10); wait(100,msec);
  scraper.set(false);
  intake.setVelocity(100, rpm); intake.spin(reverse);
  wait(50,msec);
  intake.setVelocity(600, rpm); intake.spin(forward);  
  scraper.set(true);

  wait(1100, msec);
  
  boomerang(48.5 ,-6.5,1,180,0.1,5000,true,12,false); wait(100, msec);
  turnToAngle(180,1000,false,12);

  moveToPoint(48.5, 30, -1, 1000, true, 12,false);
  moveToPoint(48.5,29.5,1,100,true,12,false);
  turnToAngle(185, 500);
  turnToAngle(175, 500);
  turnToAngle(185, 500);
  turnToAngle(175, 500);
  turnToAngle(180, 500);

  
  thread scoring(ArmAuton);

  wait(1000, msec);

  thread scorin(ArmAuton);

  wait(1000, msec);

  moveToPoint(48.5, 0 ,1,3000,true,11,false);
  turnToAngle(230, 500);
  moveToPoint(57,10,-1,1000, true, 11,false);
  turnToAngle(180, 1000,true,11);
  moveToPoint(57,38,-1,3000,true,11,false);
  stopChassis(hold);
  wait(3000, msec);
  turnToAngle(200, 500, true, 12);

}

void L4BP() {
  // thread scr(Scraper4BP);
  intake.setVelocity(600, rpm); intake.spin(forward);
  wing.set(false);

  boomerang(-13,29,1,45,0.3,2000,true,8,false); wait(100,msec);

  wing.set(true);
  turnToAngle(-135, 1000,true,12); wait(100,msec);
  boomerang(-20,-7.7,1,-180,0.1,5000,true,12,false);
  turnToAngle(-180,1000,false,12);
  moveToPoint(-20, 30, -1, 1000, true, 12,false);
  moveToPoint(-20, 8, 1, 1500, true, 12,false);
  moveToPoint(-20, 30, -1, 1200, true, 12,false);
  
  thread scoring(ArmAuton);

  wait(1000, msec);

  

  moveToPoint(-20, 0 ,1,3000,true,11,false);
  turnToAngle(230, 500);
  moveToPoint(-11.5,25,-1,1000, true, 11,false);
  turnToAngle(180, 1000,true,11);
  

  moveToPoint(-11.5,38,-1,3000,true,11,false);
  stopChassis(hold);
  wait(3000, msec);
  turnToAngle(200, 500, true, 12);

}

void R4_2() {
  intake.setVelocity(600, rpm); intake.spin(forward);

  boomerang(13,29,1,45,0.3,2000,true,8,false);
  turnToAngle(135, 1000,true,12);
  boomerang(45,-7.7,1,180,0.1,5000,true,12,false);
  turnToAngle(180,1000,false,12);
  moveToPoint(45, 30, -1, 1500, true, 12,false);
  thread scoring(ArmAuton); wait(1000, msec);

  turnToAngle(-90, 1000, false, 12);
  boomerang(40,25,1,0,0.1,2000,true,12,false);
  moveToPoint(45,30,1,2000,true,2,false);
}

void Skills15() {
  intake.setVelocity(600,rpm); wait(1000, msec); intake.setVelocity(0, rpm);
}

void Skills20() {
  intake.setVelocity(-600,rpm);
  moveToPoint(0, -19, -1, 5000, true, 6, false);
  moveToPoint(0,100,1,5000,true,12,false);
}

void SAWP() {
  driveTo(10,5000,true,5);
}

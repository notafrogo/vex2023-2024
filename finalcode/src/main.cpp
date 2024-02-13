/*----------------------------------------------------------------------------*/
/* */
/* Module: main.cpp */
/* Author: VEX */
/* Created: Thu Sep 26 2019 */
/* Description: Competition Template */
/* */
/*----------------------------------------------------------------------------*/




// ---- STArm VEXCODE CONFIGURED DEVICES ----
// Robot Configuration:
// [Name]               [Type]        [Porm(s)]
// Controller1          controller                    
// intake               motor         4               
// rb                   motor         10              
// rm                   motor         9               
// rf                   motor         8               
// lf                   motor         3               
// lb                   motor         1               
// lm                   motor         2               
// wings                digital_out   A               
// inert                inertial      19              
// kicker               motor_group   6, 7            
// ---- END VEXCODE CONFIGURED DEVICES ----

#include "vex.h"

using namespace vex;

competition Competition;

double KICK_SPEED = 70;

int auton = 1;
int noa = 4;
void autonselector() {
  if (auton>noa){
    auton=1;
  }
  if (auton<1){
    auton=noa;
  }
  if(Controller1.ButtonRight.pressing()){
    auton++;
    wait(0.1,seconds);
  }
  if(Controller1.ButtonLeft.pressing()) {
    auton--;
    wait(0.1,seconds);
  }
  if(auton == 1){
    Controller1.Screen.clearScreen();
    Controller1.Screen.setCursor(1,1);
    Controller1.Screen.print("Far");
  }
  if(auton == 2){
    Controller1.Screen.clearScreen();
    Controller1.Screen.setCursor(1,1);
    Controller1.Screen.print("Near");
  }
  if(auton == 3){
    Controller1.Screen.clearScreen();
    Controller1.Screen.setCursor(1,1);
    Controller1.Screen.print("Skills");
  }
  if(auton == 4){
    Controller1.Screen.clearScreen();
    Controller1.Screen.setCursor(1,1);
    Controller1.Screen.print("Minor Violation");
  }
}

void dtCode(double x, double y) {
  double leftY = x*Controller1.Axis3.position(percent);
  double rightX = y*pow(Controller1.Axis1.position(percent), 3);
  lf.spin(forward, (leftY+rightX), percent);
  lb.spin(forward, (leftY+rightX), percent);
  lm.spin(forward, (leftY+rightX), percent);
  rf.spin(forward, (leftY-rightX), percent);
  rb.spin(forward, (leftY-rightX), percent);
  rm.spin(forward, (leftY-rightX), percent);
}

void farside(){
}

void closeside(){

}

void skills(){
  
}

void minorViolation(){
  
}

void pre_auton(void) {
  vexcodeInit();
}

void autonomous(void) {
  lf.setStopping(hold);
  lb.setStopping(hold);
  lm.setStopping(hold);
  rf.setStopping(hold);
  rb.setStopping(hold);
  rm.setStopping(hold);
  
  if (auton == 1){
    farside();
  }

  if (auton == 2){
    closeside();
  }

  if (auton == 3){
    skills();
  }

  if (auton == 4){
    minorViolation();
  }
}

// intake
void intakeControl() {
  if (Controller1.ButtonL1.pressing()){
    intake.spin(reverse,90,percent);
  }
  if (Controller1.ButtonL2.pressing()){
    intake.spin(forward,90,percent);
  }
  if(Controller1.ButtonL2.pressing() && Controller1.ButtonL1.pressing()){
    intake.stop();
  }
}

// kicker
bool toggle = false; 
bool latch = false;

void kickerControl() {
  if (toggle){
    kicker.spin(reverse, KICK_SPEED ,percent); 
  } 
  else {
    kicker.stop();
  }
  if (Controller1.ButtonR1.pressing()) {
    if(!latch){ 
      toggle = !toggle;
      latch = true;
    }
  } 
  else {
    latch = false; 
  }
}

// wings
bool toggle2 = false; 
bool latch2 = false;

void wingControl() {
  if (toggle2) {
    wings.set(true);
  }
  else {
    wings.set(false);
  }
  if (Controller1.ButtonR2.pressing()) {
    if (!latch2) {
      toggle2 = !toggle2;
      latch2 = true;
    }
  }
  else {
    latch2 = false;
  }
}

void usercontrol(void) {
  lf.setStopping(brake);
  lb.setStopping(brake);
  lm.setStopping(brake);
  rf.setStopping(brake);
  rb.setStopping(brake);
  rm.setStopping(brake);
  
  while (true){
    dtCode(1, 0.0001);
    autonselector();

    wingControl();
    kickerControl();
    intakeControl();
  }
}

int main() {
  Competition.autonomous(autonomous);
  Competition.drivercontrol(usercontrol);
  pre_auton();
  while (true) {
    wait(20, msec);
  }
}


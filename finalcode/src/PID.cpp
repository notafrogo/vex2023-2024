#include "vex.h"

using namespace vex;

void turnToAngle(float targetAngle) {
  // Initialize PID constants and variables
  inert.setHeading(0, degrees);
  float kp = 0.7; // Replace with your PID constants
  float ki = 0.03;
  float kd = 0.4;
  float starmi = 15;
  float settle_error = 1.0; // Replace with a suitable settle_error for your system
  float settle_time = 20.0; // Replace with a suitable settle_time for your system
  float timeout = 5000.0; // Timeout to prevent infinite loop if unable to settle

  // Initialize variables for PID control
  float accumulated_error = 0;
  float previous_error = 0;
  float output = 0;
  float time_spent_settled = 0;
  float time_spent_running = 0;

  // Initialize current angle as 0 (assuming the gyro sensor measures angles)
  float currentAngle = 0;

  // Loop until the system settles or times out
  while (true) {
    // Read the current angle from the gyro sensor
    currentAngle = inert.heading(degrees);

    // Calculate the error (difference between target and current angles)
    float error = targetAngle - currentAngle;
    
    // Take the shormest route to desired target angle
    if (error > 180) {
      error -= 360;
    }
    if (error < -180) {
      error += 360;
    }

    // PID calculation
    if (fabs(error) < starmi) {
      accumulated_error += error;
    }
    if ((error > 0 && previous_error < 0) || (error < 0 && previous_error > 0)) {
      accumulated_error = 0;
    }

    output = kp * error + ki * accumulated_error + kd * (error - previous_error);
    previous_error = error;

    if (fabs(error) < settle_error) {
      time_spent_settled += 20;
    } else {
      time_spent_settled = 0;
    }

    time_spent_running += 20;

    // Apply control output to the motor
    lf.spin(forward, output, percent);
    lm.spin(forward, output, percent);
    lb.spin(forward, output, percent);
    rf.spin(reverse, output, percent);
    rm.spin(reverse, output, percent);
    rb.spin(reverse, output, percent);

    // Check if settled or timed out
    if (time_spent_running > timeout || time_spent_settled > settle_time) {
      break; // Exit the loop if settled or timed out
    }

    wait(20, msec); // Adjust delay as needed
    
    Controller1.Screen.clearScreen();
    Controller1.Screen.setCursor(1,1);
    Controller1.Screen.print("inertial Heading : %f, ", inert.heading(degrees));
    Controller1.Screen.setCursor(2,1);
    Controller1.Screen.print("Time Spent Settled : %f, ", time_spent_settled);
    Controller1.Screen.setCursor(3,1);
    Controller1.Screen.print("Time Spent : %f, ", time_spent_running);
    
  }

  // Stop the motor after reaching the target angle or timeout
  lf.stop();
  lm.stop();
  lb.stop();
  rf.stop();
  rm.stop();
  rb.stop();
}


void fwd(double duration, int speed) {
  rf.spin(forward, speed, percent);
  rm.spin(forward, speed, percent);
  rb.spin(forward, speed, percent);
  lf.spin(forward, speed, percent);
  lm.spin(forward, speed, percent);
  lb.spin(forward, speed, percent);

  double stopTime = Brain.timer(vex::timeUnits::sec) + duration;

  while (Brain.timer(vex::timeUnits::sec) < stopTime) { }

  rf.stop();
  rm.stop();
  rb.stop();
  lf.stop();
  lm.stop();
  lb.stop();
}


void bkwd(double duration, int speed) {
  rf.spin(reverse, speed, percent);
  rm.spin(reverse, speed, percent);
  rb.spin(reverse, speed, percent);
  lf.spin(reverse, speed, percent);
  lm.spin(reverse, speed, percent);
  lb.spin(reverse, speed, percent);

  double stopTime = Brain.timer(vex::timeUnits::sec) + duration;

  while (Brain.timer(vex::timeUnits::sec) < stopTime) { }

  rf.stop();
  rm.stop();
  rb.stop();
  lf.stop();
  lm.stop();
  lb.stop();
}

void turnRight(double duration) {
  int speed = 20;  
  
  lf.spin(forward, speed, percent);
  lm.spin(forward, speed, percent);
  lb.spin(forward, speed, percent);

  double stopTime = Brain.timer(vex::timeUnits::sec) + duration;

  while (Brain.timer(vex::timeUnits::sec) < stopTime) { }

  lf.stop();
  lm.stop();
  lb.stop();
}

void fullRight(double duration) {
  int speed = 20;  
  
  lf.spin(forward, speed, percent);
  lm.spin(forward, speed, percent);
  lb.spin(forward, speed, percent);
  rf.spin(reverse, speed, percent);
  rm.spin(reverse, speed, percent);
  rb.spin(reverse, speed, percent);

  double stopTime = Brain.timer(vex::timeUnits::sec) + duration;

  while (Brain.timer(vex::timeUnits::sec) < stopTime) { }

  lf.stop();
  lm.stop();
  lb.stop();
}

void turnLeft(double duration) {
  int speed = 20;  
  
  rf.spin(forward, speed, percent);
  rm.spin(forward, speed, percent);
  rb.spin(forward, speed, percent);
  
  double stopTime = Brain.timer(vex::timeUnits::sec) + duration;

  while (Brain.timer(vex::timeUnits::sec) < stopTime) { }

  rf.stop();
  rm.stop();
  rb.stop();
}
void fullLeft(double duration) {
  int speed = 20;
  
  rf.spin(forward, speed, percent);
  rm.spin(forward, speed, percent);
  rb.spin(forward, speed, percent);
  lf.spin(reverse, speed, percent);
  lm.spin(reverse, speed, percent);
  lb.spin(reverse, speed, percent);
  
  double stopTime = Brain.timer(vex::timeUnits::sec) + duration;

  while (Brain.timer(vex::timeUnits::sec) < stopTime) { }

  rf.stop();
  rm.stop();
  rb.stop();
}

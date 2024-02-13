#include "vex.h"

using namespace vex;
using signature = vision::signature;
using code = vision::code;

// A global instance of brain used for printing to the V5 Brain screen
brain  Brain;

// VEXcode device constructors
controller Controller1 = controller(primary);
motor intake = motor(PORT4, ratio6_1, false);
motor rb = motor(PORT10, ratio18_1, false);
motor rm = motor(PORT9, ratio18_1, false);
motor rf = motor(PORT8, ratio18_1, false);
motor lf = motor(PORT3, ratio18_1, true);
motor lb = motor(PORT1, ratio18_1, true);
motor lm = motor(PORT2, ratio18_1, true);
digital_out wings = digital_out(Brain.ThreeWirePort.A);
inertial inert = inertial(PORT19);
motor kickerMotorA = motor(PORT6, ratio18_1, false);
motor kickerMotorB = motor(PORT7, ratio18_1, true);
motor_group kicker = motor_group(kickerMotorA, kickerMotorB);

// VEXcode generated functions
// define variable for remote controller enable/disable
bool RemoteControlCodeEnabled = true;

/**
 * Used to initialize code/tasks/devices added using tools in VEXcode Pro.
 * 
 * This should be called at the start of your int main function.
 */
void vexcodeInit( void ) {
  // nothing to initialize
}
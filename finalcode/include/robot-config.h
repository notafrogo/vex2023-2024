using namespace vex;

extern brain Brain;

// VEXcode devices
extern controller Controller1;
extern motor intake;
extern motor rb;
extern motor rm;
extern motor rf;
extern motor lf;
extern motor lb;
extern motor lm;
extern digital_out wings;
extern inertial inert;
extern motor_group kicker;

/**
 * Used to initialize code/tasks/devices added using tools in VEXcode Pro.
 * 
 * This should be called at the start of your int main function.
 */
void  vexcodeInit( void );
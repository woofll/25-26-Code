#include "main.h"

/////
// For installation, upgrading, documentations, and tutorials, check out our website!
// https://ez-robotics.github.io/EZ-Template/
/////


// Chassis constructor
ez::Drive chassis(
    // These are your drive motors, the first motor is used for sensing!
    {-10, -9, -8},     // Left Chassis Ports (negative port will reverse it!)
    {5, 6, 7},  // Right Chassis Ports (negative port will reverse it!)


    12,      // IMU Port (4 = radio)
    3.25,  // Wheel Diameter (Remember, 4" wheels without screw holes are actually 4.125!) Actual wheels are 3.25
    360);   // Wheel RPM = cartridge * (motor gear / wheel gear) Actual rpm is 360

  // extern bool teamBlue = false;
  bool colorStatus = true;
  bool dP = false;
  bool teamBlue;

  int startTime = 0;
  int scoreTime = 0;

// Uncomment the trackers  you're using here!
// ez::tracking_wheel horiz_tracker(16, 2, 5.25);  // This tracking wheel is perpendicular to the drive wheels
// ez::tracking_wheel vert_tracker(-11, 2, 5.5);   // This tracking wheel is parallel to the drive wheels //og (-11, 2, 5.5) 12/9/25


/**S
 * Runs initialization code. This occurs as soon as the program is started.
 *
 * All other competition modes are blocked by initialize; it is recommended
 * to keep execution time for this mode under a few seconds.
 */
void initialize() {
  // Print our branding over your terminal :D
  ez::ez_template_print();


  pros::delay(300);  // Stop the user from doing anything while legacy ports configure


  // Look at your horizontal tracking wheel and decide if it's in front of the midline of your robot or behind it
  //  - change `back` to `front` if the tracking wheel is in front of the midline
  //  - ignore this if you aren't using a horizontal tracker
  // chassis.odom_tracker_back_set(&horiz_tracker);
  // Look at your vertical tracking wheel and decide if it's to the left or right of the center of the robot
  //  - change `left` to `right` if the tracking wheel is to the right of the centerline
  //  - ignore this if you aren't using a vertical tracker
  // chassis.odom_tracker_left_set(&vert_tracker);
  chassis.odom_enable(true);  // Enable odometry


  // Configure your chassis controls
  chassis.opcontrol_curve_buttons_toggle(true);   // Enables modifying the controller curve with buttons on the joysticks
  chassis.opcontrol_drive_activebrake_set(0.0);   // Sets the active brake kP. We recommend ~2.  0 will disable.
  chassis.opcontrol_curve_default_set(0.0, 0.0);  // Defaults for curve. If using tank, only the first parameter is used. (Comment this line out if you have an SD card!)


  // Set the drive to your own constants from autons.cpp!
  default_constants();
  int initialColor = global::color.get_hue();
  if (initialColor > 120 && initialColor < 250) { //Checks if blue, if so = true
    teamBlue = true;  
  }

  // These are already defaulted to these buttons, but you can change the left/right curve buttons here!
  // chassis.opcontrol_curve_buttons_left_set(pros::E_CONTROLLER_DIGITAL_LEFT, pros::E_CONTROLLER_DIGITAL_RIGHT);  // If using tank, only the left side is used.
  // chassis.opcontrol_curve_buttons_right_set(pros::E_CONTROLLER_DIGITAL_Y, pros::E_CONTROLLER_DIGITAL_A);


  // Autonomous Selector using LLEMU
  ez::as::auton_selector.autons_add({
      Auton{"LEFT Top Goal ONLY", leftTop},
      Auton{"RIGHT Top Goal ONLY", rightTop},
      Auton{"LEFT Mid + Top Goals", leftMid},
      Auton{"RIGHT Mid + Top Goals", rightMid},
      Auton{"SOLO WINNERSSSS", SAWP},
      Auton{"Skills", skills},

  });


  // Initialize chassis and auton selector
  chassis.initialize();
  ez::as::initialize();
  master.rumble(chassis.drive_imu_calibrated() ? "." : "---");
}


/**
 * Runs while the robot is in the disabled state of Field Management System or
 * the VEX Competition Switch, following either autonomous or opcontrol. When
 * the robot is enabled, this task will exit.
 */
void disabled() {
  // . . .
}


/**
 * Runs after initialize(), and before autonomous when connected to the Field
 * Management System or the VEX Competition Switch. This is intended for
 * competition-specific initialization routines, such as an autonomous selector
 * on the LCD.
 *
 * This task will exit when the robot is enabled and autonomous or opcontrol
 * starts.
 */
void competition_initialize() {
  // . . .
}


/**
 * Runs the user autonomous code. This function will be started in its own task
 * with the default priority and stack size whenever the robot is enabled via
 * the Field Management System or the VEX Competition Switch in the autonomous
 * mode. Alternatively, this function may be called in initialize or opcontrol
 * for non-competition testing purposes.
 *
 * If the robot is disabled or communications is lost, the autonomous task
 * will be stopped. Re-enabling the robot will restart the task, not re-start it
 * from where it left off.
 */
void autonomous() {
  chassis.pid_targets_reset();                // Resets PID targets to 0
  chassis.drive_imu_reset();                  // Reset gyro position to 0
  chassis.drive_sensor_reset();               // Reset drive sensors to 0
  chassis.odom_xyt_set(0_in, 0_in, 0_deg);    // Set the current position, you can start at a specific position with this
  chassis.drive_brake_set(MOTOR_BRAKE_HOLD);  // Set motors to hold.  This helps autonomous consistency.
  ez::as::auton_selector.selected_auton_call();  // Calls selected auton from autonomous selector

}


/**
 * Simplifies printing tracker values to the brain screen
 */
void screen_print_tracker(ez::tracking_wheel *tracker, std::string name, int line) {
  std::string tracker_value = "", tracker_width = "";
  // Check if the tracker exists
  if (tracker != nullptr) {
    tracker_value = name + " tracker: " + util::to_string_with_precision(tracker->get());             // Make text for the tracker value
    tracker_width = "  width: " + util::to_string_with_precision(tracker->distance_to_center_get());  // Make text for the distance to center
  }
  ez::screen_print(tracker_value + tracker_width, line);  // Print final tracker text
}


/**
 * Ez screen task
 * Adding new pages here will let you view them during user control or autonomous
 * and will help you debug problems you're having
 */
void ez_screen_task() {
  while (true) {
    // Only run this when not connected to a competition switch
    if (!pros::competition::is_connected()) {
      // Blank page for odom debugging
      if (chassis.odom_enabled() && !chassis.pid_tuner_enabled()) {
        // If we're on the first blank page...
        if (ez::as::page_blank_is_on(0)) {
          // Display X, Y, and Theta
          ez::screen_print("x: " + util::to_string_with_precision(chassis.odom_x_get()) +
                               "\ny: " + util::to_string_with_precision(chassis.odom_y_get()) +
                               "\na: " + util::to_string_with_precision(chassis.odom_theta_get()),
                      
                           1);  // Don't override the top Page line
      
          
          // Display all trackers that are being used
          screen_print_tracker(chassis.odom_tracker_left, "l", 4);
          screen_print_tracker(chassis.odom_tracker_right, "r", 5);
          screen_print_tracker(chassis.odom_tracker_back, "b", 6);
          screen_print_tracker(chassis.odom_tracker_front, "f", 7);
          // chassis.pid_wait c
        }
      }
    }


    // Remove all blank pages when connected to a comp switch
    else {
      if (ez::as::page_blank_amount() > 0)
        ez::as::page_blank_remove_all();
    }


    pros::delay(ez::util::DELAY_TIME);
  }
}
pros::Task ezScreenTask(ez_screen_task);


/**
 * Gives you some extras to run in your opcontrol:
 * - run your autonomous routine in opcontrol by pressing DOWN and B
 *   - to prevent this from accidentally happening at a competition, this
 *     is only enabled when you're not connected to competition control.
 * - gives you a GUI to change your PID values live by pressing X
 */
void ez_template_extras() {
  // Only run this when not connected to a competition switch
  if (!pros::competition::is_connected()) {
    // PID Tuner
    // - after you find values that you're happy with, you'll have to set them in auton.cpp


    // Enable / Disable PID Tuner
    //  When enabled:
    //  * use A and Y to increment / decrement the constants
    //  * use the arrow keys to navigate the constants
    if (master.get_digital_new_press(DIGITAL_X))
      chassis.pid_tuner_toggle();


    // Trigger the selected autonomous routine
    if (master.get_digital(DIGITAL_B) && master.get_digital(DIGITAL_DOWN)) {
      pros::motor_brake_mode_e_t preference = chassis.drive_brake_get();
      autonomous();
      chassis.drive_brake_set(preference);
    }


    // Allow PID Tuner to iterate
    chassis.pid_tuner_iterate();
  }


  // Disable PID Tuner when connected to a comp switch
  else {
    if (chassis.pid_tuner_enabled())
      chassis.pid_tuner_disable();
  }
}

void scoreColorSort() {  
  
    int opticalDistance = global::color.get_proximity(); //Timing
    int activeColor = global::color.get_hue();
    int currentTime = pros::millis();
    int scoreDuration = 180;
  if (master.get_digital_new_press(DIGITAL_B)) { // Y is pressed, reset score time
    pros::lcd::set_text(3, std::to_string((scoreTime)));
    scoreTime = pros::millis();
  }

  if (colorStatus == true){ // If color sorting is active.
    if (opticalDistance > 150 && master.get_digital(DIGITAL_Y)) { // If we are detecting a ball and scoring top
      if (teamBlue == true){ // And If we are blue
        if (activeColor > 0 && activeColor < 40){ // We detect red
        global::hoodRoller.move_velocity(200); //Reversal; Balls shoot out mid
        } 
        //   else {
        //    outTop();
        // }

    } else if (teamBlue == false) { // And If we are red
        if (activeColor > 120 && activeColor < 250){ // We detect blue
        global::hoodRoller.move_velocity(200); //Reversal; Balls shoot out mid
        }
       //   else {
        //    outTop();
        // }
    }
/**/
 } else if (opticalDistance > 150 && master.get_digital(DIGITAL_B)) { // If we are detecting a ball and scoring mid 
      if (teamBlue == true){ // And If we are blue
        if (activeColor > 0 && activeColor < 40){ // We detect red
        global::hoodRoller.move_velocity(-200); //Reversal; Balls shoot out top
        global::hood.set_value(true);
        }
          //  if (master.get_digital(DIGITAL_B) && (currentTime - scoreTime) < scoreDuration){ 
          //   global::hoodRoller.move_velocity(-600);
          // } else if (master.get_digital(DIGITAL_B) && (currentTime - scoreTime) >= scoreDuration) {
          //     outMid();
          // }

      } else if (teamBlue == false) { // And If we are red
        if (activeColor > 120 && activeColor < 250){ // We detect blue
        global::hoodRoller.move_velocity(-200); //Reversal; Balls shoot out top
        global::hood.set_value(true);
      }
      //   else {
        //    outMid();
        // }
    }
  } else {} // If we don't see anything, do nothing
 } else if (colorStatus == false) {} //If color sorting is inactive, do nothing


}

void intakeColorSort() {
int opticalDistance = global::color.get_proximity();
int activeColor = global::color.get_hue();
  if (opticalDistance < 150) { // If we are detecting a ball 
    if (teamBlue == true){ // And If we are blue
      if (activeColor > 0 && activeColor < 50){ // We detect red
        global::hood.extend();
        global::hoodRoller.move_velocity(-200); //Reversal; Balls shoot out top
      }

   } else if (teamBlue == false) { // And If we are red
      if (activeColor > 120 && activeColor < 250){ // We detect blue
        global::hood.extend();
        global::hoodRoller.move_velocity(-200); //Reversal; Balls shoot out top
      }
    }
  }
}

void TESTColorSort() {
int opticalDistance = global::color.get_proximity(); //og wasn't here
int activeColor = global::color.get_hue();
  if (opticalDistance > 150) { //  we are detecting a ball and scoring top
    if (teamBlue == true){ // And If we are blue
      if (activeColor > 0 && activeColor < 40){ // We detect red
        global::testMotor1.move_velocity(-200); //Reversal; Balls shoot out mid
      }

   } else if (teamBlue == false) { // And If we are red
      if (activeColor > 120 && activeColor < 250){ // We detect blue
        global::testMotor1.move_velocity(-200); //Reversal; Balls shoot out mid
      }
    }
  }
}

// void timer() {
//     int currentTime = pros::millis();
//     int duration = 500; //0.5 seconds
//     if (currentTime - startTime >= duration){
//       pros::lcd::set_text(7, std::to_string((currentTime)));
//       startTime = currentTime;
//     }
// }


/**
 * Runs the operator control code. This function will be started in its own task
 * with the default priority and stack size whenever the robot is enabled via
 * the Field Management System or the VEX Competition Switch in the operator
 * control mode.
 *
 * If no competition control is connected, this function will run immediately
 * following initialize().
 *
 * If the robot is disabled or communications is lost, the
 * operator control task will be stopped. Re-enabling the robot will restart the
 * task, not resume it from where it left off.
 */

/**************************************************************************************************************************************  */
void opcontrol() { 
  // This is preference to what you like to drive on
  chassis.drive_brake_set(MOTOR_BRAKE_COAST);
  // chassis.odom_enable(false);

  // variable start
  bool tongue = true; //Tongue is up
  bool descore = false; //Descore is retracted
  bool intaked = false; //Intaking is active
  bool y = false;

  teamBlue = true;

  while (true) {
    // Gives you some extras to make EZ-Template ezier
    ez_template_extras();
    int activeColor = global::color.get_hue();
    int opticalDistance = global::color.get_proximity();
    int currentTime = pros::millis();
    int scoreDuration = 150;
    teamBlue = true;

    // pros::lcd::set_text (4, std::to_string(teamBlue));
    // pros::lcd::set_text(5, std::to_string(colorStatus));
    // pros::lcd::set_text(6, std::to_string(global::color.get_proximity()));
    // pros::lcd::set_text(7, std::to_string(global::color.get_hue()));
    pros::lcd::set_text(7, std::to_string(chassis.drive_imu_get()));
 
      // pros::lcd::set_text(2, std::to_string(scoreDuration));
      // pros::lcd::set_text(3, std::to_string((scoreTime)));
      // pros::lcd::set_text(4, std::to_string((currentTime)));
      // pros::lcd::set_text(5, std::to_string(master.get_digital(DIGITAL_Y)));
      // pros::lcd::set_text(6, std::to_string(y));
      // pros::lcd::set_text(7, std::to_string(pros::millis()));

  // if (master.get_digital_new_press(DIGITAL_B)) { // B is pressed, reset score time
  //   pros::lcd::set_text(3, std::to_string((scoreTime)));
  //   scoreTime = pros::millis();
  //     if (!y) {
  //       y = true;
  //     } else if (y) {
  //       y = false;
  //     }
  // }

    bool top = master.get_digital(DIGITAL_B); // Value depends on if we scoring top
    bool mid = master.get_digital(DIGITAL_Y); // Value depends on if we scoring mid

    if (!pros::competition::is_connected()){
      if (master.get_digital(DIGITAL_L1) && master.get_digital(DIGITAL_R2)) {
        // turnCW90();
        driveFwd24();
      }   
      if (master.get_digital(DIGITAL_L1) && master.get_digital(DIGITAL_R1)){
        // turnCCW90();
        driveBack24();
      }
    //   if (master.get_digital(DIGITAL_B) && master.get_digital(DIGITAL_UP)){
    //     driveFwd24();
    //   }
    //   if (master.get_digital(DIGITAL_B) && master.get_digital(DIGITAL_DOWN)){
    //     driveBack24();
    //   }
     }
    
    // chassis.opcontrol_tank();  // Tank control
    chassis.opcontrol_arcade_standard(ez::SPLIT);   // Standard split arcade !!!USE THIS!!!!
    // chassis.opcontrol_arcade_standard(ez::SINGLE);  // Standard single arcade
    // chassis.opcontrol_arcade_flipped(ez::SPLIT);    // Flipped split arcade
    // chassis.opcontrol_arcade_flipped(ez::SINGLE);   // Flipped single arcade

    
    if (master.get_digital(DIGITAL_DOWN)) { // DOWN Toggle = Match Loader
      global::descore.set_value(false);
    } else if(!master.get_digital(DIGITAL_DOWN)) {
      global::descore.set_value(true);
    }
    if (master.get_digital(DIGITAL_L2)) { // DOWN Toggle = Match Loader
      global::tongue.extend();
    } else if (!master.get_digital(DIGITAL_L2)) {
      global::tongue.retract();
    }

    if (master.get_digital(DIGITAL_R2)){ // R2 Hold = Intake In
      intake();
    } else if (master.get_digital(DIGITAL_R1)){// R1 Hold = Reverse Intake/Bottom Goal Score
      outLow();
    } else if (master.get_digital(DIGITAL_Y)){// Y Hold = Top Goal Score
      outTop();
    } else if (master.get_digital(DIGITAL_B)) {// B Hold = Middle Goal Score
       if (master.get_digital(DIGITAL_B) && (currentTime - scoreTime) < scoreDuration){ 
        // global::topRoller.move_velocity(-200);
        global::hoodRoller.move_velocity(-200);
      } else if (master.get_digital(DIGITAL_B) && (currentTime - scoreTime) >= scoreDuration) {
        outMid();
      }
    } else { // Stop all motors if nothing pressed
      stopAll();
    }



    pros::delay(ez::util::DELAY_TIME);  // This is used for timer calculations!  Keep this ez::util::DELAY_TIME
    } 
  }


/******************************************************************************************************************************** */
  // void opcontrol() { //TEST OP CONTROL
  //   chassis.drive_brake_set(MOTOR_BRAKE_COAST);
  //  while (true) {
  //   // Gives you some extras to make EZS-Template ezier
  //   global::color.set_led_pwm(35);
  //   pros::lcd::set_text (5, std::to_string(teamBlue));
  //   pros::lcd::set_text(6, std::to_string(global::color.get_proximity()));
  //   pros::lcd::set_text(7, std::to_string(global::color.get_hue()));
  //   ez_template_extras();
  //   if (master.get_digital_new_press(DIGITAL_L2)){
  //     if (teamBlue) {
  //       teamBlue = false;
  //     } else if (!teamBlue) {
  //       teamBlue = true;
  //     }
  //   }
  //   if (master.get_digital(DIGITAL_R2)) {
  //     global::testMotor1.move_velocity(200);
  //     TESTColorSort();
  //   } else {
  //     global::testMotor1.brake();
  //   }
  //   pros::delay(ez::util::DELAY_TIME);  // This is used for timer calculations!  Keep this ez::util::DELAY_TIME
  //   }
  // }


//run this before pros m
//    pros m --project "c:\Users\jaych\Desktop\25-26 Code!\25-26-Code-main\Code"
//    pros mu --project "c:\Users\jaych\Desktop\25-26 Code!\25-26-Code-main\Code"
//idk why but for now do it
// PID site https://ez-robotics.github.io/EZ-Template/tutorials/tuning_pid_constants\
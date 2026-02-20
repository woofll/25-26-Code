#include "main.h"

/////
// For installation, upgrading, documentations, and tutorials, check out our website!
// https://ez-robotics.github.io/EZ-Template/
/////


// Chassis constructor
ez::Drive chassis(
    // These are your drive motors, the first motor is used for sensing!
     {-5, -8, 20},     // Left Chassis Ports (negative port will reverse it!) (10, -9, -8)
    {6, -19, 7}, // Right Chassis Ports (negative port will reverse it!) (5, 6, 7)

    11,      // IMU Port (4 = radio)
    3.22,  // Wheel Diameter (Remember, 4" wheels without screw holes are actually 4.125!) Actual wheels are 3.25
    450);   // Wheel RPM = cartridge * (motor gear / wheel gear) Actual rpm is 360

  // extern bool teamBlue = false;
  bool colorStatus = false;
  bool teamBlue = false;

  double startTime, scoreTime, colorTime, midTime = 0;


// Uncomment the trackers  you're using here!
// ez::tracking_wheel horiz_tracker(16, 2, 5.25);  // This tracking wheel is perpendicular to the drive wheels
ez::tracking_wheel vert_tracker(-18, 2.001, 0.02);   // This tracking wheel is parallel tfo the drive wheels 


/**S
 * Runs initialization code. This occurs as soon as the program is started.
 *
 * All other competition modes are blocked by initialize; it is recommended
 * to keep execution time for this mode under a few seconds.
 */
void initialize() {
  // Print our branding over your terminal :D
  ez::ez_template_print();


  pros::delay(500);  // Stop the user from doing anything while legacy ports configure


  // Look at your horizontal tracking wheel and decide if it's in front of the midline of your robot or behind it
  //  - change `back` to `front` if the tracking wheel is in front of the midline
  //  - ignore this if you aren't using a horizontal tracker
  // chassis.odom_tracker_back_set(&horiz_tracker);
  // Look at your vertical tracking wheel and decide if it's to the left or right of the center of the robot
  //  - change `left` to `right` if the tracking wheel is to the right of the centerline
  //  - ignore this if you aren't using a vertical tracker
  chassis.odom_tracker_left_set(&vert_tracker);
  chassis.odom_enable(true);  // Enable odometry


  // Configure your chassis controls
  chassis.opcontrol_curve_buttons_toggle(false);   // Enables modifying the controller curve with buttons on the joysticks
  chassis.opcontrol_drive_activebrake_set(0.0);   // Sets the active brake kP. We recommend ~2.  0 will disable.
  chassis.opcontrol_curve_default_set(2.5, 2.5);  // Defaults for curve. If using tank, only the first parameter is used. (Comment this line out if you have an SD card!)


  // Set the drive to your own constants from autons.cpp!
  default_constants();
  if (global::colorF.get_hue() > 75 && global::colorF.get_hue() < 250) { //Checks if blue, if so = true
    teamBlue = true;
  } else if (!(global::colorF.get_hue() > 75 && global::colorF.get_hue() < 250)){
    teamBlue = false;
  }

  // These are already defaulted to these buttons, but you can change the left/right curve buttons here!
  // chassis.opcontrol_curve_buttons_left_set(pros::E_CONTROLLER_DIGITAL_LEFT, pros::E_CONTROLLER_DIGITAL_RIGHT);  // If using tank, only the left side is used.
  // chassis.opcontrol_curve_buttons_right_set(pros::E_CONTROLLER_DIGITAL_Y, pros::E_CONTROLLER_DIGITAL_A);


  // Autonomous Selector using LLEMU
  ez::as::auton_selector.autons_add({
      Auton{"gofoward!", goforward},
      Auton{"LEFT MID 3 + 4", leftMid},
      Auton{"RIGHT MID 3 + 4", rightMid},
      Auton{"LEFT Top Goal + Descore ONLY 7", leftTopDescore},
      Auton{"RIGHT Top Goal + Descore ONLY 7", rightTopDescore},
      Auton{"winninigning SAWP", SAWP},
      Auton{"LEFT antisawp", leftAntiSAWP},
      Auton{"RIGHT antisawp", rightAntiSAWP},
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
      chassis.pid_tuner_full_enable(true);  // Enable full PID Tuner

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

  while (true) {
    ez_template_extras();

    int activeColorF = global::colorF.get_hue();
    int opticalDistanceF = global::colorF.get_proximity();
    int activeColorB = global::colorB.get_hue();
    int opticalDistanceB = global::colorB.get_proximity();

    int currentTime = pros::millis();
    int scoreDuration = 200;
    int midTime = 300;
    int lowTime = 200;
    int colorTimeDuration = 200;
    // i am a monkey
    global::colorB.set_integration_time(5);
    global::colorB.set_led_pwm(20);
    global::colorF.set_integration_time(5);
    global::colorF.set_led_pwm(20);

    // pros::lcd::set_text (4, std::to_string(teamBlue));
    // pros::lcd::set_text(5, std::to_string(colorTime));
    // pros::lcd::set_text(7, std::to_string(global::colorF.get_proximity()));
    // pros::lcd::set_text(5, std::to_string(global::colorB.get_hue()));
    //   pros::lcd::set_text(6, std::to_string(global::colorF.get_hue()));
    pros::lcd::set_text(7, std::to_string(chassis.drive_imu_get()));
 
      // pros::lcd::set_text(2, std::to_string(scoreDuration));
      // pros::lcd::set_text(3, std::to_string((scoreTime)));
      // pros::lcd::set_text(4, std::to_string((currentTime)));
      // pros::lcd::set_text(5, std::to_string(master.get_digital(DIGITAL_Y)));
      // pros::lcd::set_text(6, std::to_string(y));
      // pros::lcd::set_text(7, std::to_string(pros::millis()));

    if (teamBlue){ // We are BLUE
      if (activeColorF > 0 && activeColorF < 25){ // We see RED, update colorTime
        colorTime = pros::millis();
      } else if (activeColorB > 0 && activeColorB < 25){
        colorTime = pros::millis() - 130;
      }
    }

    if (!teamBlue){ // We are RED
      if (activeColorF > 75 && activeColorF < 250){ // We see BLUE, update colorTime
        colorTime = pros::millis();
      } else if (activeColorB > 75 && activeColorB < 250){
        colorTime = pros::millis() - 130;
      }
    }

    if (master.get_digital(DIGITAL_UP)){ // Disables/Enables Color Sorting
      if (colorStatus == true){
        colorStatus = false;
       master.rumble(".--");
      } else if (colorStatus == false){
        colorStatus = true;
        master.rumble(".");
      }
    }

    if (master.get_digital_new_press(DIGITAL_A)) { // A is pressed, change team colors (used for testing)
     if (!teamBlue) {
      teamBlue = true;
     } else if (teamBlue){
      teamBlue = false;
     }
   }
// /************************************************************************************************************************************************************************* */

    if (!pros::competition::is_connected()){
      if (master.get_digital(DIGITAL_L1)) {
        // measure_offsets();
        // chassis.drive_sensor_reset();
        // SAWP();
        // leftMid();
        //rightAntiSAWP();
        // leftTopDescore();
        // rightTopDescore();
        // skills();
        // leftAntiSAWP();
        // rightAntiSAWP();
      // goforward();
      }   
    }
      // if (master.get_digital(DIGITAL_L1) && master.get_digital(DIGITAL_A)){
      //   // driveFwd24();
      //   // leftMid();
      // }
     
      
/*********************************************************     CAM CONTROLS      ******************************************************************************************** */
  chassis.opcontrol_arcade_standard(ez::SPLIT);   // Standard split arcade !!!USE THIS!!!!
  //  chassis.opcontrol_tank();
    
    if (master.get_digital_new_press(DIGITAL_B) || master.get_digital_new_press(DIGITAL_R1)) { // B or R1 is pressed, reset scoretime
    pros::lcd::set_text(3, std::to_string((scoreTime)));
    scoreTime = pros::millis();
   }
    
    if (master.get_digital(DIGITAL_DOWN)) { // L2 Toggle = Match Loader
      global::descore.retract();
    } else if (!master.get_digital(DIGITAL_DOWN)) {
      global::descore.extend();
    }

    if (master.get_digital(DIGITAL_L2)) { // L2 Toggle = Match Loader
      global::tongue.extend();
    } else if (!master.get_digital(DIGITAL_L2)) {
      global::tongue.retract();
    }

    if (master.get_digital(DIGITAL_R2)){ // R2 Hold = Intake In
      intake();
      
        // if (teamBlue == true && colorStatus == true){ // If we ARE blue,
        //     if ((currentTime - colorTime) < colorTimeDuration){
        //       global::intake.move_velocity(600);
        //       global::topRoller.move_velocity(160);
        //       global::hoodRoller.move_velocity(-160);
        //     } else if ((currentTime - colorTime) >= colorTimeDuration){
        //       intake(); //Intake as normal
        //     }
        // } else if (teamBlue == false && colorStatus == true){ // If we ARE red,
        //     if ((currentTime - colorTime) < colorTimeDuration){
        //       global::intake.move_velocity(600);
        //       global::topRoller.move_velocity(160);
        //       global::hoodRoller.move_velocity(-160);
        //     } else if ((currentTime - colorTime) >= colorTimeDuration){
        //       intake(); // Top as normal
        //     }
        // } else {
        //   intake();
        // }

    } else if (master.get_digital(DIGITAL_R1)){// R1 Hold = Reverse Intake/Bottom Goal Score
       if ((currentTime - scoreTime) < lowTime){ // Hood Roller doesn't spin for lowTime
        global::intake.move_velocity(-600);
        global::topRoller.move_velocity(-200);
        global::hoodRoller.brake();

        // global::intakeLift.extend(); //
      } else if ((currentTime - scoreTime) >= lowTime) { // After lowTime since R1, outLow as normal
        outLow();

        // global::intakeLift.extend(); //
      }
    } else if (master.get_digital(DIGITAL_Y)){// Y Hold = Top Goal Score
      // outTop();
      // global::hood.extend();

        if (teamBlue == true && colorStatus == true){ // If we ARE blue,
            if ((currentTime - colorTime) < colorTimeDuration){
              global::intake.move_velocity(600);
              global::topRoller.move_velocity(70);
              global::hoodRoller.move_velocity(-110);
            } else if ((currentTime - colorTime) >= colorTimeDuration){
              global::intake.move_velocity(600);
              global::topRoller.move_velocity(140);   
              global::hoodRoller.move_velocity(170);
              global::hood.set_value(true);
            }
        } else if (teamBlue == false  && colorStatus == true){ // If we ARE red,
            if ((currentTime - colorTime) < colorTimeDuration){
              global::intake.move_velocity(600);
              global::topRoller.move_velocity(70);
              global::hoodRoller.move_velocity(-110);
            } else if ((currentTime - colorTime) >= colorTimeDuration){
              global::intake.move_velocity(600);
              global::topRoller.move_velocity(140);   
              global::hoodRoller.move_velocity(170);
              global::hood.set_value(true);
            }
        } else {
          outTop();
          global::hood.extend();
        }

    } else if (master.get_digital(DIGITAL_B)) {// B Hold = Middle Goal Score
       if (master.get_digital(DIGITAL_B) && (currentTime - scoreTime) < scoreDuration){ 
        global::topRoller.move_velocity(-200);
        global::hoodRoller.move_velocity(-100);
      } else if (master.get_digital(DIGITAL_B) && (currentTime - scoreTime) >= scoreDuration) {
        // outMid();

        // global::intake.move_velocity(300);
        // global::topRoller.move_velocity(60);
        // global::hoodRoller.move_velocity(-40);
        // global::hood.set_value(false);
      }
    } else { // Stop all motors if nothing pressed
      stopAll();
    }

    /*******************************************************      JAYDEN CONTROLS       *************************************************************************************** */

  //   chassis.opcontrol_tank();  // Tank control

  //   if (master.get_digital_new_press(DIGITAL_Y) || (master.get_digital_new_press(DIGITAL_L1))) { // Y or L1 is pressed, reset scoreTime
  //   pros::lcd::set_text(3, std::to_string((scoreTime)));
  //   scoreTime = pros::millis();
  // }

  //   if (master.get_digital(DIGITAL_L1)) { // L1 Toggle = Descore
  //     global::descore.retract();
  //   } else if(!master.get_digital(DIGITAL_L1)) {
  //     global::descore.extend();
  //   }

  //   // if (master.get_digital_new_press(DIGITAL_L1)) { // L1 Toggle = Descore
  //   //   global::descore.toggle();
  //   // } 

  //   if (master.get_digital(DIGITAL_DOWN)) { // DOWN Toggle = Match Loader
  //     global::tongue.extend();
  //   } else if (!master.get_digital(DIGITAL_DOWN)) {
  //     global::tongue.retract();
  //   }
  //   if (master.get_digital(DIGITAL_R2)){ // R2 Hold = Intake In
  //     intake();
      
  //       // if (teamBlue == true && colorStatus == true){ // If we ARE blue,
  //       //     if ((currentTime - colorTime) < colorTimeDuration){
  //       //       global::intake.move_velocity(600);
  //       //       global::topRoller.move_velocity(160);
  //       //       global::hoodRoller.move_velocity(-160);
  //       //     } else if ((currentTime - colorTime) >= colorTimeDuration){
  //       //       intake(); //Intake as normal
  //       //     }
  //       // } else if (teamBlue == false /* && colorStatus == true */ ){ // If we ARE red,
  //       //     if ((currentTime - colorTime) < colorTimeDuration){
  //       //       global::intake.move_velocity(600);
  //       //       global::topRoller.move_velocity(160);
  //       //       global::hoodRoller.move_velocity(-160);
  //       //     } else if ((currentTime - colorTime) >= colorTimeDuration){
  //       //       intake(); // Top as normal
  //       //     }
  //       // } else {
  //       //   intake();
  //       // }
  //   } else if (master.get_digital(DIGITAL_L2)){// L2 Hold = Reverse Intake/Bottom Goal Score
  //      if ((currentTime - scoreTime) < lowTime){ // Hood Roller doesn't spin for lowTime
  //       global::intake.move_velocity(-600);
  //       global::topRoller.move_velocity(-200);
  //       global::hoodRoller.brake();
  //     } else if ((currentTime - scoreTime) >= lowTime) { // After lowTime since R1, outLow as normal
  //       outLow();
  //       global::intakeLift.extend();
  //     }
  //   } else if (master.get_digital(DIGITAL_B)){// B Hold = Top Goal Score
  //     outTop();
  //     global::hood.extend();

  //       // if (teamBlue == true && colorStatus == true){ // If we ARE blue,
  //       //     if ((currentTime - colorTime) < colorTimeDuration){
  //       //       global::intake.move_velocity(600);
  //       //       global::topRoller.move_velocity(140);
  //       //       global::hoodRoller.move_velocity(-130);
  //       //     } else if ((currentTime - colorTime) >= colorTimeDuration){
  //       //       global::intake.move_velocity(600);
  //       //       global::topRoller.move_velocity(175);   
  //       //       global::hoodRoller.move_velocity(200);
  //       //       global::hood.set_value(true);
  //       //     }
  //       // } else if (teamBlue == false  && colorStatus == true  ){ // If we ARE red,
  //       //     if ((currentTime - colorTime) < colorTimeDuration){
  //       //       global::intake.move_velocity(600);
  //       //       global::topRoller.move_velocity(140);
  //       //       global::hoodRoller.move_velocity(-130);
  //       //     } else if ((currentTime - colorTime) >= colorTimeDuration){
  //       //       global::intake.move_velocity(600);
  //       //       global::topRoller.move_velocity(175);   
  //       //       global::hoodRoller.move_velocity(200);
  //       //       global::hood.set_value(true);
  //       //     }
  //       // } else {
  //       //   outTop();
  //       // }
  //   } else if (master.get_digital(DIGITAL_Y)) {// Y Hold = Middle Goal Score
  //      if (master.get_digital(DIGITAL_Y) && (currentTime - scoreTime) < scoreDuration){ 
  //       global::topRoller.move_velocity(-200);
  //       global::hoodRoller.move_velocity(200);
  //     } else if (master.get_digital(DIGITAL_Y) && ((currentTime - scoreTime) >= scoreDuration) && (((currentTime - scoreTime) < midTime))) {
  //       outMidSkillsFast();
  //     } else if (master.get_digital(DIGITAL_Y) && (currentTime - scoreTime) >= midTime){
  //       outMidSkillsSlow();
  //     }
  //   } else { // Stop all motors if nothing pressed
  //     stopAll();
  //   }

/****************************************************************************************************************************************************************************************** */
    pros::delay(ez::util::DELAY_TIME);  // This is used for timer calculations!  Keep this ez::util::DELAY_TIME
    } 
  }


//run this before pros m
//    pros m --project "c:\Users\jaych\Desktop\25-26 Code!\25-26-Code-main\Code"
//    pros mu --project "c:\Users\jaych\Desktop\25-26 Code!\25-26-Code-main\Code"
//idk why but for now do it
// PID site https://ez-robotics.github.io/EZ-Template/tutorials/tuning_pid_constants
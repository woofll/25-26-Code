#include "main.h"
//void functionName(){
// description of the function
//}

bool hoodie = false;
int activeTime = pros::millis();
int pressTime;

static bool qbActive = false;


void intake() {
    global::intake.move_velocity(600);
    global::topRoller.move_velocity(200);
    global::hoodRoller.brake();
}
void reverseIntake() {
    global::intake.move_velocity(-600);
    global::topRoller.move_velocity(-200);
}

bool reversePhase = false;
int reverseStartTime = 0;

void outTop() {
    if (master.get_digital(DIGITAL_Y)) {

        // 1. If button just pressed → begin the 100 ms reverse phase
        if (!reversePhase && master.get_digital_new_press(DIGITAL_Y)) {
            reversePhase = true;
            reverseStartTime = pros::millis();

            global::intake.move_velocity(-600);
            global::topRoller.move_velocity(-200);
            global::hoodRoller.move_velocity(200);
        }

        // 2. If reverse phase is active, check if 100 ms have passed
        if (reversePhase) {
            if (pros::millis() - reverseStartTime >= 100) {
                reversePhase = false;

                // Switch to normal forward direction
                global::intake.move_velocity(600);
                global::topRoller.move_velocity(200);
                global::hoodRoller.move_velocity(-200);
                global::hood.set_value(true);
            }
        }

        // 3. After reverse phase is over and button still held
        if (!reversePhase) {
            global::intake.move_velocity(600);
            global::topRoller.move_velocity(200);
            global::hoodRoller.move_velocity(-200);
            global::hood.set_value(true);
        }

    } else {
        // 4. Button not pressed → stop or idle
        reversePhase = false;  // reset for next press

        global::intake.move_velocity(0);
        global::topRoller.move_velocity(0);
        global::hoodRoller.move_velocity(0);
    }
}

void outMid() {
    if (master.get_digital(DIGITAL_B)) {

        // 1. If button just pressed → begin the 100 ms reverse phase
        if (!reversePhase && master.get_digital_new_press(DIGITAL_B)) {
            reversePhase = true;
            reverseStartTime = pros::millis();

            global::intake.move_velocity(-600);
            global::topRoller.move_velocity(-200);
            global::hoodRoller.move_velocity(200);
        }

        // 2. If reverse phase is active, check if 100 ms have passed
        if (reversePhase) {
            if (pros::millis() - reverseStartTime >= 100) {
                reversePhase = false;

                // Switch to normal forward direction
                global::intake.move_velocity(600);
                global::topRoller.move_velocity(200);
                global::hoodRoller.move_velocity(200);
                global::hood.set_value(true);
            }
        }

        // 3. After reverse phase is over and button still held
        if (!reversePhase) {
            global::intake.move_velocity(600);
            global::topRoller.move_velocity(200);
            global::hoodRoller.move_velocity(200);
            global::hood.set_value(true);
        }

    } else {
        // 4. Button not pressed → stop or idle
        reversePhase = false;  // reset for next press

        global::intake.move_velocity(0);
        global::topRoller.move_velocity(0);
        global::hoodRoller.move_velocity(0);
    }
}

// void outTop() {
//     global::intake.move_velocity(600);
//     global::topRoller.move_velocity(200);
//     global::hoodRoller.move_velocity(-200);
//     global::hood.set_value(true);
//     hoodie = true;
// }

// void outMid() {
//     global::intake.move_velocity(600);
//     global::topRoller.move_velocity(200);
//     global::hoodRoller.move_velocity(200);
//     global::hood.set_value(true);
//     hoodie = true;
// }
void outLow() {
    global::intake.move_velocity(-600);
    global::topRoller.move_velocity(-200);
}

void stopAll() {
    global::intake.brake();
    global::topRoller.brake();
    global::hoodRoller.brake();
    global::hood.set_value(false);
    hoodie = false;
}

void matchLoad() {
    chassis.drive_set(-50, -50);
    pros::delay(210);
    chassis.drive_set(40, 40);
    pros::delay(550);
    chassis.drive_set(0, 0);
    pros::delay(250);
}

void doublePark(){
    while (global::distance.get() > 50){
        global::intake.move_velocity(-300);
        global::topRoller.move_velocity(-200);
    }
    global::topRoller.brake();
    global::intake.move_velocity(-600);
    pros::delay(95);
    global::intake.brake();
}



#include "main.h"
//void functionName(){
// description of the function
//}

bool hoodie = false;
bool quickBack = false;

// void quickBack() {
//     global::intake.move_velocity(-600);
//     global::topRoller.move_velocity(-200);
//     pros::delay(140);
// }

void intake() {
    global::intake.move_velocity(600);
    global::topRoller.move_velocity(200);
}
void reverseIntake() {
    global::intake.move_velocity(-600);
    global::topRoller.move_velocity(-200);
    // if (hoodie) {
    //     global::hoodRoller.move_velocity(200);
    //     global::hood.set_value(true);
    //     pros::delay(500);
    //     global::hoodRoller.brake();
    //     global::hood.set_value(false);
    //     hoodie = false;
    //     return;
    // }
}
void outTop() {
    // quickBack = true;
    // if (quickBack){
    //     global::intake.move_velocity(-600);
    //     global::topRoller.move_velocity(-200);
    //     pros::delay(150);
    //     quickBack = false;
    //     return;
    // }
    global::intake.move_velocity(600);
    global::topRoller.move_velocity(200);
    global::hoodRoller.move_velocity(-200);
    global::hood.set_value(true);
    hoodie = true;

}
void outMid() {
    // quickBack = true;
    // if (quickBack){
    //     global::intake.move_velocity(-600);
    //     global::topRoller.move_velocity(-200);
    //     pros::delay(150);
    //     quickBack = false;
    //     return;
    // }
    global::intake.move_velocity(600);
    global::topRoller.move_velocity(200);
    global::hoodRoller.move_velocity(200);
    global::hood.set_value(true);
    hoodie = true;
}
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



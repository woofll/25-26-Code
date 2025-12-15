#include "main.h"
//void functionName(){
// description of the function
//}

bool hoodie = false;
int activeTime = pros::millis();
int pressTime;




void intake() {
    if (global::color.get_proximity() < 200){
        global::intake.move_velocity(600);
        global::topRoller.move_velocity(200);
        global::hoodRoller.move_velocity(-100);    
    } else if (global::color.get_proximity() >= 200){
        global::intake.move_velocity(600);
        global::topRoller.move_velocity(200);
        global::hoodRoller.move_velocity(-30);
    }
}
void reverseIntake() {
    global::intake.move_velocity(-600);
    global::topRoller.move_velocity(-200);
}

//

void outTop() {
    global::intake.move_velocity(600);
    global::topRoller.move_velocity(200);
    global::hoodRoller.move_velocity(-200);
    global::hood.set_value(true);
    hoodie = true;
}

void outMid() {
    global::intake.move_velocity(600);
    global::topRoller.move_velocity(200);
    global::hoodRoller.move_velocity(200);
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


// void doublePark(){
//     if (dP) {
//     while (global::distance.get() > 50){
//         global::intake.move_velocity(-300);
//         global::topRoller.move_velocity(-200);
//         if (master.get_digital_new_press(DIGITAL_Y)){
//             dP = false;
//         }
//         }
//     }
//     global::topRoller.brake();
//     global::intake.move_velocity(-600);
//     pros::delay(95);
//     global::intake.brake();
// }



#include "main.h"
//void functionName(){
// description of the function
//}

int activeTime = pros::millis();
int pressTime;


void intake() {
    if (global::color.get_proximity() < 200){
        global::intake.move_velocity(600);
        global::topRoller.move_velocity(200);
        global::hoodRoller.move_velocity(75);    
    } else if (global::color.get_proximity() >= 200){
        global::intake.move_velocity(600);
        global::topRoller.move_velocity(180);
        global::hoodRoller.move_velocity(55);
    }
        
}
void reverseIntake() {
    global::intake.move_velocity(-600);
    global::topRoller.move_velocity(-200);
}

//I WANNA GOON AND COME

void outTop() {
    global::intake.move_velocity(600);
    global::topRoller.move_velocity(200);   
    global::hoodRoller.move_velocity(200);
    global::hood.set_value(true);
}

void outMid() {
    global::intake.move_velocity(600);
    global::topRoller.move_velocity(200);
    global::hoodRoller.move_velocity(-160);
}

void outMidSkills(){
    global::intake.move_velocity(300);
    global::topRoller.move_velocity(100);
    global::hoodRoller.move_velocity(-100);
}

void outLow() {
    global::intake.move_velocity(-600);
    global::topRoller.move_velocity(-200);
    global::hoodRoller.move_velocity(-200);
}

void stopAll() {
    global::intake.brake();
    global::topRoller.brake();
    global::hoodRoller.brake();
    global::hood.set_value(false);
}

void matchLoad() {
    chassis.drive_set(-50, -50);
    pros::delay(210);
    chassis.drive_set(40, 40);
    pros::delay(550);
    chassis.drive_set(0, 0);
    pros::delay(250);
}



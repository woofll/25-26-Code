#include "main.h"
//void functionName(){
// description of the function
//}

// void intake();
// void outTop();
// void outMid();
// void outLow();
// void stopAll();

// void tongueOut();
// void tongueIn();

// void descoreExtend();
// void descoreRetract();

bool hoodie = false;

void intake() {
    global::intake.move_velocity(-500);
    global::topRoller.move_velocity(200);
}
void reverseIntake() {
    global::intake.move_velocity(500);
    global::topRoller.move_velocity(-200);
    if (hoodie) {
        global::hoodRoller.move_velocity(200);
        global::hood.set_value(false);
        pros::delay(1000);
        global::hoodRoller.brake();
        global::hood.set_value(true);
        hoodie = false;
        return;
    }
}
void outTop() {
    global::intake.move_velocity(-500);
    global::topRoller.move_velocity(200);
    global::hoodRoller.move_velocity(200);
    global::hood.set_value(false);
    hoodie = true;
}
void outMid() {
    global::intake.move_velocity(-50);
    global::topRoller.move_velocity(200);
    global::hoodRoller.move_velocity(-200);
}
void outLow() {
    global::intake.move_velocity(500);
    global::topRoller.move_velocity(-200);
    global::hoodRoller.move_velocity(-200);
}
void stopAll() {
    global::intake.brake();
    global::topRoller.brake();
    global::hoodRoller.brake();
    global::hood.set_value(true);
    hoodie = false;
}

void matchLoad(){

}


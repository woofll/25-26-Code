#include "main.h"
//void functionName(){
// description of the function
//}

void intake() {
    if (global::color.get_proximity() < 200){
        global::intake.move_velocity(600);
        global::topRoller.move_velocity(190);
        global::hoodRoller.move_velocity(30);
        global::hood.set_value(false);    
    } else if (global::color.get_proximity() >= 200){
        global::intake.move_velocity(600);
        global::topRoller.move_velocity(200);
        global::hoodRoller.move_velocity(75);
        global::hood.set_value(false);   
    }
        
}
void reverseIntake() {
    global::intake.move_velocity(-600);
    global::topRoller.move_velocity(-200);
}

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

void outMidSkillsFast(){
    global::intake.move_velocity(500);
    global::topRoller.move_velocity(200);
    global::hoodRoller.move_velocity(-200);
}
void outMidSkillsSlow(){
    global::intake.move_velocity(350);
    global::topRoller.move_velocity(50);
    global::hoodRoller.move_velocity(-50);
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




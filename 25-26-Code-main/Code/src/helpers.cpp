#include "main.h"
//void functionName(){
// description of the function
//}

/// void intaking();
// void outtakeTop();
// void outtakeMiddle();
// void outtakeBottom();
// void outtakeStop();
// void stop();

// void tongueExtend();
// void tongueRetract();

// void descoreExtend();
// void descoreRetract();

void intake(){ //Intake in
    global::intake.move_velocity(200);
    global::score.move_velocity(-200);
}
void outTop(){ //Score Top
    global::intake.move_velocity(200);
    global::score.move_velocity(-200);
    global::topFlex.move_velocity(-200);
}
void outMid(){ //Score Middle
    global::intake.move_velocity(200);
    global::score.move_velocity(-200);
    global::topFlex.move_velocity(200);
}
void outLow(){ //Score Low
    global::intake.move_velocity(200);
    global::score.move_velocity(-200);
    global::topFlex.move_velocity(200);
}
void stopAll(){ //Stop all motors
    global::intake.brake();
    global::score.brake();
    global::topFlex.brake();
}

void tongueOut(){ //Tongue down
    global::tongue.retract();
}
void tongueIn(){ //Tongue in
    global::tongue.extend();
}

void descoreExtend(){ //Descore out
    global::descore.extend();
}
void descoreRetract(){ //Descore in
    global::descore.retract();
}

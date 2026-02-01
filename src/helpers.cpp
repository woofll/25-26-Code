#include "main.h"
//void functionName(){
// description of the function
//}

extern Drive chassis;



void intake() {
        global::intake.move_velocity(600);
        global::topRoller.move_velocity(200);
        global::hoodRoller.move_velocity(30);
        global::hood.set_value(false);  
        
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
    global::hood.set_value(false);
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


void posxdsr(){

}

void negxdsr(){

}

// void posydsr(){
//     ycoor = 72 - (disF * cos(theta)) - ftoC;
// }

// void negydsr(){
//     ycoor = (disF * cos(theta)) - 72 + ftoC;
// }


// void staticdsr(){
// /***************************************************************/
//     double disF = global::distanceF.get_distance();
//     double disB = global::distanceB.get_distance();
//     double disL = global::distanceL.get_distance();
//     double disR = global::distanceR.get_distance();
    
//     double curX = chassis.odom_x_get();
//     double curY = chassis.odom_y_get();
//     double curTheta = chassis.drive_imu_get();

//     double newX, newY, newTheta;

//     double ftoC = 0;
//     double btoC = 0;
//     double ltoC = 0;
//     double rtoC = 0;

//     const double PI = 3.14159265358979323846;
// /***************************************************************/

//     if ((disR <= disL) && (disF <= disB)){ // Right and Front sensors

//         if ((curY >= 0) && (curX >= 0)){ // Positive Y, Positive X
//             newY = 72 - (disF * cos((curTheta) * (PI/180))) - ftoC; //reset Y
//             newX = 72 - (disR * cos((curTheta) * (PI/180))) - rtoC; //reset X
//         } else if ((curY >= 0) && (curX < 0)){ // Positive Y, Negative X

//         } else if ((curY < 0) && (curX >= 0)){ // Negative Y, Positive X

//         } else if ((curY < 0) && (curX < 0)){ // Negative Y, Negative X

//         }

//     } else if ((disR <= disL) && (disB < disF)){ // Right and Back sensors

//     } else if ((disL < disR) && (disF <= disB)){ // Left and Front sensors

//     } else if ((disL < disR) && (disB < disF)){ // Left and Back sensors

//     }

// }

// void turndsr(){ 
// //-----------------------------------------------------------------------------------------------------------------------------//
//     double disF = global::distanceF.get_distance() / 25.4; // Distance of what Front sensor sees, converted into inches
//     double disB = global::distanceB.get_distance() / 25.4; // Distance of what Back sensor sees, converted into inches
//     double disL = global::distanceL.get_distance() / 25.4; // Distance of what Left sensor sees, converted into inches
//     double disR = global::distanceR.get_distance() / 25.4; // Distance of what Right sensor sees, converted into inches
    
//     double curX = chassis.odom_x_get(); // Current odom x coordinate
//     double curY = chassis.odom_y_get(); // Current odom y coordinate
//     double curTheta = chassis.drive_imu_get(); // Current angle coordinate

//     double newX, newY, newTheta; // Sets new coordinates

//     double ftoC = 0; // Distance of Front sensor to Center of the bot
//     double btoC = 0; // Distance of Back sensor to Center of the bot
//     double ltoC = 0; // Distance of Left sensor to Center of the bot
//     double rtoC = 0; // Distance of Right sensor to Center of the bot

//     const double PI = 3.14159265358979323846;
// //-----------------------------------------------------------------------------------------------------------------------------//
//     if ((disR <= disL) && (disF <= disB)){ // Right and Front sensors

//         if ((curY >= 0) && (curX >= 0)){ // Positive Y, Positive X
//             newY = (72 - disF - ftoC); // POS Y reset
//             newX = (72 - disR - rtoC); // POS X reset
//             chassis.odom_xyt_set(newX, newY, curTheta);
//         } else if ((curY >= 0) && (curX < 0)){ // Positive Y, Negative X
//             newY = (72 - disF - ftoC); // POS Y reset
//             newX = -(72 - disR - rtoC); // NEG X reset
//             chassis.odom_xyt_set(newX, newY, curTheta);
//         } else if ((curY < 0) && (curX >= 0)){ // Negative Y, Positive X
//             newY = -(72 - disF - ftoC); // NEG Y reset
//             newX = (72 - disR - rtoC); // POS X reset
//             chassis.odom_xyt_set(newX, newY, curTheta);
//         } else if ((curY < 0) && (curX < 0)){ // Negative Y, Negative X
//             newY = -(72 - disF - ftoC); // NEG Y reset
//             newX = -(72 - disR - rtoC); // NEG X reset
//             chassis.odom_xyt_set(newX, newY, curTheta);
//         }

//     } else if ((disR <= disL) && (disB < disF)){ // Right and Back sensors

//         if ((curY >= 0) && (curX >= 0)){ // Positive Y, Positive X
//             newY = (72 - disB - btoC); // POS Y reset
//             newX = (72 - disR - rtoC); // POS X reset
//             chassis.odom_xyt_set(newX, newY, curTheta);
//         } else if ((curY >= 0) && (curX < 0)){ // Positive Y, Negative X
//             newY = (72 - disB - btoC); // POS Y reset
//             newX = -(72 - disR - rtoC); // NEG X reset
//             chassis.odom_xyt_set(newX, newY, curTheta);
//         } else if ((curY < 0) && (curX >= 0)){ // Negative Y, Positive X
//             newY = -(72 - disB - btoC); // NEG Y reset
//             newX = (72 - disR - rtoC); // POS X reset
//             chassis.odom_xyt_set(newX, newY, curTheta);
//         } else if ((curY < 0) && (curX < 0)){ // Negative Y, Negative X
//             newY = -(72 - disB - btoC); // NEG Y reset
//             newX = -(72 - disR - rtoC); // NEG X reset
//             chassis.odom_xyt_set(newX, newY, curTheta);
//         }

//     } else if ((disL < disR) && (disF <= disB)){ // Left and Front sensors

//         if ((curY >= 0) && (curX >= 0)){ // Positive Y, Positive X
//             newY = (72 - disF - ftoC); // POS Y reset
//             newX = (72 - disL - ltoC); // POS X reset
//             chassis.odom_xyt_set(newX, newY, curTheta);
//         } else if ((curY >= 0) && (curX < 0)){ // Positive Y, Negative X
//             newY = (72 - disF - ftoC); // POS Y reset
//             newX = -(72 - disL - ltoC); // NEG X reset
//             chassis.odom_xyt_set(newX, newY, curTheta);
//         } else if ((curY < 0) && (curX >= 0)){ // Negative Y, Positive X
//             newY = -(72 - disF - ftoC); // NEG Y reset
//             newX = (72 - disL - ltoC); // POS X reset
//             chassis.odom_xyt_set(newX, newY, curTheta);
//         } else if ((curY < 0) && (curX < 0)){ // Negative Y, Negative X
//             newY = -(72 - disF - ftoC); // NEG Y reset
//             newX = -(72 - disL - ltoC); // NEG X reset
//             chassis.odom_xyt_set(newX, newY, curTheta);
//         }

//     } else if ((disL < disR) && (disB < disF)){ // Left and Back sensors
    
//         if ((curY >= 0) && (curX >= 0)){ // Positive Y, Positive X
//             newY = (72 - disB - btoC); // POS Y reset
//             newX = (72 - disL - ltoC); // POS X reset
//             chassis.odom_xyt_set(newX, newY, curTheta);
//         } else if ((curY >= 0) && (curX < 0)){ // Positive Y, Negative X
//             newY = (72 - disB - btoC); // POS Y reset
//             newX = -(72 - disL - ltoC); // NEG X reset
//             chassis.odom_xyt_set(newX, newY, curTheta);
//         } else if ((curY < 0) && (curX >= 0)){ // Negative Y, Positive X
//             newY = -(72 - disB - btoC); // NEG Y reset
//             newX = (72 - disL - ltoC); // POS X reset
//             chassis.odom_xyt_set(newX, newY, curTheta);
//         } else if ((curY < 0) && (curX < 0)){ // Negative Y, Negative X
//             newY = -(72 - disB - btoC); // NEG Y reset
//             newX = -(72 - disL - ltoC); // NEG X reset
//             chassis.odom_xyt_set(newX, newY, curTheta);
//         }
//     }
// }


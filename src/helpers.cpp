#include "main.h"
//void functionName(){
// description of the function
//}

extern Drive chassis;
    double disF = global::distanceF.get_distance() / 25.4; // Distance of what Front sensor sees, converted into inches
    double disB = global::distanceB.get_distance() / 25.4; // Distance of what Back sensor sees, converted into inches
    double disL = global::distanceL.get_distance() / 25.4; // Distance of what Left sensor sees, converted into inches
    double disR = global::distanceR.get_distance() / 25.4; // Distance of what Right sensor sees, converted into inches
    
    double curX = chassis.odom_x_get(); // Current odom x coordinate
    double curY = chassis.odom_y_get(); // Current odom y coordinate
    double curTheta = chassis.drive_imu_get(); // Current angle coordinate

    double newX, newY, newTheta; // Sets new coordinates

    double ftoC = 5.75; // Distance of Front sensor to Center of the bot
    double btoC = 5.00; // Distance of Back sensor to Center of the bot
    double ltoC = 5.00; // Distance of Left sensor to Center of the bot
    double rtoC = 5.00; // Distance of Right sensor to Center of the bot

    const double PI = 3.14159265358979323846;


void intake() {
        global::intake.move_velocity(600);
        global::topRoller.move_velocity(200);
        global::hoodRoller.move_velocity(38);
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

void outLow() {
    global::intake.move_velocity(-450);
    global::topRoller.move_velocity(-150);
    global::hoodRoller.move_velocity(-150);
    global::intakeLift.extend();
}

void stopAll() {
    global::intake.brake();
    global::topRoller.brake();
    global::hoodRoller.brake();
    global::hood.set_value(false);
    global::intakeLift.retract();
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



// void staticdsr(){
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

// void frposxposy(){ // If this doesn't work, put double before newY and newX
//          newX = (72 - (disR * cos((curTheta) * (PI/180))) - rtoC); //reset X  
//          newY = (72 - (disF * cos((curTheta) * (PI/180))) - ftoC); //reset Y
//          chassis.odom_xyt_set(newX, newY, curTheta);
// }
// void frposxnegy(){
//          newX = (72 - (disF * cos((curTheta) * (PI/180))) - ftoC); //reset X  
//          newY = -(72 - (disR * cos((curTheta) * (PI/180))) - rtoC); //reset Y
//          chassis.odom_xyt_set(newX, newY, curTheta);
// }
// void frnegxposy(){
//          newX = -(72 - (disF * cos((curTheta) * (PI/180))) - ftoC); //reset X 
//          newY = (72 - (disR * cos((curTheta) * (PI/180))) - rtoC); //reset Y 
//          chassis.odom_xyt_set(newX, newY, curTheta);
// }
// void frnegxnegy(){
//          newX = -(72 - (disR * cos((curTheta) * (PI/180))) - rtoC); //reset X  
//          newY = -(72 - (disF * cos((curTheta) * (PI/180))) - ftoC); //reset Y
//          chassis.odom_xyt_set(newX, newY, curTheta);
// }

// void brposxposy(){
//          newX = (72 - (disB * cos((curTheta) * (PI/180))) - btoC); //reset X  
//          newY = (72 - (disR * cos((curTheta) * (PI/180))) - rtoC); //reset Y
//          chassis.odom_xyt_set(newX, newY, curTheta);
// }
// void brposxnegy(){
//          newX = (72 - (disR * cos((curTheta) * (PI/180))) - rtoC); //reset X  
//          newY = -(72 - (disB * cos((curTheta) * (PI/180))) - btoC); //reset Y
//          chassis.odom_xyt_set(newX, newY, curTheta);
// }
// void brnegxposy(){
//          newX = -(72 - (disR * cos((curTheta) * (PI/180))) - rtoC); //reset X  
//          newY = (72 - (disB * cos((curTheta) * (PI/180))) - btoC); //reset Y
//          chassis.odom_xyt_set(newX, newY, curTheta);
// }
// void brnegxnegy(){
//          newX = -(72 - (disB * cos((curTheta) * (PI/180))) - btoC); //reset X  
//          newY = -(72 - (disR * cos((curTheta) * (PI/180))) - rtoC); //reset Y
//          chassis.odom_xyt_set(newX, newY, curTheta);
// }

// void flposxposy(){
//          newX = (72 - (disF * cos((curTheta) * (PI/180))) - ftoC); //reset X  
//          newY = (72 - (disL * cos((curTheta) * (PI/180))) - ltoC); //reset Y
//          chassis.odom_xyt_set(newX, newY, curTheta);
// }
// void flposxnegy(){
//          newX = (72 - (disL * cos((curTheta) * (PI/180))) - ltoC); //reset X  
//          newY = -(72 - (disF * cos((curTheta) * (PI/180))) - ftoC); //reset Y
//          chassis.odom_xyt_set(newX, newY, curTheta);
// }
// void flnegxposy(){
//          newX = -(72 - (disL * cos((curTheta) * (PI/180))) - ltoC); //reset X  
//          newY = (72 - (disF * cos((curTheta) * (PI/180))) - ftoC); //reset Y
//          chassis.odom_xyt_set(newX, newY, curTheta);
// }
// void flnegxnegy(){
//          newX = -(72 - (disF * cos((curTheta) * (PI/180))) - ftoC); //reset X  
//          newY = -(72 - (disL * cos((curTheta) * (PI/180))) - ltoC); //reset Y
//          chassis.odom_xyt_set(newX, newY, curTheta);
// }

// void blposxposy(){
//          newX = (72 - (disL * cos((curTheta) * (PI/180))) - ltoC); //reset X  
//          newY = (72 - (disB * cos((curTheta) * (PI/180))) - btoC); //reset Y
//          chassis.odom_xyt_set(newX, newY, curTheta);
// }
// void blposxnegy(){
//          newX = (72 - (disB * cos((curTheta) * (PI/180))) - btoC); //reset X  
//          newY = -(72 - (disL * cos((curTheta) * (PI/180))) - ltoC); //reset Y
//          chassis.odom_xyt_set(newX, newY, curTheta);
// }
// void blnegxposy(){
//          newX = -(72 - (disB * cos((curTheta) * (PI/180))) - btoC); //reset X  
//          newY = (72 - (disL * cos((curTheta) * (PI/180))) - ltoC); //reset Y
//          chassis.odom_xyt_set(newX, newY, curTheta);
// }
// void blnegxnegy(){
//          newX = -(72 - (disL * cos((curTheta) * (PI/180))) - ltoC); //reset X  
//          newY = -(72 - (disB * cos((curTheta) * (PI/180))) - btoC); //reset Y
//          chassis.odom_xyt_set(newX, newY, curTheta);
// }


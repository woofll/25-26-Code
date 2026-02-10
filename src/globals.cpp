#include "main.h"
namespace global{
//pros::Motor motorName(portNumber, motorType);
//pros::sensorType sensorName (portNumber);
//pros::adi::Pneumatics pneumaticsName('portLetter', state(true/false));

pros::Motor intake(2, pros::v5::MotorGearset::rpm_600); //3
pros::Motor topRoller(16, pros::v5::MotorGearset::rpm_200);  //1
pros::Motor hoodRoller(-9, pros::v5::MotorGearset::rpm_200); //-2

pros::Optical colorF(1);
pros::Optical colorB(4);

pros::Distance distanceF(13);
pros::Distance distanceB(3);//3
pros::Distance distanceL(15);//15
pros::Distance distanceR(17);//17

pros::adi::Pneumatics tongue('B', false); //Starts retracted
pros::adi::Pneumatics hood('C', false); //Starts retracted
pros::adi::Pneumatics descore('A', false); //Starts retracted 
pros::adi::Pneumatics intakeLift('D', false);

}
#include "main.h"
namespace global{
//pros::Motor motorName(portNumber, motorType);
//pros::sensorType sensorName (portNumber);
//pros::adi::Pneumatics pneumaticsName('portLetter', state(true/false));

pros::Motor intake(20, pros::v5::MotorGearset::rpm_200);
pros::Motor score(19, pros::v5::MotorGearset::rpm_200); 
pros::Motor topFlex(9, pros::v5::MotorGearset::rpm_200); //Flex Wheel

// pros::adi::Pneumatics plate('A', false); //Starts retracted
}
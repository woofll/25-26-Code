#include "main.h"
namespace global{
//pros::Motor motorName(portNumber, motorType);
//pros::sensorType sensorName (portNumber);
//pros::adi::Pneumatics pneumaticsName('portLetter', state(true/false));

pros::Motor intake(20, pros::v5::MotorGearset::rpm_200);
pros::Motor score(19, pros::v5::MotorGearset::rpm_200); 
pros::Motor topFlex(9, pros::v5::MotorGearset::rpm_200); //Flex Wheel

pros::adi::Pneumatics tongue('A', false); //Starts extended
//Note, we haven't actually built descore or gate yet!!!
pros::adi::Pneumatics descore('B', false);
pros::adi::Pneumatics gate('C', true); 
}
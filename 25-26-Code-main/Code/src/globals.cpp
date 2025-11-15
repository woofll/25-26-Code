#include "main.h"
namespace global{
//pros::Motor motorName(portNumber, motorType);
//pros::sensorType sensorName (portNumber);
//pros::adi::Pneumatics pneumaticsName('portLetter', state(true/false));

pros::Motor intake(11, pros::v5::MotorGearset::rpm_600);
pros::Motor topRoller(12, pros::v5::MotorGearset::rpm_200); 
pros::Motor hoodRoller(10, pros::v5::MotorGearset::rpm_200);

pros::adi::Pneumatics tongue('A', false); //Starts extended
pros::adi::Pneumatics descore('B', false);
pros::adi::Pneumatics hood('C', false); //Starts retracted


}
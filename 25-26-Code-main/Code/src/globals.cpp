#include "main.h"
namespace global{
//pros::Motor motorName(portNumber, motorType);
//pros::sensorType sensorName (portNumber);
//pros::adi::Pneumatics pneumaticsName('portLetter', state(true/false));

pros::Motor intake(3, pros::v5::MotorGearset::rpm_600);
pros::Motor topRoller(1, pros::v5::MotorGearset::rpm_200); 
pros::Motor hoodRoller(2, pros::v5::MotorGearset::rpm_200);

pros::Optical color(13);
pros::Distance distance(14);
// pros::Rotation odom(11);

pros::adi::Pneumatics tongue('H', false); //Starts retracted
pros::adi::Pneumatics topDescore('D', false); //Starts extended (up)
pros::adi::Pneumatics midDescore('B', false);
pros::adi::Pneumatics hood('A', false); //Starts retracted



pros::Motor testMotor1(1, pros::v5::MotorGearset::blue);

}
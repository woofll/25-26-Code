#include "main.h"
namespace global{
//pros::Motor motorName(portNumber, motorType);
//pros::sensorType sensorName (portNumber);
//pros::adi::Pneumatics pneumaticsName('portLetter', state(true/false));

pros::Motor leftIntake(3, pros::v5::MotorGearset::rpm_200);
pros::Motor rightIntake(10, pros::v5::MotorGearset::rpm_200);

}
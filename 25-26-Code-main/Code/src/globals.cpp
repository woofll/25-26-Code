#include "main.h"
namespace global{
//pros::Motor motorName(portNumber, motorType);
//pros::sensorType sensorName (portNumber);
//pros::adi::Pneumatics pneumaticsName('portLetter', state(true/false));

pros::Motor leftIntake(2, pros::v5::MotorGearset::rpm_200);
pros::Motor rightIntake(9, pros::v5::MotorGearset::rpm_200);

}
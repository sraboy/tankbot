#include "Tankbot.h"

namespace TankBot {


} //namepsace TankBot




void setup() {
	using namespace TankBot;

	Serial.begin(9600);

	Drive::Setup(Ports::Port::PM1, Ports::Port::PM2);
	//Drive::SetFwdNoGoCheck(CanGoOnCloseObject);


	delay(250);		// wait on everything above to finish
	buzz();
	delay(500);		// short pause to let everything finish
	Serial.println(F("Setup complete"));
}

void loop() {
	//Infrared::Process();
}

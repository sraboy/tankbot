#include "Infrared.h"
#include "Drive.h"

namespace Infrared {

	void Process() {
		infraredReceiverDecode.loop();
		IrButton pressed = static_cast<IrButton>(infraredReceiverDecode.getCode());

		switch (pressed) {
		case IR_BUTTON_PLUS:
			Drive::Forward();
			break;
		case IR_BUTTON_MINUS:
			Drive::Backward();
			break;
		case IR_BUTTON_NEXT:
			Drive::TurnRight();
			break;
		case IR_BUTTON_PREVIOUS:
			Drive::TurnLeft();
			break;
		case IR_BUTTON_D:
			Drive::ForwardAndTurnLeft();
			break;
		case IR_BUTTON_E:
			Drive::ForwardAndTurnRight();
			break;
		case IR_BUTTON_0:
			Drive::BackwardAndTurnLeft();
			break;
		case IR_BUTTON_F:
			Drive::BackwardAndTurnRight();
			break;
		case IR_BUTTON_9:
			Drive::ChangeSpeed(9);
			break;
		case IR_BUTTON_8:
			Drive::ChangeSpeed(8);
			break;
		case IR_BUTTON_7:
			Drive::ChangeSpeed(7);
			break;
		case IR_BUTTON_6:
			Drive::ChangeSpeed(6);
			break;
		case IR_BUTTON_5:
			Drive::ChangeSpeed(5);
			break;
		case IR_BUTTON_4:
			Drive::ChangeSpeed(4);
			break;
		case IR_BUTTON_3:
			Drive::ChangeSpeed(3);
			break;
		case IR_BUTTON_2:
			Drive::ChangeSpeed(2);
			break;
		case IR_BUTTON_1:
			Drive::ChangeSpeed(1);
			break;
		default:
			Drive::Stop();
			break;
		}
	}

} //namespace Infrared
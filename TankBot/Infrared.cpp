#include "Infrared.h"
#include "Drive.h"

namespace Infrared {
	MeInfraredReceiver ir_recv;
	button_callbacks Callbacks;

	void Setup(Ports::Port port, button_callbacks callbacks) {
		ir_recv = MeInfraredReceiver(static_cast<uint8_t>(port));
		ir_recv.begin();
		Callbacks.OnUp = no_callback;
		Callbacks = callbacks;
	}

	uint8_t ButtonVal(Button b) {
		switch (b) {
		case Button::A:
			return 'A';
		case Button::B:
			return 'B';
		case Button::C:
			return 'C';
		case Button::D:
			return 'D';
		case Button::E:
			return 'E';
		case Button::F:
			return 'F';
		case Button::NUM0:
			return 0;
		case Button::NUM1:
			return 1;
		case Button::NUM2:
			return 2;
		case Button::NUM3:
			return 3;
		case Button::NUM4:
			return 4;
		case Button::NUM5:
			return 5;
		case Button::NUM6:
			return 6;
		case Button::NUM7:
			return 7;
		case Button::NUM8:
			return 8;
		case Button::NUM9:
			return 9;
		default:
			return -1;
		}
	}

	void Process() {
		ir_recv.loop();
		Button pressed = static_cast<Button>(ir_recv.getCode());

		switch (pressed) {
		case IR_BUTTON_UP:
			Callbacks.OnUp();
			break;
		case IR_BUTTON_DOWN:
			Callbacks.OnDown();
			break;
		case IR_BUTTON_LEFT:
			Callbacks.OnLeft();
			break;
		case IR_BUTTON_RIGHT:
			Callbacks.OnRight();
			break;
		case IR_BUTTON_A:
			Callbacks.OnA();
			break;
		case IR_BUTTON_B:
			Callbacks.OnB();
			break;
		case IR_BUTTON_C:
			Callbacks.OnC();
			break;
		case IR_BUTTON_D:
			Callbacks.OnD();
			break;
		case IR_BUTTON_E:
			Callbacks.OnE();
			break;
		case IR_BUTTON_F:
			Callbacks.OnF();
			break;
		case IR_BUTTON_SETTING:
			Callbacks.OnSetting();
			break;
		case IR_BUTTON_9:
			Callbacks.OnNum(Button::NUM9);
			break;
		case IR_BUTTON_8:
			Callbacks.OnNum(Button::NUM8);
			break;
		case IR_BUTTON_7:
			Callbacks.OnNum(Button::NUM7);
			break;
		case IR_BUTTON_6:
			Callbacks.OnNum(Button::NUM6);
			break;
		case IR_BUTTON_5:
			Callbacks.OnNum(Button::NUM5);
			break;
		case IR_BUTTON_4:
			Callbacks.OnNum(Button::NUM4);
			break;
		case IR_BUTTON_3:
			Callbacks.OnNum(Button::NUM3);
			break;
		case IR_BUTTON_2:
			Callbacks.OnNum(Button::NUM2);
			break;
		case IR_BUTTON_1:
			Callbacks.OnNum(Button::NUM1);
			break;
		case IR_BUTTON_0:
			Callbacks.OnNum(Button::NUM0);
			break;
		default:
			Drive::Stop();
			break;
		}
	}
} //namespace Infrared
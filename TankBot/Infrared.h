#ifndef _INFRARED_H_
#define _INFRARED_H_
#include <MeInfraredReceiver.h>

namespace Infrared {

	extern MeInfraredReceiver infraredReceiverDecode;

	enum IrButton : uint8_t {
		A = 0x45,
		B = 0x46,
		C = 0x47,
		D = 0x44,
		E = 0x43,
		F = 0x0D,

		UP = 0x40,
		LEFT = 0x07,
		RIGHT = 0x09,
		DOWN = 0x19,

		SETTING = 0x15,

		NUM0 = 0x16,
		NUM1 = 0x0C,
		NUM2 = 0x18,
		NUM3 = 0x5E,
		NUM4 = 0x08,
		NUM5 = 0x1C,
		NUM6 = 0x5A,
		NUM7 = 0x42,
		NUM8 = 0x52,
		NUM9 = 0x4A
	};

	void Process();

}

#endif
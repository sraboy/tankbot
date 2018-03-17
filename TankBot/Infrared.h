#ifndef _INFRARED_H_
#define _INFRARED_H_
#include <MeInfraredReceiver.h>
#include "Port.h"

namespace Infrared {

	enum Button : uint8_t {
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

	uint8_t ButtonVal(Button);

	inline void no_callback(void) {};
	inline void no_callback(Button) {};

	typedef struct button_callbacks_t {
		void(*OnUp)(void) = no_callback;
		void(*OnDown)(void) = no_callback;
		void(*OnLeft)(void) = no_callback;
		void(*OnRight)(void) = no_callback;
		void(*OnSetting)(void) = no_callback;
		void(*OnNum)(Button) = no_callback;

		//void(*On0)(int) = no_callback;
		//void(*On1)(int) = no_callback;
		//void(*On2)(int) = no_callback;
		//void(*On3)(int) = no_callback;
		//void(*On4)(int) = no_callback;
		//void(*On5)(int) = no_callback;
		//void(*On6)(int) = no_callback;
		//void(*On7)(int) = no_callback;
		//void(*On8)(int) = no_callback;
		//void(*On9)(int) = no_callback;

		void(*OnA)(void) = no_callback;
		void(*OnB)(void) = no_callback;
		void(*OnC)(void) = no_callback;
		void(*OnD)(void) = no_callback;
		void(*OnE)(void) = no_callback;
		void(*OnF)(void) = no_callback;

	} button_callbacks;

	void Process();
	void Setup(Ports::Port, button_callbacks*);

}

#endif
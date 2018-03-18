#ifndef _LEDDISPLAY_H_
#define _LEDDISPLAY_H_

#include "Port.h"

namespace LedDisplay {
	uint32_t const SEG_A = 0b00000001;
	uint32_t const SEG_B = 0b00000010;
	uint32_t const SEG_C = 0b00000100;
	uint32_t const SEG_D = 0b00001000;
	uint32_t const SEG_E = 0b00010000;
	uint32_t const SEG_F = 0b00100000;
	uint32_t const SEG_G = 0b01000000;
	uint32_t const SEG_P = 0b10000000;

	enum Brightness : uint8_t {
		BRT_0 = 0,
		BRT_1,
		BRT_2,
		BRT_3,
		BRT_4,
		BRT_5,
		BRT_6,
		BRT_7
	};

	enum Char : uint32_t {
		A = SEG_E | SEG_F | SEG_A | SEG_B | SEG_C | SEG_G,
		//B
		//C
		D = SEG_E | SEG_F | SEG_A | SEG_B | SEG_C | SEG_D,
		E = SEG_E | SEG_F | SEG_A | SEG_D | SEG_G,
		// lower case //
		d = SEG_G | SEG_E | SEG_D | SEG_C | SEG_B,
		e = SEG_G | SEG_B | SEG_A | SEG_F | SEG_E | SEG_D,
		r = SEG_A | SEG_F | SEG_E,
		u = SEG_F | SEG_E | SEG_D | SEG_C | SEG_B,
		v = u,
		y = SEG_F | SEG_G | SEG_B | SEG_C | SEG_D,
		P_UNDER = SEG_D,
		P_DASH = SEG_G,
		P_QUES = SEG_A | SEG_B | SEG_G | SEG_E | SEG_P,
		P_SPACE = 0x0
	};

	void Display(double d);
	void Write(uint8_t * data);
	void Setup(Ports::Port, Brightness);
} //namespace LedDisplay

#endif
#ifndef _LEDDISPLAY_H_
#define _LEDDISPLAY_H_

#include "Port.h"

namespace LedDisplay {
	uint8_t const SEG_A = 0b00000001;
	uint8_t const SEG_B = 0b00000010;
	uint8_t const SEG_C = 0b00000100;
	uint8_t const SEG_D = 0b00001000;
	uint8_t const SEG_E = 0b00010000;
	uint8_t const SEG_F = 0b00100000;
	uint8_t const SEG_G = 0b01000000;
	uint8_t const SEG_P = 0b10000000;

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

	void Write(double d);
	void Write(char * data);
	void Setup(Ports::Port, Brightness);

	class LedWord {
	private:
		uint8_t _data[4] = { 0x0, 0x0, 0x0, 0x0 };
		//
		// Ref: https://github.com/avishorp/TM1637/blob/master/docs/TM1637_V2.4_EN.pdf
		//
		constexpr uint8_t char_lookup(char c) {
			switch (c) {
			case 'A':
				return SEG_E | SEG_F | SEG_A | SEG_B | SEG_C | SEG_G;
			case 'D':
				return SEG_E | SEG_F | SEG_A | SEG_B | SEG_C | SEG_D;
			case 'E':
				return SEG_E | SEG_F | SEG_A | SEG_D | SEG_G;
			case 'd':
				return SEG_G | SEG_E | SEG_D | SEG_C | SEG_B;
			case 'e':
				return SEG_G | SEG_B | SEG_A | SEG_F | SEG_E | SEG_D;
				break;
			case 'r':
				return SEG_A | SEG_F | SEG_E;
			case 'u':
			case 'v':
				return SEG_F | SEG_E | SEG_D | SEG_C | SEG_B;
			case 'y':
				return SEG_F | SEG_G | SEG_B | SEG_C | SEG_D;
			case '_':
				return SEG_D;
			case '-':
				return SEG_G;
			case '?':
				return SEG_A | SEG_B | SEG_G | SEG_E | SEG_P;
			default:
			case ' ':
				return 0x0;
			}
		}
	public:
		constexpr LedWord(char * word) {
			for (int i = 0; i < 4; i++) {
				_data[i] = char_lookup(word[i]);
			}
		}
		constexpr uint8_t * data() {
			return _data;
		}
	};
} //namespace LedDisplay

#endif
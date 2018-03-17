#ifndef _PORT_H_
#define _PORT_H_

#include <MePort.h>

namespace Ports {

	enum Port : uint8_t {
		P1 = 0x01,
		P2 = 0x02,
		P3 = 0x03,
		P4 = 0x04,
		P5 = 0x05,
		P6 = 0x06,
		P7 = 0x07,
		P8 = 0x08,
		P9 = 0x09,
		P10 = 0x0a,

		PM1 = 0x09,
		PM2 = 0x0a,

		P11 = 0x0b,
		P12 = 0x0c,
		P13 = 0x0d,
		P14 = 0x0e,
		P15 = 0x0f,
		P16 = 0x10

	};

} //namespace Port
#endif
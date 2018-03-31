#ifndef _TANKBOT_H
#define _TANKBOT_H
#include "BT12.h"
#include <Arduino.h>

extern Bluetooth::BTCommand;

namespace TankBot {
  void ProcessCmd(Bluetooth::BTCommand);
}

inline void buzz(int delay_time = 100) {
	pinMode(SCL, OUTPUT);
	digitalWrite(SCL, HIGH);
	delay(delay_time);
	pinMode(SCL, OUTPUT);
	digitalWrite(SCL, LOW);
}

/*********************  Orion Board GPIO Map *********************************/
// struct defined in MePort.h
// MePort_Sig mePort[17] = {
// 	{ NC, NC },{ 11, 10 },{ 3,  9 },{ 12, 13 },{ 8,  2 },
// 	{ NC, NC },{ A2, A3 },{ A6, A1 },{ A7, A0 },{ 6,  7 },
// 	{ 5,  4 },{ NC, NC },{ NC, NC },{ NC, NC },{ NC, NC },
// 	{ NC, NC },{ NC, NC },
// };

#endif

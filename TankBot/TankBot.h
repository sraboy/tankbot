#ifndef _TANKBOT_H
#define _TANKBOT_H

//
// Note that the includes below depend on a modified version of Makeblock-Libraries:
// https://github.com/sraboy/Makeblock-Libraries
//
// The changes may or may not make any difference but ensure you're including the
// right ones.
//

#include <Wire.h>
#include <SoftwareSerial.h>
#include <Arduino.h>

#include "Port.h"
#include "Drive.h"
#include "BT12.h"

void setup();
void loop();

inline void buzz(int delay_time = 100) {
	pinMode(SCL, OUTPUT);
	digitalWrite(SCL, HIGH);
	delay(delay_time);
	pinMode(SCL, OUTPUT);
	digitalWrite(SCL, LOW);
}

/*********************  Orion Board GPIO Map *********************************/
// struct defined in MePort.h
MePort_Sig mePort[17] = {
	{ NC, NC },{ 11, 10 },{ 3,  9 },{ 12, 13 },{ 8,  2 },
	{ NC, NC },{ A2, A3 },{ A6, A1 },{ A7, A0 },{ 6,  7 },
	{ 5,  4 },{ NC, NC },{ NC, NC },{ NC, NC },{ NC, NC },
	{ NC, NC },{ NC, NC },
};

#endif

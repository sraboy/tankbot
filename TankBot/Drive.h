#ifndef _DRIVE_H_
#define _DRIVE_H_

#include "Port.h"

namespace Drive {
	int const MaxSpeed = 255;
	int const SpeedFactor = 28;

	void Stop();

	void Forward();
	void Reverse();

	void ReverseLeft();
	void ReverseRight();
	void ForwardLeft();
	void ForwardRight();

	void TurnLeft();
	void TurnRight();

	void SetSpeedLevel(int new_speed);
	void SetSpeedRaw(int new_speed);

	void ultrCarProcess();

	void Setup(Ports::Port portLeft = Ports::Port::PM1, Ports::Port portRight = Ports::Port::PM2);
}

#endif
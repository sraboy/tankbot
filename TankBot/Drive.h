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

	void SetSpeedLevel(int);
	void SetSpeedRaw(int);

	void SetFwdNoGoCheck(bool(*)(void));

	int GetCurrentSpeed();
	void Setup(Ports::Port portLeft, Ports::Port portRight);
}

#endif
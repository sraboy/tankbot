#ifndef _DRIVE_H_
#define _DRIVE_H_

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

	void Left();
	void Right();

	void SetSpeedLevel(int);
	void SetSpeedRaw(int);

	void SetFwdNoGoCheck(bool(*)(void));

	int GetCurrentSpeed();
	void Setup(short ltPort, short rtPort);
}

#endif

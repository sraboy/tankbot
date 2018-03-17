#ifndef _DRIVE_H_
#define _DRIVE_H_

namespace Drive {

	void Reset();

	void Forward();
	void Backward();
	void BackwardAndTurnLeft();
	void BackwardAndTurnRight();
	void TurnLeft();
	void TurnRight();
	void Stop();
	void ChangeSpeed(int new_speed);
	void ForwardAndTurnLeft();
	void ForwardAndTurnRight();

	void ultrCarProcess();
}

#endif
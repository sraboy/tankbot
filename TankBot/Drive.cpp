#include <MeDCMotor.h>
#include "Drive.h"

using namespace Ports;

//extern MeUltrasonicSensor ultrasonic_sensor;// (PORT_3);
namespace Drive {

	MeDCMotor dc;
	Port Left, Right;

	int CurrentSpeed = 0;

	void Setup(Port portLeft, Port portRight) {
		Left = portLeft;
		Right = portRight;
		CurrentSpeed = MaxSpeed * 0.66;
		Stop();
	}

	void Stop() {
		dc.reset(Left);
		dc.run(0);
		dc.reset(Right);
		dc.run(0);
	}

	void Forward() {
		dc.reset(Left);
		dc.run(CurrentSpeed);
		dc.reset(Right);
		dc.run(CurrentSpeed);
	}

	void Reverse() {
		dc.reset(Left);
		dc.run(-CurrentSpeed);
		dc.reset(Right);
		dc.run(-CurrentSpeed);
	}

	void ForwardLeft() {
		dc.reset(Left);
		dc.run(CurrentSpeed / 2);
		dc.reset(Right);
		dc.run(CurrentSpeed);
	}

	void ForwardRight() {
		dc.reset(Left);
		dc.run(CurrentSpeed);
		dc.reset(Right);
		dc.run(CurrentSpeed / 2);
	}

	void ReverseLeft() {
		dc.reset(Left);
		dc.run(-CurrentSpeed / 2);
		dc.reset(Right);
		dc.run(-CurrentSpeed);
	}

	void ReverseRight() {
		dc.reset(Left);
		dc.run(-CurrentSpeed);
		dc.reset(Right);
		dc.run(-CurrentSpeed / 2);
	}

	void TurnLeft() {
		dc.reset(Left);
		dc.run(-CurrentSpeed);
		dc.reset(Right);
		dc.run(CurrentSpeed);
	}

	void TurnRight() {
		dc.reset(Left);
		dc.run(CurrentSpeed);
		dc.reset(Right);
		dc.run(-CurrentSpeed);
	}

	//
	// Sets the speed to new_speed * SpeedFactor
	//
	void SetSpeedLevel(int new_speed) {
		CurrentSpeed = new_speed * SpeedFactor;
	}

	void SetSpeedRaw(int new_speed) {
		CurrentSpeed = new_speed;
	}

	void ultrCarProcess() {}
	//	distance = ultrasonic_sensor.distanceCm();
	//	randomSeed(analogRead(A4));
	//	if ((distance > 10) && (distance < 40)) {
	//		randnum = random(300);
	//		if ((randnum > 190) && (!rightflag)) {
	//			leftflag = true;
	//			DriveTurnLeft();
	//		} else {
	//			rightflag = true;
	//			DriveTurnRight();
	//		}
	//	} else if (distance < 10) {
	//		randnum = random(300);
	//		if (randnum > 190) {
	//			DriveBackwardAndTurnLeft();
	//		} else {
	//			DriveBackwardAndTurnRight();
	//		}
	//	} else {
	//		leftflag = false;
	//		rightflag = false;
	//		DriveForward();
	//	}
	//}
} //namespace Drive
#include "Drive.h"
#include <MeDCMotor.h>

//extern MeUltrasonicSensor ultrasonic_sensor;// (PORT_3);
namespace Drive {
	MeDCMotor dc;
	int moveSpeed = 190;
	int turnSpeed = 200;
	int minSpeed = 45;
	int factor = 23;
	bool leftflag = false;
	bool rightflag = false;
	int randnum = 0;
	int distance = 0;

	void Reset() {
		dc.reset(M1);
		dc.run(0);
		dc.reset(M2);
		dc.run(0);
		dc.reset(PORT_1);
		dc.run(0);
		dc.reset(PORT_2);
		dc.run(0);
	}

	void Forward() {
		dc.reset(M1);
		dc.run(moveSpeed);
		dc.reset(M2);
		dc.run(moveSpeed);
	}

	void Backward() {
		dc.reset(M1);
		dc.run(-moveSpeed);
		dc.reset(M2);
		dc.run(-moveSpeed);
	}

	void ForwardAndTurnLeft() {
		dc.reset(M1);
		dc.run(moveSpeed / 2);
		dc.reset(M2);
		dc.run(moveSpeed);
	}

	void ForwardAndTurnRight() {
		dc.reset(M1);
		dc.run(moveSpeed);
		dc.reset(M2);
		dc.run(moveSpeed / 2);
	}

	void BackwardAndTurnLeft() {
		dc.reset(M1);
		dc.run(-moveSpeed / 2);
		dc.reset(M2);
		dc.run(-moveSpeed);
	}

	void BackwardAndTurnRight() {
		dc.reset(M1);
		dc.run(-moveSpeed);
		dc.reset(M2);
		dc.run(-moveSpeed / 2);
	}

	void TurnLeft() {
		dc.reset(M1);
		dc.run(-moveSpeed);
		dc.reset(M2);
		dc.run(moveSpeed);
	}

	void TurnRight() {
		dc.reset(M1);
		dc.run(moveSpeed);
		dc.reset(M2);
		dc.run(-moveSpeed);
	}

	void Stop() {
		dc.reset(M1);
		dc.run(0);
		dc.reset(M2);
		dc.run(0);
	}

	void ChangeSpeed(int new_speed) {
		int spd = new_speed * factor + minSpeed;
		moveSpeed = spd;
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
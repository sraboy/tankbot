#include <MeDCMotor.h>
#include "Drive.h"

using namespace Ports;

//extern MeUltrasonicSensor ultrasonic_sensor;// (PORT_3);
namespace Drive {

	MeDCMotor dc;
	Port Left, Right;
	int CurrentSpeed = 0;
	int StopVal = 0;
	//
	// With very low speeds and/or low battery power,
	// the tank may not be able to turn so we ensure
	// a minimum value that appears to work.
	//
	int const MinTurnSpeed = 80;

	bool(*CheckSensorVal)() = nullptr;

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

	inline bool CanGo() {
		bool can_go = true;
		if (CheckSensorVal) {
			can_go = CheckSensorVal();
			//Serial.print("can_go: ");
			//Serial.println(can_go);
		}
		return can_go;
	}

	void Forward() {
		bool can_go = CanGo();
		dc.reset(Left);
		dc.run(can_go ? CurrentSpeed : 0);
		dc.reset(Right);
		dc.run(can_go ? CurrentSpeed : 0);
	}

	void Reverse() {
		CheckSensorVal();
		dc.reset(Left);
		dc.run(-CurrentSpeed);
		dc.reset(Right);
		dc.run(-CurrentSpeed);
	}

	void ForwardLeft() {
		bool can_go = CanGo();
		dc.reset(Left);
		dc.run(can_go ? CurrentSpeed / 2 : 0);
		dc.reset(Right);
		dc.run(can_go ? CurrentSpeed : 0);
	}

	void ForwardRight() {
		bool can_go = CanGo();
		dc.reset(Left);
		dc.run(can_go ? CurrentSpeed : 0);
		dc.reset(Right);
		dc.run(can_go ? CurrentSpeed / 2 : 0);
	}

	void ReverseLeft() {
		CheckSensorVal();
		dc.reset(Left);
		dc.run(-CurrentSpeed / 2);
		dc.reset(Right);
		dc.run(-CurrentSpeed);
	}

	void ReverseRight() {
		CheckSensorVal();
		dc.reset(Left);
		dc.run(-CurrentSpeed);
		dc.reset(Right);
		dc.run(-CurrentSpeed / 2);
	}

	void TurnLeft() {
		CheckSensorVal();
		dc.reset(Left);
		dc.run(-max(CurrentSpeed, MinTurnSpeed));
		dc.reset(Right);
		dc.run(max(CurrentSpeed, MinTurnSpeed));
	}

	void TurnRight() {
		CheckSensorVal();
		dc.reset(Left);
		dc.run(max(CurrentSpeed, MinTurnSpeed));
		dc.reset(Right);
		dc.run(-max(CurrentSpeed, MinTurnSpeed));
	}

	//
	// Sets the speed to new_speed * SpeedFactor
	//
	void SetSpeedLevel(int new_speed) {
		CheckSensorVal();
		CurrentSpeed = new_speed * SpeedFactor;
	}

	void SetSpeedRaw(int new_speed) {
		CheckSensorVal();
		CurrentSpeed = new_speed;
	}

	int GetCurrentSpeed() {
		return CurrentSpeed;
	}

	void SetFwdNoGoCheck(bool(*check_val)(void)) {
		CheckSensorVal = check_val;
	}
} //namespace Drive
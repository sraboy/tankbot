#include "Eyes.h"
#include <Servo.h>
#include <MeUltrasonicSensor.h>

namespace Eyes {

	MeUltrasonicSensor Ultrasonic;
	Servo Neck;
	MePort ServoPort;
	int16_t ServoPin;

	int last_ultra_sonic_time = 0;

	int ServoMoveSafetyDelay = 250;
	int const UltrasonicReadMinDelay = 100;
	int const UltrasonicReadDelay = UltrasonicReadMinDelay * 2;

	void Setup(Ports::Port ultrasonic_port, Ports::Port servo_port, bool servo_pin_one, int safety_delay_ms) {
		Ultrasonic = MeUltrasonicSensor(static_cast<uint8_t>(ultrasonic_port));
		ServoPort = MePort(servo_port);
		ServoPin = servo_pin_one ? ServoPort.pin1() : ServoPort.pin2();
		Neck.attach(ServoPin);
		ServoMoveSafetyDelay = safety_delay_ms;
		Test();
	}

	//
	// Wait for the servo to move. The Mini Servo 9g moves at
	// 0.12sec/60 degrees so we wait twice as many milliseconds
	// as degrees we're moving. We can add extra time for safety.
	//
	int get_wait_needed(int old_pos, int new_pos) {
		//Serial.print("old_pos: ");
		//Serial.println(old_pos);
		//Serial.print("new_pos: ");
		//Serial.println(new_pos);
		
		//
		// Can't do operations within abs()
		//
		int diff = old_pos - new_pos;
		//Serial.print("diff: ");
		//Serial.println(diff);
		//Serial.print("abs: ");
		//Serial.println(abs(diff));
		
		int delay_time = (abs(diff) * 2) + ServoMoveSafetyDelay;
		//Serial.print("delay_time: ");
		//Serial.println(delay_time);
		return delay_time;
	}

	void Test() {
		//
		// We increase the safety delay for the test, just in case
		//
		ServoMoveSafetyDelay += 250;
		Look(LookWhere::Ahead);
		Look(LookWhere::Down);
		Look(LookWhere::Ahead);
		Look(LookWhere::GlanceDown);
		Look(LookWhere::Ahead);
		ServoMoveSafetyDelay -= 250;
	}

	//
	// Ultrasonic sensor needs ~100ms between reads. If not enough
	// time has passed since the last read, the function returns -1.0
	//
	double TryReadDistanceCm(int max_view_dist) {
		auto cur_time = millis();
		double distance = -1.0;
		if (cur_time - last_ultra_sonic_time >= UltrasonicReadDelay) {
			last_ultra_sonic_time = cur_time;
			distance = Ultrasonic.distanceCm(max_view_dist);
		}
		return distance;
	}

	void Look(LookWhere pos, bool do_delay = true) {
		int old_pos = SetRawServoPos(pos);
		int wait_time = get_wait_needed(old_pos, pos);
		if (do_delay) {
			delay(wait_time);
		}
	}

	int GetPos() {
		return Neck.read();
	}
	//
	// Sets the position and does not have an
	// automatic delay, so the caller must handle
	// that appropriately. Old position is returned.
	//
	int SetRawServoPos(int value) {
		int old_pos = Neck.read();
		Neck.write(value);
		return old_pos;
	}
} //namespace Eyes
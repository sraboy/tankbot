/*************************************************************************
* File Name          :starter_factory_firmware.ino
* Author             : Ander, Mark Yan
* Updated            : Ander, Mark Yan
* Version            : V0a.01.007
* Date               : 21/06/2017
* Description        : Firmware for Makeblock Electronic modules with Scratch.
* License            : CC-BY-SA 3.0
* Copyright (C) 2013 - 2016 Maker Works Technology Co., Ltd. All right reserved.
* http://www.makeblock.cc/
**************************************************************************/
#include <Wire.h>
#include <SoftwareSerial.h>
#include <Arduino.h>
#include <MeOrion.h>
#include "Port.h"
#include "Drive.h"
#include "Infrared.h"

MeUltrasonicSensor ultrasonic_sensor(PORT_4);
Me7SegmentDisplay display(PORT_3);
Servo servo;
MePort servo_port(PORT_8);
int16_t servo_pin = servo_port.pin2();

void IrNumToDrive(Infrared::Button button) {
	switch (button) {
	case Infrared::Button::NUM0:
		//Serial.println("Got 0");
		Drive::ReverseLeft();
		break;
	default:
		//Serial.print("Got ");
		//Serial.println(Infrared::ButtonVal(button));
		Drive::SetSpeedLevel(Infrared::ButtonVal(button));
		break;
	}
}

int last_ultra_sonic_time = 0;
bool last_can_go = true;
int const sensor_delay = 100;
bool CanGoOnCloseObject() {
	auto cur_time = millis();
	//
	// Ultrasonic sensor needs ~100ms between reads
	//
	if (cur_time - last_ultra_sonic_time >= sensor_delay) {
		
		last_ultra_sonic_time = cur_time;
		
		int const max_view_dist = 400;
		double distance = ultrasonic_sensor.distanceCm(max_view_dist);
		Serial.print(F("Distance: "));
		Serial.println(distance);
		display.display(distance);

		double stop_distance = 8.0;
		int cur_spd = Drive::GetCurrentSpeed();
		if (cur_spd > 180) {
			stop_distance = 12.0;
		} else if (cur_spd < 40) {
			stop_distance = 4.0;
		}

		if (distance < stop_distance) {
			last_can_go = false;
			return last_can_go;
		} else {
			last_can_go = true;
			return last_can_go;
		}

	}
	return last_can_go;
}

Infrared::button_callbacks cb;

void setup() {
	Serial.begin(9600);

	Drive::Setup();
	Drive::SetFwdNoGoCheck(CanGoOnCloseObject);

	cb.OnUp = Drive::Forward;
	cb.OnDown = Drive::Reverse;
	cb.OnLeft = Drive::TurnLeft;
	cb.OnRight = Drive::TurnRight;
	cb.OnD = Drive::ForwardLeft;
	cb.OnE = Drive::ForwardRight;
	cb.OnF = Drive::ReverseRight;
	cb.OnNum = IrNumToDrive;

	Infrared::Setup(Ports::Port::P6, &cb);
	Serial.println("Setup complete");

	display.init();
	display.set(BRIGHTNESS_2);

	servo.attach(servo_pin);

	servo.write(120);
	delay(500);		// servo may have a long way to move
	servo.write(180);
	delay(250);		// servo only moving 60* now, delay for buzzer too
	buzzerOn();
	delay(100);		// buzzer delay
	buzzerOff();
	delay(500);		// short pause to let everything finish
}

void loop() {
	Infrared::Process();
}
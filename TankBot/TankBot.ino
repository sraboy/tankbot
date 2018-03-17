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

MeUltrasonicSensor ultrasonic_sensor(PORT_3);

int last_ultra_sonic_time = 0;

void IrNumToDrive(Infrared::Button button) {
	switch (button) {
	case Infrared::Button::NUM0:
		//Serial.println("Got 0");
		Drive::ReverseRight();
		break;
	default:
		//Serial.print("Got ");
		//Serial.println(Infrared::ButtonVal(button));
		Drive::SetSpeedLevel(Infrared::ButtonVal(button));
		break;
	}
}

bool last_can_go = true;
bool CanGoOnCloseObject() {
	auto cur_time = millis();
	if (cur_time - last_ultra_sonic_time > 99) {
		last_ultra_sonic_time = cur_time;
		double cm = ultrasonic_sensor.distanceCm();
		Serial.print("Distance: ");
		Serial.println(cm);

		if (cm < 10.0) {
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
	delay(500);
	buzzerOn();
	delay(100);
	buzzerOff();
	delay(500);

	Drive::Setup();
	Drive::SetFwdNoGoCheck(CanGoOnCloseObject);

	cb.OnUp = Drive::Forward;
	cb.OnDown = Drive::Reverse;
	cb.OnLeft = Drive::TurnLeft;
	cb.OnRight = Drive::TurnRight;
	cb.OnD = Drive::ForwardLeft;
	cb.OnE = Drive::ForwardRight;
	cb.OnF = Drive::ReverseLeft;
	cb.OnNum = IrNumToDrive;

	Infrared::Setup(Ports::Port::P6, &cb);
	Serial.println("Setup complete");
}
void loop() {

	Infrared::Process();

}
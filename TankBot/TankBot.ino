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
Me7SegmentDisplay display(PORT_4);
MePotentiometer pot(PORT_7);

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

int last_ultra_sonic_time = 0;
bool last_can_go = true;
double last_distance = 0.0;
int const sensor_delay = 100;
bool CanGoOnCloseObject() {
	auto cur_time = millis();
	if (cur_time - last_ultra_sonic_time >= sensor_delay) {
		last_ultra_sonic_time = cur_time;
		int p = pot.read();
		int max_dist = p / 2.5;
		Serial.print(F("Max Distance: "));
		Serial.println(last_distance);
		last_distance = ultrasonic_sensor.distanceCm(max_dist);
		Serial.print(F("Distance: "));
		Serial.println(last_distance);
		display.display(last_distance);

		double stop_distance = 8.0;
		int cur_spd = Drive::GetCurrentSpeed();
		if (cur_spd > 180) {
			stop_distance = 12.0;
		} else if (cur_spd < 40) {
			stop_distance = 4.0;
		}
		if (last_distance < stop_distance) {
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

	display.init();
	display.set(BRIGHTNESS_2);
}

void loop() {

	Infrared::Process();

}
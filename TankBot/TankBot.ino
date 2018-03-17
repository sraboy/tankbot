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
#include "Eyes.h"

Me7SegmentDisplay display(PORT_3);
//
// See CanGoOnCloseObject()
//
bool last_can_go = true;
Infrared::button_callbacks ir_btn_callbacks;

//
// Callback for IR number buttons
//
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

//
// Decides whether or not to prevent the bot from moving
// forward based on the (projected) speed and how near/far
// any obstacles are.
//
bool CanGoOnCloseObject() {

	double distance = Eyes::TryReadDistanceCm();
	if (distance > 0.0) {
		//Serial.print(F("Distance: "));
		//Serial.println(distance);
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

void setup() {
	Serial.begin(9600);

	Drive::Setup();
	Drive::SetFwdNoGoCheck(CanGoOnCloseObject);

	ir_btn_callbacks.OnUp = Drive::Forward;
	ir_btn_callbacks.OnDown = Drive::Reverse;
	ir_btn_callbacks.OnLeft = Drive::TurnLeft;
	ir_btn_callbacks.OnRight = Drive::TurnRight;
	ir_btn_callbacks.OnD = Drive::ForwardLeft;
	ir_btn_callbacks.OnE = Drive::ForwardRight;
	ir_btn_callbacks.OnF = Drive::ReverseRight;
	ir_btn_callbacks.OnNum = IrNumToDrive;

	Infrared::Setup(Ports::Port::P6, &ir_btn_callbacks);

	display.init();
	display.set(BRIGHTNESS_2);
	Eyes::Setup(Ports::P4, Ports::P8, false, 50);
	display.display(Eyes::TryReadDistanceCm());

	delay(250);		// wait on everything above to finish
	buzzerOn();
	delay(100);		// buzzer delay
	buzzerOff();
	delay(500);		// short pause to let everything finish
	Serial.println(F("Setup complete"));
}

void loop() {
	Infrared::Process();
}
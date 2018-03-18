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
enum IrCallbackSet {
	CbDrive = 1,
	CbEyes = 2
};
void SetCallbacks(IrCallbackSet cbset);
#include <Wire.h>
#include <SoftwareSerial.h>
#include <Arduino.h>
#include <MeOrion.h>
#include "Port.h"
#include "Drive.h"
#include "Infrared.h"
#include "Eyes.h"
#include "LedDisplay.h"

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
		LedDisplay::Display(distance);

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

void SetCallbacks(IrCallbackSet cbset) {
	uint8_t mode[4] = { 0x40, 0x40, 0x40, 0x40 }; // ----
	switch (cbset) {
	case IrCallbackSet::CbDrive:
		mode[1] = LedDisplay::Char::d;
		mode[2] = LedDisplay::Char::r;
		mode[3] = LedDisplay::Char::v;
		ir_btn_callbacks.OnUp = Drive::Forward;
		ir_btn_callbacks.OnDown = Drive::Reverse;
		ir_btn_callbacks.OnLeft = Drive::TurnLeft;
		ir_btn_callbacks.OnRight = Drive::TurnRight;
		ir_btn_callbacks.OnD = Drive::ForwardLeft;
		ir_btn_callbacks.OnE = Drive::ForwardRight;
		ir_btn_callbacks.OnF = Drive::ReverseRight;
		ir_btn_callbacks.OnNum = IrNumToDrive;
		ir_btn_callbacks.OnSetting = SetCallbacksEyes;
		break;
	case IrCallbackSet::CbEyes:
		mode[1] = LedDisplay::Char::e;
		mode[2] = LedDisplay::Char::y;
		mode[3] = LedDisplay::Char::e;
		ir_btn_callbacks.OnUp = LookAhead;
		ir_btn_callbacks.OnDown = LookDown;
		ir_btn_callbacks.OnLeft = Infrared::no_callback;
		ir_btn_callbacks.OnRight = Infrared::no_callback;
		ir_btn_callbacks.OnD = Infrared::no_callback;
		ir_btn_callbacks.OnE = Infrared::no_callback;
		ir_btn_callbacks.OnF = Infrared::no_callback;
		ir_btn_callbacks.OnNum = Infrared::no_callback;
		ir_btn_callbacks.OnSetting = SetCallbacksDrive;
		break;
	default:
		break;
	}
	
	LedDisplay::Write(mode);
}

void SetCallbacksDrive() {
	SetCallbacks(IrCallbackSet::CbDrive);
}

void SetCallbacksEyes() {
	SetCallbacks(IrCallbackSet::CbEyes);
}

void LookAhead() {
	Eyes::Look(Eyes::LookWhere::Ahead);
}

void LookDown() {
	Eyes::Look(Eyes::LookWhere::Down);
}

void setup() {
	Serial.begin(9600);
	LedDisplay::Setup(Ports::P3, LedDisplay::Brightness::BRT_3);
	
	Drive::Setup(Ports::Port::PM1, Ports::Port::PM2);
	Drive::SetFwdNoGoCheck(CanGoOnCloseObject);
	SetCallbacks(IrCallbackSet::CbDrive);
	
	Infrared::Setup(Ports::Port::P6, &ir_btn_callbacks);

	Eyes::Setup(Ports::P4, Ports::P8, false, 50);
	LedDisplay::Display(Eyes::TryReadDistanceCm());

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
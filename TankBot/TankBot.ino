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

//MeInfraredReceiver infraredReceiverDecode(PORT_6);

MeUltrasonicSensor ultrasonic_sensor(PORT_3);

MePort generalDevice;


typedef struct MeModule {
	int device;
	int port;
	int slot;
	int pin;
	int index;
	float values[3];
} MeModule;

union {
	byte byteVal[4];
	float floatVal;
	long longVal;
}val;

union {
	byte byteVal[8];
	double doubleVal;
}valDouble;

union {
	byte byteVal[2];
	short shortVal;
}valShort;
MeModule modules[12];
#if defined(__AVR_ATmega32U4__) 
int analogs[12] = { A0,A1,A2,A3,A4,A5,A6,A7,A8,A9,A10,A11 };
#endif
#if defined(__AVR_ATmega328P__) or defined(__AVR_ATmega168__)
int analogs[8] = { A0,A1,A2,A3,A4,A5,A6,A7 };
#endif
#if defined(__AVR_ATmega1280__)|| defined(__AVR_ATmega2560__)
int analogs[16] = { A0,A1,A2,A3,A4,A5,A6,A7,A8,A9,A10,A11,A12,A13,A14,A15 };
#endif

#define BLUE_TOOTH      0
#define IR_CONTROLER    1

boolean isStart = false;
boolean isAvailable = false;

char buffer[52];
char serialRead;
byte index = 0;
byte dataLen;
byte modulesLen = 0;
uint8_t keyPressed = 0;
uint8_t command_index = 0;
uint8_t prevc = 0;

int len = 52;


int starter_mode = 0;
int servo_pins[8] = { 0,0,0,0,0,0,0,0 };

double lastTime = 0.0;
double currentTime = 0.0;
float angleServo = 90.0;

String mVersion = "0a.01.007";

#define VERSION                0
#define ULTRASONIC_SENSOR      1
#define TEMPERATURE_SENSOR     2
#define LIGHT_SENSOR           3
#define POTENTIONMETER         4
#define JOYSTICK               5
#define GYRO                   6
#define SOUND_SENSOR           7
#define RGBLED                 8
#define SEVSEG                 9
#define MOTOR                  10
#define SERVO                  11
#define ENCODER                12
#define IR                     13
#define PIRMOTION              15
#define INFRARED               16
#define LINEFOLLOWER           17
#define SHUTTER                20
#define LIMITSWITCH            21
#define BUTTON                 22
#define HUMITURE               23
#define FLAMESENSOR            24
#define GASSENSOR              25
#define COMPASS                26
#define TEMPERATURE_SENSOR_1   27
#define DIGITAL                30
#define ANALOG                 31
#define PWM                    32
#define SERVO_PIN              33
#define TONE                   34
#define BUTTON_INNER           35
#define ULTRASONIC_ARDUINO     36
#define PULSEIN                37
#define STEPPER                40
#define LEDMATRIX              41
#define TIMER                  50
#define TOUCH_SENSOR           51
#define JOYSTICK_MOVE          52
#define COMMON_COMMONCMD       60
//Secondary command
#define SET_STARTER_MODE     0x10
#define SET_AURIGA_MODE      0x11
#define SET_MEGAPI_MODE      0x12
#define GET_BATTERY_POWER    0x70
#define GET_AURIGA_MODE      0x71
#define GET_MEGAPI_MODE      0x72
#define ENCODER_BOARD          61
//Read type
#define ENCODER_BOARD_POS    0x01
#define ENCODER_BOARD_SPEED  0x02

#define ENCODER_PID_MOTION     62
//Secondary command
#define ENCODER_BOARD_POS_MOTION         0x01
#define ENCODER_BOARD_SPEED_MOTION       0x02
#define ENCODER_BOARD_PWM_MOTION         0x03
#define ENCODER_BOARD_SET_CUR_POS_ZERO   0x04
#define ENCODER_BOARD_CAR_POS_MOTION     0x05

#define GET 1
#define RUN 2
#define RESET 4
#define START 5

unsigned char readBuffer(int index) {
	return buffer[index];
}

void writeBuffer(int index, unsigned char c) {
	buffer[index] = c;
}

void writeHead() {
	writeSerial(0xff);
	writeSerial(0x55);
}

void writeEnd() {
	Serial.println();
#if defined(__AVR_ATmega32U4__) 
	Serial1.println();
#endif
}

void writeSerial(unsigned char c) {
	Serial.write(c);
#if defined(__AVR_ATmega32U4__) 
	Serial1.write(c);
#endif
}

void readSerial() {
	isAvailable = false;
	if (Serial.available() > 0) {
		isAvailable = true;
		serialRead = Serial.read();
	}
}
/*
ff 55 len idx action device port  slot  data a
0  1  2   3   4      5      6     7     8
*/
void parseData() {
	isStart = false;
	int idx = readBuffer(3);
	command_index = (uint8_t)idx;
	int action = readBuffer(4);
	int device = readBuffer(5);
	switch (action) {
	case GET: {
		if (device != ULTRASONIC_SENSOR) {
			writeHead();
			writeSerial(idx);
		}
		readSensor(device);
		writeEnd();
	}
			  break;
	case RUN: {
		runModule(device);
		callOK();
	}
			  break;
	case RESET: {
		//reset
		Drive::Stop();
		callOK();
	}
				break;
	case START: {
		//start
		callOK();
	}
				break;
	}
}

void callOK() {
	writeSerial(0xff);
	writeSerial(0x55);
	writeEnd();
}

void sendByte(char c) {
	writeSerial(1);
	writeSerial(c);
}

void sendString(String s) {
	int l = s.length();
	writeSerial(4);
	writeSerial(l);
	for (int i = 0; i < l; i++) {
		writeSerial(s.charAt(i));
	}
}

void sendFloat(float value) {
	writeSerial(0x2);
	val.floatVal = value;
	writeSerial(val.byteVal[0]);
	writeSerial(val.byteVal[1]);
	writeSerial(val.byteVal[2]);
	writeSerial(val.byteVal[3]);
}

void sendShort(double value) {
	writeSerial(3);
	valShort.shortVal = value;
	writeSerial(valShort.byteVal[0]);
	writeSerial(valShort.byteVal[1]);
}

void sendDouble(double value) {
	writeSerial(2);
	valDouble.doubleVal = value;
	writeSerial(valDouble.byteVal[0]);
	writeSerial(valDouble.byteVal[1]);
	writeSerial(valDouble.byteVal[2]);
	writeSerial(valDouble.byteVal[3]);
}

short readShort(int idx) {
	valShort.byteVal[0] = readBuffer(idx);
	valShort.byteVal[1] = readBuffer(idx + 1);
	return valShort.shortVal;
}

float readFloat(int idx) {
	val.byteVal[0] = readBuffer(idx);
	val.byteVal[1] = readBuffer(idx + 1);
	val.byteVal[2] = readBuffer(idx + 2);
	val.byteVal[3] = readBuffer(idx + 3);
	return val.floatVal;
}

long readLong(int idx) {
	val.byteVal[0] = readBuffer(idx);
	val.byteVal[1] = readBuffer(idx + 1);
	val.byteVal[2] = readBuffer(idx + 2);
	val.byteVal[3] = readBuffer(idx + 3);
	return val.longVal;
}

void runModule(int device) {
	//0xff 0x55 0x6 0x0 0x1 0xa 0x9 0x0 0x0 0xa
	int port = readBuffer(6);
	int pin = port;
	switch (device) {
		//case MOTOR: {
		//	controlflag = BLUE_TOOTH;
		//	int speed = readShort(7);
		//	dc.reset(port);
		//	dc.run(speed);
		//}
		//			break;
		//case JOYSTICK: {
		//	controlflag = BLUE_TOOTH;
		//	int leftSpeed = readShort(6);
		//	dc.reset(M1);
		//	dc.run(leftSpeed);
		//	int rightSpeed = readShort(8);
		//	dc.reset(M2);
		//	dc.run(rightSpeed);
		//}

	case COMMON_COMMONCMD: {
		int slot = readBuffer(7);
		int subcmd = readBuffer(8);
		int cmd = readBuffer(9);
		if (SET_STARTER_MODE == subcmd) {
			Drive::Stop();
			if ((cmd == 0x01) || (cmd == 0x00)) {
				starter_mode = cmd;
			} else {
				starter_mode = 0;
			}
		}
	}
						   break;



	case DIGITAL: {
		pinMode(pin, OUTPUT);
		int v = readBuffer(7);
		digitalWrite(pin, v);
	}
				  break;
	case PWM: {
		pinMode(pin, OUTPUT);
		int v = readBuffer(7);
		analogWrite(pin, v);
	}
			  break;

	case TIMER: {
		lastTime = millis() / 1000.0;
	}
				break;
	}
}

void readSensor(int device) {
	/**************************************************
	ff 55 len idx action device port slot data a
	0  1  2   3   4      5      6    7    8
	***************************************************/
	float value = 0.0;
	int port, slot, pin;
	port = readBuffer(6);
	pin = port;
	switch (device) {
	case  ULTRASONIC_SENSOR: {
		if (ultrasonic_sensor.getPort() != port) {
			ultrasonic_sensor.reset(port);
		}
		value = ultrasonic_sensor.distanceCm();
		writeHead();
		writeSerial(command_index);
		sendFloat(value);
	}
							 break;

	case  POTENTIONMETER: {
		if (generalDevice.getPort() != port) {
			generalDevice.reset(port);
			pinMode(generalDevice.pin2(), INPUT);
		}
		value = generalDevice.aRead2();
		sendFloat(value);
	}
						  break;

	case  PIRMOTION: {
		if (generalDevice.getPort() != port) {
			generalDevice.reset(port);
			pinMode(generalDevice.pin2(), INPUT);
		}
		value = generalDevice.dRead2();
		sendFloat(value);
	}
					 break;
	case  LINEFOLLOWER: {
		if (generalDevice.getPort() != port) {
			generalDevice.reset(port);
			pinMode(generalDevice.pin1(), INPUT);
			pinMode(generalDevice.pin2(), INPUT);
		}
		value = generalDevice.dRead1() * 2 + generalDevice.dRead2();
		sendFloat(value);
	}
						break;
	case LIMITSWITCH: {
		slot = readBuffer(7);
		if (generalDevice.getPort() != port || generalDevice.getSlot() != slot) {
			generalDevice.reset(port, slot);
		}
		if (slot == 1) {
			pinMode(generalDevice.pin1(), INPUT_PULLUP);
			value = !generalDevice.dRead1();
		} else {
			pinMode(generalDevice.pin2(), INPUT_PULLUP);
			value = !generalDevice.dRead2();
		}
		sendFloat(value);
	}
					  break;

	case  VERSION: {
		sendString(mVersion);
	}
				   break;
	case  DIGITAL: {
		pinMode(pin, INPUT);
		sendFloat(digitalRead(pin));
	}
				   break;
	case  ANALOG: {
		pin = analogs[pin];
		pinMode(pin, INPUT);
		sendFloat(analogRead(pin));
	}
				  break;
	case  PULSEIN: {
		int pw = readShort(7);
		pinMode(pin, INPUT);
		sendShort(pulseIn(pin, HIGH, pw));
	}
				   break;
	case ULTRASONIC_ARDUINO: {
		int trig = readBuffer(6);
		int echo = readBuffer(7);
		pinMode(trig, OUTPUT);
		digitalWrite(trig, LOW);
		delayMicroseconds(2);
		digitalWrite(trig, HIGH);
		delayMicroseconds(10);
		digitalWrite(trig, LOW);
		pinMode(echo, INPUT);
		sendFloat(pulseIn(echo, HIGH, 30000) / 58.0);
	}
							 break;
	case TIMER: {
		sendFloat((float)currentTime);
	}
				break;

	}
}

void IrNumToDrive(Infrared::Button button) {
	switch (button) {
	case Infrared::Button::NUM0:
		Drive::ReverseRight();
		break;
	default:
		Drive::SetSpeedLevel(Infrared::ButtonVal(button));
		break;
	}
}

void setup() {
	pinMode(13, OUTPUT);
	digitalWrite(13, HIGH);
	delay(300);
	digitalWrite(13, LOW);
	Serial.begin(115200);
	delay(500);
	buzzerOn();
	delay(100);
	buzzerOff();
	delay(500);
	randomSeed(analogRead(0));

	Drive::Setup();

	Infrared::button_callbacks cb;
	cb.OnUp = Drive::Forward;
	cb.OnDown = Drive::Reverse;
	cb.OnLeft = Drive::TurnLeft;
	cb.OnRight = Drive::TurnRight;
	cb.OnD = Drive::ForwardLeft;
	cb.OnE = Drive::ForwardRight;
	cb.OnF = Drive::ReverseLeft;
	cb.OnNum = IrNumToDrive;

	Infrared::Setup(Ports::Port::P6, cb);

	Serial.print(F("Makeblock Version: "));
	Serial.println(mVersion);
}
void loop() {

	currentTime = millis() / 1000.0 - lastTime;
	readSerial();

	if (isAvailable) {
		unsigned char c = serialRead & 0xff;
		if ((c == 0x55) && (isStart == false)) {
			if (prevc == 0xff) {
				index = 1;
				isStart = true;
			}
		} else {
			prevc = c;
			if (isStart) {
				if (index == 2) {
					dataLen = c;
				} else if (index > 2) {
					dataLen--;
				}
				writeBuffer(index, c);
			}
		}
		index++;
		if (index > 51) {
			index = 0;
			isStart = false;
		}
		if (isStart && (dataLen == 0) && (index > 3)) {
			isStart = false;
			parseData();
			index = 0;
		}
	}
	Infrared::Process();
	if (starter_mode == 1) {
		Drive::ultrCarProcess();
	}
}
/*
 * Copyright: Steven Lavoie (2018)
 * BT12 with BlueTooth Serial Controller
 * -------------------------------------------------------------------------------------------
 * App: https://play.google.com/store/apps/details?id=nextprototypes.BTSerialController&hl=en
 * Controller: See "tankbot_controller.dat". You'll need to load the settings in the app or
 *             create your own and adjust Commands as needed.
 * -------------------------------------------------------------------------------------------
 */

#include <Arduino.h>
#include <SoftwareSerial.h>

SoftwareSerial bt_serial(10, 11); // RX, TX

enum Commands {
  NONE    = 0x0,
  FWD     = 0x2,
  REV     = 0x8,
  LEFT    = 0x4,
  RIGHT   = 0x6,
  FWDLEFT   = 0x1,
  FWDRIGHT  = 0x3,
  REVLEFT   = 0x7,
  REVRIGHT  = 0x9,
  TURNAROUND = 0x5,
  LIGHTS  = 0xa,
  GET_DIST  = 0xb,
  GET_GYRO  = 0xe,
  GET_TEMP  = 0xf,

  //
  // We'll know when the user disconnects Bluetooth
  //
  DISCONNECT = 0xfe,
  //
  // When movement buttons are released, this is sent
  // so we know to stop driving the motors.
  //
  STOP     = 0xff
};

Commands last_cmd = Commands::STOP;

void setup() {
  pinMode(LED_BUILTIN, OUTPUT);
  digitalWrite(LED_BUILTIN, LOW);
  Serial.begin(9600);
  bt_serial.begin(9600);
  Serial.println("Setup done");
}

void loop() {
  bool changed = false;
  if(bt_serial.available() > 0){
    int cur_cmd = bt_serial.read();
    if (cur_cmd != last_cmd) {
      Serial.print(" *** New command: ");
      Serial.print(cur_cmd);
      Serial.println(" *** ");
      last_cmd = cur_cmd;
      changed = true;
    }
  }

  switch(last_cmd) {
  case Commands::NONE:
    Serial.println("NONE");
    digitalWrite(LED_BUILTIN, LOW);
      break;
  case Commands::STOP:
    Serial.println("STOP");
    digitalWrite(LED_BUILTIN, LOW);
      break;
  case Commands::FWD:
    Serial.println("FWD");
    digitalWrite(LED_BUILTIN, HIGH);
      break;
  case Commands::REV:
      Serial.println("REV");
      break;
  case Commands::LEFT:
      break;
  case Commands::RIGHT:
      break;
  case Commands::FWDLEFT:
      break;
  case Commands::FWDRIGHT:
      break;
  case Commands::REVLEFT:
      break;
  case Commands::REVRIGHT:
      break;
  case Commands::LIGHTS:
      break;
  case Commands::GET_DIST:
      break;
  case Commands::GET_GYRO:
      break;
  case Commands::GET_TEMP:
      break;
    default:
    Serial.print("Unknown command: ");
    Serial.println(last_cmd);
      digitalWrite(LED_BUILTIN, HIGH);
      break;
  }
}


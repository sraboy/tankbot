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
  //
  // We'll know when the has closed the controller/terminal app
  // and we may need to act for safety.
  //
  NO_USER    = 0x0,
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
  // When movement buttons are released, this is sent
  // so we know to stop driving the motors.
  //
  BTN_RELEASE = 0xff
};

Commands last_cmd = Commands::BTN_RELEASE;

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
  case Commands::NO_USER:
    Serial.println("PANIC! User has disconnected!");
    digitalWrite(LED_BUILTIN, LOW);
    break;
  case Commands::BTN_RELEASE:
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
    Serial.println("LEFT");
    break;
  case Commands::RIGHT:
    Serial.println("RIGHT");
    break;
  case Commands::FWDLEFT:
    Serial.println("FWDLEFT");
    break;
  case Commands::FWDRIGHT:
    Serial.println("FWDRIGHT");
    break;
  case Commands::REVLEFT:
    Serial.println("REVLEFT");
    break;
  case Commands::REVRIGHT:
    Serial.println("REVRIGHT");
    break;
  case Commands::LIGHTS:
    Serial.println("LIGHTS");
    break;
  case Commands::GET_DIST:
    Serial.println("GET_DIST");
    break;
  case Commands::GET_GYRO:
    Serial.println("GET_GYRO");
    break;
  case Commands::GET_TEMP:
    Serial.println("GET_TEMP");
    break;
  case Commands::TURNAROUND:
    Serial.println("TURNAROUND");
    break;
  default:
    Serial.print("Unknown command: ");
    Serial.println(last_cmd);
      digitalWrite(LED_BUILTIN, HIGH);
    break;
  }
}


#include "Tankbot.h"
#include "Drive.h"
#include "BT12.h"
#include "Gyro.h"
#include <MeOrion.h>

namespace TankBot {

void ProcessCmd(Bluetooth::BTCommand cmd) {
  switch(cmd) {
  case Bluetooth::BTCommand::NO_USER:
    Serial.println("PANIC! User has disconnected!");
    digitalWrite(LED_BUILTIN, LOW);
    break;
  case Bluetooth::BTCommand::BTN_RELEASE:
    digitalWrite(LED_BUILTIN, LOW);
    Drive::Stop();
    break;
  case Bluetooth::BTCommand::FWD:
    //Serial.println("FWD");
    digitalWrite(LED_BUILTIN, HIGH);
    Drive::Forward();
    break;
  case Bluetooth::BTCommand::REV:
    //Serial.println("REV");
    Drive::Reverse();
    break;
  case Bluetooth::BTCommand::LEFT:
    //Serial.println("LEFT");
    Drive::Left();
    break;
  case Bluetooth::BTCommand::RIGHT:
    //Serial.println("RIGHT");
    Drive::Right();
    break;
  case Bluetooth::BTCommand::FWDLEFT:
    //Serial.println("FWDLEFT");
    Drive::ForwardLeft();
    break;
  case Bluetooth::BTCommand::FWDRIGHT:
    //Serial.println("FWDRIGHT");
    Drive::ForwardRight();
    break;
  case Bluetooth::BTCommand::REVLEFT:
    //Serial.println("REVLEFT");
    Drive::ReverseLeft();
    break;
  case Bluetooth::BTCommand::REVRIGHT:
    //Serial.println("REVRIGHT");
    Drive::ReverseRight();
    break;
  case Bluetooth::BTCommand::LIGHTS:
    //Serial.println("LIGHTS");
    break;
  case Bluetooth::BTCommand::GET_DIST:
    //Serial.println("GET_DIST");
    break;
  case Bluetooth::BTCommand::GET_GYRO:
    //Serial.println("GET_GYRO");
    break;
  case Bluetooth::BTCommand::GET_TEMP:
    //Serial.println("GET_TEMP");
    break;
  case Bluetooth::BTCommand::TURNAROUND:
    //Serial.println("TURNAROUND");
    // TODO: Measure travel distance to do a 180
    break;
  default:
    Serial.print("Unknown command: ");
    Serial.println(cmd);
    digitalWrite(LED_BUILTIN, HIGH);
    break;
  }
}

} //namepsace TankBot

void setup() {
  Serial.begin(9600);
  Bluetooth::Setup();
  Drive::Setup(M1, M2);
  //Drive::SetFwdNoGoCheck(CanGoOnCloseObject);

  delay(500);   // short pause to let everything finish
  Serial.println(F("Setup complete"));
}

void loop() {
  Bluetooth::BTCommand cmd = Bluetooth::Read();
  TankBot::ProcessCmd(cmd);

  

}

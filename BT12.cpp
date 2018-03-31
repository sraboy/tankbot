#include "BT12.h"
#include <Arduino.h>

namespace Bluetooth {

void Setup() { }

BTCommand last_cmd = BTCommand::BTN_RELEASE;
// TODO: Check for user connection first. 
// Otherwise, we get inifinite garbage from module on boot until first command.
BTCommand Read() {
  //bool changed = false;
  if(Serial.available() > 0){
    Serial.println("Got serial data");
    BTCommand cur_cmd = static_cast<BTCommand>(Serial.read());
    if (cur_cmd != last_cmd) {
      Serial.print(" *** New command: ");
      Serial.print(cur_cmd);
      Serial.println(" *** ");
      last_cmd = cur_cmd;
      //changed = true;
    }
  }

  return last_cmd;
}

}


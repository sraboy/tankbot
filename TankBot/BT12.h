#include "Port.h"

namespace Bluetooth {

typedef void(*ProcessCallback)(uint8_t);

enum Commands {
    //
    // We'll know when the has closed the controller/terminal app
    // and we may need to act for safety.
    //
    NO_USER = 0x0,
    FWD = 0x2,
    REV = 0x8,
    LEFT = 0x4,
    RIGHT = 0x6,
    FWDLEFT = 0x1,
    FWDRIGHT = 0x3,
    REVLEFT = 0x7,
    REVRIGHT = 0x9,
    TURNAROUND = 0x5,
    LIGHTS = 0xa,
    GET_DIST = 0xb,
    GET_GYRO = 0xe,
    GET_TEMP = 0xf,

    //
    // When movement buttons are released, this is sent
    // so we know to stop driving the motors.
    //
    BTN_RELEASE = 0xff
};

Commands last_cmd = Commands::BTN_RELEASE;

ProcessCallback Process;

void Setup(Ports::Port, ProcessCallback);

}
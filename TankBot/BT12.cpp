#include "BT12.h"

namespace Bluetooth {

void Setup(Ports::Port port, ProcessCallback process) {
    Process = process;
}

}


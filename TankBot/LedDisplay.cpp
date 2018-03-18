#include "LedDisplay.h"
#include <Me7SegmentDisplay.h>

namespace LedDisplay {
	Me7SegmentDisplay display;

	void Setup(Ports::Port port, Brightness bt) {
		display = Me7SegmentDisplay(port);
		display.init();
		display.setBrightness(bt);
	}

	void Write(uint8_t * data) {
		display.write(data);
	}

	void Display(double d) {
		display.display(d);
	}

} //namespace LedDisplay

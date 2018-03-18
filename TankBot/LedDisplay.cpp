#include "LedDisplay.h"
#include <Me7SegmentDisplay.h>


namespace LedDisplay {
	Me7SegmentDisplay display;

	void Setup(Ports::Port port, Brightness bt) {
		display = Me7SegmentDisplay(port);
		display.init();
		display.setBrightness(bt);
	}

	void Write(char * data) {
		LedWord str(data);
		display.write(str.data());
	}

	void Write(double d) {
		display.display(d);
	}

} //namespace LedDisplay

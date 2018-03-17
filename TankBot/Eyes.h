#ifndef _EYES_H_
#define _EYES_H_

#include "Port.h"

namespace Eyes {

	//
	// TODO: Rotate everything back 90* once servo is mounted properly
	//
	enum LookWhere {
		Ahead = 180,
		GlanceDown = 120,
		Down = 90,
		//Back = 0 // Disabled for now since it could damage the sensor
	};

	void Setup(Ports::Port, Ports::Port, bool, int);
	double TryReadDistanceCm(int max_view_dist = 400);
	int SetRawServoPos(int);
	void Look(LookWhere, bool do_delay = true);
	int GetPos();
	void Test();
}

#endif
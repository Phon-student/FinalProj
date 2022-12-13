#include "../lib/map.h"

#if MAP_DEF == 2

SensorArr	sensor;

void map_setup () {
	motorInit();
	sensorInit(&sensor);
	sensorThresh(&sensor, 20);
}

void map_logic () {
	sensorRead(&sensor);
	motorSpeed(1000, 0);
}

#endif
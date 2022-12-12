#include "../lib/map.h"

#if MAP_DEF == 1

SensorArr	sensor;

void map_setup () {
	motorInit();
	sensorInit(&sensor);
	sensorThresh(&sensor, 20);
}

void map_logic () {
	motorSpeed(1000, 1000);
}

#endif
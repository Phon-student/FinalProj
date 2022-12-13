#include "../lib/map.h"

#if MAP_DEF == 0

byte		state;
SensorArr	sensor;

void map_setup () {
	Serial.begin(19200);
	motorInit();
	sensorInit(&sensor);
	sensorThresh(&sensor, 20);
}

void map_logic () {
	sensorRead(&sensor);
	// switch (state) {
	// 	case 0:
	// 		// 
	// 		break;
	// 	case 1:
	// 		break;
	// 	case 2:
	// 		break;
	// }
	Serial.println(sensor.val);
	if (sensor.val < 450)
		motorSpeed(1000, 100);
	else if (sensor.val > 550)
		motorSpeed(100, 1000);
	else
		motorSpeed(1000, 100);
}

#endif
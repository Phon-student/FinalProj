/******************************************************\
*    _______    ___    __ __                           *
*   /  _____|  /_ |   / /| |     ____     ___    ___   *
*   | |  ____   | |  / /_| |     |   \   /   \   | |   *
*   | | |__ |   | | |____  |     |   /  |  A  |  | |   *
*   | |___| |   | |      | |     | _ \  |  _  |  | |   *
*   \_______/   |_|      |_|     |_|\_| |_| |_|  |_|   *
*                                                      *
\******************************************************/

extern "C" {
	// Includes
	#include "lib/robot.h"
	#include "lib/sensor.h"
	// Maps (Uncomment or include a new map here)
	#include "map/map_01.c"
}

Robot		robot;
SensorArr	sensor;

void setup() {
	Serial.begin(19200);
	motorInit();
	sensorInit(&sensor);
	sensorThresh(&sensor, 20);
}

void loop() {
	map_logic(&robot);
}

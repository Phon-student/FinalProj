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
	#include "lib/map.h"
}

// void setup() { map_setup(); }
// void loop() { map_logic(); }

SensorArr	sensor;
PID			pid;
byte state = 0;

void setup () {
	Serial.begin(19200);
	motorInit();
	sensorInit(&sensor);
	sensorCalibrate(&sensor);
	PIDInit(&pid, &sensor.val);
	PIDSetTarget(&pid, IR_LEN >> 1);
	// Serial.print("Threshold: ");
	// Serial.println(sensor.thresh);
	// delay(5000);
}

void loop () {
	sensorRead(&sensor);

	PIDSetConst(&pid, 0.8, 0.1, 0.1);

	motorSpeed(900 + pid.output, 900 - pid.output);

	// Serial.println(pid.output);

	// for (byte i = 0; i < IR_LEN; i++) {
	// 	Serial.print(sensor.read[i]);
	// 	Serial.print(" ");
	// }
	// Serial.println("\n");

	// Serial.println(sensor.val);
	// if (sensor.val < 1.5)
	// 	motorSpeed(0, 1000);
	// else if (sensor.val > 2.5)
	// 	motorSpeed(1000, 0);
	// else
	// 	motorSpeed(1000, 1000);

	PIDUpdate(&pid);
}

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
	delay(2000);
}

void loop () {
	 sensorRead(&sensor);

	 PIDSetConst(&pid, 50, 2.2, 0.5);

	 motorSpeed(150 + pid.output, 150 - pid.output);

  // if (pid.output < 1.5)
  //   motorSpeed(800, 1000);
  // else if (pid.output > 2.5)
  //   motorSpeed(1000, 800);  
  // else
  //   motorSpeed(1000, 1000);

	for (byte i = 0; i < IR_LEN; i++) {
		Serial.print(sensor.read[i]);
		Serial.print(" ");
	}
	Serial.println("\n");

	//  Serial.print("Value: ");
	//  Serial.println(sensor.val);
	//  Serial.print("Output: ");
	//  Serial.println(pid.output);

	 PIDUpdate(&pid);
}

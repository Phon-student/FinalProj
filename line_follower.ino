/******************************************************\
*    _______    ___    __ __                           *
*   /  _____|  /_ |   / /| |     ____     ___    ___   *
*   | |  ____   | |  / /_| |     |   \   /   \   | |   *
*   | | |__ |   | | |____  |     |   /  |  A  |  | |   *
*   | |___| |   | |      | |     | _ \  |  _  |  | |   *
*   \_______/   |_|      |_|     |_|\_| |_| |_|  |_|   *
*                                                      *
\******************************************************/

// Includes
extern "C" {
	#include "lib/map.h"
}

// void setup() { map_setup(); }
// void loop() { map_logic(); }

SensorArr	sensor;
PID			pid;

// Switch state
byte		state = 0;
// Intersect count
byte		intr = 0;

// Where to turn (0 = do not turn, 1 = left, 2 = right, 3 = end)
byte		turns[] = {
	0,				// First section
	0, 0, 0, 0,		// Second section
	0, 0,			// Third section
	2,				// Fourth section
	3				// End
};

void setup() {
	Serial.begin(19200);
	// Initializes the motor
	motorInit();
	// Initializes the sensor
	sensorInit(&sensor);
	sensorCalibrate(&sensor);
	// Initializes the PID controller
	PIDInit(&pid, &sensor.val);
	PIDSetTarget(&pid, IR_LEN >> 1);
	PIDSetConst(&pid, 50, 2.2, 0.5);

	// Debuging
	// Serial.print("Threshold: ");
	// Serial.println(sensor.thresh);
	delay(2000);
}

void loop() {
	sensorRead(&sensor);
	PIDUpdate(&pid);

	switch (state) {
		// state 0 = Terminate program (from default).
		// state 1 = Walk straight (with PID)
		// state 2 = Intersection
		case 1:
			motorSpeed(180 + pid.output, 180 - pid.output);
			if (sensor.intersect) {
				++intr;
				state = 2;
				break;
			}
		break;
		case 2:
			switch (turns[intr - 1])
			{
				// 0 = do not turn, 1 = left, 2 = right, 3 = end
				case 0:
					motorSpeed(255, 255);
					if (!sensor.intersect)
						state = 1;
				break;
				case 1:
					motorSpeed(BASE_SPEED, MAX_SPEED);
					if (sensor.val <= pid.target)
						state = 1;
				break;
				case 2:
					motorSpeed(MAX_SPEED, BASE_SPEED);
					if (sensor.val >= pid.target)
						state = 1;
				break;
				case 3:
					motorSpeed(BASE_SPEED, BASE_SPEED);
					delay(200);
					state = 0;
				break;
			}
		break;
		default:
			exit(1);
		break;
	}

	// Debug

	// for (byte i = 0; i < IR_LEN; i++) {
	// 	Serial.print(sensor.read[i]);
	// 	Serial.print(" ");
	// }
	
	// Serial.println("\n");
	
	//  Serial.print("Value: ");
	//  Serial.println(sensor.val);
	//  Serial.print("Output: ");
	//  Serial.println(pid.output);
}

#include "../lib/sensor.h"
#include <stdbool.h>

void sensorInit(SensorArr *sensor) {
	for (byte i = 0; i < IR_LEN; i++) {
		// Sets' the pinmode of each pins.
		pinMode(IR_PINS[i], INPUT);
		// Zeros out the pin value.
		sensor->read[i] = 0;
		// Sets the minimum value to the maximum of the possible input.
		sensor->min[i] = 1023;
		// Sets the opposite of min.
		sensor->max[i] = 0;
	}
	sensor->val = 0;
	sensor->outofbound = false;
	sensor->intersect = false;
}

void sensorCalibrate(SensorArr *sensor) {
	bool noisy = false;

	// Rough tuning
	do {
		sensor->thresh += 5;
		for (byte i = 0; i < IR_LEN; i++)
		{
			noisy = analogRead(IR_PINS[i]) > sensor->thresh;
			if (noisy)
				break;
		}
		delay(10);
	} while (noisy);
	// Fine tuning
	while (noisy) {
		sensor->thresh++;
		for (byte n = 0; n < 10; n++)
		{
			for (byte i = 0; i < IR_LEN; i++)
			{
				noisy = analogRead(IR_PINS[i]) > sensor->thresh;
				if (noisy)
					break;
			}
			delay(5);
		}
	};
}

void sensorGetRange(SensorArr *sensor) {
	for (byte i = 0; i < IR_LEN; i++) {
		sensor->read[i] = analogRead(IR_PINS[i]);
		// If the sensor's minimum value is greater than the value read,
		// set it the the current value.
		if (sensor->min[i] > sensor->read[i])
			sensor->min[i] = sensor->read[i];
		// Sets the sensor value.
		sensor->read[i] = sensor->read[i] - sensor->min[i];
		// Same thing for sensor's maximum value.
		if (sensor->max[i] < sensor->read[i])
			sensor->max[i] = sensor->read[i];
		if (sensor->read[i] < sensor->thresh)
			sensor->read[i] = 0;
	}
}

void sensorRead(SensorArr *sensor) {
	float	a = 0, b = 0;
	// Gets sensor's range
	sensorGetRange(sensor);
	for (byte i = 0; i < IR_LEN; i++) {
		// // Reads the senosr's value, and store it for later use.
		// sensor->read[i] = analogRead(IR_PINS[i]);
		// Constraints the value.
		if (sensor->read[i] < sensor->thresh)
		{
			sensor->read[i] = 0;
			continue; // skip the calculation for the current sensor.
		}
		// Calculate the line's position.
		a += sensor->read[i] + ((i - 1) * sensor->max[i]);
        b += sensor->read[i];
	}
	if (b > 0) {
		sensor->val = a / b;
		sensor->outofbound = false;
		if (sensor->val < 0)
			sensor->val = 0;
		else if (sensor->val > IR_LEN)
			sensor->val = IR_LEN;
		if (b > IR_LEN * sensor->thresh)
			sensor->intersect = true;
		else
			sensor->intersect = false;
	} else {
		sensor->val = IR_LEN >> 1;
		sensor->outofbound = true;
	}
}

#include "../lib/sensor.h"

void sensorInit(SensorArr *sensor) {
	for (byte i = 0; i < IR_LEN; i++) {
		// Sets' the pinmode of each pins.
		pinMode(IR_PINS[i], INPUT);
		// Zeros out the pin value.
		sensor->read[i] = 0;
		// Sets the minimum value to the maximum of the possible input.
		sensor->min[i] = 1023;
		// Set's the opposite of min.
		sensor->max[i] = 0;
	}
	sensor->val = 0;
	sensor->outofbound = false;
	sensor->intersect = false;
}

void sensorThresh(SensorArr *sensor, int val) {
	sensor->thresh = val;
}

void sensorRead(SensorArr *sensor) {
	long	Sn = 0;
	long	sum = 0;

	sensor->val = 0;
	for (byte i = 0; i < IR_LEN; i++) {
		// Reads the senosr's value, and store it for later use.
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
		// Constraints the value.
		if (sensor->read[i] < sensor->thresh)
		{
			sensor->read[i] = 0;
			continue; // skip the calculation for the current sensor.
		}
		// Calculate the sensor's position.
		// Bit shift to avoid rounding error.
		Sn = IR_ONE * ((sensor->read[i] << 2) / (sensor->max[i] - sensor->min[i])) >> 2;
		if (Sn > IR_ONE)
			Sn = IR_ONE;
		sensor->val += Sn + (IR_ONE * i);
	}
}

#ifndef SENSOR_H
#define SENSOR_H

#include <Arduino.h>
#include <stdbool.h>
#include "../lib/robot.h"

#define IR_LEN  (byte)		5						// Number of sensors
#define IR_PINS	(byte[])	{ A0, A1, A2, A3, A4 }	// IR pin define

typedef struct {
	int		read[IR_LEN];	// Sensor values (value tared & de-noised)
	int		min[IR_LEN];	// Minimum values (raw value)
	int		max[IR_LEN];	// Maximum values (raw value)
	int		thresh;			// Sensor activation threshold
	bool	outofbound;		// Is the robot is not on the line
	bool	intersect;		// Is intersected
	float	val;			// Combined value (abstracted, 0 to IR_LEN - 1)
} SensorArr;

void sensorInit(SensorArr *sensor);
void sensorCalibrate(SensorArr *sensor);
void sensorGetRange(SensorArr *sensor);
void sensorRead(SensorArr *sensor);

#endif
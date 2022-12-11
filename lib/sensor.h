#ifndef SENSOR_H
#define SENSOR_H

#include <Arduino.h>
#include <stdbool.h>

#define IR_LEN  (byte)		5						// Number of sensors
#define IR_PINS	(byte[])	{ A0, A1, A2, A3, A4 }	// IR pin define
#define IR_CONST			1000					// Lerp constants
#define IR_ONE				IR_CONST / IR_LEN		// One sensor value

typedef struct {
	long	read[IR_LEN];	// Sensor values (value tared & de-noised)
	int		min[IR_LEN];	// minimum values (raw value)
	int		max[IR_LEN];	// maximum values (raw value)
	int		thresh;			// Sensor activation threshold
	bool	outofbound;		// Is the robot is not on the line
	bool	intersect;		// Is intersected
	int		val;			// Combined value (abstracted, 0 to 1000)
} SensorArr;

void sensorInit(SensorArr *sensor);
void sensorThresh(SensorArr *sensor, int val);
void sensorRead(SensorArr *sensor);

#endif
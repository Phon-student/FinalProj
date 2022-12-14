#ifndef ROBOT_H
#define ROBOT_H

#include <Arduino.h>

#define MOTR_A	(byte[])	{ 9, 10, 11 }	// ENA IN1 IN2
#define MOTR_B	(byte[])	{ 5, 6, 7 }		// ENB IN3 IN4
#define BASE_SPEED			180
#define MAX_SPEED			255

void motorInit();
void motorSpeed(int a, int b);

#endif
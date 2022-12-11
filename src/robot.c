#include "../lib/robot.h"

void motorInit() {
	// Motor A
	pinMode(MOTR_A[0], OUTPUT); // Enable A
	pinMode(MOTR_A[1], OUTPUT); // Input 1
	pinMode(MOTR_A[2], OUTPUT); // Input 2
	// Motor B
	pinMode(MOTR_B[0], OUTPUT); // Enable B
	pinMode(MOTR_B[1], OUTPUT); // Input 3
	pinMode(MOTR_B[2], OUTPUT); // Input 4
}

void motorSpeed(int a, int b) {
	if (a != 0) {
		if (a > 0) {
			analogWrite(MOTR_A[0], a);
			digitalWrite(MOTR_A[1], HIGH);
			digitalWrite(MOTR_A[2], LOW);
		} else if (a < 0) {
			analogWrite(MOTR_A[0], -a);
			digitalWrite(MOTR_A[1], LOW);
			digitalWrite(MOTR_A[2], HIGH);
		}
	} else {
		analogWrite(MOTR_A[0], 0);
		digitalWrite(MOTR_A[1], LOW);
		digitalWrite(MOTR_A[2], LOW);
	}
	if (b != 0) {
		if (b > 0) {
			analogWrite(MOTR_B[0], b);
			digitalWrite(MOTR_B[1], HIGH);
			digitalWrite(MOTR_B[2], LOW);
		} else if (b < 0) {
			analogWrite(MOTR_B[0], -b);
			digitalWrite(MOTR_B[1], LOW);
			digitalWrite(MOTR_B[2], HIGH);
		}
	} else {
		analogWrite(MOTR_B[0], 0);
		digitalWrite(MOTR_B[1], LOW);
		digitalWrite(MOTR_B[2], LOW);
	}
}

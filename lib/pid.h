#ifndef PID_H
#define PID_H

#include <Arduino.h>

// PID controller data structure
typedef struct {
	// inputs, outputs, target
	float	*input;
	float	output;
	float	target;
	// constants
	float	kp, ki, kd;
	// data store
	float	Iterm, pErr;
}	PID;

void	PIDInit (PID *pid, float *input);
void	PIDSetConst (PID *pid, float kp, float ki, float kd);
void	PIDSetTarget (PID *pid, float val);
void	PIDUpdate (PID *pid);

#endif

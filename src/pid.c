#include "../lib/pid.h"

void	PIDInit (PID *pid, float *input) {
	PIDSetConst(pid, 0, 0, 0);
	PIDSetTarget(pid, 0);
	pid->input = input;
	pid->pErr = 0;
	pid->Iterm = 0;
}

void	PIDSetConst (PID *pid, float kp, float ki, float kd) {
	pid->kp = kp;
	pid->ki = ki;
	pid->kd = kd;
}

void	PIDSetTarget (PID *pid, float val) {
	pid->target = val;
}

void	PIDUpdate (PID *pid) {
	float	Pterm, Dterm, err;

	err = *pid->input - pid->target;
	// Calculates the proportional term, and drivertive term
	Pterm = err * pid->kp;
	Dterm = (err - pid->pErr) * pid->kd;
	// Sets the new previous error
	pid->pErr = err;
	// Calculates the integral term
	if (pid->Iterm > -1023 && pid->Iterm < 1023)
		pid->Iterm += err * pid->ki;

	// Calculates the output
	pid->output = Pterm + pid->Iterm + Dterm;
	if (pid->output > 1023)
		pid->output = 1023;
	else if (pid->output <= -1023)
		pid->output = -1023;
}
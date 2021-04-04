#ifndef _TEMP_CTRL_H_
#define _TEMP_CTRL_H_

#define PWM_CONTROL

#ifdef PWM_CONTROL
	#define MAX_OUTPUT 999
	#define MIN_OUTPUT 0
#else
	#define MAX_OUTPUT 100
	#define MIN_OUTPUT -100
#endif

void PID_Control(void);
void PID_Clear(void);

#endif

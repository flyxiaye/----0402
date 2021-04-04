#include "temp_ctrl.h"
#include "GlobalVar.h"
#include "gpio.h"
#include "max31865.h"

float d_value = 0;
float i_value = 0;
float dd_value = 0;

void get_error(){
  error_1 = expect_temp - real_temp;
	error_1 = 0.7 * error_1 + 0.3 * error_2;
}

void cal_duty() {
//	d_value = D * (error_1 - error_2);
//	i_value += I * error_1;
//	if (i_value > MAX_OUTPUT) duty = MAX_OUTPUT;
//	if (i_value < MIN_OUTPUT) duty = MIN_OUTPUT;
//	d_value = 0.7f * dd_value + 0.3f * d_value;
//	dd_value = d_value;
  d_duty = P * (error_1 - error_2) + I * error_1 + d_value + D * (error_1 - error_2 - error_2 + error_3);
	duty += d_duty;
//	duty = P * error_1 + i_value + d_value;
	error_3 = error_2;
	error_2 = error_1;
//	if(error_1 < 0)
//		duty = 0;
	if (duty > MAX_OUTPUT) duty = MAX_OUTPUT;
	if (duty < MIN_OUTPUT) duty = MIN_OUTPUT;
}

void output() {
#ifdef PWM_CONTROL
	TIM_SetCompare4(TIM3, (int)(duty+0.5f + 50));
#else
	static unsigned char count = 0;
	count ++;
	if (count > 9) count = 0;
	if (duty > 0){
		if (count < duty / MAX_OUTPUT * 10){
			RELAY1_ON;
		} else {
			RELAY1_OFF;
		}
	} else {
		RELAY1_OFF;
	}
#endif
}

void PID_Control() {
	get_error();
	cal_duty();
	output();
}

void PID_Clear() {
	error_1 = 0;
	error_2 = 0;
	error_3 = 0;
	duty = 0;
	d_duty = 0;
	TIM_SetCompare4(TIM3, 0);
}

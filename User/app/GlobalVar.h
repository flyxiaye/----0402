#ifndef _GLOBALVAR_H_
#define _GLOBALVAR_H_
#include "stdint.h"

//
// GUI FLAG
//
extern unsigned char gui_time2_flag;
extern unsigned char gui_time3_flag;
extern unsigned char gui_floor1_flag;

//
// Other FLAG
//
extern int32_t gui_time2_count;
extern int32_t gui_time3_count;
extern float expect_temp;
extern float real_temp;

extern unsigned char floor2_open_flag;
extern unsigned char floor3_open_flag;

//
// PID
//
extern float P;
extern float I;
extern float D;
extern float error_1;
extern float error_2;
extern float error_3;
extern float duty;
extern float d_duty;

#endif

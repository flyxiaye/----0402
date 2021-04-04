#include "GlobalVar.h"
#include "stdint.h"
#include "temp_ctrl.h"


//
// GUI FLAG
//
unsigned char gui_time2_flag = 0;
unsigned char gui_time3_flag = 0;
unsigned char gui_floor1_flag = 0;

//
// Other FLAG
//
int32_t gui_time2_count = 0;
int32_t gui_time3_count = 0;
float expect_temp = 37.0;
float real_temp = 0;

unsigned char floor2_open_flag = 0;
unsigned char floor3_open_flag = 0;

//
// PID
//
#ifdef PWM_CONTROL
float P =200;
float I = 0.03;
float D = 10;
#else
float P = 10;
float I = 0.1;
float D = 2;
#endif
float error_1 = 0;
float error_2 = 0;
float error_3 = 0;
float duty = 0;
float d_duty = 0;

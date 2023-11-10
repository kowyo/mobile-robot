/**
 * @file motor.h
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2022-08-05
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#ifndef _MOTOR_H
#define _MOTOR_H
#include "stm32f4xx_hal.h"
#include <math.h>
#define HALF_OF_H 92.5 //单位是mm
#define HALF_OF_W 103.8 //单位是mm
#define SERVOR_INIT_1 1550.0f
#define SERVOR_INIT_2 2300.0f
#define SERVOR_INIT_3 550.0f
#define SERVOR_INIT_4 2100.0f
#define SERVOR_INIT_5 1350.0f
#define SERVOR_INIT_6 500.0f
#define ARR 20000.0f
#define STEP_SIZE 50
void Servo_Angle(int object, float angle, int time); 
void Motor_Init(void);
float Motor_Reverse(int arr, TIM_HandleTypeDef *htim, int mode);
void Motor_Time(int motor_type, float t, float speed);
void Motor_Move_Time(int t, float x_speed, float y_speed, float z_speed);
void Motor_Move(float x_speed, float y_speed, float z_speed);
void Motor_Calibration(int location, int target, float speed, int count);
void Servo_Grab(void);
void Servo_Put_Down(void);
void Motor_Move_Distance(int move_distance,int speed);
#endif

/**
 * @file pid.h
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2022-08-05
 * 
 * @copyright Copyright (c) 2022
 * 
 */
#ifndef _PID_H
#define _PID_H
#define T 5.0f
int pidController1(float targetVelocity, float currentVelocity, float Kp, float Ti, float Td);
int pidController2(float targetVelocity, float currentVelocity, float Kp, float Ti, float Td);
int pidController3(float targetVelocity, float currentVelocity, float Kp, float Ti, float Td);
int pidController4(float targetVelocity, float currentVelocity, float Kp, float Ti, float Td);
#endif


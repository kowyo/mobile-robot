/**
 * @file pid.c
 * @author HuangZifeng
 * @brief PID Controller
 * @version 0.1
 * @date 2022-08-05
 * 
 * @copyright Copyright (c) 2022
 * 
 */
#include "pid.h"
#include <stdint.h>
int pidController1(float targetVelocity, float currentVelocity, float Kp, float Ti, float Td)
{
	float ek0;
	static float u1, ek1, ek2;
  	float q0 = Kp * (1 + T/Ti + Td/T);
  	float q1 = -Kp * (1 + 2 * Td/T);
  	float q2 = Kp * Td/T;
	ek0 = targetVelocity - currentVelocity;
	u1 = u1 + q0 * ek0 + q1 * ek1 + q2 * ek2;
	if (u1 > 19999)
 	{
		u1 = 19999;
	}
 	if (u1 < -19999)
	{
		u1 = -19999;
	}
	ek2 = ek1;
	ek1 = ek0;
 	return (int)u1;
}

int pidController2(float targetVelocity, float currentVelocity, float Kp, float Ti, float Td)
{
	float ek0;
	static float u1, ek1, ek2;
	float q0 = Kp * (1 + T/Ti + Td/T);
	float q1 = -Kp * (1 + 2 * Td/T);
	float q2 = Kp * Td/T;
	ek0 = targetVelocity - currentVelocity;
	u1 = u1 + q0 * ek0 + q1 * ek1 + q2 * ek2;
	if (u1 > 19999)
 	{
		u1 = 19999;
	}
	if (u1 < -19999)
	{
		u1 = -19999;
	}
	ek2 = ek1;
	ek1 = ek0;
 	return (int)u1;
}

int pidController3(float targetVelocity, float currentVelocity, float Kp, float Ti, float Td)
{
	float ek0;
	static float u1, ek1, ek2;
	float q0 = Kp * (1 + T/Ti + Td/T);
	float q1 = -Kp * (1 + 2 * Td/T);
	float q2 = Kp * Td/T;
	ek0 = targetVelocity - currentVelocity;
	u1 = u1 + q0 * ek0 + q1 * ek1 + q2 * ek2;
	if (u1 > 19999)
 	{
		u1 = 19999;
	}
	if (u1 < -19999)
	{
		u1 = -19999;
	}
	ek2 = ek1;
	ek1 = ek0;
	return (int)u1;
}

int pidController4(float targetVelocity, float currentVelocity, float Kp, float Ti, float Td)
{
	float ek0;
	static float u1, ek1, ek2;
	float q0 = Kp * (1 + T/Ti + Td/T);
	float q1 = -Kp * (1 + 2 * Td/T);
	float q2 = Kp * Td/T;
	ek0 = targetVelocity - currentVelocity;
	u1 = u1 + q0 * ek0 + q1 * ek1 + q2 * ek2;
	if (u1 > 19999)
 	{
		u1 = 19999;
	}
	if (u1 < -19999)
	{
		u1 = -19999;
	}
	ek2 = ek1;
	ek1 = ek0;
 	return (int)u1;
}

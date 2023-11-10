/**
 * @file motor.c
 * @author 黄梓峰
 * @brief 控制电机和舵机运动的各种函数
 * @version 0.1
 * @date 2022-08-05
 * 
 * @copyright Copyright (c) 2022
 * 
 */
#include "motor.h"
#include "tim.h"
#include "math.h"

static float angle1=((SERVOR_INIT_1/ARR)-0.025f)*1800;
static float angle2=((SERVOR_INIT_2/ARR)-0.025f)*1800;
static float angle3=((SERVOR_INIT_3/ARR)-0.025f)*1800;
static float angle4=((SERVOR_INIT_4/ARR)-0.025f)*1800;
static float angle5=((SERVOR_INIT_5/ARR)-0.025f)*1800;
static float angle6=((SERVOR_INIT_6/ARR)-0.025f)*1800;
extern float targetVelocity1, targetVelocity2, targetVelocity3, targetVelocity4;
extern int time;
/**
 * @brief 测电机转速，电机反转时可以测出负的速度
 * 
 * @param arr 
 * @param htim 
 * @param mode 正转时编码器读数溢出，则mode=0，反之mode=1
 * @return float 
 */
float Motor_Reverse(int arr, TIM_HandleTypeDef *htim, int mode)
{
	float temp, velocity;
	temp = (float)(__HAL_TIM_GET_COUNTER(htim))/(330*4*0.005);// TIM计数器获得电机脉冲，该电机在5ms采样的脉冲/18则为实际转速的rpm	
	if((int)temp<100)
	{
		if(mode == 0)
			velocity = -temp;
		else
			velocity = temp;
	}
	else
	{
		if(mode == 0)
			velocity = (float)(arr+1)/(330*4*0.005)-temp;
		else
			velocity = temp-(float)(arr+1)/(330*4*0.005) ;
	}
	return velocity;
}
/**
 * @brief 让电机以一定的速度转动一段时间
 * 
 * @param motor_type 电机编号
 * @param t 电机运转时间，单位为ms
 * @param speed 电机转速
 */
void Motor_Time(int motor_type, float t, float speed)
{
	if(time<t)
	{
		switch (motor_type)
		{
		case 1:
			targetVelocity1 = speed;
			break;
		case 2:
			targetVelocity2 = speed;
			break;
		case 3:
			targetVelocity3 = speed;
			break;
		case 4:
			targetVelocity4 = speed;
			break;
		default:
			break;
		}
	}
	else 
	{
		switch (motor_type)
		{
		case 1:
			targetVelocity1 = 0;
			break;
		case 2:
			targetVelocity2 = 0;
			break;
		case 3:
			targetVelocity3 = 0;
			break;
		case 4:
			targetVelocity4 = 0;
			break;
		default:
			break;
		}
	}
}
/**
 * @brief 让机器人以一定的速度运动一段时间
 * 
 * @param t 机器人运动时间
 * @param x_speed x轴速度
 * @param y_speed y轴速度
 * @param z_speed z轴速度，角速度
 */
void Motor_Move_Time(int t, float x_speed, float y_speed, float z_speed)
{
	time =0;
	while(time<t)//无法进入循环是因为Optimization的level不是level-0
	{
		//麦克纳姆轮运动算解
		
		targetVelocity1=x_speed+y_speed-z_speed*(HALF_OF_H+HALF_OF_W);
		targetVelocity2=x_speed-y_speed-z_speed*(HALF_OF_H+HALF_OF_W);
		targetVelocity3=x_speed+y_speed+z_speed*(HALF_OF_H+HALF_OF_W);
		targetVelocity4=x_speed-y_speed+z_speed*(HALF_OF_H+HALF_OF_W);
	}
	targetVelocity1=0;
	targetVelocity2=0;
	targetVelocity3=0;
	targetVelocity4=0;
	time =0;
	
}
/**
 * @brief 让机器人以一定的速度运动
 * 
 * @param x_speed x轴速度
 * @param y_speed y轴速度
 * @param z_speed z轴速度，角速度
 */
void Motor_Move(float x_speed, float y_speed, float z_speed)
{
		targetVelocity1=x_speed+y_speed-z_speed*(HALF_OF_H+HALF_OF_W);
		targetVelocity2=x_speed-y_speed-z_speed*(HALF_OF_H+HALF_OF_W);
		targetVelocity3=x_speed+y_speed+z_speed*(HALF_OF_H+HALF_OF_W);
		targetVelocity4=x_speed-y_speed+z_speed*(HALF_OF_H+HALF_OF_W);
}
/**
 * @brief 初始化电机和舵机
 * 
 */
void Motor_Init(void)
{
	/*电机A,左下，正转溢出*/
	__HAL_TIM_SetCompare(&htim10,TIM_CHANNEL_1,0);//设置占空比,此时正转
	HAL_TIM_PWM_Start(&htim10,TIM_CHANNEL_1);
	__HAL_TIM_SetCompare(&htim11,TIM_CHANNEL_1,0);
	HAL_TIM_PWM_Start(&htim11,TIM_CHANNEL_1);
	/*电机B，左上，正转溢出*/
	__HAL_TIM_SetCompare(&htim9,TIM_CHANNEL_1,0);
	HAL_TIM_PWM_Start(&htim9,TIM_CHANNEL_1);
	__HAL_TIM_SetCompare(&htim9,TIM_CHANNEL_2,0);//设置占空比，此时正转
	HAL_TIM_PWM_Start(&htim9,TIM_CHANNEL_2);
	/*电机C，右上*/
	__HAL_TIM_SetCompare(&htim1,TIM_CHANNEL_1,0);//设置占空比，此时正转
	HAL_TIM_PWM_Start(&htim1,TIM_CHANNEL_1);
	__HAL_TIM_SetCompare(&htim1,TIM_CHANNEL_2,0);
	HAL_TIM_PWM_Start(&htim1,TIM_CHANNEL_2);
	/*电机D，右下*/
	__HAL_TIM_SetCompare(&htim1,TIM_CHANNEL_3,0);
	HAL_TIM_PWM_Start(&htim1,TIM_CHANNEL_3);
	__HAL_TIM_SetCompare(&htim1,TIM_CHANNEL_4,0);//设置占空比，此时正转
	HAL_TIM_PWM_Start(&htim1,TIM_CHANNEL_4);
	
	
	__HAL_TIM_SetCompare(&htim8,TIM_CHANNEL_3,SERVOR_INIT_4);//C8(对应舵机4),
	HAL_TIM_PWM_Start(&htim8,TIM_CHANNEL_3);
	__HAL_TIM_SetCompare(&htim8,TIM_CHANNEL_4,SERVOR_INIT_3);//C9(对应舵机3),所有占空比不可以为0或者负数
	HAL_TIM_PWM_Start(&htim8,TIM_CHANNEL_4);
	
	__HAL_TIM_SetCompare(&htim8,TIM_CHANNEL_2,SERVOR_INIT_5);//C7(对应舵机5)
	HAL_TIM_PWM_Start(&htim8,TIM_CHANNEL_2);
	__HAL_TIM_SetCompare(&htim8,TIM_CHANNEL_1,SERVOR_INIT_6);//C6(对应舵机6)
	HAL_TIM_PWM_Start(&htim8,TIM_CHANNEL_1);
	__HAL_TIM_SetCompare(&htim12,TIM_CHANNEL_1,SERVOR_INIT_2);//B14(对应舵机2)
	HAL_TIM_PWM_Start(&htim12,TIM_CHANNEL_1);
	__HAL_TIM_SetCompare(&htim12,TIM_CHANNEL_2,SERVOR_INIT_1);//B15(对应舵机1)，最下面的舵机（从下往上依次为1，2，3，4，5，6）
	HAL_TIM_PWM_Start(&htim12,TIM_CHANNEL_2);
	
	HAL_Delay(500);
	__HAL_TIM_SetCompare(&htim8,TIM_CHANNEL_1,750);
	HAL_Delay(500);
	__HAL_TIM_SetCompare(&htim8,TIM_CHANNEL_1,500);
	
	
	HAL_TIM_Encoder_Start(&htim2, TIM_CHANNEL_ALL);
	HAL_TIM_Encoder_Start(&htim3, TIM_CHANNEL_ALL);
	HAL_TIM_Encoder_Start(&htim4, TIM_CHANNEL_ALL);
	HAL_TIM_Encoder_Start(&htim5, TIM_CHANNEL_ALL);
}
/**
 * @brief 控制舵机匀速的转动到一定角度
 * @reference http://t.csdn.cn/8ALSs
 * @param object 舵机对象，从下往上依次是1，2，3，4，5，6.
				舵机1，从上往下看，数值增大往顺时针方向转
				舵机4，数值增大往顺时针方向转
 * @param angle 舵机转动到指定的角度，范围是0-180°
 * @note: angle=((PWM/ARR)-0.025)*1800,PWM=(int)(angle/1800+0.025)*ARR
 */
void Servo_Angle(int object, float angle,int time)
{
	int temp1 = (int)((angle/1800.0f+0.025f)*ARR);
	int temp2;
	switch (object)
	{
	case 1:
		//__HAL_TIM_SetCompare(&htim12,TIM_CHANNEL_2,temp1);
		 temp2 = (int)((angle1/1800.0f+0.025f)*ARR);
		if(temp1>temp2)
		{
			int counter = (temp1-temp2)/STEP_SIZE;
			int bias = (temp1-temp2)%STEP_SIZE;
			int i;
			for(i=0;i<counter;i++)
			{
				temp2+=STEP_SIZE;
				__HAL_TIM_SetCompare(&htim12,TIM_CHANNEL_2,temp2);
				HAL_Delay(time);			
			}
			temp2+=bias;
			__HAL_TIM_SetCompare(&htim12,TIM_CHANNEL_2,temp2);
		}
		else
		{
			int counter = (temp2-temp1)/STEP_SIZE;
			int bias = (temp2-temp1)%STEP_SIZE;
			int i;
			for(i=0;i<counter;i++)
			{
				temp2-=STEP_SIZE;
				__HAL_TIM_SetCompare(&htim12,TIM_CHANNEL_2,temp2);
				HAL_Delay(time);
			}
			temp2-=bias;
			__HAL_TIM_SetCompare(&htim12,TIM_CHANNEL_2,temp2);
		}
		angle1=angle;
		break;
	case 2:
		temp2 = (int)((angle2/1800.0f+0.025f)*ARR);
		//__HAL_TIM_SetCompare(&htim12,TIM_CHANNEL_1,temp1);
		if(temp1>temp2)
		{
			int counter = (temp1-temp2)/STEP_SIZE;
			int bias = (temp1-temp2)%STEP_SIZE;
			int i;
			for(i=0;i<counter;i++)
			{
				temp2+=STEP_SIZE;
				__HAL_TIM_SetCompare(&htim12,TIM_CHANNEL_1,temp2);
				HAL_Delay(time);			
			}
			temp2+=bias;
			__HAL_TIM_SetCompare(&htim12,TIM_CHANNEL_1,temp2);
		}
		else
		{
			int counter = (temp2-temp1)/STEP_SIZE;
			int bias = (temp2-temp1)%STEP_SIZE;
			int i;
			for(i=0;i<counter;i++)
			{
				temp2-=STEP_SIZE;
				__HAL_TIM_SetCompare(&htim12,TIM_CHANNEL_1,temp2);
				HAL_Delay(time);
			}
			temp2-=bias;
			__HAL_TIM_SetCompare(&htim12,TIM_CHANNEL_1,temp2);
		}
		angle2=angle;
		break;
	case 3:
		temp2 = (int)((angle3/1800.0f+0.025f)*ARR);
		//__HAL_TIM_SetCompare(&htim8,TIM_CHANNEL_4,temp1);
		if(temp1>temp2)
		{
			int counter = (temp1-temp2)/STEP_SIZE;
			int bias = (temp1-temp2)%STEP_SIZE;
			int i;
			for(i=0;i<counter;i++)
			{
				temp2+=STEP_SIZE;
				__HAL_TIM_SetCompare(&htim8,TIM_CHANNEL_4,temp2);
				HAL_Delay(time);			
			}
			temp2+=bias;
			__HAL_TIM_SetCompare(&htim8,TIM_CHANNEL_4,temp2);
		}
		else
		{
			int counter = (temp2-temp1)/STEP_SIZE;
			int bias = (temp2-temp1)%STEP_SIZE;
			int i;
			for(i=0;i<counter;i++)
			{
				temp2-=STEP_SIZE;
				__HAL_TIM_SetCompare(&htim8,TIM_CHANNEL_4,temp2);
				HAL_Delay(time);
			}
			temp2-=bias;
			__HAL_TIM_SetCompare(&htim8,TIM_CHANNEL_4,temp2);
		}
		angle3=angle;
		break;	
	case 4:
		temp2 = (int)((angle4/1800.0f+0.025f)*ARR);
		 //__HAL_TIM_SetCompare(&htim8,TIM_CHANNEL_3,temp1);
		if(temp1>temp2)
		{
			int counter = (temp1-temp2)/STEP_SIZE;
			int bias = (temp1-temp2)%STEP_SIZE;
			int i;
			for(i=0;i<counter;i++)
			{
				temp2+=STEP_SIZE;
				__HAL_TIM_SetCompare(&htim8,TIM_CHANNEL_3,temp2);
				HAL_Delay(time);			
			}
			temp2+=bias;
			__HAL_TIM_SetCompare(&htim8,TIM_CHANNEL_3,temp2);
		}
		else
		{
			int counter = (temp2-temp1)/STEP_SIZE;
			int bias = (temp2-temp1)%STEP_SIZE;
			int i;
			for(i=0;i<counter;i++)
			{
				temp2-=STEP_SIZE;
				__HAL_TIM_SetCompare(&htim8,TIM_CHANNEL_3,temp2);
				HAL_Delay(time);
			}
			temp2-=bias;
			__HAL_TIM_SetCompare(&htim8,TIM_CHANNEL_3,temp2);
		}
		angle4=angle;
		break;
	case 5:
		temp2 = (int)((angle5/1800.0f+0.025f)*ARR);
		//__HAL_TIM_SetCompare(&htim8,TIM_CHANNEL_2,temp1);
		if(temp1>temp2)
		{
			int counter = (temp1-temp2)/STEP_SIZE;
			int bias = (temp1-temp2)%STEP_SIZE;
			int i;
			for(i=0;i<counter;i++)
			{
				temp2+=STEP_SIZE;
				__HAL_TIM_SetCompare(&htim8,TIM_CHANNEL_2,temp2);
				HAL_Delay(time);			
			}
			temp2+=bias;
			__HAL_TIM_SetCompare(&htim8,TIM_CHANNEL_2,temp2);
		}
		else
		{
			int counter = (temp2-temp1)/STEP_SIZE;
			int bias = (temp2-temp1)%STEP_SIZE;
			int i;
			for(i=0;i<counter;i++)
			{
				temp2-=STEP_SIZE;
				__HAL_TIM_SetCompare(&htim8,TIM_CHANNEL_2,temp2);
				HAL_Delay(time);
			}
			temp2-=bias;
			__HAL_TIM_SetCompare(&htim8,TIM_CHANNEL_2,temp2);
		}
		angle5=angle;
		break;
	case 6:
		temp2 = (int)((angle6/1800.0f+0.025f)*ARR);
		//__HAL_TIM_SetCompare(&htim8,TIM_CHANNEL_1,temp2);
		if(temp1>temp2)
		{
			int counter = (temp1-temp2)/STEP_SIZE;
			int bias = (temp1-temp2)%STEP_SIZE;
			int i;
			for(i=0;i<counter;i++)
			{
				temp2+=STEP_SIZE;
				__HAL_TIM_SetCompare(&htim8,TIM_CHANNEL_1,temp2);
				HAL_Delay(time);			
			}
			temp2+=bias;
			__HAL_TIM_SetCompare(&htim8,TIM_CHANNEL_1,temp2);
		}
		else
		{
			int counter = (temp2-temp1)/STEP_SIZE;
			int bias = (temp2-temp1)%STEP_SIZE;
			int i;
			for(i=0;i<counter;i++)
			{
				temp2-=STEP_SIZE;
				__HAL_TIM_SetCompare(&htim8,TIM_CHANNEL_1,temp2);
				HAL_Delay(time);
			}
			temp2-=bias;
			__HAL_TIM_SetCompare(&htim8,TIM_CHANNEL_1,temp2);
		}
		angle6=angle;
		break;
	default:
		break;
	}
}
/**
 * @brief 通过openmv传回来的坐标数据进行位置校准，以对准待抓取的物体
 * 
 * @param location 物体在图像中的实时位置
 * @param target 物体在图像中的目标位置
 * @param speed 机器人校准过程中的电机速度
 * @param count 校准次数
 * @shortage 使用了比较低级的控制算法，后期可改为pid
 */
void Motor_Calibration(int location, int target, float speed, int count)
{
	for(int i=0;i<count;i++)
	{
		if(location>target)
			while(location>target)
				Motor_Move(0,speed,0);
		else if(location<target)
			while(location<target)
				Motor_Move(0,-speed,0);
		Motor_Move(0,0,0);
	}
}
/**
 * @brief 控制舵机放下机械臂并抓取物体
 * 
 */
void Servo_Grab(void)
{
	Servo_Angle(4,15,50);
	Servo_Angle(2,35,50);
	HAL_Delay(1500);
	Servo_Angle(4,30,100);
	Servo_Angle(3,35,100);
	HAL_Delay(1500);
	Servo_Angle(6,20,100);
	Servo_Angle(5,10,100);
	HAL_Delay(1500);
}
/**
 * @brief 控制舵机将抓取的物体放下
 * 
 */
void Servo_Put_Down(void)
{
	Servo_Angle(2,160,100);
	Servo_Angle(4,135,100);
	HAL_Delay(1000);
	Servo_Angle(1,180,100);
	Servo_Angle(2,90,100);
	HAL_Delay(1000);
	Servo_Angle(6,0,100);
	HAL_Delay(1000);
	Servo_Angle(3,90,100);
	Servo_Angle(1,90,100);
	Servo_Angle(3,10,100);
	Motor_Init();
}
/**
 * @brief 控制机器人进行移动
 * 
 * @param move_distance 移动的距离单位
 * @param speed 移动速度
 */
void Motor_Move_Distance(int move_distance,int speed)
{
	const int STEP=1500;
	if(move_distance<0)
		speed = -speed;
	time = move_distance*STEP;
	Motor_Move_Time(time,0,speed,0);
}

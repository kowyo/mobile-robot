/**
 * @file openmv.c
 * @author 黄梓峰
 * @brief 实现与openmv之间进行通信的函数
 * @version 0.1
 * @date 2022-08-07
 *
 * @copyright Copyright (c) 2022
 *
 */

#include "openmv.h"
#include <stdio.h>
#include "main.h"
extern uint8_t cx,cy,cw,ch,state,sequency;
/**
 * @brief 接受并解析openmv发送过来的字节数组
 * 
 * @param com_data 接收到的数据，大小为1字节
 */
void OpenMV_Data_Receive(int16_t com_data)
{
    uint8_t i;
    static uint8_t RxCounter1 = 0; //计数
    static uint16_t RxBuffer1[10] = {0};
    static uint8_t RxState = 0;
    if (RxState == 0 && com_data == 0x2C) // 0x2c帧头
    {
        //HAL_GPIO_WritePin(LED_GPIO_Port,LED_Pin,GPIO_PIN_SET);
				RxState = 1;
        RxBuffer1[RxCounter1++] = com_data;  
    }

    else if (RxState == 1 && com_data == 0x12) // 0x12帧头
    {
        //HAL_GPIO_WritePin(LED_GPIO_Port,LED_Pin,GPIO_PIN_RESET);
        RxState = 2;
        RxBuffer1[RxCounter1++] = com_data;
    }
    else if (RxState == 2)//cx
    {
        //HAL_GPIO_WritePin(LED_GPIO_Port,LED_Pin,GPIO_PIN_SET);
				RxBuffer1[RxCounter1++] = com_data;
				RxState = 3;
        
    }
		else if(RxState == 3)//cy
		{
				//HAL_GPIO_WritePin(LED_GPIO_Port,LED_Pin,GPIO_PIN_RESET);
				RxBuffer1[RxCounter1++] = com_data;
				RxState = 4;
		}
		else if(RxState == 4)//cw
		{
				//HAL_GPIO_WritePin(LED_GPIO_Port,LED_Pin,GPIO_PIN_SET);	
				RxBuffer1[RxCounter1++] = com_data;
				RxState = 5;
		}
    else if (RxState == 5) //ch
    {
				//HAL_GPIO_WritePin(LED_GPIO_Port,LED_Pin,GPIO_PIN_RESET);  
				RxBuffer1[RxCounter1++] = com_data;
				RxState = 6;
		}
		else if (RxState == 6) //state
    {
				//HAL_GPIO_WritePin(LED_GPIO_Port,LED_Pin,GPIO_PIN_SET);  
				RxBuffer1[RxCounter1++] = com_data;
				RxState = 7;
    }
		else if (RxState == 7) //state
    {
				//HAL_GPIO_WritePin(LED_GPIO_Port,LED_Pin,GPIO_PIN_SET);  
				RxBuffer1[RxCounter1++] = com_data;
				RxState = 8;
    }
		else if(RxState == 8)
    {
      //HAL_GPIO_WritePin(LED_GPIO_Port,LED_Pin,GPIO_PIN_RESET);  
			if(com_data == 0x5B)//0x5B帧尾
				{
					RxState = 0;
					RxBuffer1[RxCounter1]=com_data;
					cx = RxBuffer1[RxCounter1-6];
					cy = RxBuffer1[RxCounter1-5];
					cw = RxBuffer1[RxCounter1-4];
					ch = RxBuffer1[RxCounter1-3];
					state = RxBuffer1[RxCounter1-2];
					sequency = RxBuffer1[RxCounter1-1];
				}
				else
				{
					RxState = 0;
					for(i=0;i<10;i++)
					{
						RxBuffer1[i]=0x00;
					}
				}
    }
}

McEbham_wheel8:
添加了README更新说明:-)
添加了cjson,
除了电机C之外实现了PID控制，反应时间略慢（四个电机都开了之后这样，后期可以调整）
PID控制函数现在可以单独传递参数
在CubeMX中开启了UART2（与openmv进行串口通信）

McEbham_wheel11:
将自己编写的函数放入头文件中
解决了用VSC编写keil时将注释变成中文乱码的问题（setting搜索encoding，auto,gbk都开一下）
添加了对麦克纳姆轮算解的支持
已经解决：小车移动一定距离后无法停止

McEbham_wheel12:
创建了openmv.h，用于存放和openmv相关的库
目标是完成openmv和stm32之间的通信（已完成)

McEbham_wheel14:
添加对OLED的支持（可显示字符串，数字）
添加对蜂鸣器的支持

McEbham_wheel15:
添加对舵机的支持
移植PWM_Motor时出现的问题，电机的频率一定要是50Hz,为了使Freq=50Hz,参考公式（笔记本），预分频要调成15，
但对于控制电机的定时器中断来说，50Hz(T=20ms)的响应速度太慢，所以开了TIM7作为新的定时器中断源，预分频为3（T=5ms)
增加了对按键控制OLED屏开关的支持

McEbham_wheel16:
机械臂抓取物品的动作能够流畅完成，通过摄像头对准物品（未实现）
修复了Motor_Time无法进入循环的bug

McEbham_wheel17:
加入了对舵机转速控制的支持（加入了HAL_Delay)
修复了无法通信的bug（rx和tx插反了）

McEbham_wheel18:
通过二维码获取抓取顺序
“1”为红色，“2”为绿色，“3”为蓝色
seq=1 红绿蓝（1，2，3）
seq=2 红蓝绿（1，3，2）
seq=3 蓝绿红（3，2，1）
seq=4 蓝红绿（3，1，2）
seq=5 绿红蓝（2，1，3）
seq=6 绿蓝红（2，3，1）


logistics_bot_1：
时隔一周，开始恢复更新啦
更新内容：
1、项目更名为logistics_bot，更贴近所要实现的任务
2、添加注释，优化代码，增强可读性

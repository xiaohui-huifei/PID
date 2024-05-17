#ifndef _pid_H_
#define _pid_H_

// 定义一个PID结构体，用于存储PID控制相关的参数
typedef struct Pid
{

     float Sv; // 用户设定值
     float Pv; // 当前测量值
 
     float Kp; // 比例系数
     int T;    // PID计算周期--采样周期
     float Ti; // 积分时间常数
     float Td; // 微分时间常数
    
     float Ek;   // 本次偏差
    float Ek_1; // 上次偏差
    float SEk;  // 历史偏差之和
    
    float Iout; // 积分输出
    float Pout; // 比例输出
    float Dout; // 微分输出
    
     float OUT0; // 初始输出值

     float OUT;  // 控制输出值

     int C1ms;   // 1ms计数器
    
     int pwmcycle; // pwm周期
 
     int times;    // 控制次数
} PID;

extern PID pid; // 声明一个全局的PID结构体变量

// PID控制相关函数声明
void PID_Init(void); // PID初始化函数
void PID_Calc(void); // PID计算函数

#endif


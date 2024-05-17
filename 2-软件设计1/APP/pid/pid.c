#include "pid.h" // 引入PID头文件

PID pid; // 定义一个全局的PID结构体变量

// PID初始化函数
void PID_Init()
{
     
    pid.Kp=30; // 比例系数
    pid.T=400; // PID计算周期
      pid.Ti=4000000; // 积分时间常数
    pid.Td=1000; // 微分时间常数
    pid.pwmcycle=200; // pwm周期200
    pid.OUT0=1; // 初始输出值
    pid.C1ms=0; // 1ms计数器初始化
}

// PID计算函数
void PID_Calc()  // pid计算
{
     float DelEk; // 偏差变化量
    float ti, ki; // 积分计算中间变量
    float td;
    float kd; // 微分计算中间变量
    float out; // 输出值
     if(pid.C1ms < (pid.T))  // 如果计算周期未到，直接返回
     {
        return ;
     }
 
     pid.Ek = pid.Sv - pid.Pv;   // 计算当前偏差值
     pid.Pout = pid.Kp * pid.Ek; // 计算比例输出
 
     pid.SEk += pid.Ek; // 累加历史偏差
 
     DelEk = pid.Ek - pid.Ek_1; // 计算最近两次偏差之差
 
     ti = pid.T / pid.Ti;
     ki = ti * pid.Kp;
      pid.Iout = ki * pid.SEk; // 计算积分输出

     td = pid.Td / pid.T;
     kd = pid.Kp * td;
      pid.Dout = kd * DelEk; // 计算微分输出
 
     out = pid.Pout + pid.Iout + pid.Dout; // 计算总输出
 
     // 根据输出值和pwm周期限制最终的控制输出
     if(out > pid.pwmcycle)
     {
          pid.OUT = pid.pwmcycle;
     }
     else if(out <= 0)
     {
        pid.OUT = pid.OUT0; 
     }
     else 
     {
          pid.OUT = out;
     }
     pid.Ek_1 = pid.Ek; // 更新偏差值，为下一次计算做准备
     pid.C1ms = 0; // 重置1ms计数器
}

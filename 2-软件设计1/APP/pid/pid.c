#include "pid.h" // ����PIDͷ�ļ�

PID pid; // ����һ��ȫ�ֵ�PID�ṹ�����

// PID��ʼ������
void PID_Init()
{
     
    pid.Kp=30; // ����ϵ��
    pid.T=400; // PID��������
      pid.Ti=4000000; // ����ʱ�䳣��
    pid.Td=1000; // ΢��ʱ�䳣��
    pid.pwmcycle=200; // pwm����200
    pid.OUT0=1; // ��ʼ���ֵ
    pid.C1ms=0; // 1ms��������ʼ��
}

// PID���㺯��
void PID_Calc()  // pid����
{
     float DelEk; // ƫ��仯��
    float ti, ki; // ���ּ����м����
    float td;
    float kd; // ΢�ּ����м����
    float out; // ���ֵ
     if(pid.C1ms < (pid.T))  // �����������δ����ֱ�ӷ���
     {
        return ;
     }
 
     pid.Ek = pid.Sv - pid.Pv;   // ���㵱ǰƫ��ֵ
     pid.Pout = pid.Kp * pid.Ek; // ����������
 
     pid.SEk += pid.Ek; // �ۼ���ʷƫ��
 
     DelEk = pid.Ek - pid.Ek_1; // �����������ƫ��֮��
 
     ti = pid.T / pid.Ti;
     ki = ti * pid.Kp;
      pid.Iout = ki * pid.SEk; // ����������

     td = pid.Td / pid.T;
     kd = pid.Kp * td;
      pid.Dout = kd * DelEk; // ����΢�����
 
     out = pid.Pout + pid.Iout + pid.Dout; // ���������
 
     // �������ֵ��pwm�����������յĿ������
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
     pid.Ek_1 = pid.Ek; // ����ƫ��ֵ��Ϊ��һ�μ�����׼��
     pid.C1ms = 0; // ����1ms������
}

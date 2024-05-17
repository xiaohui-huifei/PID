#ifndef _pid_H_
#define _pid_H_

// ����һ��PID�ṹ�壬���ڴ洢PID������صĲ���
typedef struct Pid
{

     float Sv; // �û��趨ֵ
     float Pv; // ��ǰ����ֵ
 
     float Kp; // ����ϵ��
     int T;    // PID��������--��������
     float Ti; // ����ʱ�䳣��
     float Td; // ΢��ʱ�䳣��
    
     float Ek;   // ����ƫ��
    float Ek_1; // �ϴ�ƫ��
    float SEk;  // ��ʷƫ��֮��
    
    float Iout; // �������
    float Pout; // �������
    float Dout; // ΢�����
    
     float OUT0; // ��ʼ���ֵ

     float OUT;  // �������ֵ

     int C1ms;   // 1ms������
    
     int pwmcycle; // pwm����
 
     int times;    // ���ƴ���
} PID;

extern PID pid; // ����һ��ȫ�ֵ�PID�ṹ�����

// PID������غ�������
void PID_Init(void); // PID��ʼ������
void PID_Calc(void); // PID���㺯��

#endif


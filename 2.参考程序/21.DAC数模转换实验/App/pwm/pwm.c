#include "pwm.h"

//ȫ�ֱ�������
unsigned char gtim_h = 0; // ���涨ʱ����ֵ��8λ
unsigned char gtim_l = 0; // ���涨ʱ����ֵ��8λ
unsigned char gduty = 0; // ����PWMռ�ձ�
unsigned char gtim_scale = 0; // ����PWM����=��ʱ����ֵ*tim_scale

// PWM��ʼ������
void pwm_init(unsigned char tim_h, unsigned char tim_l, unsigned int tim_scale, unsigned char duty)
{
	gtim_h = tim_h; // ������ĳ�ֵ������ȫ�ֱ����У������жϺ�����������
	gtim_l = tim_l;
	gduty = duty;
	gtim_scale = tim_scale;

	TMOD|=0X01;	// ѡ��Ϊ��ʱ��0ģʽ��������ʽ1
	TH0 = gtim_h; // ��ʱ��ֵ���� 
	TL0 = gtim_l;	

	ET0 = 1; // �򿪶�ʱ��0�ж�����
	EA = 1; // �����ж�
	TR0 = 1; // �򿪶�ʱ��
}

// ����ռ�ձ�
void pwm_set_duty_cycle(unsigned char duty)
{
	gduty = duty;	
}

void pwm(void) interrupt 1	//��ʱ��0�жϺ���
{
	static unsigned int time = 0;

	TH0 = gtim_h; // ��ʱ��ֵ���� 
	TL0 = gtim_l;
	
	time++;
	if(time >= gtim_scale) // PWM����=��ʱ����ֵ*gtim_scale�����¿�ʼ����
		time=0;
	if(time <= gduty) // ռ�ձ�	
		PWM = 1;
	else
		PWM = 0;		
}
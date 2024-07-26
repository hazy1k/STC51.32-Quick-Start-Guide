#include "reg52.h"

typedef unsigned int u16;	//��ϵͳĬ���������ͽ����ض���
typedef unsigned char u8;

//����LED1�ܽ�
sbit LED1=P2^0;

void delay_10us(u16 ten_us)
{
	while(ten_us--);	
}

void time1_init(void)
{
	TMOD |= 0X10; // ѡ��Ϊ��ʱ��0ģʽ��������ʽ1
	TH1 = 0XFC;	// ����ʱ������ֵ����ʱ1ms
	TL1=0X18;

	ET1 = 1; // �򿪶�ʱ��1�ж�����
	EA = 1; // �����ж�
	TR1 = 1; // �򿪶�ʱ��		
}

void main()
{	
	time1_init();//��ʱ��1�ж�����

	while(1)
	{			
							
	}		
}

void time1() interrupt 3 // ��ʱ��1�жϺ���
{
	static u16 i; // ���徲̬����i
	TH1 = 0XFC;	// ����ʱ������ֵ����ʱ1ms
	TL1 = 0X18;
	i++;
	
	if(i == 1000)
	{
		i = 0;
		LED1 =! LED1;	
	}						
}
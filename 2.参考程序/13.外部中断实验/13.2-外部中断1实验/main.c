#include "reg52.h"

typedef unsigned int u16;	//��ϵͳĬ���������ͽ����ض���
typedef unsigned char u8;

// ����LED1�ܽ�
sbit LED1 = P2^0;

//�����������K4���ƽ�
sbit KEY4 = P3^3;

void delay_10us(u16 ten_us)
{
	while(ten_us--);	
}

// �ⲿ�ж�1��ʼ������
void exti1_init(void)
{
	IT1 = 1; // �����ش�����ʽ���½��أ�
	EX1 = 1; // ��INT1���ж�����
	EA = 1; // �����ж�
}

void main()
{	
	exti1_init(); // �ⲿ�ж�1����

	while(1)
	{			
							
	}		
}

void exti1() interrupt 2 // �ⲿ�ж�1�жϺ���
{
	delay_10us(1000); // ����
	if(KEY4 == 0) // �ٴ��ж�K4���Ƿ���
		LED1 =! LED1;//LED1״̬��ת					
}
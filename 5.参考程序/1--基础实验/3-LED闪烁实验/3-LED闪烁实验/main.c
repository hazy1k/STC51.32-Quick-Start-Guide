#include <REGX52.H>

sbit LED1=P2^0;	//��P2.0�ܽŶ���ΪLED1


void delay_us(unsigned int set_us)
{
	while(set_us--);	
}

void main()
{	
	while(1)
	{
		LED1 = 0; // �͵�ƽ����
		delay_us(50000); //��Լ��ʱ450ms

		LED1=1;	//Ϩ��
		delay_us(50000); 	
	}		
}
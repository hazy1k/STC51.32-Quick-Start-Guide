#include <REGX52.H>

// ����LED1�ܽ�
sbit LED1 = P2^0;

// �����������K3���ƽ�
sbit KEY3=P3^2;

// ��ʱ����
void delay_10us(unsigned int ten_us)
{
	while(ten_us--);	
}

// �ⲿ�ж�0���ú���
void exti0_init()
{
	IT0 = 1; // �½��ش��� 
	EX0 = 1; // ʹ���ⲿ�ж�0
	EA = 1; // ʹ�����ж�
}

// �ⲿ�ж�0�жϺ���
// ��������ⲿ�ж�0����ִ�иú���
void exti0() interrupt 0
{
	delay_10us(1000); // ����

	if(KEY3 == 0) // �ж�K3���Ƿ���
		LED1 =! LED1; // LED1״̬��ת					
}

void main()
{	
	exti0_init(); // �ⲿ�ж�0����

	while(1)
	{			
							
	}		
}

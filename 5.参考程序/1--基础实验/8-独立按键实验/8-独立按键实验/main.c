#include <REGX52.H>

//����K1�������ƽ�
sbit KEY1 = P3^0;

//����LED1���ƽ�
sbit LED1 = P2^0;

// ��ʱ����
void delay_us(unsigned int ten_us)
{
	while(ten_us--);	
}

int main()
{
	while(1)
	{
		if(KEY1 == 0) // ���˿��Ƿ�Ϊ�͵�ƽ-���ذ���
		{
			delay_us(20); // ����
			LED1 = !LED1; // ģ��Ƶ�����
		}
	}
}
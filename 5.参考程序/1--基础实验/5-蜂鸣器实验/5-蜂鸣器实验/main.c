#include <REGX52.H>

sbit BEEP = P2^5;	//��P2.5�ܽŶ���ΪBEEP-��������

// ��ʱ����-�Ѿ�����Ϥ�ˣ����ؽ���
void delay_us(unsigned int ten_us)
{
	while(ten_us--);	
}


void main()
{
	unsigned int i;

	BEEP = 0; // ��ʼ��ʱ�رշ�����

	for(i = 0; i < 1000; i++)
	{
		BEEP = !BEEP; // �л�������״̬
		delay_us(500);
	}

	BEEP = 0; // ѭ�������رշ�����

	while(1); // ά�ֳ����������

}

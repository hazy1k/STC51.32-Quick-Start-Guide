#include <REGX52.H>

// ����74HC165���ƹܽ�
sbit HC165_QH = P1^7; // �����������
sbit HC165_CLK = P1^6; // ʱ������
sbit HC165_SHLD = P1^5; // �Ĵ����洢����

#define LED_PORT	P2	// LEDģ�����

// ��ʱ����
void delay_10us(unsigned int ten_us)
{
	while(ten_us--);	
}

// ��ȡ���ݺ���
// ��74HC165�ж�ȡһ���ֽ�����
unsigned char hc165_read_data(void)
{
	unsigned char i = 0;
	unsigned char value = 0;

	HC165_SHLD = 0; // SHLD���ͣ�165�������ݴ��뵽��λ�Ĵ�����
	delay_10us(5); // ������ʱ
	HC165_SHLD=1; // SHLD���ߣ���ֹ165�������ݴ��뵽��λ�Ĵ�����

	for(i = 0; i < 8; i++) // ѭ��8�ζ�ȡһ���ֽ�
	{
		value <<= 1; // ����1λ���ȶ�ȡ�������Ǹ�λ������8��ѭ���򽫵�һ�ζ�ȡ��λ�ŵ��ֽڸ�λ
		HC165_CLK = 0; // CLK INHΪ�͵�ƽ��ʼ��ȡ����
		delay_10us(5);

		value |= HC165_QH; // ��ȡ���ݣ��������ݷŵ�value�����λ
		HC165_CLK = 1;//�����ض�ȡ����
		delay_10us(5);				
	}	
	return value; // ���ض�ȡ��������
}

void main()
{	
	unsigned char value = 0;

	LED_PORT = 0xff; // ��֤LEDĬ����Ϩ���
	while(1)
	{		
		value = hc165_read_data();
		
		if(value != 0xff)
			LED_PORT = value;								
	}		
}
#include <REGX52.H>

// ����74HC595���ƹܽ�
sbit SC = P3^6;	// ��������ʱ��(SCK)
sbit RC = P3^5;	// �洢�Ĵ���ʱ��(RCK)
sbit SE = P3^4; // ������������(SER)

unsigned char ghc595_buf[8]={0x01,0x02,0x04,0x08,0x10,0x20,0x40,0x80};

// ��ʱ������ten_us=1ʱ����Լ��ʱ10us
void delay_10us(unsigned int ten_us)
{
	while(ten_us--);	
}

// ms��ʱ������ms=1ʱ����Լ��ʱ1ms
void delay_ms(unsigned int ms)
{
	unsigned int i,j;
	for(i=ms;i>0;i--)
		for(j=110;j>0;j--);
}

/*
��74HC595д��4���ֽڵ�����
dat1����Ӧ74HC595(A)�����1��-��8��
dat2����Ӧ74HC595(B)�����9��-��16��
dat3����Ӧ74HC595(C)�����1��-��8��
dat4����Ӧ74HC595(D)�����9��-��16��
*/
void hc595_write_data(unsigned char dat1, unsigned char dat2, unsigned char dat3, unsigned char dat4)
{
	unsigned char i = 0;
	
	// ��ϸ����dat4������ͬ��
	for(i = 0; i < 8; i++) // ѭ��8�μ��ɽ�һ���ֽ�д��Ĵ�����
	{
		SE = dat4 >> 7; // �����λ����������������
		dat4 <<= 1; // ����һ�������Ƶ����λ
		SC = 0; // ����������ʱ����0��׼�����������뵽74HC595�Ĵ���
		delay_10us(1);
		SC = 1; // ��ʱ������SC��Ϊ1�������ݴ�SE�������뵽74HC595�Ĵ���
		delay_10us(1); // ��λ�Ĵ���ʱ�������ؽ��˿���������Ĵ�����	
	}
	
	// ����ͬ�ϣ�ֻ�ǻ�������ĵط�
	for(i = 0; i < 8; i++)
	{
		SE = dat3 >> 7;
		dat3 <<= 1;
		SC = 0;
		delay_10us(1);
		SC = 1;
		delay_10us(1);	
	}

	for(i = 0; i < 8; i++)
	{
		SE = dat2 >> 7;
		dat2 <<= 1;
		SC = 0;
		delay_10us(1);
		SC = 1;
		delay_10us(1);	
	}

	for(i = 0; i < 8; i++)
	{
		SE = dat1 >> 7;
		dat1 <<= 1;
		SC = 0;
		delay_10us(1);
		SC = 1;
		delay_10us(1);	
	}

	// ��δ��뽫�洢�Ĵ�����ʱ������RC��Ϊ1��Ȼ��������Ϊ0��
	// ��������Ǵ洢74HC595�Ĵ�����֮ǰ������������ݣ�ʹ������������Ͽ��á�
	RC = 1;
	delay_10us(1);
	RC = 0; // �洢�Ĵ���ʱ�������ؽ�ǰ��д�뵽�Ĵ������������	
}

// ����һ���𽥹������
void main()
{	
	unsigned char i = 0; // ������

	// A��B�����У�C��D������
	// ���������һ�й�����ʾ�ģ���Ӧ��֪����ô����
	while(1)
	{		
		for(i = 0; i < 8; i++)
		{	
			hc595_write_data(ghc595_buf[i], 0, 0, 0); // ʹ74HC595(A)���
			delay_ms(100); // ��ʱ100ms	
		}
		for(i = 0; i < 8; i++)
		{	
			hc595_write_data(0,ghc595_buf[i],0,0); // ʹ74HC595(B)���
			delay_ms(100);
		}									
	}		
}
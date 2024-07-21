#include "ds1302.h"
#include "intrins.h"

//---DS1302д��Ͷ�ȡʱ����ĵ�ַ����
//---���ʱ�������� ���λ��дλ
unsigned char gREAD_RTC_ADDR[7] = {0x81, 0x83, 0x85, 0x87, 0x89, 0x8b, 0x8d}; 
unsigned char gWRITE_RTC_ADDR[7] = {0x80, 0x82, 0x84, 0x86, 0x88, 0x8a, 0x8c};

//---�洢˳�������ʱ��������,�洢��ʽ����BCD��
unsigned char gDS1302_TIME[7] = {0x47, 0x51, 0x13, 0x20, 0x04, 0x05, 0x21}; // ��ʼ��2021��5��20��������13��51��47��


// DS1302д���ֽ�
void ds1302_write_byte(unsigned char addr, unsigned char dat) // ��������ַ������
{
	unsigned char i = 0;
	
	DS1302_RST = 0; // RST����
	_nop_();	

	DS1302_CLK = 0; // CLK�͵�ƽ
	_nop_();

	DS1302_RST = 1; // RST�ɵ͵��߱仯-�����˸�λ�����Ӷ�����׼����ʼд������
	_nop_();

	for(i = 0; i < 8; i++) // ѭ��8�Σ�ÿ��д1λ����д��λ��д��λ
	{
		DS1302_IO = addr & 0x01; // ȡ��ַ�ĵ�λ
		addr >>= 1; 

		DS1302_CLK = 1; // CLK�ɵ͵��߲���һ�������أ��Ӷ�д������
		_nop_();
		DS1302_CLK = 0; // CLK�ɵ͵��߲���һ�������أ��Ӷ�д������
		_nop_();		
	}

	for(i = 0; i < 8; i++) // ѭ��8�Σ�ÿ��д1λ����д��λ��д��λ
	{
		DS1302_IO = dat & 0x01;
		dat >>= 1;

		DS1302_CLK = 1;
		_nop_();
		DS1302_CLK = 0;
		_nop_();		
	}

	DS1302_RST = 0; // RST����-��λ
	_nop_();	
}

// DS1302�����ֽ�
unsigned char ds1302_read_byte(unsigned char addr)
{
	unsigned char i = 0;
	unsigned char temp = 0;
	unsigned char value = 0;

	DS1302_RST=0;
	_nop_();	
	DS1302_CLK = 0; // CLK�͵�ƽ
	_nop_();
	DS1302_RST = 1; // RST�ɵ͵��߱仯
	_nop_();
	
	for(i = 0; i < 8; i++) // ѭ��8�Σ�ÿ��д1λ����д��λ��д��λ
	{
		DS1302_IO = addr & 0x01;
		addr >>= 1;

		DS1302_CLK = 1;
		_nop_();
		DS1302_CLK = 0;
		_nop_();		
	}

	for(i = 0; i < 8; i++) // ѭ��8�Σ�ÿ�ζ�1λ���ȶ���λ�ٶ���λ
	{
		temp = DS1302_IO; // ��ȡ���ݸ���ʱ����
		value = (temp<<7) | (value>>1); // �Ƚ�value����1λ��Ȼ��temp����7λ����������-�����������

		DS1302_CLK = 1;
		_nop_();
		DS1302_CLK = 0;
		_nop_();		
	}

	DS1302_RST = 0; // RST����
	_nop_();	
	DS1302_CLK=1; // ����ʵ���У�P3.4��û�������������ģ��˴�������Ҫ��ӣ�ʹ���ݿ���һ�����������塣
	_nop_();
	DS1302_IO = 0;
	_nop_();
	DS1302_IO = 1;
	_nop_();	
	return value;		
}

// DS1302��ʼ��ʱ��
void ds1302_init(void)
{
	unsigned char i = 0;
	ds1302_write_byte(0x8E, 0X00); // д���ʼʱ��
	for(i = 0; i < 7; i++)
	{
		ds1302_write_byte(gWRITE_RTC_ADDR[i], gDS1302_TIME[i]);	
	}
	ds1302_write_byte(0x8E, 0X80);	
}

// DS1302��ȡʱ��
void ds1302_read_time(void)
{
	unsigned char i = 0;
	for(i = 0; i < 7; i++)
	{
		gDS1302_TIME[i] = ds1302_read_byte(gREAD_RTC_ADDR[i]);	
	}	
}

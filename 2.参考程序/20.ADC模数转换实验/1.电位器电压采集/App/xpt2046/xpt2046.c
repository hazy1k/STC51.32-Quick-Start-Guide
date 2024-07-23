#include "xpt2046.h"
#include "intrins.h"

// xpt2046д������
void xpt2046_wirte_data(unsigned char dat)
{
	unsigned char i;

	CLK = 0; // ������ʱ��
	_nop_(); // ��ʱ100ns

	for(i = 0; i < 8; i++) // ѭ��8�Σ�ÿ�δ���һλ����һ���ֽ�
	{
		DIN = dat >> 7; // �ȴ���λ�ٴ���λ
		dat <<= 1; // ����λ�Ƶ���λ

		CLK = 0; // CLK�ɵ͵��߲���һ�������أ��Ӷ�д������
		_nop_();

		CLK = 1;
		_nop_();
	}
}

// XPT2046������
unsigned int xpt2046_read_data(void)
{
	unsigned char i;
	unsigned int dat = 0;

	CLK = 0; // ������ʱ��
	_nop_();

	for(i = 0; i < 12; i++) // ѭ��12�Σ�ÿ�ζ�ȡһλ������һ���ֽ��������Է���ֵ������u16
	{
		dat <<= 1; // ����λ�Ƶ���λ

		CLK = 1;
		_nop_();
		CLK = 0; // CLK�ɸߵ��Ͳ���һ���½��أ��Ӷ���ȡ����
		_nop_();

		dat |= DOUT; // ��DOUT��ȡ����
	}
	return dat;	
}

// XPT2046��AD����
unsigned int xpt2046_read_adc_value(unsigned char cmd)
{
	unsigned char i;
	unsigned int adc_value = 0;

	CLK = 0; // ������ʱ��
	CS  = 0; // ʹ��XPT2046
	xpt2046_wirte_data(cmd); // ����������
	for(i = 6; i > 0; i--); // ��ʱ�ȴ�ת�����

	CLK = 1;
	_nop_();
	CLK = 0; // ����һ��ʱ�ӣ����BUSY
	_nop_();

	adc_value = xpt2046_read_data(); // ��ȡADC����

	CS = 1; // �ر�XPT2046
	
	return adc_value;
}

#include "public.h"
#include "smg.h"
#include "xpt2046.h"

void main()
{	
	unsigned int adc_value = 0; // ��ʼ��ADCֵ
	float adc_vol; // ADC��ѹֵ
	unsigned char adc_buf[3]; // 3λ�������ʾ

	while(1)
	{				
		adc_value = xpt2046_read_adc_value(0x94); // ������λ��

		adc_vol = 5.0*adc_value/4096; // ����ȡ��ADֵת��Ϊ��ѹ
		adc_value = adc_vol*10; // �Ŵ�10����������С�����һλ
		
		adc_buf[0] = gsmg_code[adc_value/10]|0x80;
		adc_buf[1] = gsmg_code[adc_value%10];
	   	adc_buf[2] = 0x3e; // ��ʾ��λV
		smg_display(adc_buf, 6);		
	}		
}

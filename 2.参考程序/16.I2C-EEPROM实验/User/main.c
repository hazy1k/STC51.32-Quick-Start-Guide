#include "public.h"
#include "24c02.h"
#include "key.h"
#include "smg.h"

#define EEPROM_ADDRESS	0 // �������ݴ���EEPROM����ʼ��ַΪ0

void main()
{	
	unsigned char key_temp = 0; // ���尴����ʱ����
   	unsigned char save_value=0; // ���屣��ֵ����
	unsigned char save_buf[3]; // ����ʱ�������ʾ����

	while(1)
	{			
		key_temp = key_scan(0); // key��ֵ��������д�İ���ɨ�躯������ֵ

		if(key_temp == KEY1_PRESS)
		{
			at24c02_write_one_byte(EEPROM_ADDRESS, save_value); // ����1����ʱд�����ݵ�at24c02
		}
		else if(key_temp == KEY2_PRESS) // ����2����ʱ��ȡ����
		{
			save_value = at24c02_read_one_byte(EEPROM_ADDRESS);
		}
		else if(key_temp == KEY3_PRESS) // ����3����ʱ��������
		{
			save_value++; // ÿ��һ����������1
			if(save_value == 255) // ��ֹ�������
				save_value = 255;
		}
		else if(key_temp == KEY4_PRESS) // ����4�������
		{
			save_value=0;	
		}

		// �������ʾ
		save_buf[0] = save_value/100;
		save_buf[1] = save_value%100/10;
		save_buf[2] = save_value%100%10;
		smg_display(save_buf,6);
	}		
}

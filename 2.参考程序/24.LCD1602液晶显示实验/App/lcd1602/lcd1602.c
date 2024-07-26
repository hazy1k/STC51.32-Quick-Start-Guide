#include "lcd1602.h"

// 8λ����1602д�뺯��
#if (LCD1602_4OR8_DATA_INTERFACE == 0)

// д�������
void lcd1602_write_cmd(unsigned char cmd)
{
	LCD1602_RS = 0; // ѡ������
	LCD1602_RW = 0; // ѡ��д
	LCD1602_E = 0;

	LCD1602_DATAPORT = cmd; // ׼������
	delay_ms(1);

	LCD1602_E = 1; // ʹ�ܽ�E��������д��
	delay_ms(1);

	LCD1602_E = 0; // ʹ�ܽ�E���������д��	
}
#else	// 4λLCD
void lcd1602_write_cmd(unsigned char cmd)
{
	LCD1602_RS = 0;//ѡ������
	LCD1602_RW = 0;//ѡ��д
	LCD1602_E = 0;
	LCD1602_DATAPORT = cmd;//׼������
	delay_ms(1);

	LCD1602_E = 1;//ʹ�ܽ�E��������д��
	delay_ms(1);

	LCD1602_E = 0;//ʹ�ܽ�E���������д��
	
	LCD1602_DATAPORT=cmd<<4; // ׼������
	delay_ms(1);

	LCD1602_E = 1; // ʹ�ܽ�E��������д��
	delay_ms(1);

	LCD1602_E = 0;//ʹ�ܽ�E���������д��	
}
#endif

// д�����ݺ���
#if (LCD1602_4OR8_DATA_INTERFACE == 0) // 8λLCD
void lcd1602_write_data(unsigned char dat) 
{
	LCD1602_RS = 1; // ѡ������
	LCD1602_RW = 0; // ѡ��д
	LCD1602_E = 0;

	LCD1602_DATAPORT = dat; // ׼������
	delay_ms(1);

	LCD1602_E = 1; // ʹ�ܽ�E��������д��
	delay_ms(1);

	LCD1602_E = 0; // ʹ�ܽ�E���������д��		
}
#else
void lcd1602_write_data(unsigned char dat) // 4λ
{
	LCD1602_RS = 1; // ѡ������
	LCD1602_RW = 0; // ѡ��д
	LCD1602_E = 0;

	LCD1602_DATAPORT = dat;//׼������
	delay_ms(1);

	LCD1602_E = 1; // ʹ�ܽ�E��������д��
	delay_ms(1);

	LCD1602_E = 0; // ʹ�ܽ�E���������д��
	
	LCD1602_DATAPORT=dat<<4; // ׼������
	delay_ms(1);

	LCD1602_E = 1; // ʹ�ܽ�E��������д��
	delay_ms(1);

	LCD1602_E = 0; // ʹ�ܽ�E���������д��		
}
#endif

// 1602��ʼ������
#if (LCD1602_4OR8_DATA_INTERFACE == 0) // 8λLCD
void lcd1602_init(void)
{
	lcd1602_write_cmd(0x38); // ��������8λ����ʾ2�У�5*7����/�ַ�
	lcd1602_write_cmd(0x0c); // ��ʾ���ܿ����޹�꣬�����˸
	lcd1602_write_cmd(0x06); // д�������ݺ������ƣ���ʾ�����ƶ�
	lcd1602_write_cmd(0x01); // ����	
}
#else
void lcd1602_init(void) // 4λ
{
	lcd1602_write_cmd(0x28); // ��������4λ����ʾ2�У�5*7����/�ַ�
	lcd1602_write_cmd(0x0c); // ��ʾ���ܿ����޹�꣬�����˸
	lcd1602_write_cmd(0x06); // д�������ݺ������ƣ���ʾ�����ƶ�
	lcd1602_write_cmd(0x01); // ����	
}
#endif

// 1602��������
void lcd1602_clear(void)
{
	lcd1602_write_cmd(0x01);	
}

// 1602��ʾ�ַ���������xy�������꣬str�����ַ�����
void lcd1602_show_string(unsigned char x,unsigned char y,unsigned char *str)
{
	unsigned char i=0;

	if(y>1 || x>15)
		return; // ���в���������ǿ���˳�

	if(y < 1) // ��1����ʾ
	{	
		while(*str != '\0')//�ַ�������'\0'��β��ֻҪǰ�������ݾ���ʾ
		{
			if(i <16 - x)//����ַ����ȳ�����һ����ʾ��Χ�����ڵڶ��м�����ʾ
			{
				lcd1602_write_cmd(0x80+i+x); // ��һ����ʾ��ַ����	
			}
			else
			{
				lcd1602_write_cmd(0x40+0x80+i+x-16); // �ڶ�����ʾ��ַ����	
			}
			lcd1602_write_data(*str); // ��ʾ����

			str++; // ָ�����
			i++;	
		}	
	}
	else // ��2����ʾ
	{
		while(*str != '\0')
		{
			if(i < 16 - x) //����ַ����ȳ����ڶ�����ʾ��Χ�����ڵ�һ�м�����ʾ
			{
				lcd1602_write_cmd(0x80+0x40+i+x);	
			}
			else
			{
				lcd1602_write_cmd(0x80+i+x-16);	
			}
			lcd1602_write_data(*str);

			str++;
			i++;	
		}	
	}				
}

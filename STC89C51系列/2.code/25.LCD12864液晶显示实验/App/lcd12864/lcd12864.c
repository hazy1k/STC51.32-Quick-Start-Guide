#include "lcd12864.h"

// д�������
void lcd12864_write_cmd(unsigned char cmd)
{
	// 1. ѡ������
	LCD12864_RS = 0;

	// 2. ѡ��д����
	LCD12864_WR = 0;

	// 3. ʹ���ź�
	LCD12864_E = 0;

	// 4. ׼��д������
	LCD12864_DATAPORT = cmd;
	delay_ms(1);

	LCD12864_E = 1; // ʹ�ܽ�E��������д��
	delay_ms(1);

	LCD12864_E = 0; // ʹ�ܽ�E���������д��
}

// д�����ݺ���
void lcd12864_write_data(unsigned char dat)
{
	// 1. ѡ������
	LCD12864_RS = 1;

    // 2. ѡ��д����
	LCD12864_WR = 0;

	// 3. ʹ���ź�
	LCD12864_E = 0;

	// 4. ׼��д������
	LCD12864_DATAPORT = dat; // ׼������
	delay_ms(1);

	LCD12864_E = 1; // ʹ�ܽ�E��������д��
	delay_ms(1);
	LCD12864_E = 0; // ʹ�ܽ�E���������д��
}

// ��ʼ������
void lcd12864_init(void)
{
	// 1. ѡ��8λģʽ
	LCD12864_PSB = 1;

	// ����д�������Ǹ���оƬ���ģ���֪���������ϲ�һ��
	lcd12864_write_cmd(0x30); // ��������8λ������ָ�����
	lcd12864_write_cmd(0x0c); // ������ʾ�أ��α���ʾ�أ��α�������ʾ
	lcd12864_write_cmd(0x06); // д�������ݺ������ƣ���ʾ�����ƶ�
	lcd12864_write_cmd(0x01); // ����	
}

// ��������
void lcd12864_clear(void)
{
	lcd12864_write_cmd(0x01);	
} 

// ��ʾ�ַ�������
// x,y: ��ʾλ������ str������Ҫ��ʾ���ַ���
void lcd12864_show_string(unsigned char x,unsigned char y,unsigned char *str)
{
	if(y <= 0) // ����y����С��0
		y = 0;
	if( y > 3) // ����y���ܴ���3
		y = 3;

	x &= 0x0f; // ����x,y���ܴ�����ʾ��Χ

	switch(y)
	{
		case 0: 
			x |= 0x80; // ��1�е�ַ+x��ƫ��
			break; 
		case 1: 
			x |= 0x90; // ��2�е�ַ+x��ƫ��
			break;
		case 2: 
			x |= 0x88; // ��3�е�ַ+x��ƫ��
			break;
		case 3: 
			x |= 0x98; // ��4�е�ַ+x��ƫ��
			break;
	}
	lcd12864_write_cmd(x); // д����ʾλ������
	while(*str != '\0') // ���ַ�����Ϊ��ʱ
	{
		lcd12864_write_data(*str); // д����ʾ�ַ�
		str++;		
	}		
} 
#include "public.h"
#include "lcd1602.h"

void main()
{	
	lcd1602_init(); // LCD1602��ʼ��

	lcd1602_show_string(0, 0, "Hello hazy1k"); // ��һ����ʾ�ַ�
	lcd1602_show_string(0, 1, "0123456789"); // �ڶ�����ʾ����

	while(1)
	{
		
	}	
}

#include "public.h"
#include "lcd12864.h"

void main()
{	
	lcd12864_init(); // LCD12864��ʼ��

	lcd12864_show_string(0,0,"Hello World!"); // ��1���ַ�����ʾ
	lcd12864_show_string(0,1,"��Һã�"); // ��2���ַ�����ʾ
	lcd12864_show_string(0,2,"��ӭʹ��51������"); // ��3���ַ�����ʾ
	lcd12864_show_string(0,3,"�ú�ѧϰ��������"); // ��4���ַ�����ʾ
	while(1)
	{
		
	}	
}

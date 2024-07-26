#include "public.h"  
#include "uart.h"
#include "tftlcd.h"
#include "gui.h"
#include "picture.h"



void main()
{
	UART_Init(); // ���ڳ�ʼ��������ʹ��printf����
	TFTLCD_Init(); // TFTLCD��ʼ��
		
	FRONT_COLOR = WHITE;
	LCD_ShowString(10,80,tftlcd_data.width,tftlcd_data.height,16,"0123456789");
	//LCD_ShowFontHZ(10,100,"�úú�");
	LCD_ShowPicture(10,60,56,56,gImage_picture_snow);
	
	while(1)
	{
		
	}					
}

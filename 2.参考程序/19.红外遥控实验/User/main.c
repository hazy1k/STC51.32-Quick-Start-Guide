#include "public.h"
#include "smg.h"
#include "ired.h"

void main()
{	
	unsigned char ired_buf[3];

	ired_init();//�����ʼ��

	while(1)
	{				
		ired_buf[0]=gsmg_code[gired_data[2]/16]; // ���������4λת��Ϊ����ܶ���
		ired_buf[1]=gsmg_code[gired_data[2]%16]; // ���������4λת��Ϊ����ܶ���
		ired_buf[2]=0X76; // ��ʾH�Ķ���
		smg_display(ired_buf, 6);	
	}		
}

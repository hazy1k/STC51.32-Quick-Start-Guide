#include "24c02.h"
#include "iic.h"

// AT24C02��д�����ݵĺ���
void at24c02_write_one_byte(unsigned char addr, unsigned char dat)
{				   	  	    																 
    iic_start(); // iic��ʼ�ź� 
	iic_write_byte(0XA0); // ����д����

	iic_wait_ack(); // iic�ȴ�Ӧ��				   
    iic_write_byte(addr); // ����д��ַ

	iic_wait_ack(); 	 										  		   
	iic_write_byte(dat); // �����ֽ�

	iic_wait_ack();  		    	   
    iic_stop(); // ����һ��ֹͣ����
	delay_ms(10);	 
}

// AT24C02�Ķ�ȡ���ݵĺ���
unsigned char at24c02_read_one_byte(unsigned char addr)
{				  
	unsigned char temp = 0; // ����һ����ʱ�����洢��ȡ������		  

    iic_start(); // iic��ʼ�ź�  
	iic_write_byte(0XA0); // ����д����

	iic_wait_ack(); // iic�ȴ�Ӧ��				   
    iic_write_byte(addr); // ����д��ַ

	iic_wait_ack();	    
	iic_start();  	 	   
	iic_write_byte(0XA1); // �������ģʽ 

	iic_wait_ack();	 
    temp = iic_read_byte(0); // ��ȡ�ֽ�

    iic_stop();	// ����һ��ֹͣ����
	    
	return temp; // ���ض�ȡ������
}

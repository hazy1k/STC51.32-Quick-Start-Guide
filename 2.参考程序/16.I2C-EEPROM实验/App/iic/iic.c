#include "iic.h"

// iic��ʼ�ź�
void iic_start(void)
{
	IIC_SDA = 1; // ����Ѹ���������SCL���棬�ڶ��ζ�д���������
	delay_10us(1);

	IIC_SCL = 1;
	delay_10us(1);

	IIC_SDA = 0; // ��SCLΪ�ߵ�ƽʱ��SDA�ɸ߱�Ϊ��
	delay_10us(1);

	IIC_SCL = 0; // ǯסI2C���ߣ�׼�����ͻ��������
	delay_10us(1);
}

// iicֹͣ�ź�
void iic_stop(void)
{	
	IIC_SDA = 0; // ����Ѹ���������SCL���棬�ڶ��ζ�д���������
	delay_10us(1);

	IIC_SCL = 1;
	delay_10us(1);

	IIC_SDA = 1; // ��SCLΪ�ߵ�ƽʱ��SDA�ɵͱ�Ϊ��
	delay_10us(1);			
}

// iic����ACKӦ��
void iic_ack(void)
{
	IIC_SCL = 0;
	IIC_SDA = 0; // SDAΪ�͵�ƽ
	delay_10us(1);	

   	IIC_SCL = 1;
	delay_10us(1);
	IIC_SCL = 0;
}

// ����NACK��Ӧ��  
void iic_nack(void)
{
	IIC_SCL = 0;
	IIC_SDA = 1; // SDAΪ�ߵ�ƽ
	delay_10us(1);

   	IIC_SCL = 1;
	delay_10us(1);
	IIC_SCL = 0;	
}

// iic�ȴ�Ӧ��
unsigned char iic_wait_ack(void)
{
	unsigned char time_temp = 0;
	
	IIC_SCL = 1; // ����SCL��׼������Ӧ��
	delay_10us(1);
	while(IIC_SDA) // �ȴ�SDAΪ�͵�ƽ
	{
		time_temp++;
		if(time_temp > 100) // ��ʱ��ǿ�ƽ���IICͨ��
		{	
			iic_stop();
			return 1; // ��ʱ����1-�쳣	
		}			
	}
	IIC_SCL = 0; // ����SCL��׼������Ӧ��
	return 0; // ��������0
}

// iic����һ���ֽ�
void iic_write_byte(unsigned char dat)
{                        
    unsigned char i = 0; 
	   	    
    IIC_SCL = 0;  // ��ʱ�������ͣ�׼����������

    for(i = 0; i < 8; i++) // ѭ��8�ν�һ���ֽڴ������ȴ���λ�ٴ���λ
    {              
        if((dat & 0x80) > 0) // ���dat�����λ�Ƿ�Ϊ1
            IIC_SDA = 1;     // ������λΪ1�������������ߣ������߼�1��
        else
            IIC_SDA = 0;     // ������λΪ0�������������ͣ������߼�0��
        
        dat <<= 1;  // ������dat�����ƶ�һλ��׼��������һ��λ
        delay_10us(1);  // ������ʱ����֤ʱ������Ҫ��

        IIC_SCL = 1;  // ��ʱ�������ߣ�֪ͨ���շ����Զ�ȡ����
        delay_10us(1);  // ������ʱ����֤ʱ������Ҫ��

        IIC_SCL = 0;  // ��ʱ�����ٴ����ͣ�Ϊ������һλ������׼��
        delay_10us(1);  // ������ʱ����֤ʱ������Ҫ��
    }	 
}


// IIC��һ���ֽ� ack=1ʱ������ACK��ack=0������nACK 
unsigned char iic_read_byte(unsigned char ack)
{
	unsigned char i = 0, receive = 0;
   	
    for(i =0; i < 8; i++ ) // ѭ��8�ν�һ���ֽڶ������ȶ����ٴ���λ
	{
        IIC_SCL = 0; 
        delay_10us(1);

		IIC_SCL = 1;
        receive <<= 1;

        if(IIC_SDA)
			receive++;   
		delay_10us(1); 
    }					 
    if (!ack)
        iic_nack(); // ����nACK
    else
        iic_ack(); // ����ACK
		  
    return receive; // ���ض������ֽ�
}

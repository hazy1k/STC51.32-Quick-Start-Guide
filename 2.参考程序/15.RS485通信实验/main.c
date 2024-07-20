#include <REGX52.H>

//�����������IO
sbit RS485_DIR = P1^0; // ���ͺͽ��տ���

void delay_10us(unsigned int ten_us)
{
	while(ten_us--);	
}

// ����ͨ���ж����ú�����ͨ������TH��TL����ȷ����ʱʱ��
void uart_init(unsigned char baud)
{
	TMOD |= 0X20; // ���ü�����������ʽ2
	SCON = 0X50; // ����Ϊ������ʽ1
	PCON = 0X80; // �����ʼӱ�
	TH1 = baud;	// ��������ʼֵ����
	TL1 = baud;

	// ���ô���ͨ���ж�
	ES = 1;	// �򿪽����ж�
	EA = 1;	// �����ж�
	TR1 = 1; // �򿪼�����		
}

void uart() interrupt 4 // ����ͨ���жϺ���
{
	unsigned char rec_data; // ���յ�������

	RI = 0;			// ��������жϱ�־λ
	rec_data = SBUF; // �洢���յ�������
	delay_10us(100); // ��ʱ10us
	RS485_DIR = 1; // ����RS485Ϊ����ģʽ
	SBUF = rec_data; // �����յ������ݷ��뵽���ͼĴ���

	while(!TI);	 // �ȴ������������
	TI = 0;	// ���������ɱ�־λ

	RS485_DIR = 0; // ����RS485Ϊ����ģʽ				
}

void main()
{	
	uart_init(0XFA); // ������Ϊ9600

	RS485_DIR = 0; // ����RS485Ϊ����ģʽ

	while(1)
	{			
							
	}		
}

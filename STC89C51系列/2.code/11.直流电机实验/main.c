#include <REGX52.H>

//����ֱ��������ƹܽ�
sbit DC_Motor = P1^0; // ����DC_MotorΪP1.0��

//ms��ʱ������ms=1ʱ����Լ��ʱ1ms
void delay_ms(unsigned int ms)
{
	int i,j;
	for(i=ms;i>0;i--)
		for(j=110;j>0;j--);
}

int main()
{	
	DC_Motor = 1; // �o�ߵ�ƽ-�������
	delay_ms(5000); // �趨����ʱ��
	DC_Motor = 0;// ���͵�ƽ-�رյ��
	while(1)
	{			
								
	}		
}

#include <REGX52.H>

//����̵������ƹܽ�
sbit Relay = P1^4;

#define RELAY_OEPN_TIME	5000 // ����̵�������ʱ��Ϊ5000ms

// ��ʱ����
void delay_ms(unsigned int ms)
{
	unsigned int i,j;
	for(i=ms;i>0;i--)
		for(j=110;j>0;j--);
}

void main()
{	
	// �̵������ع���
	// 1.�������ϼ̵���
	// 2.��ʱ
	// 3.Ȼ��Ͽ��̵���
	
	Relay = 0; // �̵�������
	delay_ms(RELAY_OEPN_TIME); // ��ʱ
	Relay = 1; // �̵����Ͽ�

	while(1)
	{			
								
	}		
}
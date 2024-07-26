#include "reg52.h"

//����TC1508S���Ʋ�������ܽ�
sbit IN_A = P1^0;
sbit IN_B = P1^1;
sbit IN_C = P1^2;
sbit IN_D = P1^3;

// ��������������ƽ�
sbit KEY1 = P3^1;
sbit KEY2 = P3^0;
sbit KEY3 = P3^2;
sbit KEY4 = P3^3;

//ʹ�ú궨������������µļ�ֵ
#define KEY1_PRESS	1
#define KEY2_PRESS	2
#define KEY3_PRESS	3
#define KEY4_PRESS	4
#define KEY_UNPRESS	0

// ���岽������ٶȣ�ֵԽС���ٶ�Խ��
// ��С����С��1
#define STEPMOTOR_MAXSPEED	1  
#define STEPMOTOR_MINSPEED  5  	


void delay_10us(unsigned int ten_us)
{
	while(ten_us--);	
}

void delay_ms(unsigned int ms)
{
	unsigned int i,j;
	for(i=ms;i>0;i--)
		for(j=110;j>0;j--);
}

// ���ͽ����ź�
void step_motor_send_pulse(unsigned char step, unsigned char dir)
{
	unsigned char temp = step;
	
	if(dir == 0) // ���Ϊ��ʱ����ת
		temp = 7 - step; // ���������ź�

	switch(temp)//8�����Ŀ��ƣ�(A+)->(A+B+)->(B+)->(B+A-)->(A-)->(A-B-)->(B-)>(B-A+)
	{
		case 0: 
			IN_A=1;IN_B=0;IN_C=0;IN_D=0;
			break;
		case 1: 
			IN_A=1;IN_B=0;IN_C=1;IN_D=0;
			break;
		case 2: 
			IN_A=0;IN_B=0;IN_C=1;IN_D=0;
			break;
		case 3: 
			IN_A=0;IN_B=1;IN_C=1;IN_D=0;
			break;
		case 4: 
			IN_A=0;IN_B=1;IN_C=0;IN_D=0;
			break;
		case 5: 
			IN_A=0;IN_B=1;IN_C=0;IN_D=1;
			break;
		case 6: 
			IN_A=0;IN_B=0;IN_C=0;IN_D=1;
			break;
		case 7: 
			IN_A=1;IN_B=0;IN_C=0;IN_D=1;
			break;
		default:
			IN_A=0;IN_B=0;IN_C=0;IN_D=0;
			break; // ֹͣ����	
	}			
}

// ����ɨ��
u8 key_scan(unsigned char mode)
{
	static unsigned char key = 1;

	if(mode)
		key = 1; // ����ɨ�谴��
	if(key == 1 && ( KEY1 == 0 || KEY2 == 0 || KEY3 == 0 || KEY4 == 0)) // ���ⰴ������
	{
		delay_10us(1000);//����
		key = 0;
		if(KEY1 == 0)
			return KEY1_PRESS;
		else if(KEY2 == 0)
			return KEY2_PRESS;
		else if(KEY3 == 0)
			return KEY3_PRESS;
		else if(KEY4 == 0)
			return KEY4_PRESS;	
	}
	else if(KEY1 == 1 && KEY2 == 1 && KEY3 == 1 && KEY4 == 1) // �ް�������
	{
		key = 1;			
	}
	return KEY_UNPRESS;		
}

void main()
{	
	unsigned char key = 0;
	unsigned char dir = 0; // Ĭ����ʱ�뷽��
	unsigned char speed = STEPMOTOR_MAXSPEED; // Ĭ������ٶ���ת
	unsigned char step = 0;

	while(1)
	{			
		key = key_scan(0);
		if(key == KEY1_PRESS) // ����
		{
			dir =! dir;    
		}
		else if(key == KEY2_PRESS) // ����
		{
			if(speed > STEPMOTOR_MAXSPEED)
				speed -= 1;			
		}
		else if(key == KEY3_PRESS) // ����
		{
			if(speed < STEPMOTOR_MINSPEED)
				speed += 1;			
		}
		step_motor_send_pulse(step++, dir);
		if(step == 8)
			step = 0;		
		delay_ms(speed);						
	}		
}
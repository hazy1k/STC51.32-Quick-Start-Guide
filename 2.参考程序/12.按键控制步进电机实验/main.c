#include <REGX52.H>

//����ULN2003���Ʋ�������ܽ�
sbit IN1_A = P1^0;
sbit IN2_B = P1^1;
sbit IN3_C = P1^2;
sbit IN4_D = P1^3;

//��������������ƽ�
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

// ���岽������ٶȣ�ֵԽС���ٶ�Խ�죨1~5��
#define STEPMOTOR_MAXSPEED	1  
#define STEPMOTOR_MINSPEED	5  	

// ������ʱ����
void delay_10us(unsigned int ten_us)
{
	while(ten_us--);	
}

// ������ʱ����
void delay_ms(unsigned int ms)
{
	unsigned int i,j;
	for(i=ms;i>0;i--)
		for(j=110;j>0;j--);
}

// �������庯��
void motor_28BYJ48_send(unsigned char step, unsigned char dir) // step:������ţ�dir:����
{
	unsigned char temp = step; // ������ʱ����Ϊ�������
	
	if(dir == 0) // ���Ϊ��ʱ����ת
	{
		temp = 7 - step; // ���������ź�
	}

	switch(temp) // 8�����Ŀ��ƣ�A->AB->B->BC->C->CD->D->DA
	{
		// ��������ֱ�Ӹ���ճ������
		case 0: 
			IN1_A=1;IN2_B=0;IN3_C=0;IN4_D=0;
			break;
		case 1: 
			IN1_A=1;IN2_B=1;IN3_C=0;IN4_D=0;
			break;
		case 2: 
			IN1_A=0;IN2_B=1;IN3_C=0;IN4_D=0;
			break;
		case 3: 
			IN1_A=0;IN2_B=1;IN3_C=1;IN4_D=0;
			break;
		case 4: 
			IN1_A=0;IN2_B=0;IN3_C=1;IN4_D=0;
			break;
		case 5: 
			IN1_A=0;IN2_B=0;IN3_C=1;IN4_D=1;
			break;
		case 6: 
			IN1_A=0;IN2_B=0;IN3_C=0;IN4_D=1;
			break;
		case 7: 
			IN1_A=1;IN2_B=0;IN3_C=0;IN4_D=1;
			break;
		default: 
			IN1_A=0;IN2_B=0;IN3_C=0;IN4_D=0;
			break; // ֹͣ����	
	}			
}

// ����ɨ�躯�������������Ҫ�ص���⣩
// mode: 0-����ɨ�裬1-����ɨ��
unsigned char key_scan(int mode)
{
	static int key = 1; // ��̬����-Ŀ����Ϊ��ʵ������ɨ�谴��,����ʹkey�ĳ�ʼֵ�ı�

	if(mode)
		key = 1; // ����ɨ�谴��
	if(key == 1 && (KEY1 == 0 || KEY2 == 0 || KEY3 == 0|| KEY4 == 0)) // �������ⰴ������
	{
		delay_10us(1000); // ����
		key = 0;
		if(KEY1 == 0) // ������1����
			return KEY1_PRESS;
		else if(KEY2 == 0) // ������1����
			return KEY2_PRESS;
		else if(KEY3 == 0) // ������3����
			return KEY3_PRESS;
		else if(KEY4 == 0) // ������4����
			return KEY4_PRESS;	
	}
	else if(KEY1 == 1 && KEY2 == 1 && KEY3 == 1 && KEY4 == 1) // �����ް�������
	{
		key = 1;			
	}
	return KEY_UNPRESS;		
}

void main()
{	
	int key = 0;
	int dir = 0; // Ĭ����ʱ�뷽��
	int speed = STEPMOTOR_MAXSPEED; // Ĭ������ٶ���ת
	int step = 0;

	while(1)
	{			
		key = key_scan(0);
		if(key == KEY1_PRESS) // ����
		{
			dir = !dir; // ����ת    
		}
		else if(key == KEY2_PRESS) // ����
		{
			// ���ٶ��Ѿ���󣬴�ʱ���ٻᵼ���ٶȼ�1
			if(speed>STEPMOTOR_MAXSPEED)
				speed -= 1;			
		}
		else if(key == KEY3_PRESS)//����
		{
			// ���ٶ��Ѿ���С����ʱ���ٻᵼ���ٶȼ�1
			if(speed < STEPMOTOR_MINSPEED)
				speed +=1;			
		}

		motor_28BYJ48_send(step++, dir); // ��������
		if(step == 8) // ������ŵ���8���ص�0
		{
			step=0;	
		}	
		delay_ms(speed); // ��ʱ					
	}		
}
// �ܵ���˵���������ʵ���˰������Ʋ�������Ĺ��ܣ�ͨ���������Ʒ����ٶȡ��������
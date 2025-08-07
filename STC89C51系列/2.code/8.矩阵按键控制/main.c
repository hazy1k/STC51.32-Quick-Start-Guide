#include <REGX52.H>

// ��������������
unsigned char gsmg_code[17]={0x3f,0x06,0x5b,0x4f,0x66,0x6d,0x7d,0x07,
                0x7f,0x6f,0x77,0x7c,0x39,0x5e,0x79,0x71};    
// ��ʱ����
void delay_us(unsigned int ten_us)
{
    while(ten_us--);    
}

// ɨ�躯��
int key_scan()
{
    unsigned int key_value; // �����ֵ

    P1 = 0xf7; // ����һ�и�ֵ0������ȫΪ1��������1111 0111�������1��Ϊ�͵�ƽ��P1�����Ӿ��󰴼���

    /* 
    Ϊʲô����ʵ��������ܣ�
    ���д����ǽ� P1 ��ֵ��Ϊ 0xF7������������ʽΪ 11110111��
    11110111��������P1.7~P1.0,��ζ�ţ�P1.7~P1.4��P1.2~P1.0����ֵΪ1����P1.3����ֵΪ0
    �����ǵĽ��߾�֪��-P1.3ȷʵ�ǽ���L1�ϵ�-�������˵�һ��
    �Ӷ����Ǿ�����˸���һ�и�0�������ģʽ���Ĳ���-����λȫ����-����ɨ�跨-
	�ȸ�һ��Ϊ�͵�ƽ��������Ϊ�ߵ�ƽ��Ȼ���������һ�θ����Ƿ�Ϊ�͵�ƽ������⵽ĳһ��Ϊ�͵�ƽ�������Ǳ��ȷ�ϵ�ǰ�����µļ�����һ����һ�е�
    */

    if(P1 != 0xf7) // �жϵ�һ�а����Ƿ���-������£���P1�ڲ�����1111 0111��ִ���������
    {
        delay_us(1000);// ����
        switch(P1) // �����һ�а������º�ļ�ֵ    
        {
        /*
        ����Աȶ���ֵ���ٷ��ؾ����ˣ�ע��Ҫ���ص�һ�е������
        ���Ǿ�һ�����ӣ�1234
                        5678
                        9ABC
                        DF
        �����һ�е�5��ͨ����ѯ����ֵ����0xb7
        ��ô����ֱ��дcase 0xb7 ��ѭ����������ݣ�����ҵ��ˣ��ͷ���5��Ȼ������ܾ���ʾ5��
        */
            case 0x77: 
                key_value = 1;
                break;
            case 0xb7: 
                key_value = 5;
                break;
            case 0xd7: 
                key_value = 9;
                break;
            case 0xe7: 
                key_value = 13; // D
                break;
        }
    }while(P1 != 0xf7); // �ȴ������ɿ�    

    P1 = 0xfb;//���ڶ��и�ֵ0������ȫΪ1
    if(P1 != 0xfb)//�жϵڶ��а����Ƿ���
    {
        delay_us(1000);//����
        switch(P1)//����ڶ��а������º�ļ�ֵ    
        {
            case 0x7b: 
                key_value = 2;
                break;
            case 0xbb: 
                key_value = 6;
                break;
            case 0xdb: 
                key_value = 10;
                break;
            case 0xeb: 
                key_value = 14;
                break;
        }
    }while(P1 != 0xfb);//�ȴ������ɿ�    

    P1 = 0xfd; // �������и�ֵ0������ȫΪ1
    if(P1 != 0xfd) // �жϵ����а����Ƿ���
    {
        delay_us(1000); // ����
        switch(P1) // ��������а������º�ļ�ֵ    
        {
            case 0x7d: 
                key_value = 3;
                break;
            case 0xbd: 
                key_value = 7;
                break;
            case 0xdd: 
                key_value = 11;
                break;
            case 0xed: 
                key_value = 15;
                break;
        }
    }while(P1 != 0xfd);//�ȴ������ɿ�    

    P1 = 0xfe;//�������и�ֵ0������ȫΪ1
    if(P1 != 0xfe)//�жϵ����а����Ƿ���
    {
        delay_us(1000);//����
        switch(P1)//��������а������º�ļ�ֵ    
        {
            case 0x7e: 
                key_value = 4;
                break;
            case 0xbe: 
                key_value = 8;
                break;
            case 0xde: 
                key_value = 12;
                break;
            case 0xee: 
                key_value = 16;
                break;
        }
    }while(P1 != 0xfe);//�ȴ������ɿ�

    return key_value; // ���صõ���ֵ       
}


// ������
void main()
{    
    int key; // ������Ҫ���ص�ֵ

    while(1)
    {
        key = key_scan(); // ����ֵ�������з��ص�ֵ
        if(key != 0)
            P0 = ~gsmg_code[key-1]; // �õ��İ���ֵ��1����������±��Ӧ0-F����
        // Ϊʲô��Ҫ��1�أ���1~f��    ��
        // ��Ϊѧ��C����֪����������±��Ǵ�0��ʼ�ģ�����ֵ�Ǵ�1��ʼ�ģ�����ҪkeyҪ��1���ܶԵ�������
    }        
}
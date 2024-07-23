#ifndef _pwm_H
#define _pwm_H

#include "public.h"

//�ܽŶ���
sbit PWM = P2^1;

//��������
extern unsigned char gtim_scale;

//��������
void pwm_init(unsigned char tim_h, unsigned char tim_l, unsigned int tim_scale, unsigned char duty);
void pwm_set_duty_cycle(unsigned char duty);

#endif

#ifndef _24c02_H
#define _24c02_H

#include "public.h"

void at24c02_write_one_byte(unsigned char addr, unsigned char dat); // AT24C02ָ����ַд����
unsigned char at24c02_read_one_byte(unsigned char addr); // AT24C02ָ����ַ������

#endif
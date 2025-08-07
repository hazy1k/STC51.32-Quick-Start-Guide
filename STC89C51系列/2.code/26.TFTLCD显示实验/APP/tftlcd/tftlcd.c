#include "tftlcd.h"
#include "font.h" 
#include "uart.h"
#include "stdlib.h"

// LCD�Ļ�����ɫ�ͱ���ɫ	   
unsigned int FRONT_COLOR = WHITE; // ������ɫ
unsigned int BACK_COLOR = BLACK; // ����ɫ 

_tftlcd_data tftlcd_data; 

void Delay(unsigned int dly)
{
    unsigned int i,j;

    for(i = 0; i < dly; i++)
    	for(j = 0; j < 255; j++);
}

// д�Ĵ�������
// cmd:�Ĵ���ֵ
void LCD_WriteCmd(unsigned int cmd)
{	
	TFT_WR = 1;
	TFT_CS = 0;
	TFT_RD = 1;
 	TFT_RS = 0;

 	TFT_DATAPORTL = cmd>>8;
	TFT_WR = 0;
 	TFT_WR = 1;

 	TFT_DATAPORTL = cmd&0x00ff;
 	TFT_WR = 0;
 	TFT_WR = 1;

 	TFT_CS = 1;
}

//д����
//dat:Ҫд���ֵ
void LCD_WriteData(unsigned int dat)
{
	TFT_WR = 1;
	TFT_CS = 0;
	TFT_RD = 1;
 	TFT_RS = 1;
		 
 	TFT_DATAPORTL = dat>>8;
 	TFT_WR = 0;
 	TFT_WR = 1;
 	TFT_DATAPORTL = dat&0x00ff;
 	TFT_WR = 0;
 	TFT_WR = 1;

 	TFT_CS = 1;	
}

void LCD_WriteData_Color(unsigned int color)
{
	TFT_WR = 1;
	TFT_CS = 0;
	TFT_RD = 1;
 	TFT_RS = 1;
		 
 	TFT_DATAPORTL = color>>8;
 	TFT_WR = 0;
 	TFT_WR = 1;
 	TFT_DATAPORTL = color&0x00ff;
 	TFT_WR = 0;
 	TFT_WR = 1;

 	TFT_CS=1;	
}

void LCD_WriteCmdData(unsigned int cmd, unsigned int dat)
{
	LCD_WriteCmd(cmd);
	LCD_WriteData(dat);
}

// ������
// ����ֵ:������ֵ
unsigned int LCD_ReadData(void)
{
	unsigned int ram;

	TFT_DATAPORTH = 0xff;
	TFT_DATAPORTL = 0xff;	

	TFT_CS = 0;
	TFT_RS = 1;
	TFT_RD = 0;
	_nop_();
	ram = TFT_DATAPORTL;
	ram <<= 8;
	ram |= TFT_DATAPORTL;
	TFT_RD = 1;	
 	TFT_CS = 1;

	return ram;	
}

// ����LCD��ʾ����
// dir:0,������1,����
void LCD_Display_Dir(unsigned char dir)
{
	tftlcd_data.dir = dir;
	if(dir == 0)  // Ĭ����������
	{		
		LCD_WriteCmdData(0x0001, 0x0100); // Output Direct
		LCD_WriteCmdData(0x0003, 0x1030); // ���ò�����ʾ����ļĴ���

		tftlcd_data.height = HEIGHT;
		tftlcd_data.width = WIDTH;		
	}
	else
	{	
		LCD_WriteCmdData(0x0001, 0x0000); // Output Direct
		LCD_WriteCmdData(0x0003, 0x1038); // ���ò�����ʾ����ļĴ���

	   	tftlcd_data.height = WIDTH;
		tftlcd_data.width = HEIGHT;
	}
}

// TFTLCD��ʼ��
void TFTLCD_Init(void)
{
	unsigned int i = 0;
	TFT_RST = 1;  
	delay_ms(100);
	
	TFT_RST = 0;
	delay_ms(100);

	TFT_RST = 1;
	delay_ms(100);
	
	LCD_WriteCmd(0X0000);			   	
	tftlcd_data.id = LCD_ReadData();

	//************* Start Initial Sequence **********// 
	LCD_WriteCmdData(0x0001, 0x0100); // set SS  and SM bit 
	LCD_WriteCmdData(0x0002, 0x0200); // set 1 line inversion 
	LCD_WriteCmdData(0x0003, 0x1030); // set GRAM write direction and BGR=1. 
	LCD_WriteCmdData(0x0004, 0x0000); // Resize register 
	LCD_WriteCmdData(0x0008, 0x0202); // set theback porch and front porch 
	LCD_WriteCmdData(0x0009, 0x0000); // set non-display area refresh cycle ISC[3:0] 
	LCD_WriteCmdData(0x000A, 0x0000); // FMARK function 
	LCD_WriteCmdData(0x000C, 0x0000); // RGB interface setting 
	LCD_WriteCmdData(0x000D, 0x0000); // Frame marker Position 
	LCD_WriteCmdData(0x000F, 0x0000); // RGB int erface polarity 
	//*************Power On sequence **************** // 
	LCD_WriteCmdData(0x0010, 0x0000); // SAP, BT[3:0], AP, DSTB, SLP, STB 
	LCD_WriteCmdData(0x0011, 0x0007); // DC1[2:0 ], DC0[2:0], VC[2:0] 
	LCD_WriteCmdData(0x0012, 0x0000); // VREG1OUT voltage 
	LCD_WriteCmdData(0x0013, 0x0000); // VDV[4:0] for VCOM amplitude 
	delay_ms(10);                         // Dis-charge capacitor power voltage 
	LCD_WriteCmdData(0x0010, 0x1690); // SAP, BT[3:0], AP, DSTB, SLP, STB 
	LCD_WriteCmdData(0x0011, 0x0227); // R11h=0x 0221 at VCI=3.3V, DC1[2:0], DC0[2:0], VC[2:0] 
	delay_ms(10);                          // Delay 50ms 
	LCD_WriteCmdData(0x0012, 0x008D); // External reference voltage= Vci; 
	delay_ms(10);                          // Delay 50ms 
	LCD_WriteCmdData(0x0013, 0x1200); // VDV[4:0] for VCOM amplitude 
	LCD_WriteCmdData(0x0029, 0x0005); // VCM[5:0] for VCOMH 
	LCD_WriteCmdData(0x002B, 0x000C); // Frame Rate = 91Hz 
	delay_ms(10);                          // Delay 50ms 
	LCD_WriteCmdData(0x0020, 0x0000); // GRAM horizontal Address 
	LCD_WriteCmdData(0x0021, 0x0000); // GRAM Vertical Address 
	// ----------- Adjust the Gamma Curve ----------// 
	//a-Si TFT LCD Single Chip Driver 
	//240RGBx320 Resolution and 262K color  ILI9325D
	//The information contained herein is the exclusive property of ILI Technology Corp. and shall not be distributed, reproduced, or disclosed in 
	//whole or in part without prior written permission of ILI Technology Corp.
	//Page 24 of 26  V0.14
	LCD_WriteCmdData(0x0030, 0x0000); 
	LCD_WriteCmdData(0x0031, 0x0303); 
	LCD_WriteCmdData(0x0032, 0x0103); 
	LCD_WriteCmdData(0x0035, 0x0103); 
	LCD_WriteCmdData(0x0036, 0x0004); 
	LCD_WriteCmdData(0x0037, 0x0406); 
	LCD_WriteCmdData(0x0038, 0x0404); 
	LCD_WriteCmdData(0x0039, 0x0707); 
	LCD_WriteCmdData(0x003C, 0x0301); 
	LCD_WriteCmdData(0x003D, 0x0004); 
	//------------------ Set GRAM area ---------------// 
	LCD_WriteCmdData(0x0050, 0x0000); // Horizontal GRAM Start Address 
	LCD_WriteCmdData(0x0051, 0x00EF); // Horizontal GRAM End Address 
	LCD_WriteCmdData(0x0052, 0x0000); // Vertical GRAM Start Address 
	LCD_WriteCmdData(0x0053, 0x013F); // Vertical GRAM Start Address 
	LCD_WriteCmdData(0x0060, 0xA700); // Gate Sc an Line 
	LCD_WriteCmdData(0x0061, 0x0001); // NDL,VLE, REV 
	LCD_WriteCmdData(0x006A, 0x0000); // set scrolling line 
	//-------------- Partial Display Control ---------// 
	LCD_WriteCmdData(0x0080, 0x0000); 
	LCD_WriteCmdData(0x0081, 0x0000); 
	LCD_WriteCmdData(0x0082, 0x0000); 
	LCD_WriteCmdData(0x0083, 0x0000); 
	LCD_WriteCmdData(0x0084, 0x0000); 
	LCD_WriteCmdData(0x0085, 0x0000); 
	//-------------- Panel Control -------------------// 
	LCD_WriteCmdData(0x0090, 0x0010); 
	LCD_WriteCmdData(0x0092, 0x0600); 
	LCD_WriteCmdData(0x0007, 0x0133); // 262K color and display ON 
	
	LCD_WriteCmd(0x0022);


	LCD_Display_Dir(TFTLCD_DIR); // 0������  1������  Ĭ������
	LCD_Clear(BACK_COLOR);
}

// ���ô���,���Զ����û������굽�������Ͻ�(sx,sy).
// sx,sy:������ʼ����(���Ͻ�)
// width,height:���ڿ�Ⱥ͸߶�,�������0!!
// �����С:width*height. 
void LCD_Set_Window(unsigned int sx,unsigned int sy,unsigned int width,unsigned int height)
{
	if(tftlcd_data.dir == 0)	
	{
		LCD_WriteCmdData(0x0050, sx); // Horizontal GRAM Start Address 
		LCD_WriteCmdData(0x0051, width); // Horizontal GRAM End Address 
		LCD_WriteCmdData(0x0052, sy); // Vertical GRAM Start Address 
		LCD_WriteCmdData(0x0053, height); // Vertical GRAM Start Address 
	
		LCD_WriteCmdData(0x0020, sx); // GRAM horizontal Address 
		LCD_WriteCmdData(0x0021, sy); // GRAM Vertical Address
		LCD_WriteCmd(0x0022);
	}
	else
	{
		LCD_WriteCmdData(0x0052, sx); // Horizontal GRAM Start Address 
		LCD_WriteCmdData(0x0053, width); // Horizontal GRAM End Address 
		LCD_WriteCmdData(0x0050, sy); // Vertical GRAM Start Address 
		LCD_WriteCmdData(0x0051, height); // Vertical GRAM Start Address 
	
		LCD_WriteCmdData(0x0021, sx); // GRAM horizontal Address 
		LCD_WriteCmdData(0x0020, sy); // GRAM Vertical Address
		LCD_WriteCmd(0x0022);
	}
}

// ��ȡ��ĳ�����ɫֵ	 
// x,y:����
// ����ֵ:�˵����ɫ
unsigned int LCD_ReadPoint(unsigned int x, unsigned int y)
{
 	unsigned int r=0,g=0x0001,b=0x0001,dat;
	if(x >= tftlcd_data.width || y>= tftlcd_data.height)
		return 0;	//�����˷�Χ,ֱ�ӷ���		     
	LCD_Set_Window(x, y, x, y);
	
	LCD_WriteCmd(0X0022);
	r = LCD_ReadData();  		//dummy Read     		 				    	   
 	r = LCD_ReadData();  		//ʵ��������ɫ

	return r;
}

// ��������
// color:Ҫ���������ɫ
void LCD_Clear(unsigned int color)
{
	unsigned int i=0, j=0 ;

	LCD_Set_Window(0, 0, tftlcd_data.width-1, tftlcd_data.height-1);	 //��������
  	for(i = 0; i < tftlcd_data.width; i++)
	{
		for(j = 0; j < tftlcd_data.height; j++)
		{
			LCD_WriteData_Color(color);
		}
	} 
}

// ��ָ����������䵥����ɫ
// (sx,sy),(ex,ey):�����ζԽ�����,�����СΪ:(ex-sx+1)*(ey-sy+1)   
// color:Ҫ������ɫ
void LCD_Fill(unsigned int xState, unsigned int yState, unsigned int xEnd, unsigned int yEnd, unsigned int color)
{          
	unsigned int temp = 0;

    if((xState > xEnd) || (yState > yEnd))
    {
        return;
    }   
	LCD_Set_Window(xState, yState, xEnd, yEnd); 
    xState = xEnd - xState + 1;
	yState = yEnd - yState + 1;

	while(xState--)
	{
	 	temp = yState;
		while (temp--)
	 	{			
			LCD_WriteData_Color(color);	
		}
	}	
} 

// ��ָ�����������ָ����ɫ��			 
// (sx,sy),(ex,ey):�����ζԽ�����,�����СΪ:(ex-sx+1)*(ey-sy+1)   
// color:Ҫ������ɫ
void LCD_Color_Fill(unsigned int sx,unsigned int sy,unsigned int ex,unsigned int ey,unsigned int *color)
{  
	unsigned int height,width;
	unsigned int i,j;
	width = ex-sx+1; 			// �õ����Ŀ��
	height = ey-sy+1;			// �߶�
	LCD_Set_Window(sx, sy,ex, ey);
 	for(i = 0; i< height; i++)
	{
		for(j =0 ; j < width; j++)
		{
			LCD_WriteData_Color(color[i*width+j]);
		}
	}		    
}

// ����
// x,y:����
// FRONT_COLOR:�˵����ɫ
void LCD_DrawPoint(unsigned int x, unsigned int y)
{
	LCD_Set_Window(x, y, x, y);  // ���õ��λ��
	LCD_WriteData_Color(FRONT_COLOR);	
}

//���ٻ���
//x,y:����
//color:��ɫ
void LCD_DrawFRONT_COLOR(unsigned int x, unsigned int y, unsigned int color)
{	   
	LCD_Set_Window(x, y, x, y);
	LCD_WriteData_Color(color);	
} 

// ��һ�����
// 2*2�ĵ�			   
void LCD_DrawBigPoint(unsigned int x, unsigned int y, unsigned int color)
{	    
	LCD_DrawFRONT_COLOR(x,y, color); // ���ĵ� 
	LCD_DrawFRONT_COLOR(x+1,y, color);
	LCD_DrawFRONT_COLOR(x,y+1, color);
	LCD_DrawFRONT_COLOR(x+1,y+1, color);	 	  	
}

// ����
// x1,y1:�������
// x2,y2:�յ�����  
void LCD_DrawLine(unsigned int x1, unsigned int y1, unsigned int x2, unsigned int y2)
{
	unsigned int t = 0; 
	int xerr=0,yerr=0,delta_x,delta_y,distance; 
	int incx,incy,uRow,uCol; 
	delta_x = x2-x1; // ������������ 
	delta_y = y2-y1; 
	uRow = x1; 
	uCol = y1; 
	if(delta_x > 0)
		incx = 1; // ���õ������� 
	else if(delta_x == 0)
		incx = 0; // ��ֱ�� 
	else 
	{
		incx = -1;
		delta_x = -delta_x;
	} 
	if(delta_y > 0)
		incy = 1; 
	else if(delta_y == 0)
		incy = 0 ; // ˮƽ�� 
	else
	{
		incy=-1; 
		delta_y = -delta_y;
	} 
	if(delta_x > delta_y)
		distance = delta_x; // ѡȡ�������������� 
	else 
		distance = delta_y; 
	for(t = 0; t<= distance+1; t++ ) // ������� 
	{  
		LCD_DrawPoint(uRow, uCol); // ���� 
		xerr += delta_x ; 
		yerr += delta_y ; 
		if(xerr > distance) 
		{ 
			xerr -= distance; 
			uRow += incx; 
		} 
		if(yerr > distance) 
		{ 
			yerr -= distance; 
			uCol += incy; 
		} 
	}  
} 

void LCD_DrawLine_Color(unsigned int x1, unsigned int y1, unsigned int x2, unsigned int y2,unsigned int color)
{
	unsigned int t; 
	int xerr=0,yerr=0,delta_x,delta_y,distance; 
	int incx,incy,uRow,uCol; 
	delta_x = x2-x1; //������������ 
	delta_y = y2-y1; 
	uRow = x1; 
	uCol = y1; 
	if(delta_x>0)
		incx = 1; // ���õ������� 
	else if(delta_x == 0)
		incx=0; // ��ֱ�� 
	else 
	{
		incx =-1; delta_x =- delta_x;
	} 
	if(delta_y>0)
		incy = 1; 
	else if(delta_y == 0)
		incy = 0;//ˮƽ�� 
	else
	{
		incy =- 1;
		delta_y =- delta_y;
	} 
	if( delta_x > delta_y)
		distance = delta_x; //ѡȡ�������������� 
	else 
		distance = delta_y; 
	for(t = 0; t<= distance+1; t++ ) // ������� 
	{  
		LCD_DrawFRONT_COLOR(uRow,uCol,color);//���� 
		xerr += delta_x ; 
		yerr += delta_y ; 
		if(xerr > distance) 
		{ 
			xerr -= distance; 
			uRow += incx; 
		} 
		if(yerr > distance) 
		{ 
			yerr -= distance; 
			uCol += incy; 
		} 
	}  
} 


// ��һ��ʮ�ֵı��
// x����ǵ�X����
// y����ǵ�Y����
// color����ǵ���ɫ
void LCD_DrowSign(u16 x, u16 y, u16 color)
{
    u8 i;

    /* ���� */
    LCD_Set_Window(x-1, y-1, x+1, y+1);
    for(i=0; i<9; i++)
    {
		LCD_WriteData_Color(color);   
    }

    /* ���� */
    LCD_Set_Window(x-4, y, x+4, y);
    for(i=0; i<9; i++)
    {
		LCD_WriteData_Color(color); 
    }

    /* ���� */
    LCD_Set_Window(x, y-4, x, y+4);
    for(i=0; i<9; i++)
    {
		LCD_WriteData_Color(color); 
    }
}

//������	  
//(x1,y1),(x2,y2):���εĶԽ�����
void LCD_DrawRectangle(u16 x1, u16 y1, u16 x2, u16 y2)
{
	LCD_DrawLine(x1,y1,x2,y1);
	LCD_DrawLine(x1,y1,x1,y2);
	LCD_DrawLine(x1,y2,x2,y2);
	LCD_DrawLine(x2,y1,x2,y2);
}
//��ָ��λ�û�һ��ָ����С��Բ
//(x,y):���ĵ�
//r    :�뾶
void LCD_Draw_Circle(u16 x0,u16 y0,u8 r)
{
	int a,b;
	int di;
	a=0;b=r;	  
	di=3-(r<<1);             //�ж��¸���λ�õı�־
	while(a<=b)
	{
		LCD_DrawPoint(x0+a,y0-b);             //5
 		LCD_DrawPoint(x0+b,y0-a);             //0           
		LCD_DrawPoint(x0+b,y0+a);             //4               
		LCD_DrawPoint(x0+a,y0+b);             //6 
		LCD_DrawPoint(x0-a,y0+b);             //1       
 		LCD_DrawPoint(x0-b,y0+a);             
		LCD_DrawPoint(x0-a,y0-b);             //2             
  		LCD_DrawPoint(x0-b,y0-a);             //7     	         
		a++;
		//ʹ��Bresenham�㷨��Բ     
		if(di<0)di +=4*a+6;	  
		else
		{
			di+=10+4*(a-b);   
			b--;
		} 						    
	}
} 


//��ָ��λ����ʾһ���ַ�
//x,y:��ʼ����
//num:Ҫ��ʾ���ַ�:" "--->"~"
//size:�����С 12/16/24
//mode:���ӷ�ʽ(1)���Ƿǵ��ӷ�ʽ(0)
void LCD_ShowChar(u16 x,u16 y,u8 num,u8 size,u8 mode)
{  							  
    u8 temp,t1,t;
	u16 y0=y;
	u8 csize=(size/8+((size%8)?1:0))*(size/2);		//�õ�����һ���ַ���Ӧ������ռ���ֽ���	
 	num=num-' ';//�õ�ƫ�ƺ��ֵ��ASCII�ֿ��Ǵӿո�ʼȡģ������-' '���Ƕ�Ӧ�ַ����ֿ⣩
	for(t=0;t<csize;t++)
	{   
		if(size==12)temp=ascii_1206[num][t]; 	 	//����1206����
		else if(size==16)temp=ascii_1608[num][t];	//����1608����
		else if(size==24)temp=ascii_2412[num][t];	//����2412����
		else return;								//û�е��ֿ�
		for(t1=0;t1<8;t1++)
		{			    
			if(temp&0x80)LCD_DrawFRONT_COLOR(x,y,FRONT_COLOR);
			else if(mode==0)LCD_DrawFRONT_COLOR(x,y,BACK_COLOR);
			temp<<=1;
			y++;
			if(y>=tftlcd_data.height)return;		//��������
			if((y-y0)==size)
			{
				y=y0;
				x++;
				if(x>=tftlcd_data.width)return;	//��������
				break;
			}
		}  	 
	}  	    	   	 	  
}   
//m^n����
//����ֵ:m^n�η�.
u32 LCD_Pow(u8 m,u8 n)
{
	u32 result=1;	 
	while(n--)result*=m;    
	return result;
}			 
//��ʾ����,��λΪ0,����ʾ
//x,y :�������	 
//len :���ֵ�λ��
//size:�����С
//color:��ɫ 
//num:��ֵ(0~4294967295);	 
void LCD_ShowNum(u16 x,u16 y,u32 num,u8 len,u8 size)
{         	
	u8 t,temp;
	u8 enshow=0;						   
	for(t=0;t<len;t++)
	{
		temp=(num/LCD_Pow(10,len-t-1))%10;
		if(enshow==0&&t<(len-1))
		{
			if(temp==0)
			{
				LCD_ShowChar(x+(size/2)*t,y,' ',size,0);
				continue;
			}else enshow=1; 
		 	 
		}
	 	LCD_ShowChar(x+(size/2)*t,y,temp+'0',size,0); 
	}
} 

//��ʾ����,��λΪ0,������ʾ
//x,y:�������
//num:��ֵ(0~999999999);	 
//len:����(��Ҫ��ʾ��λ��)
//size:�����С
//mode:
//[7]:0,�����;1,���0.
//[6:1]:����
//[0]:0,�ǵ�����ʾ;1,������ʾ.
void LCD_ShowxNum(u16 x,u16 y,u32 num,u8 len,u8 size,u8 mode)
{  
	u8 t,temp;
	u8 enshow=0;						   
	for(t=0;t<len;t++)
	{
		temp=(num/LCD_Pow(10,len-t-1))%10;
		if(enshow==0&&t<(len-1))
		{
			if(temp==0)
			{
				if(mode&0X80)LCD_ShowChar(x+(size/2)*t,y,'0',size,mode&0X01);  
				else LCD_ShowChar(x+(size/2)*t,y,' ',size,mode&0X01);  
 				continue;
			}else enshow=1; 
		 	 
		}
	 	LCD_ShowChar(x+(size/2)*t,y,temp+'0',size,mode&0X01); 
	}
} 
//��ʾ�ַ���
//x,y:�������
//width,height:�����С  
//size:�����С
//*p:�ַ�����ʼ��ַ		  
void LCD_ShowString(u16 x,u16 y,u16 width,u16 height,u8 size,u8 *p)
{         
	u8 x0=x;
	width+=x;
	height+=y;
    while((*p<='~')&&(*p>=' '))//�ж��ǲ��ǷǷ��ַ�!
    {       
        if(x>=width){x=x0;y+=size;}
        if(y>=height)break;//�˳�
        LCD_ShowChar(x,y,*p,size,0);
        x+=size/2;
        p++;
    }  
}

/****************************************************************************
*��������LCD_ShowFontHZ
*��  �룺x��������ʾ��X����
*      * y��������ʾ��Y����
*      * cn��Ҫ��ʾ�ĺ���
*      * wordColor�����ֵ���ɫ
*      * backColor��������ɫ
*��  ����
*��  �ܣ�д���ſ��庺��
****************************************************************************/
#if 1
void LCD_ShowFontHZ(u16 x, u16 y, u8 *cn)	 
{  
	u8 i, j, wordNum;
	u16 color;
	while (*cn != '\0')
	{
		LCD_Set_Window(x, y, x+31, y+28);
		for (wordNum=0; wordNum<20; wordNum++)
		{	//wordNumɨ���ֿ������
			if ((CnChar32x29[wordNum].Index[0]==*cn)
			     &&(CnChar32x29[wordNum].Index[1]==*(cn+1)))
			{
				
				for(i=0; i<116; i++) 
				{	//MSK��λ��
					color=CnChar32x29[wordNum].Msk[i];
					for(j=0;j<8;j++) 
					{
						if((color&0x80)==0x80)
						{
							LCD_WriteData_Color(FRONT_COLOR); 						
						} 						
						else
						{
							LCD_WriteData_Color(BACK_COLOR); 
						} 
						color<<=1;
					}//for(j=0;j<8;j++)����
				}    
			}
		} //for (wordNum=0; wordNum<20; wordNum++)���� 	
		cn += 2;
		x += 32;
	}
}
#endif


#if 0
void LCD_ShowFontHZ(u16 x, u16 y, u8 *cn)
{
	u8 i, j, wordNum;
	u16 color;
	u16 x0=x; 
	u16 y0=y; 
	while (*cn != '\0')
	{
		for (wordNum=0; wordNum<20; wordNum++)
		{	//wordNumɨ���ֿ������
			if ((CnChar32x29[wordNum].Index[0]==*cn)
			     &&(CnChar32x29[wordNum].Index[1]==*(cn+1)))
			{
				for(i=0; i<116; i++) 
				{	//MSK��λ��
					color=CnChar32x29[wordNum].Msk[i];
					for(j=0;j<8;j++) 
					{
						if((color&0x80)==0x80)
						{
							LCD_DrawFRONT_COLOR(x,y,FRONT_COLOR);
						} 						
						else
						{
							LCD_DrawFRONT_COLOR(x,y,BACK_COLOR);
						} 
						color<<=1;
						x++;
						if((x-x0)==32)
						{
							x=x0;
							y++;
							if((y-y0)==29)
							{
								y=y0;
							}
						}
					}//for(j=0;j<8;j++)����
				}	
			}
			
		} //for (wordNum=0; wordNum<20; wordNum++)���� 	
		cn += 2;
		x += 32;
		x0=x;
	}
}	
#endif

void LCD_ShowPicture(u16 x, u16 y, u16 wide, u16 high,u8 *pic)
{
	u16 temp = 0;
	long tmp=0,num=0;
	LCD_Set_Window(x, y, x+wide-1, y+high-1);
	num = wide * high*2 ;
	do
	{  
		temp = pic[tmp + 1];
		temp = temp << 8;
		temp = temp | pic[tmp];
		LCD_WriteData_Color(temp);//�����ʾ
		tmp += 2;
	}
	while(tmp < num);	
}


//////////////////////////////////////////////////////////////////////////////////	 
//±¾³ÌÐòÖ»¹©Ñ§Ï°Ê¹ÓÃ£¬Î´¾­×÷ÕßÐí¿É£¬²»µÃÓÃÓÚÆäËüÈÎºÎÓÃÍ¾
//²âÊÔÓ²¼þ£ºµ¥Æ¬»úSTM32F103RCT6,ÕýµãÔ­×ÓMiniSTM32¿ª·¢°å,Ö÷Æµ72MHZ£¬¾§Õñ12MHZ
//QDtech-TFTÒº¾§Çý¶¯ for STM32 IOÄ£Äâ
//xiao·ë@ShenZhen QDtech co.,LTD
//¹«Ë¾ÍøÕ¾:www.qdtft.com
//ÌÔ±¦ÍøÕ¾£ºhttp://qdtech.taobao.com
//wiki¼¼ÊõÍøÕ¾£ºhttp://www.lcdwiki.com
//ÎÒË¾Ìá¹©¼¼ÊõÖ§³Ö£¬ÈÎºÎ¼¼ÊõÎÊÌâ»¶Ó­ËæÊ±½»Á÷Ñ§Ï°
//¹Ì»°(´«Õæ) :+86 0755-23594567 
//ÊÖ»ú:15989313508£¨·ë¹¤£© 
//ÓÊÏä:lcdwiki01@gmail.com    support@lcdwiki.com    goodtft@163.com 
//¼¼ÊõÖ§³ÖQQ:3002773612  3002778157
//¼¼Êõ½»Á÷QQÈº:324828016
//´´½¨ÈÕÆÚ:2018/08/09
//°æ±¾£ºV1.0
//°æÈ¨ËùÓÐ£¬µÁ°æ±Ø¾¿¡£
//Copyright(C) ÉîÛÚÊÐÈ«¶¯µç×Ó¼¼ÊõÓÐÏÞ¹«Ë¾ 2018-2028
//All rights reserved
/****************************************************************************************************
//=========================================µçÔ´½ÓÏß================================================//
//     LCDÄ£¿é                STM32µ¥Æ¬»ú
//      VCC          ½Ó        DC5V/3.3V      //µçÔ´
//      GND          ½Ó          GND          //µçÔ´µØ
//=======================================Òº¾§ÆÁÊý¾ÝÏß½ÓÏß==========================================//
//±¾Ä£¿éÄ¬ÈÏÊý¾Ý×ÜÏßÀàÐÍÎªSPI×ÜÏß
//     LCDÄ£¿é                STM32µ¥Æ¬»ú    
//    SDI(MOSI)      ½Ó          PB15         //Òº¾§ÆÁSPI×ÜÏßÊý¾ÝÐ´ÐÅºÅ
//    SDO(MISO)      ½Ó          PB14         //Òº¾§ÆÁSPI×ÜÏßÊý¾Ý¶ÁÐÅºÅ£¬Èç¹û²»ÐèÒª¶Á£¬¿ÉÒÔ²»½ÓÏß
//=======================================Òº¾§ÆÁ¿ØÖÆÏß½ÓÏß==========================================//
//     LCDÄ£¿é 					      STM32µ¥Æ¬»ú 
//       LED         ½Ó          PB9          //Òº¾§ÆÁ±³¹â¿ØÖÆÐÅºÅ£¬Èç¹û²»ÐèÒª¿ØÖÆ£¬½Ó5V»ò3.3V
//       SCK         ½Ó          PB13         //Òº¾§ÆÁSPI×ÜÏßÊ±ÖÓÐÅºÅ
//      DC/RS        ½Ó          PB10         //Òº¾§ÆÁÊý¾Ý/ÃüÁî¿ØÖÆÐÅºÅ
//       RST         ½Ó          PB12         //Òº¾§ÆÁ¸´Î»¿ØÖÆÐÅºÅ
//       CS          ½Ó          PB11         //Òº¾§ÆÁÆ¬Ñ¡¿ØÖÆÐÅºÅ
//=========================================´¥ÃþÆÁ´¥½ÓÏß=========================================//
//Èç¹ûÄ£¿é²»´ø´¥Ãþ¹¦ÄÜ»òÕß´øÓÐ´¥Ãþ¹¦ÄÜ£¬µ«ÊÇ²»ÐèÒª´¥Ãþ¹¦ÄÜ£¬Ôò²»ÐèÒª½øÐÐ´¥ÃþÆÁ½ÓÏß
//	   LCDÄ£¿é                STM32µ¥Æ¬»ú 
//      T_IRQ        ½Ó          PC10         //´¥ÃþÆÁ´¥ÃþÖÐ¶ÏÐÅºÅ
//      T_DO         ½Ó          PC2          //´¥ÃþÆÁSPI×ÜÏß¶ÁÐÅºÅ
//      T_DIN        ½Ó          PC3          //´¥ÃþÆÁSPI×ÜÏßÐ´ÐÅºÅ
//      T_CS         ½Ó          PC13         //´¥ÃþÆÁÆ¬Ñ¡¿ØÖÆÐÅºÅ
//      T_CLK        ½Ó          PC0          //´¥ÃþÆÁSPI×ÜÏßÊ±ÖÓÐÅºÅ
**************************************************************************************************/	
 /* @attention
  *
  * THE PRESENT FIRMWARE WHICH IS FOR GUIDANCE ONLY AIMS AT PROVIDING CUSTOMERS
  * WITH CODING INFORMATION REGARDING THEIR PRODUCTS IN ORDER FOR THEM TO SAVE
  * TIME. AS A RESULT, QD electronic SHALL NOT BE HELD LIABLE FOR ANY
  * DIRECT, INDIRECT OR CONSEQUENTIAL DAMAGES WITH RESPECT TO ANY CLAIMS ARISING
  * FROM THE CONTENT OF SUCH FIRMWARE AND/OR THE USE MADE BY CUSTOMERS OF THE
  * CODING INFORMATION CONTAINED HEREIN IN CONNECTION WITH THEIR PRODUCTS.
**************************************************************************************************/	
#include "lcd.h"
#include "string.h"
#include <font.h> 
#include "delay.h"
#include "gui.h"

/*******************************************************************
 * @name       :void GUI_DrawPoint(u16 x,u16 y,u16 color)
 * @date       :2018-08-09 
 * @function   :draw a point in LCD screen
 * @parameters :x:the x coordinate of the point
                y:the y coordinate of the point
								color:the color value of the point
 * @retvalue   :None
********************************************************************/
void GUI_DrawPoint(u16 x,u16 y,u32 color)
{
	LCD_SetCursor(x,y);//ÉèÖÃ¹â±êÎ»ÖÃ 
	Lcd_WriteData_16Bit(color); 
}

/*******************************************************************
 * @name       :void LCD_Fill(u16 sx,u16 sy,u16 ex,u16 ey,u16 color)
 * @date       :2018-08-09 
 * @function   :fill the specified area
 * @parameters :sx:the bebinning x coordinate of the specified area
                sy:the bebinning y coordinate of the specified area
								ex:the ending x coordinate of the specified area
								ey:the ending y coordinate of the specified area
								color:the filled color value
 * @retvalue   :None
********************************************************************/
void LCD_Fill(u16 sx,u16 sy,u16 ex,u16 ey,u32 color)
{  	
	u16 i,j;			
	u16 width=ex-sx+1; 		//µÃµ½Ìî³äµÄ¿í¶È
	u16 height=ey-sy+1;		//¸ß¶È
	LCD_SetWindows(sx,sy,ex,ey);//ÉèÖÃÏÔÊ¾´°¿Ú
	for(i=0;i<height;i++)
	{
		for(j=0;j<width;j++)
		Lcd_WriteData_16Bit(color);	//Ð´ÈëÊý¾Ý 	 
	}
	LCD_SetWindows(0,0,lcddev.width-1,lcddev.height-1);//»Ö¸´´°¿ÚÉèÖÃÎªÈ«ÆÁ
}

/*******************************************************************
 * @name       :void LCD_DrawLine(u16 x1, u16 y1, u16 x2, u16 y2)
 * @date       :2018-08-09 
 * @function   :Draw a line between two points
 * @parameters :x1:the bebinning x coordinate of the line
                y1:the bebinning y coordinate of the line
								x2:the ending x coordinate of the line
								y2:the ending y coordinate of the line
 * @retvalue   :None
********************************************************************/
void LCD_DrawLine(u16 x1, u16 y1, u16 x2, u16 y2)
{
	u16 t; 
	int xerr=0,yerr=0,delta_x,delta_y,distance; 
	int incx,incy,uRow,uCol; 

	delta_x=x2-x1; //¼ÆËã×ø±êÔöÁ¿ 
	delta_y=y2-y1; 
	uRow=x1; 
	uCol=y1; 
	if(delta_x>0)incx=1; //ÉèÖÃµ¥²½·½Ïò 
	else if(delta_x==0)incx=0;//´¹Ö±Ïß 
	else {incx=-1;delta_x=-delta_x;} 
	if(delta_y>0)incy=1; 
	else if(delta_y==0)incy=0;//Ë®Æ½Ïß 
	else{incy=-1;delta_y=-delta_y;} 
	if( delta_x>delta_y)distance=delta_x; //Ñ¡È¡»ù±¾ÔöÁ¿×ø±êÖá 
	else distance=delta_y; 
	for(t=0;t<=distance+1;t++ )//»­ÏßÊä³ö 
	{  
		LCD_DrawPoint(uRow,uCol);//»­µã 
		xerr+=delta_x ; 
		yerr+=delta_y ; 
		if(xerr>distance) 
		{ 
			xerr-=distance; 
			uRow+=incx; 
		} 
		if(yerr>distance) 
		{ 
			yerr-=distance; 
			uCol+=incy; 
		} 
	}  
} 

/*****************************************************************************
 * @name       :void LCD_DrawRectangle(u16 x1, u16 y1, u16 x2, u16 y2)
 * @date       :2018-08-09 
 * @function   :Draw a rectangle
 * @parameters :x1:the bebinning x coordinate of the rectangle
                y1:the bebinning y coordinate of the rectangle
								x2:the ending x coordinate of the rectangle
								y2:the ending y coordinate of the rectangle
 * @retvalue   :None
******************************************************************************/
void LCD_DrawRectangle(u16 x1, u16 y1, u16 x2, u16 y2)
{
	LCD_DrawLine(x1,y1,x2,y1);
	LCD_DrawLine(x1,y1,x1,y2);
	LCD_DrawLine(x1,y2,x2,y2);
	LCD_DrawLine(x2,y1,x2,y2);
}  

/*****************************************************************************
 * @name       :void LCD_DrawFillRectangle(u16 x1, u16 y1, u16 x2, u16 y2)
 * @date       :2018-08-09 
 * @function   :Filled a rectangle
 * @parameters :x1:the bebinning x coordinate of the filled rectangle
                y1:the bebinning y coordinate of the filled rectangle
								x2:the ending x coordinate of the filled rectangle
								y2:the ending y coordinate of the filled rectangle
 * @retvalue   :None
******************************************************************************/  
void LCD_DrawFillRectangle(u16 x1, u16 y1, u16 x2, u16 y2)
{
	LCD_Fill(x1,y1,x2,y2,POINT_COLOR);
}
 
/*****************************************************************************
 * @name       :void _draw_circle_8(int xc, int yc, int x, int y, u16 c)
 * @date       :2018-08-09 
 * @function   :8 symmetry circle drawing algorithm (internal call)
 * @parameters :xc:the x coordinate of the Circular center 
                yc:the y coordinate of the Circular center 
								x:the x coordinate relative to the Circular center 
								y:the y coordinate relative to the Circular center 
								c:the color value of the circle
 * @retvalue   :None
******************************************************************************/  
void _draw_circle_8(int xc, int yc, int x, int y, u16 c)
{
	GUI_DrawPoint(xc + x, yc + y, c);

	GUI_DrawPoint(xc - x, yc + y, c);

	GUI_DrawPoint(xc + x, yc - y, c);

	GUI_DrawPoint(xc - x, yc - y, c);

	GUI_DrawPoint(xc + y, yc + x, c);

	GUI_DrawPoint(xc - y, yc + x, c);

	GUI_DrawPoint(xc + y, yc - x, c);

	GUI_DrawPoint(xc - y, yc - x, c);
}

/*****************************************************************************
 * @name       :void gui_circle(int xc, int yc,u16 c,int r, int fill)
 * @date       :2018-08-09 
 * @function   :Draw a circle of specified size at a specified location
 * @parameters :xc:the x coordinate of the Circular center 
                yc:the y coordinate of the Circular center 
								r:Circular radius
								fill:1-filling,0-no filling
 * @retvalue   :None
******************************************************************************/  
void gui_circle(int xc, int yc,u16 c,int r, int fill)
{
	int x = 0, y = r, yi, d;

	d = 3 - 2 * r;


	if (fill) 
	{
		// Èç¹ûÌî³ä£¨»­ÊµÐÄÔ²£©
		while (x <= y) {
			for (yi = x; yi <= y; yi++)
				_draw_circle_8(xc, yc, x, yi, c);

			if (d < 0) {
				d = d + 4 * x + 6;
			} else {
				d = d + 4 * (x - y) + 10;
				y--;
			}
			x++;
		}
	} else 
	{
		// Èç¹û²»Ìî³ä£¨»­¿ÕÐÄÔ²£©
		while (x <= y) {
			_draw_circle_8(xc, yc, x, y, c);
			if (d < 0) {
				d = d + 4 * x + 6;
			} else {
				d = d + 4 * (x - y) + 10;
				y--;
			}
			x++;
		}
	}
}

/*****************************************************************************
 * @name       :void Draw_Triangel(u16 x0,u16 y0,u16 x1,u16 y1,u16 x2,u16 y2)
 * @date       :2018-08-09 
 * @function   :Draw a triangle at a specified position
 * @parameters :x0:the bebinning x coordinate of the triangular edge 
                y0:the bebinning y coordinate of the triangular edge 
								x1:the vertex x coordinate of the triangular
								y1:the vertex y coordinate of the triangular
								x2:the ending x coordinate of the triangular edge 
								y2:the ending y coordinate of the triangular edge 
 * @retvalue   :None
******************************************************************************/ 
void Draw_Triangel(u16 x0,u16 y0,u16 x1,u16 y1,u16 x2,u16 y2)
{
	LCD_DrawLine(x0,y0,x1,y1);
	LCD_DrawLine(x1,y1,x2,y2);
	LCD_DrawLine(x2,y2,x0,y0);
}

static void _swap(u16 *a, u16 *b)
{
	u16 tmp;
  tmp = *a;
	*a = *b;
	*b = tmp;
}

/*****************************************************************************
 * @name       :void Fill_Triangel(u16 x0,u16 y0,u16 x1,u16 y1,u16 x2,u16 y2)
 * @date       :2018-08-09 
 * @function   :filling a triangle at a specified position
 * @parameters :x0:the bebinning x coordinate of the triangular edge 
                y0:the bebinning y coordinate of the triangular edge 
								x1:the vertex x coordinate of the triangular
								y1:the vertex y coordinate of the triangular
								x2:the ending x coordinate of the triangular edge 
								y2:the ending y coordinate of the triangular edge 
 * @retvalue   :None
******************************************************************************/ 
void Fill_Triangel(u16 x0,u16 y0,u16 x1,u16 y1,u16 x2,u16 y2)
{
	u16 a, b, y, last;
	int dx01, dy01, dx02, dy02, dx12, dy12;
	long sa = 0;
	long sb = 0;
 	if (y0 > y1) 
	{
    _swap(&y0,&y1); 
		_swap(&x0,&x1);
 	}
 	if (y1 > y2) 
	{
    _swap(&y2,&y1); 
		_swap(&x2,&x1);
 	}
  if (y0 > y1) 
	{
    _swap(&y0,&y1); 
		_swap(&x0,&x1);
  }
	if(y0 == y2) 
	{ 
		a = b = x0;
		if(x1 < a)
    {
			a = x1;
    }
    else if(x1 > b)
    {
			b = x1;
    }
    if(x2 < a)
    {
			a = x2;
    }
		else if(x2 > b)
    {
			b = x2;
    }
		LCD_Fill(a,y0,b,y0,POINT_COLOR);
    return;
	}
	dx01 = x1 - x0;
	dy01 = y1 - y0;
	dx02 = x2 - x0;
	dy02 = y2 - y0;
	dx12 = x2 - x1;
	dy12 = y2 - y1;
	
	if(y1 == y2)
	{
		last = y1; 
	}
  else
	{
		last = y1-1; 
	}
	for(y=y0; y<=last; y++) 
	{
		a = x0 + sa / dy01;
		b = x0 + sb / dy02;
		sa += dx01;
    sb += dx02;
    if(a > b)
    {
			_swap(&a,&b);
		}
		LCD_Fill(a,y,b,y,POINT_COLOR);
	}
	sa = dx12 * (y - y1);
	sb = dx02 * (y - y0);
	for(; y<=y2; y++) 
	{
		a = x1 + sa / dy12;
		b = x0 + sb / dy02;
		sa += dx12;
		sb += dx02;
		if(a > b)
		{
			_swap(&a,&b);
		}
		LCD_Fill(a,y,b,y,POINT_COLOR);
	}
}

/*****************************************************************************
 * @name       :void LCD_ShowChar(u16 x,u16 y,u16 fc, u16 bc, u8 num,u8 size,u8 mode)
 * @date       :2018-08-09 
 * @function   :Display a single English character
 * @parameters :x:the bebinning x coordinate of the Character display position
                y:the bebinning y coordinate of the Character display position
								fc:the color value of display character
								bc:the background color of display character
								num:the ascii code of display character(0~94)
								size:the size of display character
								mode:0-no overlying,1-overlying
 * @retvalue   :None
******************************************************************************/ 
void LCD_ShowChar(u16 x,u16 y,u16 fc, u16 bc, u8 num,u8 size,u8 mode)
{  
    u8 temp;
    u8 pos,t;
	u16 colortemp=POINT_COLOR;      
		   
	num=num-' ';//µÃµ½Æ«ÒÆºóµÄÖµ
	LCD_SetWindows(x,y,x+size/2-1,y+size-1);//ÉèÖÃµ¥¸öÎÄ×ÖÏÔÊ¾´°¿Ú
	if(!mode) //·Çµþ¼Ó·½Ê½
	{		
		for(pos=0;pos<size;pos++)
		{
			if(size==12)temp=asc2_1206[num][pos];//µ÷ÓÃ1206×ÖÌå
			else temp=asc2_1608[num][pos];		 //µ÷ÓÃ1608×ÖÌå
			for(t=0;t<size/2;t++)
		    {                 
		        if(temp&0x01)Lcd_WriteData_16Bit(fc); 
				else Lcd_WriteData_16Bit(bc); 
				temp>>=1; 
				
		    }
			
		}	
	}else//µþ¼Ó·½Ê½
	{
		for(pos=0;pos<size;pos++)
		{
			if(size==12)temp=asc2_1206[num][pos];//µ÷ÓÃ1206×ÖÌå
			else temp=asc2_1608[num][pos];		 //µ÷ÓÃ1608×ÖÌå
			for(t=0;t<size/2;t++)
		    {   
				POINT_COLOR=fc;              
		        if(temp&0x01)LCD_DrawPoint(x+t,y+pos);//»­Ò»¸öµã    
		        temp>>=1; 
		    }
		}
	}
	POINT_COLOR=colortemp;	
	LCD_SetWindows(0,0,lcddev.width-1,lcddev.height-1);//»Ö¸´´°¿ÚÎªÈ«ÆÁ    	   	 	  
}

/*****************************************************************************
 * @name       :void LCD_ShowString(u16 x,u16 y,u8 size,u8 *p,u8 mode)
 * @date       :2018-08-09 
 * @function   :Display English string
 * @parameters :x:the bebinning x coordinate of the English string
                y:the bebinning y coordinate of the English string
								p:the start address of the English string
								size:the size of display character
								mode:0-no overlying,1-overlying
 * @retvalue   :None
******************************************************************************/   	  
void LCD_ShowString(u16 x,u16 y,u8 size,u8 *p,u8 mode)
{         
    while((*p<='~')&&(*p>=' '))//ÅÐ¶ÏÊÇ²»ÊÇ·Ç·¨×Ö·û!
    {   
		if(x>(lcddev.width-1)||y>(lcddev.height-1)) 
		return;     
        LCD_ShowChar(x,y,POINT_COLOR,BACK_COLOR,*p,size,mode);
        x+=size/2;
        p++;
    }  
} 

/*****************************************************************************
 * @name       :u32 mypow(u8 m,u8 n)
 * @date       :2018-08-09 
 * @function   :get the nth power of m (internal call)
 * @parameters :m:the multiplier
                n:the power
 * @retvalue   :the nth power of m
******************************************************************************/ 
u32 mypow(u8 m,u8 n)
{
	u32 result=1;	 
	while(n--)result*=m;    
	return result;
}

/*****************************************************************************
 * @name       :void LCD_ShowNum(u16 x,u16 y,u32 num,u8 len,u8 size)
 * @date       :2018-08-09 
 * @function   :Display number
 * @parameters :x:the bebinning x coordinate of the number
                y:the bebinning y coordinate of the number
								num:the number(0~4294967295)
								len:the length of the display number
								size:the size of display number
 * @retvalue   :None
******************************************************************************/  			 
void LCD_ShowNum(u16 x,u16 y,u32 num,u8 len,u8 size)
{         	
	u8 t,temp;
	u8 enshow=0;						   
	for(t=0;t<len;t++)
	{
		temp=(num/mypow(10,len-t-1))%10;
		if(enshow==0&&t<(len-1))
		{
			if(temp==0)
			{
				LCD_ShowChar(x+(size/2)*t,y,POINT_COLOR,BACK_COLOR,' ',size,0);
				continue;
			}else enshow=1; 
		 	 
		}
	 	LCD_ShowChar(x+(size/2)*t,y,POINT_COLOR,BACK_COLOR,temp+'0',size,0); 
	}
} 

/*****************************************************************************
 * @name       :void GUI_DrawFont16(u16 x, u16 y, u16 fc, u16 bc, u8 *s,u8 mode)
 * @date       :2018-08-09 
 * @function   :Display a single 16x16 Chinese character
 * @parameters :x:the bebinning x coordinate of the Chinese character
                y:the bebinning y coordinate of the Chinese character
								fc:the color value of Chinese character
								bc:the background color of Chinese character
								s:the start address of the Chinese character
								mode:0-no overlying,1-overlying
 * @retvalue   :None
******************************************************************************/ 
void GUI_DrawFont16(u16 x, u16 y, u16 fc, u16 bc, u8 *s,u8 mode)
{
	u8 i,j;
	u16 k;
	u16 HZnum;
	u16 x0=x;
	HZnum=sizeof(tfont16)/sizeof(typFNT_GB16);	//×Ô¶¯Í³¼Æºº×ÖÊýÄ¿
	
			
	for (k=0;k<HZnum;k++) 
	{
	  if ((tfont16[k].Index[0]==*(s))&&(tfont16[k].Index[1]==*(s+1)))
	  { 	LCD_SetWindows(x,y,x+16-1,y+16-1);
		    for(i=0;i<16*2;i++)
		    {
				for(j=0;j<8;j++)
		    	{	
					if(!mode) //·Çµþ¼Ó·½Ê½
					{
						if(tfont16[k].Msk[i]&(0x80>>j))	Lcd_WriteData_16Bit(fc);
						else Lcd_WriteData_16Bit(bc);
					}
					else
					{
						POINT_COLOR=fc;
						if(tfont16[k].Msk[i]&(0x80>>j))	LCD_DrawPoint(x,y);//»­Ò»¸öµã
						x++;
						if((x-x0)==16)
						{
							x=x0;
							y++;
							break;
						}
					}

				}
				
			}
			
			
		}				  	
		continue;  //²éÕÒµ½¶ÔÓ¦µãÕó×Ö¿âÁ¢¼´ÍË³ö£¬·ÀÖ¹¶à¸öºº×ÖÖØ¸´È¡Ä£´øÀ´Ó°Ïì
	}

	LCD_SetWindows(0,0,lcddev.width-1,lcddev.height-1);//»Ö¸´´°¿ÚÎªÈ«ÆÁ  
} 

/*****************************************************************************
 * @name       :void GUI_DrawFont24(u16 x, u16 y, u16 fc, u16 bc, u8 *s,u8 mode)
 * @date       :2018-08-09 
 * @function   :Display a single 24x24 Chinese character
 * @parameters :x:the bebinning x coordinate of the Chinese character
                y:the bebinning y coordinate of the Chinese character
								fc:the color value of Chinese character
								bc:the background color of Chinese character
								s:the start address of the Chinese character
								mode:0-no overlying,1-overlying
 * @retvalue   :None
******************************************************************************/ 
void GUI_DrawFont24(u16 x, u16 y, u16 fc, u16 bc, u8 *s,u8 mode)
{
	u8 i,j;
	u16 k;
	u16 HZnum;
	u16 x0=x;
	HZnum=sizeof(tfont24)/sizeof(typFNT_GB24);	//×Ô¶¯Í³¼Æºº×ÖÊýÄ¿
		
			for (k=0;k<HZnum;k++) 
			{
			  if ((tfont24[k].Index[0]==*(s))&&(tfont24[k].Index[1]==*(s+1)))
			  { 	LCD_SetWindows(x,y,x+24-1,y+24-1);
				    for(i=0;i<24*3;i++)
				    {
							for(j=0;j<8;j++)
							{
								if(!mode) //·Çµþ¼Ó·½Ê½
								{
									if(tfont24[k].Msk[i]&(0x80>>j))	Lcd_WriteData_16Bit(fc);
									else Lcd_WriteData_16Bit(bc);
								}
							else
							{
								POINT_COLOR=fc;
								if(tfont24[k].Msk[i]&(0x80>>j))	LCD_DrawPoint(x,y);//»­Ò»¸öµã
								x++;
								if((x-x0)==24)
								{
									x=x0;
									y++;
									break;
								}
							}
						}
					}
					
					
				}				  	
				continue;  //²éÕÒµ½¶ÔÓ¦µãÕó×Ö¿âÁ¢¼´ÍË³ö£¬·ÀÖ¹¶à¸öºº×ÖÖØ¸´È¡Ä£´øÀ´Ó°Ïì
			}

	LCD_SetWindows(0,0,lcddev.width-1,lcddev.height-1);//»Ö¸´´°¿ÚÎªÈ«ÆÁ  
}

/*****************************************************************************
 * @name       :void GUI_DrawFont32(u16 x, u16 y, u16 fc, u16 bc, u8 *s,u8 mode)
 * @date       :2018-08-09 
 * @function   :Display a single 32x32 Chinese character
 * @parameters :x:the bebinning x coordinate of the Chinese character
                y:the bebinning y coordinate of the Chinese character
								fc:the color value of Chinese character
								bc:the background color of Chinese character
								s:the start address of the Chinese character
								mode:0-no overlying,1-overlying
 * @retvalue   :None
******************************************************************************/ 
void GUI_DrawFont32(u16 x, u16 y, u16 fc, u16 bc, u8 *s,u8 mode)
{
	u8 i,j;
	u16 k;
	u16 HZnum;
	u16 x0=x;
	HZnum=sizeof(tfont32)/sizeof(typFNT_GB32);	//×Ô¶¯Í³¼Æºº×ÖÊýÄ¿
	for (k=0;k<HZnum;k++) 
			{
			  if ((tfont32[k].Index[0]==*(s))&&(tfont32[k].Index[1]==*(s+1)))
			  { 	LCD_SetWindows(x,y,x+32-1,y+32-1);
				    for(i=0;i<32*4;i++)
				    {
						for(j=0;j<8;j++)
				    	{
							if(!mode) //·Çµþ¼Ó·½Ê½
							{
								if(tfont32[k].Msk[i]&(0x80>>j))	Lcd_WriteData_16Bit(fc);
								else Lcd_WriteData_16Bit(bc);
							}
							else
							{
								POINT_COLOR=fc;
								if(tfont32[k].Msk[i]&(0x80>>j))	LCD_DrawPoint(x,y);//»­Ò»¸öµã
								x++;
								if((x-x0)==32)
								{
									x=x0;
									y++;
									break;
								}
							}
						}
					}
					
					
				}				  	
				continue;  //²éÕÒµ½¶ÔÓ¦µãÕó×Ö¿âÁ¢¼´ÍË³ö£¬·ÀÖ¹¶à¸öºº×ÖÖØ¸´È¡Ä£´øÀ´Ó°Ïì
			}
	
	LCD_SetWindows(0,0,lcddev.width-1,lcddev.height-1);//»Ö¸´´°¿ÚÎªÈ«ÆÁ  
} 

/*****************************************************************************
 * @name       :void Show_Str(u16 x, u16 y, u16 fc, u16 bc, u8 *str,u8 size,u8 mode)
 * @date       :2018-08-09 
	 * @function   :Display Chinese and English strings
	 * @parameters :x:the bebinning x coordinate of the Chinese and English strings
									y:the bebinning y coordinate of the Chinese and English strings
									fc:the color value of Chinese and English strings
									bc:the background color of Chinese and English strings
									str:the start address of the Chinese and English strings
									size:the size of Chinese and English strings
									mode:0-no overlying,1-overlying
 * @retvalue   :None
******************************************************************************/	   		   
void Show_Str(u16 x, u16 y, u16 fc, u16 bc, u8 *str,u8 size,u8 mode)
{					
	u16 x0=x;							  	  
  	u8 bHz=0;     //×Ö·û»òÕßÖÐÎÄ 
    while(*str!=0)//Êý¾ÝÎ´½áÊø
    { 
        if(!bHz)
        {
			if(x>(lcddev.width-size/2)||y>(lcddev.height-size)) 
			return; 
	        if(*str>0x80)bHz=1;//ÖÐÎÄ 
	        else              //×Ö·û
	        {          
		        if(*str==0x0D)//»»ÐÐ·ûºÅ
		        {         
		            y+=size;
					x=x0;
		            str++; 
		        }  
		        else
				{
					if(size>16)//×Ö¿âÖÐÃ»ÓÐ¼¯³É12X24 16X32µÄÓ¢ÎÄ×ÖÌå,ÓÃ8X16´úÌæ
					{  
					LCD_ShowChar(x,y,fc,bc,*str,16,mode);
					x+=8; //×Ö·û,ÎªÈ«×ÖµÄÒ»°ë 
					}
					else
					{
					LCD_ShowChar(x,y,fc,bc,*str,size,mode);
					x+=size/2; //×Ö·û,ÎªÈ«×ÖµÄÒ»°ë 
					}
				} 
				str++; 
		        
	        }
        }else//ÖÐÎÄ 
        {   
			if(x>(lcddev.width-size)||y>(lcddev.height-size)) 
			return;  
            bHz=0;//ÓÐºº×Ö¿â    
			if(size==32)
			GUI_DrawFont32(x,y,fc,bc,str,mode);	 	
			else if(size==24)
			GUI_DrawFont24(x,y,fc,bc,str,mode);	
			else
			GUI_DrawFont16(x,y,fc,bc,str,mode);
				
	        str+=2; 
	        x+=size;//ÏÂÒ»¸öºº×ÖÆ«ÒÆ	    
        }						 
    }   
}

/*****************************************************************************
 * @name       :void Gui_StrCenter(u16 x, u16 y, u16 fc, u16 bc, u8 *str,u8 size,u8 mode)
 * @date       :2018-08-09 
 * @function   :Centered display of English and Chinese strings
 * @parameters :x:the bebinning x coordinate of the Chinese and English strings
                y:the bebinning y coordinate of the Chinese and English strings
								fc:the color value of Chinese and English strings
								bc:the background color of Chinese and English strings
								str:the start address of the Chinese and English strings
								size:the size of Chinese and English strings
								mode:0-no overlying,1-overlying
 * @retvalue   :None
* @ chec nang: Hien thi chính giua các chuoi tieng Anh và tieng Trung
* @parameters: 
		x: toa do bebinning x cua chuoi tieng Trung và tieng Anh
		y: toa do bebinning y cua chuoi tieng Trung và tieng Anh
		fc: giá tri màu cua chuoi tieng Trung và tieng Anh
		bc: màu nen cca chuoi tieng Trung và ti?ng Anh
		str: d?a ch? b?t d?u c?a chu?i ti?ng Trung và ti?ng Anh
		size: kích thu?c c?a chu?i ti?ng Trung và ti?ng Anh
		mode: 0-không nam trên, 1 ? trên
  * @retvalue: Không có 

*******************************************************************************/
void Gui_StrCenter(u16 x, u16 y, u16 fc, u16 bc, u8 *str,u8 size,u8 mode)
{
	u16 len=strlen((const char *)str);
	u16 x1=(lcddev.width-len*8)/2;
	Show_Str(x1,y,fc,bc,str,size,mode);
} 
 
/*****************************************************************************
 * @name       :void Gui_Drawbmp16(u16 x,u16 y,const unsigned char *p)
 * @date       :2018-08-09 
 * @function   :Display a 16-bit BMP image
 * @parameters :x:the bebinning x coordinate of the BMP image
                y:the bebinning y coordinate of the BMP image
								p:the start address of image array
 * @retvalue   :None
******************************************************************************/ 
void Gui_Drawbmp16(u16 x,u16 y,const unsigned char *p) //ÏÔÊ¾40*40 QQÍ¼Æ¬
{
  	int i; 
	unsigned char picH,picL; 
	LCD_SetWindows(x,y,x+40-1,y+49-1);// 70*85: chinh theo picxel cua image
	for(i=0;i<40*49;i++)  // 70*85: chinh theo picxel cua image
	{	
	 	picL=*(p+i*2);	//Êý¾ÝµÍÎ»ÔÚÇ°
		picH=*(p+i*2+1);				
		Lcd_WriteData_16Bit(picH<<8|picL);  						
	}	
	LCD_SetWindows(0,0,lcddev.width-1,lcddev.height-1);//»Ö¸´ÏÔÊ¾´°¿ÚÎªÈ«ÆÁ	
}

void Gui_DrawbmpUser(u16 x,u16 y, u16 picxelX, u16 picxelY ,const unsigned char *p) //ÏÔÊ¾40*40 QQÍ¼Æ¬
{
  int i; 
	unsigned char picH,picL; 
	LCD_SetWindows(x,y,x+picxelX-1,y+picxelY-1);// 70*85: chinh theo picxel cua image
	for(i=0;i<picxelX*picxelY;i++)  // 70*85: chinh theo picxel cua image
	{	
	 	picL=*(p+i*2);	//Êý¾ÝµÍÎ»ÔÚÇ°
		picH=*(p+i*2+1);				
		Lcd_WriteData_16Bit(picH<<8|picL);  						
	}	
	LCD_SetWindows(0,0,lcddev.width-1,lcddev.height-1);//»Ö¸´ÏÔÊ¾´°¿ÚÎªÈ«ÆÁ	
}

void Gui_bmp16(u16 x,u16 y,u16 a, u16 b, const unsigned char *p) //ÏÔÊ¾a*b QQÍ¼Æ¬
{
  	int i; 
	unsigned char picH,picL; 
	LCD_SetWindows(x,y,x+a-1,y+b);//´°¿ÚÉèÖÃ
    for(i=0;i<a*b;i++)
	{	
	 	picL=*(p+i*2);	//Êý¾ÝµÍÎ»ÔÚÇ°
		picH=*(p+i*2+1);				
		Lcd_WriteData_16Bit(picH<<8|picL);  						
	}	
	
	LCD_SetWindows(0,0,lcddev.width-1,lcddev.height);//»Ö¸´ÏÔÊ¾´°¿ÚÎªÈ«ÆÁ	
	
//	printf("\r\nwidth  =%d\r\n", lcddev.width-1);
//	printf("\r\nheight =%d\r\n", lcddev.height-1);
}

//void LCD_Textchar64(uint16_t x, uint16_t y, uint16_t back_color, uint16_t font_color, u8 ch, uint8_t font_size){
//	int i = 0, j = 0;
//	uint8_t temp = 0;
//	uint16_t size;
//	
//	LCD_SetWindows(x, y, x + font_size/2 - 1, y + font_size - 1);//(x,y,x+8-1,y+16-1)
//	ch-=' ';
//	//size = (font_size / 8 + ((font_size % 8) ? 1 : 0)) * (font_size / 2);
//	for(i=0;i<128;i++){
//		temp=_Text64[ch][i];//µ÷ÓÃ1206×ÖÌå
//		for(j=0;j<8;j++){                 
//			if(temp&0x80)Lcd_WriteData_16Bit(font_color); 
//			else Lcd_WriteData_16Bit(back_color); 
//			temp<<=1; 
//		}		
//	}
//}
/*
function - LCD_Textchar48:
+ font: 24x24 -> size: 48 
+ font: 
+ 
*/
void LCD_Textchar48(uint16_t x, uint16_t y, uint16_t back_color, uint16_t font_color, u8 ch, uint8_t font_size){
	int i = 0, j = 0;
	uint8_t temp = 0;
	uint16_t size;
	
	LCD_SetWindows(x, y, x + font_size/2 - 1, y + font_size - 1);//(x,y,x+8-1,y+16-1)
	ch-=' ';
	//size = (font_size / 8 + ((font_size % 8) ? 1 : 0)) * (font_size / 2);
	for(i=0;i<72;i++){
		temp=_font24x24[ch][i];//µ÷ÓÃ1206×ÖÌå
		for(j=0;j<8;j++){                 
			if(temp&0x80)Lcd_WriteData_16Bit(font_color); 
			else Lcd_WriteData_16Bit(back_color); 
			temp<<=1; 
		}		
	}
}
/*
function - LCD_Textchar33:
+ font: 08x16 -> size: 33 
+ font:
+ 
*/
void LCD_Textchar33(uint16_t x, uint16_t y, uint16_t back_color, uint16_t font_color, u8 ch, uint8_t font_size){
	int i = 0, j = 0;
	uint8_t temp = 0;
	uint16_t size;	
	LCD_SetWindows(x, y, x + font_size/2 - 1, y + font_size - 1);//(x,y,x+8-1,y+16-1)
	ch-=' ';
	for(i=0;i<32;i++){
		temp=_font08x16[ch][i];
		for(j=0;j<8;j++){                
			if(temp&0x80)Lcd_WriteData_16Bit(font_color); 
			else Lcd_WriteData_16Bit(back_color); 
			temp<<=1; 	
		}
	}	
}
/*
function - LCD_Textchar16:
+ font: 08x16 -> size: 16 
+ font: 
+ 
*/
void LCD_Textchar16(uint16_t x, uint16_t y, uint16_t back_color, uint16_t font_color, u8 ch, uint8_t font_size){
	int i = 0, j = 0;
	uint8_t temp = 0;
	uint16_t size;
	
	LCD_SetWindows(x, y, x + font_size/2 - 1, y + font_size - 1);//(x,y,x+8-1,y+16-1)
	ch-=' ';
	for(i=0;i<16;i++){
		temp=_font1608[ch][i];
		for(j=0;j<8;j++){                
			if(temp&0x80)Lcd_WriteData_16Bit(font_color); 
			else Lcd_WriteData_16Bit(back_color); 
			temp<<=1; 			
		}
	}
}

/*
function - LCD_Textchar32:
+ font: 12x16 -> size: 32 
+ font: in Dam
+ 
*/
void LCD_Textchar32(uint16_t x, uint16_t y, uint16_t back_color, uint16_t font_color, u8 ch, uint8_t font_size){
	int i = 0, j = 0;
	uint8_t temp = 0;
	uint16_t size;
	ch-=' ';
	LCD_SetWindows(x, y, x + font_size/2 - 1, y + font_size - 1);//(x,y,x+8-1,y+16-1)
	for(i=0;i<32;i++){
		temp=_font12x16B[ch][i];
		for(j=0;j<8;j++){                
			if(temp&0x80)Lcd_WriteData_16Bit(font_color); 
			else Lcd_WriteData_16Bit(back_color); 
			temp<<=1; 
		}		
	}
}

void LCD_TextStr(uint16_t x, uint16_t y, uint16_t back_color, uint16_t font_color, u8* str, uint8_t font_size){	
	while(*str!=NULL){	
		if(font_size == 32){ /*12x16*/
			LCD_Textchar32(x,y,back_color, font_color, *str, font_size);	
			
			if( *str == 'j' || *str == 'I' || *str == 'J' || *str == ' ' || *str == 'i' || *str == 'l'){
				x +=7; /* khoang cach giua 2 chu */
			}
			else if(*str == '.' || *str == ':' || *str == ';' || *str == '`' || *str == 39 || *str == ',' || *str == '!' ){
				x +=5;
			}
			else if((*str >= 65 && *str <= 90)  ){
				x +=10; /* khoang cach giua 2 chu hoa */
			}
			else if( *str == 'm' || *str == 'w' || *str == '@'){
				x +=12;
			}
			else{
				x +=9;
			}
			str++;
		}
	
	else if(font_size == 16){	
		LCD_Textchar16(x,y,back_color, font_color, *str, font_size);		
		if( *str == 'j' || *str == 'I' || *str == 'J' || *str == ' ' ){
				x +=5;
		}
		else if(*str == '.' || *str == ':' || *str == ';' || *str == '`' || *str == 39 || *str == ',' || *str == '!' || *str == 'i' || *str == 'l'){
			x +=3;
		}
		else if((*str >= 65 && *str <= 90) || *str == 'w' ){
			x +=9;
		}
		else{
			x +=8;
		}
		str++;
	}		
		
	else if(font_size == 33){
		LCD_Textchar33(x,y,back_color, font_color, *str, font_size);		
		if(*str == 'i' || *str == 'j' || *str == 'I' || *str == 'J' || *str == ' ' || *str == 'l'){
				x +=6;
		}
		else if(*str == '.' || *str == ':' || *str == ';' || *str == '`' || *str == 39 || *str == ',' || *str == '!'){
			x +=5;
		}
		else if(*str == 'm' || *str == 'w' || *str == 'M'){
			x +=16;
		}
		else if(*str >= 65 && *str <= 90){
			x +=14;
		}
		else{
			x +=11;
		}
		str++;
	}
	else if(font_size == 48){ /*24x24*/
			LCD_Textchar48(x,y,back_color, font_color, *str, font_size);
			if(*str == 'i' || *str == 'j' || *str == 'l' || *str == 'J'){
				x +=8;
			}
			else if(*str == 'I'){
				x +=12;
			}
			else if(*str == ' '){
				x+=8;
			}
			else if(*str == 'm' || *str == 'w' || *str == 'M'){
				x +=20;
			}
			else if(*str >= 65 && *str <= 90){
				x +=18;
			}
			else {
				x+=13;
			}				
			str++;
		}
	}
}
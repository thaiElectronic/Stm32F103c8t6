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
#ifndef __LCD_H
#define __LCD_H		
#include "sys.h"	 
#include "stdlib.h"

//LCDÖØÒª²ÎÊý¼¯
typedef struct  
{										    
	u16 width;			//LCD ¿í¶È
	u16 height;			//LCD ¸ß¶È
	u16 id;				  //LCD ID
	u8  dir;			  //ºáÆÁ»¹ÊÇÊúÆÁ¿ØÖÆ£º0£¬ÊúÆÁ£»1£¬ºáÆÁ¡£	
	u16	 wramcmd;		//¿ªÊ¼Ð´gramÖ¸Áî
	u16  setxcmd;		//ÉèÖÃx×ø±êÖ¸Áî
	u16  setycmd;		//ÉèÖÃy×ø±êÖ¸Áî	 
}_lcd_dev; 	

//LCD²ÎÊý
extern _lcd_dev lcddev;	//¹ÜÀíLCDÖØÒª²ÎÊý
/////////////////////////////////////ÓÃ»§ÅäÖÃÇø///////////////////////////////////	 
#define USE_HORIZONTAL  	 0//¶¨ÒåÒº¾§ÆÁË³Ê±ÕëÐý×ª·½Ïò 	0-0¶ÈÐý×ª£¬1-90¶ÈÐý×ª£¬2-180¶ÈÐý×ª£¬3-270¶ÈÐý×ª

//////////////////////////////////////////////////////////////////////////////////	  
//¶¨ÒåLCDµÄ³ß´ç
#define LCD_W 240
#define LCD_H 320

//TFTLCD²¿·ÖÍâÒªµ÷ÓÃµÄº¯Êý		   
extern u16  POINT_COLOR;//Ä¬ÈÏºìÉ«    
extern u16  BACK_COLOR; //±³¾°ÑÕÉ«.Ä¬ÈÏÎª°×É«

////////////////////////////////////////////////////////////////////
//-----------------LCD¶Ë¿Ú¶¨Òå---------------- 
#define GPIO_TYPE  GPIOB  //GPIO×éÀàÐÍ
//#define LED      9        //±³¹â¿ØÖÆÒý½Å        PB9
#define LCD_CS   9       //Æ¬Ñ¡Òý½Å            PB11
#define LCD_RS   8       //¼Ä´æÆ÷/Êý¾ÝÑ¡ÔñÒý½Å PB10 
#define LCD_RST  12       //¸´Î»Òý½Å            PB12


//QDtechÈ«ÏµÁÐÄ£¿é²ÉÓÃÁËÈý¼«¹Ü¿ØÖÆ±³¹âÁÁÃð£¬ÓÃ»§Ò²¿ÉÒÔ½ÓPWMµ÷½Ú±³¹âÁÁ¶È
//#define	LCD_LED PBout(LED) //LCD±³¹â    		 PB9
//Èç¹ûÊ¹ÓÃ¹Ù·½¿âº¯Êý¶¨ÒåÏÂÁÐµ×²ã£¬ËÙ¶È½«»áÏÂ½µµ½14Ö¡Ã¿Ãë£¬½¨Òé²ÉÓÃÎÒË¾ÍÆ¼ö·½·¨
//ÒÔÏÂIO¶¨ÒåÖ±½Ó²Ù×÷¼Ä´æÆ÷£¬¿ìËÙIO²Ù×÷£¬Ë¢ÆÁËÙÂÊ¿ÉÒÔ´ïµ½28Ö¡Ã¿Ãë£¡ 

//GPIOÖÃÎ»£¨À­¸ß£©
#define	LCD_CS_SET  GPIO_TYPE->BSRR=1<<LCD_CS    //Æ¬Ñ¡¶Ë¿Ú  	PB11
#define	LCD_RS_SET	GPIO_TYPE->BSRR=1<<LCD_RS    //Êý¾Ý/ÃüÁî  PB10	  
#define	LCD_RST_SET	GPIO_TYPE->BSRR=1<<LCD_RST   //¸´Î»			  PB12

//GPIO¸´Î»£¨À­µÍ£©							    
#define	LCD_CS_CLR  GPIO_TYPE->BRR=1<<LCD_CS     //Æ¬Ñ¡¶Ë¿Ú  	PB11
#define	LCD_RS_CLR	GPIO_TYPE->BRR=1<<LCD_RS     //Êý¾Ý/ÃüÁî  PB10	 
#define	LCD_RST_CLR	GPIO_TYPE->BRR=1<<LCD_RST    //¸´Î»			  PB12

//»­±ÊÑÕÉ«
#define WHITE       0xFFFF
#define BLACK      	0x0000	  
#define BLUE       	0x001F  
#define BRED        0XF81F
#define GRED 			 	0XFFE0
#define GBLUE			 	0X07FF
#define RED         0xF800
#define MAGENTA     0xF81F
#define GREEN       0x07E0
#define CYAN        0x7FFF
#define YELLOW      0xFFE0
#define BROWN 			0XBC40 //×ØÉ«
#define BRRED 			0XFC07 //×ØºìÉ«
#define GRAY  			0X8430 //»ÒÉ
#define DARKBLUE      	 0X01CF	//ÉîÀ¶É«
#define LIGHTBLUE      	 0X7D7C	//Ç³À¶É«  
#define GRAYBLUE       	 0X5458 //»ÒÀ¶É«
#define LIGHTGREEN     	0X841F //Ç³ÂÌÉ«
#define LIGHTGRAY     0XEF5B //Ç³»ÒÉ«(PANNEL)
#define LGRAY 			 		0XC618 //Ç³»ÒÉ«(PANNEL),´°Ìå±³¾°É«
#define LGRAYBLUE      	0XA651 //Ç³»ÒÀ¶É«(ÖÐ¼ä²ãÑÕÉ«)
#define LBBLUE          0X2B12 //Ç³×ØÀ¶É«(Ñ¡ÔñÌõÄ¿µÄ·´É«)
	    															  
void LCD_Init(void);
void LCD_DisplayOn(void);
void LCD_DisplayOff(void);
void LCD_Clear(u16 Color);	 
void LCD_SetCursor(u16 Xpos, u16 Ypos);
void LCD_DrawPoint(u16 x,u16 y);//»­µã
u16  LCD_ReadPoint(u16 x,u16 y); //¶Áµã
void LCD_DrawLine(u16 x1, u16 y1, u16 x2, u16 y2);
void LCD_DrawRectangle(u16 x1, u16 y1, u16 x2, u16 y2);		   
void LCD_SetWindows(u16 xStar, u16 yStar,u16 xEnd,u16 yEnd);

u16 LCD_RD_DATA(void);//¶ÁÈ¡LCDÊý¾Ý									    
void LCD_WriteReg(u8 LCD_Reg, u16 LCD_RegValue);
void LCD_WR_DATA(u8 data);
u16 LCD_ReadReg(u8 LCD_Reg);
void LCD_WriteRAM_Prepare(void);
void LCD_WriteRAM(u16 RGB_Code);
u16 LCD_ReadRAM(void);		   
u16 LCD_BGR2RGB(u16 c);
void LCD_SetParam(void);
void Lcd_WriteData_16Bit(u16 Data);
void LCD_direction(u8 direction );

//Èç¹ûÈÔÈ»¾õµÃËÙ¶È²»¹»¿ì£¬¿ÉÒÔÊ¹ÓÃÏÂÃæµÄºê¶¨Òå,Ìá¸ßËÙ¶È.
//×¢ÒâÒªÈ¥µôlcd.cÖÐvoid LCD_WR_DATA(u16 data)º¯Êý¶¨ÒåÅ¶
/*
#if LCD_USE8BIT_MODEL==1//Ê¹ÓÃ8Î»²¢ÐÐÊý¾Ý×ÜÏßÄ£Ê½
	#define LCD_WR_DATA(data){\
	LCD_RS_SET;\
	LCD_CS_CLR;\
	DATAOUT(data);\
	LCD_WR_CLR;\
	LCD_WR_SET;\
	DATAOUT(data<<8);\
	LCD_WR_CLR;\
	LCD_WR_SET;\
	LCD_CS_SET;\
	}
	#else//Ê¹ÓÃ16Î»²¢ÐÐÊý¾Ý×ÜÏßÄ£Ê½
	#define LCD_WR_DATA(data){\
	LCD_RS_SET;\
	LCD_CS_CLR;\
	DATAOUT(data);\
	LCD_WR_CLR;\
	LCD_WR_SET;\
	LCD_CS_SET;\
	} 	
#endif
*/
				  		 
#endif  
	 
	 




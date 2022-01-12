#include "system.h"
#include "Smart_lock_SD_Card.h"
#include <pic.h>
//#include "Image.h"



void sys_Init(void){
	SystemInit();//初始化RCC 设置系统主频为72MHZ
	delay_init(72);	
	LCD_Init();	 
	MSD0_SPI_Configuration();
//	SPI2_Init();
//	MFRC522_Init();
//	MSD0_SPI_Configuration();
}

void sys_Run(void){
//	Read_Images_SD_Card("MinhPhuong.bmp");
	Read_Images_SD_Card("HPBD.bmp");
	delay_ms(6000);
	Read_Images_SD_Card("HPBD.bmp");
	delay_ms(6000);
	Read_Images_SD_Card("HPBD1.bmp");
	delay_ms(6000);
	Read_Images_SD_Card("HPBD1.bmp");
	delay_ms(6000);
//	Read_Images_SD_Card("NguyenMinhPhuong_240x320_16bit_x1.bmp");
//	delay_ms(5000);
	Read_Images_SD_Card("MinhPhuong1_240x320_16bit.bmp");
	delay_ms(6000);
	Read_Images_SD_Card("MinhPhuong1_240x320_16bit.bmp");
	delay_ms(6000);
	Read_Images_SD_Card("MinhPhuong2_240x320_16bit.bmp");
	delay_ms(6000);
	Read_Images_SD_Card("MinhPhuong2_240x320_16bit.bmp");
	delay_ms(6000);
	Read_Images_SD_Card("MinhPhuong.bmp");
	delay_ms(6000);
		Read_Images_SD_Card("MinhPhuong.bmp");
	delay_ms(6000);

}


/*****************************************************************************
 * @name       :void SPI1_Init(void)	
 * @date       :2018-08-09 
 * @function   :Initialize the STM32 hardware SPI1
 * @parameters :None
 * @retvalue   :None
******************************************************************************/
void SPI1_Init(void)	
{
	SPI_InitTypeDef  SPI_InitStructure;
	GPIO_InitTypeDef GPIO_InitStructure;
	 
	//SPI1_Setup_GPIO
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA | RCC_APB2Periph_GPIOB | RCC_APB2Periph_AFIO, ENABLE); 
  //SPI1_SCK -> PA5 , SPI1_MISO -> PA6 , SPI1_MOSI ->	PA7	
  GPIO_InitStructure.GPIO_Pin 	= GPIO_Pin_5 | GPIO_Pin_6 | GPIO_Pin_7;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStructure.GPIO_Mode 	= GPIO_Mode_AF_PP;
  GPIO_Init(GPIOA, &GPIO_InitStructure);

	//SD_CS -> PB7 	
  GPIO_InitStructure.GPIO_Pin 	= GPIO_Pin_7;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStructure.GPIO_Mode 	= GPIO_Mode_Out_PP;
  GPIO_Init(GPIOB, &GPIO_InitStructure);  
	GPIO_SetBits(GPIOB,GPIO_Pin_7); // Card Disable  
	
	
	//SPI1_SetUp
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_SPI1, ENABLE);
	   
	SPI_InitStructure.SPI_Direction 		= SPI_Direction_2Lines_FullDuplex;
	SPI_InitStructure.SPI_Mode 					= SPI_Mode_Master;
	SPI_InitStructure.SPI_DataSize 			= SPI_DataSize_8b;
	SPI_InitStructure.SPI_CPOL 					= SPI_CPOL_Low;
	SPI_InitStructure.SPI_CPHA 					= SPI_CPHA_1Edge;
	SPI_InitStructure.SPI_NSS 					= SPI_NSS_Soft;
	SPI_InitStructure.SPI_BaudRatePrescaler = SPI_BaudRatePrescaler_8;
	SPI_InitStructure.SPI_FirstBit 			= SPI_FirstBit_MSB;
	SPI_InitStructure.SPI_CRCPolynomial = 7;
	SPI_Init(SPI1, &SPI_InitStructure);

	//Enable SPI1
	SPI_Cmd(SPI1, ENABLE);   
}

/*
ham Text_Center: su dung de viet can le giua trong pham vi chi dinh.
*/
void Text_Center(u16 x1, u16 y1, u16 x2, u16 y2, u16 fc, u16 bc, u8 *str, u8 size,u8 mode){
	int Width_x = x2-x1;
	int length_text = strlen((const char *)str);
	int Width_text = length_text*8;
	int X_text = (Width_x - Width_text)/2;
	int Y_text = ((y2-y1)-13)/2;
	Show_Str(X_text+x1,Y_text+y1,fc, bc, str, size, mode);
}

void Index(void){
// Top
	
	LCD_Fill(0,0,lcddev.width,51,LIGHTGRAY);// mau nen (0-20px);
	
	Text_Center(40,0,lcddev.width,30,BLACK,BLUE,"Posts & Telecommunications",16,1);
	Text_Center(40,0,lcddev.width,70,BLACK,BLUE,"Institule Of Technology",16,1);
//  Gui_StrCenter(40,2,WHITE,BLUE,"Posts & Telecommunications",16,1);//居中显示
//	Gui_StrCenter(40,18,WHITE,BLUE,"Institule Of Technology",24,1);//居中显示
// Centre
	LCD_Fill(0,51,lcddev.width,lcddev.height-20,WHITE);	
// Bottom
	LCD_Fill(0,lcddev.height-23,lcddev.width,lcddev.height,LIGHTGRAY);// mau nen (220-240px)
	Gui_StrCenter(0,lcddev.height-18,BLACK,BLUE,"PTIT LAB AI-PHOTONICS",16,1);//居中显示	
	Gui_DrawbmpUser(0,0,40,49,PTIT_logo40x49);
	LCD_Fill(41,0,42,49,RED);
	LCD_Fill(0,49,lcddev.width,50,BLUE);
	LCD_Fill(0,lcddev.height-25,lcddev.width,lcddev.height-24,BLUE);
	Show_Info(Image_THAI);
}

void Text_Center1(u16 x1, u16 y1, u16 x2, u16 y2, u16 fc, u16 bc, u8 *str, u8 size){
	int Width_x = x2-x1;
	int length_text = strlen((const char *)str);
	int Width_text = length_text*8;
	int X_text = (Width_x - Width_text)/2;
	int Y_text = ((y2-y1)-13)/2;
	LCD_TextStr(X_text+x1,Y_text+y1,fc, bc, str, size);
}

void Index1(void){
// Top
	
	LCD_Fill(0,0,lcddev.width,51,LIGHTGRAY);// mau nen (0-20px);
	
	LCD_TextStr(45,0,LIGHTGRAY,BLUE,"Posts Telecommunications",32);
	Text_Center1(0,0,lcddev.width,70,LIGHTGRAY,BLUE,"Institule Of Technology",32);
//  Gui_StrCenter(40,2,WHITE,BLUE,"Posts & Telecommunications",16,1);//居中显示
//	Gui_StrCenter(40,18,WHITE,BLUE,"Institule Of Technology",24,1);//居中显示
// Centre
	LCD_Fill(0,51,lcddev.width,lcddev.height-20,WHITE);	
// Bottom
	LCD_Fill(0,lcddev.height-23,lcddev.width,lcddev.height,LIGHTGRAY);// mau nen (220-240px)
	Gui_StrCenter(0,lcddev.height-18,BLACK,BLUE,"PTIT LAB AI-PHOTONICS",16,1);//居中显示	
	Gui_DrawbmpUser(0,0,40,49,PTIT_logo40x49);
	LCD_Fill(41,0,42,49,RED);
	LCD_Fill(0,49,lcddev.width,50,BLUE);
	LCD_Fill(0,lcddev.height-25,lcddev.width,lcddev.height-24,BLUE);
	Show_Info(Image_THAI);
}

void Show_Info(const unsigned char *image){
	LCD_DrawRectangle(9,64,80,165);// boder for image size: 70x100
	Gui_DrawbmpUser(10,65,70,100,image);
	Show_Str(35,170,BLUE,BLUE,"MSV",16,1);
	Show_Str(5,188,RED,BLUE,"B18DCDT230",16,1);
	Show_Str(150,60,RED,BLUE,"STUDENT CARD",16,1);
	Show_Str(100,85,BLUE,BLUE, "Full Name    : Do Van Thai",16,1);
	Show_Str(100,105,BLUE,BLUE,"Gender       : Male",16,1);
	Show_Str(100,125,BLUE,BLUE,"Date of Birth: 22/05/2000",16,1);
	Show_Str(100,145,BLUE,BLUE,"ID Card      : a29399a49",16,1);
	Show_Str(100,165,BLUE,BLUE,"Class        : D18CQDT02",16,1);
}

void main_test(void){
//	LCD_direction(USE_HORIZONTAL);
	Gui_StrCenter(0,30+15,RED,BLUE,"Phu dung som no",16,1);//居中显示
	Gui_StrCenter(0,60+15,RED,BLUE,"toi lai tan,",16,1);//居中显示	
	Gui_StrCenter(0,90+15,BLUE,BLUE,"Long nguoi de doi ",16,1);//居中显示
	Gui_StrCenter(0,120+15,BLUE,BLUE,"cung nhu hoa,",16,1);//居中显示
	Gui_StrCenter(0,150+15,RED,BLUE,"Nguyen the suot kiep,",16,1);
	Gui_StrCenter(0,180+15,RED,BLUE,"luon chung thuy,",16,1);
	Gui_StrCenter(0,210+15,BLUE,BLUE,"May ai giu duoc",16,1);//居中显示
	Gui_StrCenter(0,240+15,BLUE,BLUE,"den cuoi doi,",16,1);//居中显示
//	delay_ms(10000);
}

void Box_text(void){
	int i;
//	Interface_90();
	for(i = 0; i < 2; i++){
		POINT_COLOR = RED;
		LCD_Fill(lcddev.width/2-115,lcddev.height/2-40+(i*45),lcddev.width/2-115+70,lcddev.height/2-50+40+(i*45),0xEEEEEE);
		LCD_DrawRectangle(lcddev.width/2-115,lcddev.height/2-40+(i*45),lcddev.width/2-115+70,lcddev.height/2-50+40+(i*45)); 
		
		POINT_COLOR= RED;	
		LCD_Fill(lcddev.width/2-35,lcddev.height/2-40+(i*45),lcddev.width/2-35+150,lcddev.height/2-50+40+(i*45),WHITE); 
		LCD_DrawRectangle(lcddev.width/2-35,lcddev.height/2-40+(i*45),lcddev.width/2-35+150,lcddev.height/2-50+40+(i*45)); 		
		if(i == 0){
			Text_Center(lcddev.width/2-115,lcddev.height/2-40+(i*45),lcddev.width/2-115+70,lcddev.height/2-50+40+(i*45),BLUE,YELLOW,"ID",32,1);
//			Text_Center(lcddev.width/2-35,lcddev.height/2-40+(i*45),lcddev.width/2-35+150,lcddev.height/2-50+40+(i*45),BLUE,YELLOW,(u8*)szBuff,16,1);
		} 
		else if(i == 1){
			Text_Center(lcddev.width/2-115,lcddev.height/2-40+(i*45),lcddev.width/2-115+70,lcddev.height/2-50+40+(i*45),BLUE,YELLOW,"USER",32,1);
//			Text_Center(lcddev.width/2-35,lcddev.height/2-40+(i*45),lcddev.width/2-35+150,lcddev.height/2-50+40+(i*45),BLUE,YELLOW,"DO VAN THAI",16,1);
		}	
	}
}

/**************************************************************************/
// test font24x24: size = 32
void Test_font24x24(void){
		LCD_TextStr(0,30,WHITE,BLUE,"ptit",32);
		LCD_TextStr(0,60,WHITE,BLUE,"PTIT",32);
}

/*
function - test_font_user: test cac font 16,32,33,48
*/
void Test_font_user(void){
	LCD_TextStr(0,0,WHITE,BLUE,"Do Van Thai",16);
	LCD_TextStr(0,30,WHITE,BLUE,"Do Van Thai",32);	
	LCD_TextStr(0,60,WHITE,BROWN,"Do Van Thai",33);
	LCD_TextStr(0,90,WHITE,RED,"Do Van Thai",48);
}
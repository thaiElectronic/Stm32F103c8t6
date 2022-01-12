#include "stm32f10x.h"                  // Device header
#include "stm32f10x_gpio.h"             // Keil::Device:StdPeriph Drivers:GPIO
#include "stm32f10x_rcc.h"              // Keil::Device:StdPeriph Drivers:RCC
#include "stm32f10x_spi.h"              // Keil::Device:StdPeriph Drivers:SPI
#include "stm32f10x_tim.h"              // Keil::Device:StdPeriph Drivers:TIM
#include "ILI9341_Gui.h"
#include "ILI9341_Driver.h"
#include "ILI9341_Define.h"
#include "touchscreen.h"
#include "delay_sys.h"
#include "stdio.h"

u16 ColorTab[5]={RED,GREEN,BLUE,YELLOW,MAGENTA};
void Test_FillRec(void){
	u8 i=0;
	TFT_Gui_Fill(0,20,ili_dev.width,ili_dev.height-20,WHITE);
	for(i=0; i<5; i++){
		POINT_COLOR = ColorTab[i];
		TFT_DrawRectangle(ili_dev.width/2-80+(i*15),ili_dev.height/2-80+(i*15),ili_dev.width/2-80+(i*15)+60,ili_dev.height/2-80+(i*15)+60); 
	}
	Delay_ms(1500);	
	TFT_Gui_Fill(0,20,ili_dev.width,ili_dev.height-20,WHITE); 
	for (i=0; i<5; i++){
		POINT_COLOR = ColorTab[i];
		TFT_Gui_Fill(ili_dev.width/2-80+(i*15),ili_dev.height/2-80+(i*15),ili_dev.width/2-80+(i*15)+60,ili_dev.height/2-80+(i*15)+60,POINT_COLOR); 
	}
	Delay_ms(1500);
}

void Test_Fill(void){
	TFT_Gui_Fill(0,0,ili_dev.width,ili_dev.height,WHITE);
	Delay_ms(1000);
	TFT_Gui_Fill(0,0,ili_dev.width,ili_dev.height,RED);
	Delay_ms(1000);
	TFT_Gui_Fill(0,0,ili_dev.width,ili_dev.height,GREEN);
	Delay_ms(1000);
	TFT_Gui_Fill(0,0,ili_dev.width,ili_dev.height,BLUE);
}

void Test_Circle(void){
	u8 i=0;
	TFT_Gui_Fill(0,20,ili_dev.width,ili_dev.height-20,WHITE);
	for (i=0; i<5; i++){  
		TFT_Gui_Circle(ili_dev.width/2-80+(i*25),ili_dev.height/2-50+(i*25),ColorTab[i],30,0);
	}
	Delay_ms(1500);	
	TFT_Gui_Fill(0,20,ili_dev.width,ili_dev.height-20,WHITE); 
	for (i=0; i<5; i++){ 
		TFT_Gui_Circle(ili_dev.width/2-80+(i*25),ili_dev.height/2-50+(i*25),ColorTab[i],30,1);
	}
	Delay_ms(1500);
	
}

void Test_Triangle(void){
	u8 i=0;
	TFT_Gui_Fill(0,20,ili_dev.width,ili_dev.height-20,WHITE);
	for(i=0;i<5;i++){
		POINT_COLOR=ColorTab[i];
		TFT_Gui_Draw_Triangel(ili_dev.width/2-80+(i*20),ili_dev.height/2-20+(i*15),ili_dev.width/2-50-1+(i*20),ili_dev.height/2-20-52-1+(i*15),ili_dev.width/2-20-1+(i*20),ili_dev.height/2-20+(i*15));
	}
	Delay_ms(1500);	
	TFT_Gui_Fill(0,20,ili_dev.width,ili_dev.height-20,WHITE); 
	for(i=0;i<5;i++){
		POINT_COLOR=ColorTab[i];
		ILI9431_Gui_Fill_Triangel(ili_dev.width/2-80+(i*20),ili_dev.height/2-20+(i*15),ili_dev.width/2-50-1+(i*20),ili_dev.height/2-20-52-1+(i*15),ili_dev.width/2-20-1+(i*20),ili_dev.height/2-20+(i*15));
	}
	Delay_ms(1500);
}

void Test_font_Char(void){
//	TFT_Show_6x8_char(10,10,BLACK,WHITE,'T',1);
	TFT_Show_6x12_char(10,20,BLACK,WHITE,'A',1);
	TFT_Show_8x16_char(10,40,BLACK,WHITE,'A',1);
	TFT_Show_12x24_char(20,60,BLACK,WHITE,'A',1);
	TFT_Show_16x32_char(50,90,BLACK,YELLOW,'A',0);
	TFT_Show_24x48_char(20,120,BLACK,YELLOW,'A',0);
}

void Test_Font_String(void){ // In Thuong
//	TFT_Print(10,10,BLACK,WHITE, 8,"Thai Salem",1);
	TFT_Print(10,20,BLACK,WHITE,12,"Thai Salem",1);
	TFT_Print(10,40,BLACK,WHITE,16,"Thai Salem",1);
	TFT_Print(10,60,BLACK,WHITE,24,"Thai Salem",1);
	TFT_Print(10,90,BLACK,WHITE,48,"Thai Salem",1);
	Delay_ms(1000);
}

void Test_Font_String_Bold(void){ // In Dam
	TFT_Print_Bold(20,20,BLACK,WHITE,16,"Thai MCU",1);
	TFT_Print_Bold(20,50,BLACK,WHITE,24,"Thai Salem",1);
	TFT_Print_Bold(20,70,BLACK,WHITE,32,"22/05/2000",1);
}

void Test_Print_Num(void){
	TFT_Print_Num(100,100,BLACK,YELLOW,32,1,220500,6,1); // IN Dam
	TFT_Print_Num(130,130,BLACK,YELLOW,24,0,60700,5,1); // In Thuong
}

void Test_Main(void){
	Test_Fill();
	Delay_ms(1000);
	Test_FillRec();
	Delay_ms(1000);
	Test_Triangle();
	Delay_ms(1000);
	Test_Circle();
	Delay_ms(1000);
	TFT_Clear(WHITE);
	Test_font_Char();
	Delay_ms(3000);
	TFT_Clear(WHITE);
	Test_Font_String();
	Delay_ms(3000);
	TFT_Clear(WHITE);
	Test_Font_String_Bold();
	Delay_ms(3000);
	TFT_Clear(WHITE);
	Test_Print_Num();
	Delay_ms(3000);
	TFT_Clear(WHITE);
}

void Button(void){
	POINT_COLOR = RED;
	TFT_DrawRectangle(20,50,80,110); 
	TFT_Gui_Fill(20,50,80,110,BLUE);
	TFT_Print_Center(20,50,80,110,BLACK,BLUE,32,BOLD,"ON",1);
	POINT_COLOR = BLUE;
	TFT_DrawRectangle(160,50,220,110); 
	TFT_Gui_Fill(160,50,220,110,RED);
	TFT_Print_Center(160,50,220,110,BLACK,BLUE,32,BOLD,"OFF",1);
	Delay_ms(1);
}


void SYS_Init(void){
	SystemInit();
	Delay_init(72);
	TFT_Init();	
	touchInit();
	TFT_Gui_Fill(0,0,240,320,WHITE);
	Button();
}

char counter_buff[30];
uint16_t x_pos = 0;
uint16_t y_pos = 0;				
uint16_t position_array[2];	
void SYS_Run(void){
	

	if(TP_Touchpad_Pressed()){				
		if(TP_Read_Coordinates(position_array) == TOUCHPAD_DATA_OK){
			x_pos = position_array[0];
			y_pos = position_array[1];		
				/* Hien thi vi tri cam ung */			
//			sprintf(counter_buff, "POS X: %.3d", x_pos);						
//			TFT_Print(10, 80, BLACK, WHITE, 16, (char*)counter_buff, 1);					
//			sprintf(counter_buff, "POS Y: %.3d", y_pos);						
//			TFT_Print(10, 120, BLACK, WHITE, 16, (char*)counter_buff, 1);		
		}
	}
	if((x_pos > 20 && x_pos < 80) && (y_pos > 50 && y_pos < 110)){
		TFT_Clear_Pos(0, 200, 240, 280,WHITE);
		TFT_Print_Center(0, 200, 240, 270,  BLACK, WHITE, 24, NORMAL, "Do Van Thai", 1);
	}	
	else if((x_pos > 160 && x_pos < 220) && (y_pos > 50 && y_pos < 110)){
		TFT_Clear_Pos(0, 200, 240, 280,WHITE);
		TFT_Print_Center(0, 200, 240, 270,  BLACK, WHITE, 24, NORMAL, "Vu Thi Thu Ha", 1);
	}
	x_pos = y_pos = 0;
}


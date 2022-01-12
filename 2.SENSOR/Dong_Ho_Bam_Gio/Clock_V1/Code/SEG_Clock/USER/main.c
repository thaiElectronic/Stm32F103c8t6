#include "stm32f10x.h"                  // Device header
#include "stm32f10x_gpio.h"             // Keil::Device:StdPeriph Drivers:GPIO
#include "stm32f10x_rcc.h"              // Keil::Device:StdPeriph Drivers:RCC
#include "stm32f10x_tim.h"              // Keil::Device:StdPeriph Drivers:TIM
#include "stdio.h"
#include "string.h"
#include "debug.h"

unsigned int Cnt = 0;
unsigned int Sec = 0;
unsigned int Led7_Font[10]= {0xc0,0xf9,0xa4,0xb0,0x99,0x92,0x82,0xf8,0x80,0x90};// Ma Anode chung
int Flag = 0;
int Stop_New = 1, Stop_Old = 1;
int Start_New = 1, Start_Old = 1;
int Rst_New = 1, Rst_Old = 1;

void SEG_Config(void);// cau hinh chan du lieu: a,b,c,d,...,dp
void SEG_control(void); // cau hinh chan dieu khien
void SEG_Disp(void);
void timer_Init(void);
void Delay_ms(unsigned int _time);
void Button_Config(void);
void Button_Stop(void);
void Button_Start(void);

int main(){
	SEG_Config();
	SEG_control();
	Button_Config();
	USARTx_Init();
	timer_Init();
	TIM_ITConfig(TIM2, TIM_IT_Update, DISABLE);
	TIM_Cmd(TIM2,DISABLE);
	while(1){
		SEG_Disp();
	}
}

void Delay_ms(unsigned int _time){
	volatile unsigned int i,j;
	for(i = 0; i < _time; i++){
		for(j = 0; j < 601; j++){}
	}
}

// cau hinh chan ma hoa led
void SEG_Config(void){	
	GPIO_InitTypeDef seg_init;
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
	seg_init.GPIO_Mode = GPIO_Mode_Out_PP;
	seg_init.GPIO_Speed = GPIO_Speed_50MHz;
	seg_init.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_1 |GPIO_Pin_2 | GPIO_Pin_3 | 
											GPIO_Pin_4 | GPIO_Pin_5 | GPIO_Pin_6 | GPIO_Pin_7;
	GPIO_Init(GPIOA,&seg_init);	
	GPIOA->ODR = 0xff;
}

// cau hinh chan dieu khien.
void SEG_control(void){
	GPIO_InitTypeDef seg_control;
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
	seg_control.GPIO_Mode = GPIO_Mode_Out_PP;
	seg_control.GPIO_Speed = GPIO_Speed_50MHz;
	seg_control.GPIO_Pin = GPIO_Pin_12 | GPIO_Pin_13 |GPIO_Pin_14 | GPIO_Pin_15;
	GPIO_Init(GPIOB,&seg_control);
}

void Button_Config(void){
	GPIO_InitTypeDef button;
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
	GPIO_PinRemapConfig(GPIO_Remap_SWJ_JTAGDisable, ENABLE);
	button.GPIO_Mode = GPIO_Mode_IPU;
	button.GPIO_Speed = GPIO_Speed_50MHz;
	button.GPIO_Pin = GPIO_Pin_3 | GPIO_Pin_4 | GPIO_Pin_5;
	GPIO_Init(GPIOB,&button);
	GPIO_Write(GPIOB, 0xff);
}

void Button_Start(void){
	Start_Old = Start_New;
	Start_New = GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_11);	
	if(Start_Old == 1 && Start_New == 0){
		printf("start\n");
		TIM_ITConfig(TIM2, TIM_IT_Update, ENABLE);
		TIM_Cmd(TIM2,ENABLE);
	} 
}

void Button_Stop(void){
	Stop_Old = Stop_New;
	Stop_New = GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_12);	
	if(Stop_Old == 1 && Stop_New == 0){
		printf("stop\n");
		TIM_ITConfig(TIM2, TIM_IT_Update, DISABLE);
		TIM_Cmd(TIM2,DISABLE);
	}
}

void Button_Rst(void){
	Rst_Old = Rst_New;
	Rst_New = GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_15);	
	if(Rst_Old == 1 && Rst_New == 0){
		printf("rst\n");
		Cnt = 0;
		Sec = 0;
		TIM_ITConfig(TIM2, TIM_IT_Update, DISABLE);
		TIM_Cmd(TIM2,DISABLE);
	} 
}

void SEG_Disp(void){
	Button_Stop();
	Button_Start();
	Button_Rst();
	if(Cnt==100){
		Sec++;
		if(Sec==60){ 
			Sec = 0;
			Cnt = 0;
		}
		Cnt = 0;
	}
	// hien thi hang don vi cua tich tac
	GPIO_ResetBits(GPIOB, GPIO_Pin_15);
	GPIO_Write(GPIOA,Led7_Font[Cnt%10]);
	Delay_ms(1);
	GPIO_SetBits(GPIOB, GPIO_Pin_15);
	
	// hien thi hang chuc vi cua tich tac
	GPIO_ResetBits(GPIOB, GPIO_Pin_14);
	GPIO_Write(GPIOA,Led7_Font[Cnt/10]);
	Delay_ms(1);
	GPIO_SetBits(GPIOB, GPIO_Pin_14);
	
	// hien thi hang don vi cua giay
	GPIO_ResetBits(GPIOB, GPIO_Pin_13);
	GPIO_Write(GPIOA,Led7_Font[Sec%10]);
	GPIO_WriteBit(GPIOA,GPIO_Pin_7,Bit_RESET);
	Delay_ms(1);
	GPIO_SetBits(GPIOB, GPIO_Pin_13);
	
	// hien thi hang chuc vi cua giay
	GPIO_ResetBits(GPIOB, GPIO_Pin_12);
	GPIO_Write(GPIOA,Led7_Font[Sec/10]);
	Delay_ms(1);
	GPIO_SetBits(GPIOB, GPIO_Pin_12);
}

/*
function: 10ms
*/
void timer_Init(void){
	TIM_TimeBaseInitTypeDef timer_init;
	
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);
	
	timer_init.TIM_CounterMode = TIM_CounterMode_Up;
	timer_init.TIM_Period = 1000 - 1;
	timer_init.TIM_Prescaler = 80- 1;
	timer_init.TIM_RepetitionCounter = 0;
	TIM_TimeBaseInit(TIM2,&timer_init);
	TIM_ClearFlag(TIM2,TIM_FLAG_Update);
	NVIC_EnableIRQ(TIM2_IRQn);
}

void TIM2_IRQHandler(){
	if(TIM_GetITStatus(TIM2, TIM_IT_Update)!=RESET){		
		Cnt++;
	}	
	TIM_ClearITPendingBit(TIM2,TIM_IT_Update);
}

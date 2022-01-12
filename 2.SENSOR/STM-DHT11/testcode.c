#include "stm32f10x.h"      
#include "stdio.h"
#include "gpio_ec.h"
#include "ecdelay.h"
#include "usart_ec.h"
#include "LCD.h"
#include "mcu-adc.h"

int i = 0, j = 0;
int value = 0, value1 = 0, voltage = 0, Res = 0;
int temp = 0;
unsigned char arr[50];
char str[50];
uint32_t ADC_Value = 0;

unsigned char Character1[8]={0x07, 0x05, 0x07, 0x00, 0x00, 0x00, 0x00, 0x00}; // ki hieu do
unsigned char Character2[8] = {0x00, 0x0e, 0x11, 0x11, 0x11, 0x0A, 0x1b, 0x00 }; // ki hieu om

void delay(unsigned int time){
	unsigned int i,j;
	for(i = 0; i<time; i++){
		for(j = 0; j<0x2aff; j++);
	}
}

int Map(int x, int in_min, int in_max, int out_min, int out_max){
	return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}
unsigned int DMA_ADC = 0;

void DMA_Config(){
	DMA_InitTypeDef dma;
	ADC_InitTypeDef adc;
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE);
	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_DMA1, ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1, ENABLE);
	
	adc.ADC_ContinuousConvMode = ENABLE;
	adc.ADC_DataAlign = ADC_DataAlign_Right;
	adc.ADC_ExternalTrigConv = ADC_ExternalTrigConv_None;
	adc.ADC_ScanConvMode = DISABLE;
	adc.ADC_Mode = ADC_Mode_Independent;
	adc.ADC_NbrOfChannel = 1;
	
	ADC_Init(ADC1,&adc);
	
	ADC_RegularChannelConfig(ADC1, ADC_Channel_1, 1, ADC_SampleTime_55Cycles5);
	
	ADC_TempSensorVrefintCmd(ENABLE);
	
	DMA_DeInit(DMA1_Channel1);
	//chon dia chi ngoai vi la di chi cua thanh ghi ADC_CR
	dma.DMA_PeripheralBaseAddr =((uint32_t)0x4001244C);
	//chon di chi bo nho la di chi cuar bien DMA_ADC;
	dma.DMA_MemoryBaseAddr = (uint32_t)&DMA_ADC;
	//huong truyen tu ngoai vi den bo nho;
	dma.DMA_DIR = DMA_DIR_PeripheralSRC;
	//so luong goi du lieu can truyen la 1;
	dma.DMA_BufferSize = 1;
	// khong tang dia chi ngoai vi do ket qua chuyen doi
	// adc duoc luu co dinh tai ADC1_DR
	dma.DMA_PeripheralInc = DMA_PeripheralInc_Disable;
	//tang dia chi bo nho do phai luu 1;
	//phan tu cua mang DMA_ADC
	dma.DMA_MemoryInc = DMA_MemoryInc_Disable;
	//kich thuoc du lieu can truyen cua ngoai vi laf 16 bit
	dma.DMA_PeripheralDataSize = DMA_PeripheralDataSize_HalfWord;
	// kich thuoc du lieu can nhan cua bo nho la 16 bit
	dma.DMA_MemoryDataSize = DMA_MemoryDataSize_HalfWord;
	//chon che do xoay vong.
	dma.DMA_Mode = DMA_Mode_Circular;
	//che do uu tien cao
	dma.DMA_Priority = DMA_Priority_High;	
	//tat che do truyen tu bo nho den bo nho
	dma.DMA_M2M = DMA_M2M_Disable;
	
	DMA_Init(DMA1_Channel1,&dma);

	DMA_Cmd(DMA1_Channel1, ENABLE);

	ADC_DMACmd(ADC1,ENABLE);
	
	ADC_Cmd(ADC1,ENABLE);
	ADC_ResetCalibration(ADC1);
	while(ADC_GetCalibrationStatus(ADC1));
	ADC_StartCalibration(ADC1);
	while(ADC_GetCalibrationStatus(ADC1));
	
	ADC_SoftwareStartConvCmd(ADC1, ENABLE);
}


int main(){
	//ADCx_Init(ADC1, ADC_Channel_1);// pa7
	
	DMA_Config();
	
	pinMode(PA1, AN_INPUT);
	USARTx_Init(USART1,RCC_APB2Periph_USART1,9600);
	LCD_Init();

	Delay_ms(100);
	while(1){		
		/*LCD*/	
		value = (int)DMA_ADC *(3.3/4096);
		printf("dien tro: %d\n",value);
		Delay_ms(1000);
		
	}
}
#include "stm32f10x.h"                  // Device header
#include "stm32f10x_gpio.h"             // Keil::Device:StdPeriph Drivers:GPIO
#include "stm32f10x_rcc.h"              // Keil::Device:StdPeriph Drivers:RCC
#include "stm32f10x_tim.h"              // Keil::Device:StdPeriph Drivers:TIM

void Delay_ms(uint16_t _time);

void pwm_Init(void);
void pin_pwm_Init(void);

/*
TIM1: CH1 - PA8
			CH2 - PA9
			CH3 - PA10
			CH4 - PA11

TIM2: CH1 - PA0
			CH2 - PA1
			CH3 - PA2
			CH4 - PA3

TIM3: CH1 - PA6
			CH2 - PA7
			CH3 - PB0
			CH4 - PB1
			
TIM4: CH1 - PB6
			CH2 - PB7
			CH3 - PB8
			CH4 - PB9
*/

int main(){
	pwm_Init();	
	while(1){
		TIM2->CCR4 = 500; 	// 0.5ms: 0 do
		Delay_ms(1000);				
		TIM2->CCR4 = 1500; 	// 1.5ms	: 90 do
		Delay_ms(1000);
	}
}


void Delay_ms(uint16_t _time){
	uint16_t i,j;
	for(i = 0; i < _time; i++){
		for(j = 0; j < 0x2AFF; j++);
	}
}

void pin_pwm_Init(void){
	RCC->APB2ENR = 0x05;
	GPIOA->CRL 	 = 0xB000;
}

void pwm_Init(void){
	
	pin_pwm_Init();
	RCC->APB2ENR = 0x01;
	RCC->APB1ENR = 0x01;	
	TIM2->ARR = 0x4E1F;
	TIM2->PSC = 0x47;
	TIM2->CCMR1 = 0x6060;
	TIM2->CCMR2 = 0x6060;
	TIM2->CR1 = 0x01;
	TIM2->EGR = 0x01;
	TIM2->CCER = 0x1111;
}



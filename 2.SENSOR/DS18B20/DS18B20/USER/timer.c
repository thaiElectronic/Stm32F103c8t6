#include "timer.h"

volatile char vrvc_Stt = 0;


void TIMER2_Config(){
	TIM_TimeBaseInitTypeDef TIMER;
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);
	TIMER.TIM_CounterMode = TIM_CounterMode_Up;
	TIMER.TIM_Period = 999;
	TIMER.TIM_ClockDivision = 0;
	TIMER.TIM_RepetitionCounter = 0;
	TIMER.TIM_Prescaler = 71;	
	TIM_TimeBaseInit(TIM2,&TIMER);
	TIM_ClearFlag(TIM2,TIM_FLAG_Update);
	TIM_ITConfig(TIM2,TIM_IT_Update,ENABLE);
	NVIC_EnableIRQ(TIM2_IRQn);
	TIM_Cmd(TIM2,ENABLE);
}

void TIM2_IRQHandler(){
	if(TIM_GetITStatus(TIM2, TIM_IT_Update)!=RESET){		
	//	vrvc_SttBlink =! vrvc_SttBlink;
	//	GPIO_WriteBit(GPIOB,GPIO_Pin_6,vrvc_SttBlink);
		vrvc_Stt = !vrvc_Stt;
	}
	TIM_ClearITPendingBit(TIM2,TIM_IT_Update);
}

void BTN_Setup(){
	pinMode(PB11,INPUT_PULLUP);
}

/*
function: 0.5s
*/
void TIMER4_Config(){
	TIM_TimeBaseInitTypeDef TIMER;
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4, ENABLE);
	TIMER.TIM_CounterMode = TIM_CounterMode_Up;
	TIMER.TIM_Period = 9999;
	TIMER.TIM_ClockDivision = 0;
	TIMER.TIM_RepetitionCounter = 0;
	TIMER.TIM_Prescaler = 3599;	
	TIM_TimeBaseInit(TIM4,&TIMER);
	TIM_ClearFlag(TIM4,TIM_FLAG_Update);
	TIM_ITConfig(TIM4,TIM_IT_Update,ENABLE);
	NVIC_EnableIRQ(TIM4_IRQn);
	TIM_Cmd(TIM4,ENABLE);
}


void TIM4_IRQHandler(){
	if(TIM_GetITStatus(TIM4, TIM_IT_Update)!=RESET){		
	//	vrvc_SttBlink =! vrvc_SttBlink;
	//	GPIO_WriteBit(GPIOB,GPIO_Pin_6,vrvc_SttBlink);
		vrvc_SttBlink = !vrvc_SttBlink;
	}	
	TIM_ClearITPendingBit(TIM4,TIM_IT_Update);
}
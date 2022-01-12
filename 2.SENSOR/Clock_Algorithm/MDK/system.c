#include "system.h"
#include "algorithm.h"
#include "math.h"

unsigned int Led7_Font[10]= {0xc0,0xf9,0xa4,0xb0,0x99,0x92,0x82,0xf8,0x80,0x90};// Ma Anode chung
int Num[MAX]={1,10,7,27,2,21,8,41,15,6,11,46,103,105,3,34,121,181,4,124,94,67,16,48,51,100,126,52,18,110,54,5,38,151,148,83,20,19,9,170,118,190,192,36,17,167,146,85,12,29,82,154,152,60,53,13,25,26,59,177,156,93,71,14,200,194,102,69,40,119,81,84,86,87,185,173,72,145,97,22,33,142,73,160,180,199,66,68,122,42,186,79,23,44,24,164,135,108,187,28,31,62,112,157,75,30,32,111,133,91,35,39,189,184,47,37,96,171,106,172,198,196,104,49,43,61,131,159,158,107,147,149,113,99,45,197,114,63,127,55,176,188,140,161,89,179,64,80,90,155,101,77,123,191,57,169,50,137,74,116,98,153,174,88,56,150,182,195,65,128,92,125,168,141,165,117,58,163,136,132,115,70,193,166,162,175,178,183,78,109,120,129,130,134,95,138,139,76,143,144};
int Num1[MAX]={1,10,7,27,2,21,8,41,15,6,11,46,103,105,3,34,121,181,4,124,94,67,16,48,51,100,126,52,18,110,54,5,38,151,148,83,20,19,9,170,118,190,192,36,17,167,146,85,12,29,82,154,152,60,53,13,25,26,59,177,156,93,71,14,200,194,102,69,40,119,81,84,86,87,185,173,72,145,97,22,33,142,73,160,180,199,66,68,122,42,186,79,23,44,24,164,135,108,187,28,31,62,112,157,75,30,32,111,133,91,35,39,189,184,47,37,96,171,106,172,198,196,104,49,43,61,131,159,158,107,147,149,113,99,45,197,114,63,127,55,176,188,140,161,89,179,64,80,90,155,101,77,123,191,57,169,50,137,74,116,98,153,174,88,56,150,182,195,65,128,92,125,168,141,165,117,58,163,136,132,115,70,193,166,162,175,178,183,78,109,120,129,130,134,95,138,139,76,143,144};
int Num2[MAX]={1,10,7,27,2,21,8,41,15,6,11,46,103,105,3,34,121,181,4,124,94,67,16,48,51,100,126,52,18,110,54,5,38,151,148,83,20,19,9,170,118,190,192,36,17,167,146,85,12,29,82,154,152,60,53,13,25,26,59,177,156,93,71,14,200,194,102,69,40,119,81,84,86,87,185,173,72,145,97,22,33,142,73,160,180,199,66,68,122,42,186,79,23,44,24,164,135,108,187,28,31,62,112,157,75,30,32,111,133,91,35,39,189,184,47,37,96,171,106,172,198,196,104,49,43,61,131,159,158,107,147,149,113,99,45,197,114,63,127,55,176,188,140,161,89,179,64,80,90,155,101,77,123,191,57,169,50,137,74,116,98,153,174,88,56,150,182,195,65,128,92,125,168,141,165,117,58,163,136,132,115,70,193,166,162,175,178,183,78,109,120,129,130,134,95,138,139,76,143,144};

volatile int NUMBER_LED = 0;
volatile int vrvi_value = 0, vrvi_value1 = 0;
volatile int Flag_TIM2 = 0, Flag_TIM3 = 0;
	
typedef struct{
	unsigned char	  vruc_DataOld;
	unsigned int 	  vruc_CountAccess;
	unsigned char 	vruc_FlagChange;
  unsigned char   vruc_hold;
}	TS_TypeInput;

TS_TypeInput BTN_K1, BTN_K2, BTN_K3, BTN_K4;
	
void delay_Tms(u16 _time){
	u16 i,j;
	for(i = 0; i < _time; i++){
		for(j = 0; j < 0x2aff; j++){}
	}
}

void SEG_Config(void){	
	RCC->APB2ENR |= 0x0D;
	GPIOA->CRL 	 |= 0x33333333;
	GPIOB->CRH   |= 0x33334444;
	GPIOA->ODR    = 0xff;
	GPIOB->ODR    = 0xffff;
}

void Button_Init(void){
	RCC->APB2ENR |= 0x04;
	AFIO->MAPR   |= 0x00300200;
	GPIOA->CRH   |= 0x88488444;	
	GPIOA->BSRR   = 0xf000;
}

void Fn_INPUT_ReadInput (unsigned char _vruc_Input, TS_TypeInput *_vrts_DataInput){
  _vrts_DataInput->vruc_DataOld = _vruc_Input;
  if(!_vruc_Input){
    if(_vrts_DataInput->vruc_DataOld == _vruc_Input){
      if(_vrts_DataInput->vruc_CountAccess <= 100){
        _vrts_DataInput->vruc_CountAccess++;
        if(_vrts_DataInput->vruc_CountAccess == 10){
          _vrts_DataInput->vruc_FlagChange = 1;
          _vrts_DataInput->vruc_hold = 0;
        }
      }
      else{
				_vrts_DataInput->vruc_FlagChange = 0;
        _vrts_DataInput->vruc_hold = 1;
      }
    }
    else{
      _vrts_DataInput->vruc_CountAccess = 0;
    }
  }
  else{
    _vrts_DataInput->vruc_CountAccess = 0;
  }
}

void Button_Run(void){
  Fn_INPUT_ReadInput (GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_15), (TS_TypeInput*)(&BTN_K4));
}

void Timer1_Init(void){	
	RCC->APB2ENR |= 0x0800;	
	// CR1: CEN(bit 0) = 1: Counter Enable
	TIM1->CR1 	 |= 0x0001; 
	TIM1->ARR 	  = 0xffff;
	TIM1->PSC 	  = 0x47;
	// SR: UIF(Bit 0) = 0: Clear the UIF flag
	TIM1->SR 		 |= 0x0000;
}

void Timer2_Init(void){
	RCC->APB1ENR |= 0x00000001;	
	TIM2->ARR 	  = 0x03E7;
	TIM2->PSC 	  = 0x47;
	TIM2->SR 		 |= 0x0000;
	TIM2->DIER   |= 0x0001;
	NVIC->ISER[0]|= 1<<28;
	TIM2->CR1 	 |= 0x0001;
}

void Timer3_Init(void){
	RCC->APB1ENR |= 0x00000002;	
	TIM3->ARR 	  = 0x03E7;
	TIM3->PSC 	  = 0x47;
	TIM3->SR 		 |= 0x0000;
	TIM3->DIER   |= 0x0001;
	NVIC->ISER[0]|= 1<<29;
	TIM3->CR1 	 |= 0x0001;
}

void _stop_timer(void) {
	TIM1->CR1 |= 0x0000;
}

void _start_timer(void) {
	TIM1->CR1 |= 0x0001;
	TIM1->CNT = 0;
}

int Time_InterchangeSort(void){
	int Time_Inter = 0;
	_start_timer();
  InterchangeSort(Num,MAX);
	Time_Inter = TIM1->CNT;
	_stop_timer();
	return Time_Inter;
}

int Time_SelectionSort(void){
	int Time_Select = 0;
	_start_timer();
  SelectionSort(Num1,MAX);
	Time_Select = TIM1->CNT;
	_stop_timer();
	return Time_Select;
}

int Time_BubbleSort(void){
	int Time_Bubble = 0;
	_start_timer();
  BubbleSort(Num2,MAX);
	Time_Bubble = TIM1->CNT;
	_stop_timer();
	return Time_Bubble;
}

void TIM3_Disp_LED(int value){		
	if(Flag_TIM3){
		NUMBER_LED++;
		if(NUMBER_LED < 5){
			GPIOB->BRR = 0x8000>>(NUMBER_LED-1);
			GPIOA->ODR = Led7_Font[((value/((int)pow(10.0,(NUMBER_LED-1))))%10)];
			delay_Tms(1);
			GPIOB->BSRR = 0x8000>>(NUMBER_LED-1);
		}
		else NUMBER_LED = 0;
		Flag_TIM3 = 0;
	}
}

void Sys_Init(void){
	SEG_Config();
	Button_Init();
	Timer1_Init();
	Timer2_Init();
	Timer3_Init();
}

void Sys_Run(void){
	if(Flag_TIM2){
		Button_Run();
	  if(BTN_K4.vruc_FlagChange){
			vrvi_value1++;
			if(vrvi_value1){
				vrvi_value = Time_BubbleSort();
			}
			if(vrvi_value1 == 2){
				vrvi_value = Time_SelectionSort();
			}
			if(vrvi_value1 == 3){
				vrvi_value = Time_InterchangeSort();			
			}
			if(vrvi_value1 == 4){
				vrvi_value1 = 0;
				vrvi_value = 0;
			}
			BTN_K4.vruc_FlagChange = 0;
		}		
		Flag_TIM2 = 0;
	}	
	TIM3_Disp_LED(vrvi_value);
}

void TIM2_IRQHandler(void){
	if((TIM2->SR & 1) != RESET){
		Flag_TIM2 = 1;
	}
	TIM2->SR = 0x0000;
}

void TIM3_IRQHandler(void){
	if((TIM3->SR & 1) != RESET){
		Flag_TIM3 = 1;
	}
	TIM3->SR = 0x0000;
}




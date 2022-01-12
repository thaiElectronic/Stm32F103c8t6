#include "sys.h"


//int main(void){	
//-	Sys_Init();
//	while(1){
//		//Sys_run();
//		LCD_Gotoxy(0,0);
//		Press_key();
//	}
//}	
/*tets ma tran nut nhan++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
char vruc_key, vruc_check;

/*-----------------------------------------------------*/
char Press_key(void){
	do{	
		vruc_key = KeyPad_Press();
		if(vruc_key != 0xFF){
			delay_ms(2);
			vruc_check = vruc_key;
			printf("  %c",vruc_check);						
			LCD_PutChar(vruc_check);
			while(vruc_key != 0xFF){vruc_key = KeyPad_Press();}		
			delay_ms(20);
		}
	}while(vruc_key != 0xFF);
	return vruc_check;
}

int main(){
//	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);

//	SysTick_Init();

//	GPIO_LCD_Config();
//	LCD_Init();
//  
//	KeyPad_Init();
//	USARTx_Init(USART1,9600);
	Sys_Init();
	LCD_Puts("Do Van Thai");
	while(1){
		//Press_key();
		Sys_run();
	}
}
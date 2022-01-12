#include "sys.h"

extern char vrvc_Stt;
unsigned char Character[8]={0x07, 0x05, 0x07, 0x00, 0x00, 0x00, 0x00, 0x00};
float NhietDo;
char str[20];
extern int KEY;
unsigned int vrvc_SttBlink = 0;

void Sys_Init(){
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);
//	GPIO_SetState(GPIOB,GPIO_Pin_8,GPIO_Mode_Out_PP);	
	SysTick_Init();
	TIMER4_Config();
//	GPIO_LCD_Config();
	LCD_Init();
	USARTx_Init(USART1, 9600);
//	KeyPad_Init();
//	GPIO_SetState(GPIOB,GPIO_Pin_0,GPIO_Mode_Out_PP);
	RTC_Init(); 
	RTC_Set(22,4,2021,0,59,50);   
}

/*
function: Display the time
*/
void RTC_Disp(char* Hourx, char* Minx, char* Secx){
		LCD_Gotoxy(0,0);
		LCD_Puts("Time: ");		
		LCD_Puts(Hourx);
		LCD_PutChar(':');
		LCD_Puts(Minx);
		LCD_PutChar(':');
		LCD_Puts(Secx);
}
/*
function: adds zeros in front of the parameters with values 0->9 
*/
void RTC_Setup00(u16 Hourx, u16 Minx, u16 Secx){
	
	char _Hour[20], Hour[20];	
	char _Min[20], Min[20];
	char _Sec[20], Sec[20];
	
	if(Hourx >=0 && Hourx < 10){
		if(Minx >=0 && Minx < 10){
			if(Secx >=0 && Secx < 10){
				sprintf(_Hour,"%d",Hourx);
				sprintf(Hour,"%d",0);
				strcat(Hour,_Hour);
				
				sprintf(_Min,"%d",Minx);
				sprintf(Min,"%d",0);
				strcat(Min,_Min);
				
				sprintf(_Sec,"%d",Secx);
				sprintf(Sec,"%d",0);
				strcat(Sec,_Sec);
				
			}
			else{ // Sec > 10
				sprintf(_Hour,"%d",Hourx);
				sprintf(Hour,"%d",0);
				strcat(Hour,_Hour);
				
				sprintf(_Min,"%d",Minx);
				sprintf(Min,"%d",0);
				strcat(Min,_Min);
				
				sprintf(Sec,"%d",Secx);
								
			}			
		}
		else{ // Min > 10
			if(Secx >=0 && Secx < 10){
				sprintf(_Hour,"%d",Hourx);
				sprintf(Hour,"%d",0);
				strcat(Hour,_Hour);
				
				sprintf(_Sec,"%d",Secx);
				sprintf(Sec,"%d",0);
				strcat(Sec,_Sec);
				
				sprintf(Min,"%d",Minx);
				
			}
			else{ // Min > 10 && Sec > 10
				sprintf(_Hour,"%d",Hourx);
				sprintf(Hour,"%d",0);
				strcat(Hour,_Hour);
				
				sprintf(Min,"%d",Minx);
				
				sprintf(Sec,"%d",Secx);
				
			}
		}
	}
	else{
		if(Minx >=0 && Minx < 10){
			if(Secx >=0 && Secx < 10){

				sprintf(Hour,"%d",Hourx);					
				
				sprintf(_Min,"%d",Minx);
				sprintf(Min,"%d",0);
				strcat(Min,_Min);
				
				sprintf(_Sec,"%d",Secx);
				sprintf(Sec,"%d",0);
				strcat(Sec,_Sec);
			}
			else{ // Houu > 10 && Min < 10 && Sec > 10
				sprintf(Hour,"%d",Hourx);					
				
				sprintf(_Min,"%d",Minx);
				sprintf(Min,"%d",0);
				strcat(Min,_Min);
				
				sprintf(Sec,"%d",Secx);
			}
		}
		else{
			if(Secx >=0 && Secx < 10){
				sprintf(Hour,"%d",Hourx);
				
				sprintf(Min,"%d",Minx);
				
				sprintf(_Sec,"%d",Secx);
				sprintf(Sec,"%d",0);
				strcat(Sec,_Sec);
			}
			else{
				sprintf(Hour,"%d",Hourx);
				
				sprintf(Min,"%d",Minx);
				
				sprintf(Sec,"%d",Secx);				
			}
		}
	}
	RTC_Disp(Hour,Min,Sec);
}

//char vruc_key;
//char vruc_check;

///*-----------------------------------------------------*/
//char Press_key(void){
//	do{	
//		vruc_key = KeyPad_Press();
//		if(vruc_key != 0xFF){
//			delay_ms(2);
//			vruc_check = vruc_key;					
//			LCD_PutChar(vruc_check);
//			printf("%c",vruc_check);
//			while(vruc_key != 0xFF){vruc_key = KeyPad_Press();}		
//			delay_ms(20);
//		}
//	}while(vruc_key != 0xFF);
//	return vruc_check;
//}

void GOTO_Setup(){
	if(vrvc_Stt == 1){
		
	}
}


void Display_Temp(void){
		/*Diplay Temperature*/
		if(vrvc_SttBlink){
			NhietDo=ds18b20_read();
		//  delay_ms(100);
			sprintf(str,"Nhiet Do: %2.1f",NhietDo);
			LCD_Gotoxy(0,1);
			LCD_Puts(str);
			//tao ki tu dac biet
			LCD_Custom(0,Character);
			LCD_Gotoxy(14,1);
			LCD_PutChar(0);
			LCD_PutChar('C');			
		}
}

void Display_Time(void){
	/*Display Time*/
		if(KEY){			
			RTC_Get();
			RTC_Setup00(calendar.hour, calendar.min, calendar.sec);
			KEY = 0;
		}
}
void Sys_run(void){
	Display_Temp();
	Display_Time();
}

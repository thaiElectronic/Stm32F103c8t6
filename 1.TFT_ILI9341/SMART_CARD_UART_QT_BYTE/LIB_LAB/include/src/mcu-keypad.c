#include "mcu-keypad.h"
#include "mcu-gpio.h"
#include "string.h"

/*
	chuan theo thu mach in
*/

char Row[]={PB0,PB1,PB2,PB3};
char Column[]={PB4,PB5,PB6,PB7};
int i;

void KeyPad_Init(void){
	
	// cau hinh cot
	for(i = 0; i<4; i++){
		pinMode(Column[i], OUTPUT);
		digitalWrite(Column[i],LOW);
	}
	
	// cau hinh hang
	for(i = 0; i<4; i++){
		pinMode(Row[i], INPUT_PULLUP);
		digitalWrite(Row[i],HIGH);
	}
}

char KeyPad_Press(){
	GPIO_Write(GPIOB,0xef);
	if(!digitalRead(PB0)){return '1';}
	if(!digitalRead(PB1)){return '4';}
	if(!digitalRead(PB2)){return '7';}
	if(!digitalRead(PB3)){return '*';}
	
	GPIO_Write(GPIOB,0xdf);
	if(!digitalRead(PB0)){return '2';}
	if(!digitalRead(PB1)){return '5';}
	if(!digitalRead(PB2)){return '8';}
	if(!digitalRead(PB3)){return '0';}
	
	GPIO_Write(GPIOB,0xbf);
	if(!digitalRead(PB0)){return '3';}
	if(!digitalRead(PB1)){return '6';}
	if(!digitalRead(PB2)){return '9';}
	if(!digitalRead(PB3)){return '#';}

	GPIO_Write(GPIOB,0x7f);
	if(!digitalRead(PB0)){return 'A';}
	if(!digitalRead(PB1)){return 'B';}
	if(!digitalRead(PB2)){return 'C';}
	if(!digitalRead(PB3)){return 'D';}
	return 0xFF;
}

//uint8_t CheckPass(char *Str1, char *Str2){
//	if(strlen(Str1) == strlen(Str2)){
//		if(strstr(Str1,Str2)!=NULL){ 
//			return 1;
//		}
//	}
//	return 0;
//}
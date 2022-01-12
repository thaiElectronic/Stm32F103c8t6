#ifndef __SMART_LOCK_JSON_H
#define __SMART_LOCK_JSON_H

#include "stm32f10x.h"                  // Device header
#include "jansson.h" 
#include <string.h>
#include <stdlib.h>
#include "UART.h"
#include "test.h"
#include "Smart_lock_RFID.h"
#include "Smart_lock_TFT.h"

extern char *Id	;
extern char *name ;
extern char *school;
extern char *msv	;
extern char *str_Res;

extern char new_name[20] ;
extern char new_ID[20] ;
extern char new_school[20] ;
extern char new_msv[20] ;

extern char old_name[20] ;
extern char old_ID[20] ;
extern char old_school[20] ;
extern char old_msv[20] ;

extern char	vrc_Res[500]; 
extern int  Flag_Json_To_TFT;


void Get_Info_Json(char *Res);
void json_packing(char *Buffer);
void Delay_Ms(unsigned int time);
void Json_Copy_Info(char* TEN);

#endif 

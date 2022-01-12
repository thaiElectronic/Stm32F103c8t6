#ifndef _SYSTEM_H_
#define _SYSTEM_H_

#include "stm32f10x.h"
#include "delay.h"
#include "sys.h"
#include "lcd.h"
//#include "touch.h"
#include "gui.h"
//#include "test.h"
#include "string.h"
#include "font7s.h"
#include "mcu-usart.h"
#include "mcu-spi.h"
#include "mcu-mfrc522.h"
#include "mcu-tim.h"

void sys_Init(void);
void sys_Run(void);

void SPI1_Init(); // SPI-SD CARD

void Text_Center(u16 x1, u16 y1, u16 x2, u16 y2, u16 fc, u16 bc, u8 *str, u8 size,u8 mode);
void main_test(void);
void Box_text(void);
void Index(void);
void Show_Info(const unsigned char *image);

void Text_Center1(u16 x1, u16 y1, u16 x2, u16 y2, u16 fc, u16 bc, u8 *str, u8 size);
void Index1(void);

void Test_font_user(void);

#endif

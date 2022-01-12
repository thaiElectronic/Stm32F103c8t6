#ifndef _ILI9341_DEFINE_H_
#define _ILI9341_DEFINE_H_
#include "stm32f10x.h"


/* USER CODE BEGIN Private defines */

#define NUM_PIN_DC								8
#define ILI9341_PIN_DC	 					GPIO_Pin_8
#define ILI9341_PORT_DC	 					GPIOB
#define RCC_ILI9341_PORT_DC				RCC_APB2Periph_GPIOB

#define NUM_PIN_CS								9
#define ILI9341_PIN_CS 						GPIO_Pin_9
#define ILI9341_PORT_CS 					GPIOB
#define RCC_ILI9341_PORT_CS				RCC_APB2Periph_GPIOB

#define NUM_PIN_RST								12
#define ILI9341_PIN_RST 					GPIO_Pin_12
#define ILI9341_PORT_RST	 				GPIOB
#define RCC_ILI9341_PORT_RST			RCC_APB2Periph_GPIOB

#define ILI9341_SPI_DISPLAY				SPI2
#define ILI9341_SPI_PORT					GPIOB
#define RCC_ILI9341_SPI_DISPLAY   RCC_APB1Periph_SPI2
#define RCC_ILI9341_SPI_PORT			RCC_APB2Periph_GPIOB
#define ILI9341_PIN_SCK 					GPIO_Pin_13
#define ILI9341_PIN_MISO 					GPIO_Pin_14
#define ILI9341_PIN_MOSI 					GPIO_Pin_15

#define	ILI9341_PIN_CS_SET  			ILI9341_PORT_CS->BSRR  = 1<<NUM_PIN_CS    
#define	ILI9341_PIN_DC_SET				ILI9341_PORT_DC->BSRR  = 1<<NUM_PIN_DC      
#define	ILI9341_PIN_RST_SET				ILI9341_PORT_RST->BSRR = 1<<NUM_PIN_RST   
						    
#define	ILI9341_PIN_CS_RESET  		ILI9341_PORT_CS->BRR   = 1<<NUM_PIN_CS     
#define	ILI9341_PIN_DC_RESET			ILI9341_PORT_DC->BRR   = 1<<NUM_PIN_DC    
#define	ILI9341_PIN_RST_RESET			ILI9341_PORT_RST->BRR  = 1<<NUM_PIN_RST 

/*------------------------------------------------------------------------*/
#define ILI9341_SPI_TOUCHSCREEN		SPI1	

#define ILI9341_TP_PIN_IRQ 				GPIO_Pin_3
#define ILI9341_TP_PORT_IRQ	 			GPIOA

#define ILI9341_TP_PIN_CS 				GPIO_Pin_4
#define ILI9341_TP_PORT_CS	 			GPIOA

#define ILI9341_TP_PIN_SCK 				GPIO_Pin_5
#define ILI9341_TP_PORT_SCK	 			GPIOA

#define ILI9341_TP_PIN_MISO 			GPIO_Pin_6
#define ILI9341_TP_PORT_MISO	 		GPIOA

#define ILI9341_TP_PIN_MOSI 			GPIO_Pin_7
#define ILI9341_TP_PORT_MOSI	 		GPIOA

/*------------------------------------------------------------------------*/
//#define ILI9341_PIN_ 					GPIO_Pin_
//#define ILI9341_PORT_	 				GPIO

//#define ILI9341_PIN_ 					GPIO_Pin_
//#define ILI9341_PORT_	 				GPIO

//#define ILI9341_PIN_ 					GPIO_Pin_
//#define ILI9341_PORT_	 				GPIO

//#define ILI9341_PIN_ 					GPIO_Pin_
//#define ILI9341_PORT_	 				GPIO


#define READ_X 				0xD0
#define READ_Y 				0x90

void ILI9341_SPI_Display_Init(void);

#endif


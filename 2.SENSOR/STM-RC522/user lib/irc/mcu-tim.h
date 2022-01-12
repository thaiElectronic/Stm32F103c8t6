/*
  *****************************************************************************
  * @file			mcu-tim.h                                                              *
  * @author			Thai Salem                                               
  * @date			00/00/0000                                                         
  ******************************************************************************
*/

#ifndef MCU_TIM_H
#define MCU_TIM_H

#include "stm32f10x.h"

/*
 * PWM pins 
 *
 * 	TIMER	|CHANNEL 1				|CHANNEL 2				|CHANNEL 3				|CHANNEL 4
 * 				|PP1	PP2		PP3		|PP1	PP2		PP3		|PP1	PP2		PP3		|PP1	PP2		PP3
 *
 * 	TIM 2	|PA0	PA5		PA15	|PA1	PB3		-			|PA2	PB10	-			|PA3	PB11	-
 * 	TIM 3	|PA6	PB4		PC6		|PA7	PB5		PC7		|PB0	PC8		-			|PB1	PC9		-
 * 	TIM 4	|PB6	PD12	-			|PB7	PD13	-			|PB8	PD14	-			|PB9	PD15	-
 * 	TIM 5	|PA0	PH10	-			|PA1	PH11	-			|PA2	PH12	-			|PA3	PI0		-
 * 	TIM 8	|PC6	PI5		-			|PC7	PI6		-			|PC8	PI7		-			|PC9	PI2		-
 * 	TIM 9	|PA2	PE5		-			|PA3	PE6		-			|-		-		-				|-		-		-
 * 	TIM 10|PB8	PF6		-			|-		-		-				|-		-		-				|-		-		-
 * 	TIM 11|PB9	PF7		-			|-		-		-				|-		-		-				|-		-		-
 * 	TIM 12|PB14	PH6		-			|PB15	PH9		-			|-		-		-				|-		-		-
 * 	TIM 13|PA6	PF8		-			|-		-		-				|-		-		-				|-		-		-
 * 	TIM 14|PA7	PF9		-			|-		-		-				|-		-		-				|-		-		-
 *
*/


/* define counter mode */
#define			UP				 								TIM_CounterMode_Up                
#define 		DOWN					  					TIM_CounterMode_Down              
#define 		ALIGNED1									TIM_CounterMode_CenterAligned1    
#define 		ALIGNED2									TIM_CounterMode_CenterAligned2     
#define 		ALIGNED3									TIM_CounterMode_CenterAligned3 

typedef enum {
	Channel_1,
	Channel_2,
	Channel_3,
	Channel_4
} PWM_Channel_t;


void TIMER_InitBasic(TIM_TypeDef* TIMx,  uint16_t CounterMode, uint16_t Period, uint16_t Prescaler, uint8_t Key_EXT);
void PWM_Init(TIM_TypeDef * TIMx, PWM_Channel_t Channel, uint16_t Period, uint16_t Prescaler);
void PWM_PinChannel(TIM_TypeDef * TIMx, PWM_Channel_t Channel);


#endif

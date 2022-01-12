/****************************************************************************************************
//=================================================================================//
//     	LCD              		STM32
//      VCC             		DC5V/3.3V     
//      GND              		GND        
//=================================================================================//
//
//     	LCD              		STM32   
//   	 	SDI(MOSI)        		PB15         
//    	SDO(MISO)         	PB14         
//=================================================================================//
//     	LCD				      		STM32
//      LED               	3.3          
//      SCK                 PB13         
//      DC/RS               PB8          
//      RST                 PB12       
//      CS                  PB9          
//==================================================================================//
//
//	   	LCD             		STM32
//      T_IRQ               PC10       
//      T_DO                PC2          
//      T_DIN               PC3         
//      T_CS                PC13         
//      T_CLK               PC0         
**************************************************************************************************/
#include "delay.h"
static u8  fac_us=0;
static u16 fac_ms=0;


void delay_init(u8 SYSCLK)
{
//	SysTick->CTRL&=0xfffffffb;//
	SysTick_CLKSourceConfig(SysTick_CLKSource_HCLK_Div8);
	fac_us=SYSCLK/8;		    
	fac_ms=(u16)fac_us*1000;
}								    


void delay_ms(u16 nms)
{	 		  	  
	u32 temp;		   
	SysTick->LOAD=(u32)nms*fac_ms;//ʱ�����(SysTick->LOADΪ24bit)
	SysTick->VAL =0x00;           //��ռ�����
	SysTick->CTRL=0x01 ;          //��ʼ����  
	do
	{
		temp=SysTick->CTRL;
	}
	while(temp&0x01&&!(temp&(1<<16)));//�ȴ�ʱ�䵽��   
	SysTick->CTRL=0x00;       //�رռ�����
	SysTick->VAL =0X00;       //��ռ�����	  	    
}   
//��ʱnus
//nusΪҪ��ʱ��us��.		    								   
void delay_us(u32 nus)
{		
	u32 temp;	    	 
	SysTick->LOAD=nus*fac_us; //ʱ�����	  		 
	SysTick->VAL=0x00;        //��ռ�����
	SysTick->CTRL=0x01 ;      //��ʼ���� 	 
	do
	{
		temp=SysTick->CTRL;
	}
	while(temp&0x01&&!(temp&(1<<16)));//�ȴ�ʱ�䵽��   
	SysTick->CTRL=0x00;       //�رռ�����
	SysTick->VAL =0X00;       //��ռ�����	 
}





































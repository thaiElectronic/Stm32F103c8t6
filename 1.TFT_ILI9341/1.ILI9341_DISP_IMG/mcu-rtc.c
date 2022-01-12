
#include "mcu-rtc.h"
#include "string.h" 
#include "mcu-usart.h"
#include "mcu-delay.h"
#include "GUI.h"
#include "lcd.h"
#include <time.h>


	   
_calendar_obj calendar;
 
///////////////////////////////////////////////////////////////////////////////////////////////////
/*******************************************************************************
* Function Name  : Time_ConvUnixToCalendar
* Description    : 
* Input          : 
* Output         : None
* Return         : struct tm
* Attention		 : None
*******************************************************************************/
struct tm Time_ConvUnixToCalendar(time_t t)
{
	struct tm *t_tm;
	t_tm = localtime(&t);
	t_tm->tm_year += 1900;
	
	return *t_tm;
}

/*******************************************************************************
* Function Name  : Time_GetCalendarTime
* Description    : 
* Input          : None
* Output         : None
* Return         : struct tm
* Attention		 : None
*******************************************************************************/
struct tm Time_GetCalendarTime(void)
{
	time_t t_t;
	struct tm t_tm;

	t_t = (time_t)RTC_GetCounter();
	t_tm = Time_ConvUnixToCalendar(t_t);
	return t_tm;
}


/*******************************************************************************
* Function Name  : Time_ConvCalendarToUnix
* Description    : 
* Input          : - t: struct tm
* Output         : None
* Return         : time_t
* Attention		 : None
*******************************************************************************/
time_t Time_ConvCalendarToUnix(struct tm t)
{
	t.tm_year -= 1900;
	return mktime(&t);
}
/*******************************************************************************
* Function Name  : Time_SetUnixTime
* Description    : 
* Input          : - t: time_t 
* Output         : None
* Return         : None
* Attention		 : None
*******************************************************************************/
void Time_SetUnixTime(time_t t)
{
	RTC_WaitForLastTask();
	RTC_SetCounter((u32)t);
	RTC_WaitForLastTask();
	return;
}

void Set_Alarm(time_t t)
{
	RTC_WaitForLastTask();
	RTC_SetAlarm((u32)t);
	RTC_WaitForLastTask();
	return;
}

/*******************************************************************************
* Function Name  : Time_SetCalendarTime
* Description    : 
* Input          : - t: struct tm
* Output         : None
* Return         : None
* Attention		 : None
*******************************************************************************/
void Time_SetCalendarTime(struct tm t)
{
	Time_SetUnixTime(Time_ConvCalendarToUnix(t));
	return;
}

void Time_SetAlarmTime(struct tm t)
{
	Set_Alarm(Time_ConvCalendarToUnix(t));
	return;
}	 			   											 
///////////////////////////////////////////////////////////////////////////////

//
// 1  2  3  4  5  6  7  8  9  10 11 12
// 31 29 31 30 31 30 31 31 30 31 30 31
// 31 28 31 30 31 30 31 31 30 31 30 31

u8 Is_Leap_Year(u16 year)
{			  
	if(year%4==0) 
	{ 
		if(year%100==0) 
		{ 
			if(year%400==0)return 1;   
			else return 0;   
		}else return 1;   
	}else return 0;	
}

u8 const table_week[12]={0,3,3,6,1,4,6,2,5,0,3,5};
const u8 mon_table[12]={31,28,31,30,31,30,31,31,30,31,30,31};

/////////////////////////////////////////////////////////////////////
u8 RTC_Set(u8 day,u8 mon,u16 year,u8 hour,u8 min,u8 sec)
{
	
	struct tm time;
  memset((void*)&time, 0 , sizeof(time) );
		
  time.tm_year=year;
  time.tm_mon=mon-1;////////////
  time.tm_mday=day;
  time.tm_hour=hour;
  time.tm_min=min;
  time.tm_sec=sec;

//	u16 t;
//	u32 seccount=0;
//	
//	if(year<1970||year>2099)return 1;	   
//	for(t=1970;t<year;t++)	
//	{
//		if(Is_Leap_Year(t))seccount+=31622400;
//		else seccount+=31536000;			  
//	}
//	mon-=1;
//	for(t=0;t<mon;t++)	   
//	{
//		seccount+=(u32)mon_table[t]*86400;
//		if(Is_Leap_Year(year)&&t==1)seccount+=86400;	   
//	}
//	seccount+=(u32)(day-1)*86400;
//	seccount+=(u32)hour*3600;
//    seccount+=(u32)min*60;	
//	seccount+=sec;			    
//	
//	
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_PWR | RCC_APB1Periph_BKP, ENABLE);  
	PWR_BackupAccessCmd(ENABLE);	
	
	
	Time_SetCalendarTime(time);//RTC_SetCounter(seccount);RTC_WaitForLastTask();	 	
	 	
	return 0;	    
}


u8 RTC_Alarm_Set(u8 sday,u8 smon,u16 syear,u8 hour,u8 min,u8 sec)
{

	struct tm time;
  memset((void*)&time, 0 , sizeof(time) );
		
  time.tm_year=syear;
  time.tm_mon=smon-1;////////////
  time.tm_mday=sday;
  time.tm_hour=hour;
  time.tm_min=min;
  time.tm_sec=sec;
	
//	u16 t;
//	u32 seccount=0;

//	
//	if(syear<1970||syear>2099)return 1;	   
//	for(t=1970;t<syear;t++)	
//	{
//		if(Is_Leap_Year(t))seccount+=31622400;
//		else seccount+=31536000;			  
//	}
//	smon-=1;//////////////////////////////////////////////
//	for(t=0;t<smon;t++)	   
//	{
//		seccount+=(u32)mon_table[t]*86400;
//		if(Is_Leap_Year(syear)&&t==1)seccount+=86400;	   
//	}
//	seccount+=(u32)(sday-1)*86400;
//	seccount+=(u32)hour*3600;
//    seccount+=(u32)min*60;	 
//	seccount+=sec; 			    
//	
//	
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_PWR | RCC_APB1Periph_BKP, ENABLE);	  
	PWR_BackupAccessCmd(ENABLE);	  
	
	
	Time_SetAlarmTime(time);//RTC_SetAlarm(seccount);RTC_WaitForLastTask(); 	
	
	return 0;	    
}


//////////////////////////////////2 ham ok///////////////////////////////////////////
int weekday(int year, int month, int day)
/* Calculate day of week in proleptic Gregorian calendar. Sunday == 0. */
{
	int adjustment, mm, yy;
	
	
	//month = month-1;//da -1 luc SET Month
	
  
  if (year<2000) year+=2000;
  adjustment = (14 - month) / 12;
  mm = month + 12 * adjustment - 2;
  yy = year - adjustment;
  return (day + (13 * mm - 1) / 5 +
    yy + yy / 4 - yy / 100 + yy / 400) % 7;
}
u8 RTC_Get_Week(u16 year,u8 month,u8 day)
{	//* Calculate day of week in proleptic Gregorian calendar. Sunday == 0. mon=1 */
	u16 temp2;
	u8 yearH,yearL;
	
	//month = month-1;//da -1 luc SET Month
	
	yearH=year/100;	yearL=year%100; 
	 
	if (yearH>19)yearL+=100;
	
	temp2=yearL+yearL/4;
	temp2=temp2%7; 
	temp2=temp2+day+table_week[month-1];
	if (yearL%4==0&&month<3)temp2--;
	return(temp2%7);
}		
//////////////////////////////////////////////////////////////////////////////////
u8 RTC_Get(void)//Time_GetCalendarTime(void)
{
	struct tm time; 
	time = Time_GetCalendarTime();//
	
		calendar.week=time.tm_wday;		
		calendar.w_year=time.tm_year;
		calendar.w_month=time.tm_mon+1;
		calendar.w_date=time.tm_mday;
		calendar.hour=time.tm_hour;
		calendar.min=time.tm_min;
		calendar.sec=time.tm_sec;
		
	return 0;
}	 


static void RTC_NVIC_Config(void)
{	
  NVIC_InitTypeDef NVIC_InitStructure;
	NVIC_InitStructure.NVIC_IRQChannel = RTC_IRQn;		
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;	
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;	
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;		
	NVIC_Init(&NVIC_InitStructure);		
	
	/* Enable the RTC Alarm Interrupt */
	NVIC_InitStructure.NVIC_IRQChannel = RTCAlarm_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);
	
}



u8 RTC_Init(void)
{
	
	u8 temp=0;
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_PWR | RCC_APB1Periph_BKP, ENABLE);	   
	PWR_BackupAccessCmd(ENABLE);	  
	if (BKP_ReadBackupRegister(BKP_DR1) != 0x5050)		
		{	 			
		BKP_DeInit();	 	
		RCC_LSEConfig(RCC_LSE_ON);	
		while (RCC_GetFlagStatus(RCC_FLAG_LSERDY) == RESET&&temp<250)	
			{
			temp++;
			Delay_ms(10);
			}
		if(temp>=250)return 1;    
		RCC_RTCCLKConfig(RCC_RTCCLKSource_LSE);		   
		RCC_RTCCLKCmd(ENABLE);	 
		RTC_WaitForLastTask();	
		RTC_WaitForSynchro();		  
		RTC_ITConfig(RTC_IT_SEC, ENABLE);	
		/*  Start RTC alarm interrupt. */
    RTC_ITConfig(RTC_IT_ALR, ENABLE);
		RTC_WaitForLastTask();	
		RTC_EnterConfigMode();	
		RTC_SetPrescaler(32767); 
		RTC_WaitForLastTask();	
		//RTC_Set(14,1,2020,17,42,55);  	
		RTC_ExitConfigMode(); 
		BKP_WriteBackupRegister(BKP_DR1, 0X5050);	
		}
	else
		{

		RTC_WaitForSynchro();	
		RTC_ITConfig(RTC_IT_SEC, ENABLE);	
		/*  Start RTC alarm interrupt. */
    RTC_ITConfig(RTC_IT_ALR, ENABLE);
		RTC_WaitForLastTask();	
		}
	RTC_NVIC_Config();		    				     
	RTC_Get();	
	return 0; 

}		

void LCD_Clear_TIME(u16 Color)
{
  unsigned int i,m;  
	LCD_SetWindows(230,20,340,70);   
	LCD_CS_CLR;
	LCD_RS_SET;
	for(i=0;i<80;i++)
	{
    for(m=0;m<340;m++)
    {	
			Lcd_WriteData_16Bit(Color);
		}
	}
	 LCD_CS_SET;
} 

int i;

////////////////////////////////////////////////////////////////////////
void RTC_IRQHandler(void){		
	char vruc_gio[100];
	char vruc_phut[100];
	char vruc_giay[100];
	char vruc_ngay[100];
	char vruc_thang[100];
	char vruc_nam[100];
	if (RTC_GetITStatus(RTC_IT_SEC) != RESET){	
	
		RTC_Get();
		sprintf(vruc_giay,"%d",calendar.sec);		
		sprintf(vruc_phut,"%d",calendar.min);
		sprintf(vruc_gio,"%d",calendar.hour);
		sprintf(vruc_ngay,"%d",calendar.w_date);
		sprintf(vruc_thang,"%d",calendar.w_month);
		sprintf(vruc_nam,"%d",calendar.w_year);
//	printf("Time: %d %d-%d-%d %d:%d:%d\n",calendar.week,calendar.w_date,calendar.w_month,calendar.w_year,calendar.hour,calendar.min,calendar.sec);
		if(calendar.hour < 10){
			Show_Str(253,50,WHITE,YELLOW,"0",16,1);
			Show_Str(261,50,WHITE,YELLOW,(u8*)vruc_gio,16,1);
		}
		else{
			Show_Str(253,50,WHITE,YELLOW,(u8*)vruc_gio,16,1);
		}

		if(calendar.min < 10){
			Show_Str(273,50,WHITE,YELLOW,"0",16,1);
			Show_Str(281,50,WHITE,YELLOW,(u8*)vruc_phut,16,1);
		}
		else{
			Show_Str(273,50,WHITE,YELLOW,(u8*)vruc_phut,16,1);
		}
		
		if(calendar.sec < 10){
			Show_Str(292,50,WHITE,YELLOW,"0",16,1);
			Show_Str(299,50,WHITE,YELLOW,(u8*)vruc_giay,16,1);
		}
		else{
			Show_Str(292,50,WHITE,YELLOW,(u8*)vruc_giay,16,1);
		}
	
		if(calendar.w_date < 10){
			Show_Str(240,30,WHITE,YELLOW,"0",16,1);
			Show_Str(249,30,WHITE,YELLOW,(u8*)vruc_ngay,16,1);
		}
		else{
			Show_Str(240,30,WHITE,YELLOW,(u8*)vruc_ngay,16,1);
		}
		
		if(calendar.w_month < 10){
			Show_Str(264,30,WHITE,YELLOW,"0",16,1);
			Show_Str(272,30,WHITE,YELLOW,(u8*)vruc_thang,16,1);
		}
		else{
			Show_Str(264,30,WHITE,YELLOW,(u8*)vruc_thang,16,1);
		}
		
		Show_Str(256,30,WHITE,YELLOW,"/",16,1);	
		Show_Str(280,30,WHITE,YELLOW,"/",16,1);
		Show_Str(288,30,WHITE,YELLOW,(u8*)vruc_nam,16,1);		
		Show_Str(267,50,WHITE,YELLOW,":",16,1);
		Show_Str(286,50,WHITE,YELLOW,":",16,1);
		Delay_ms(100);
		//LCD_Clear_TIME(BLACK);
		LCD_Clear_TIME(BLACK); 
	}
	if(RTC_GetITStatus(RTC_IT_ALR)!= RESET){
		RTC_WaitForLastTask();
		RTC_ClearITPendingBit(RTC_IT_ALR);			  	
		RTC_Get();				  
		//printf("Alarm Time: %d %d-%d-%d %d:%d:%d\n",calendar.week,calendar.w_year,calendar.w_month,calendar.w_date,calendar.hour,calendar.min,calendar.sec);		
	} 				  								 
	RTC_ClearITPendingBit(RTC_IT_SEC|RTC_IT_OW);		
	RTC_WaitForLastTask();	  	
}	  














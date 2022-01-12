#include "uart.h"
#include "gpio.h"
/*******************************************************************************************************/

#define MAX 100

/*******************************************************************************************************/
struct __FILE {
    int dummy;
};
FILE __stdout;
 
int fputc(int ch, FILE *f) {
 
    USARTx_Sendc(USART1, ch);
  
    return ch;
}
/*******************************************************************************************************/
void USARTx_Init(USART_TypeDef* USART_x, uint32_t USART_Baud){
extern GPIO_InitTypeDef gpio_typedef;
USART_InitTypeDef usart_typedef;
/*-------------------if use USART1-------------------*/
	if(USART_x == USART1){
		// enable clock
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1, ENABLE);
		// congifgure pin Tx - A9;
		pinMode(PA9,AF_PP);		
		// configure pin Rx - A10;
		pinMode(PA10,INPUT);
		// usart configure
		usart_typedef.USART_BaudRate = USART_Baud;
		usart_typedef.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
		usart_typedef.USART_Mode = USART_Mode_Tx | USART_Mode_Rx; 
		usart_typedef.USART_Parity = USART_Parity_No;
		usart_typedef.USART_StopBits = USART_StopBits_1;
		usart_typedef.USART_WordLength = USART_WordLength_8b;
		USART_Init(USART_x, &usart_typedef);
/*----------------------------------------------------------------------------------------*/		
		/*if use usart interrup */
		//  Enable RXNE interrupt 
		USART_ITConfig(USART_x, USART_IT_RXNE, ENABLE);
		 /* Enable USART1 global interrupt */
		NVIC_EnableIRQ(USART1_IRQn);
/*----------------------------------------------------------------------------------------*/		
		USART_Cmd(USART_x, ENABLE);
	}

/*-------------------if use USART2-------------------*/
	else if(USART_x == USART2){
		// enable clock
		RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART2, ENABLE);
		// congifgure pin Tx - A2;
		pinMode(PA2,AF_PP);		
		// configure pin Rx - A3;
		pinMode(PA3,INPUT);
		// usart configure
		usart_typedef.USART_BaudRate = USART_Baud;
		usart_typedef.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
		usart_typedef.USART_Mode = USART_Mode_Tx | USART_Mode_Rx; 
		usart_typedef.USART_Parity = USART_Parity_No;
		usart_typedef.USART_StopBits = USART_StopBits_1;
		usart_typedef.USART_WordLength = USART_WordLength_8b;
		USART_Init(USART_x, &usart_typedef);
/*----------------------------------------------------------------------------------------*/		
		/*if use usart interrup */
		//  Enable RXNE interrupt 
		USART_ITConfig(USART_x, USART_IT_RXNE, ENABLE);
		 /* Enable USART1 global interrupt */
		NVIC_EnableIRQ(USART2_IRQn);
/*----------------------------------------------------------------------------------------*/		
		USART_Cmd(USART_x, ENABLE);
	}

/*-------------------if use USART3-------------------*/
	else if(USART_x == USART3){
		// enable clock
		RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART3, ENABLE);
		// congifgure pin Tx - B9;
		pinMode(PB9,AF_PP);		
		// configure pin Rx - B10;
		pinMode(PB10,INPUT);
		// usart configure
		usart_typedef.USART_BaudRate = USART_Baud;
		usart_typedef.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
		usart_typedef.USART_Mode = USART_Mode_Tx | USART_Mode_Rx; 
		usart_typedef.USART_Parity = USART_Parity_No;
		usart_typedef.USART_StopBits = USART_StopBits_1;
		usart_typedef.USART_WordLength = USART_WordLength_8b;
		USART_Init(USART_x, &usart_typedef);
		
		/*if use usart interrup */
		//  Enable RXNE interrupt 
		USART_ITConfig(USART_x, USART_IT_RXNE, ENABLE);
		 /* Enable USART1 global interrupt */
		NVIC_EnableIRQ(USART3_IRQn);
	
		USART_Cmd(USART_x, ENABLE);
	}
}
/*******************************************************************************************************/
void USARTx_Sendc(USART_TypeDef* USART_x, char c){
	/*----------------------------------------------------------------------------------------*/
	USART_SendData(USART_x,c);
	while(USART_GetFlagStatus(USART_x, USART_FLAG_TXE)==RESET);
}
/*******************************************************************************************************/
void USARTx_Sends(USART_TypeDef* USART_x, char* s){
	/*----------------------------------------------------------------------------------------*/
	while(*s!='\0'){
		USARTx_Sendc(USART_x,*s++);
		while(USART_GetFlagStatus(USART_x, USART_FLAG_TXE)==RESET);
	}
}
/*******************************************************************************************************/
uint16_t UARTx_Getc(USART_TypeDef* USARTx){
	return USART_ReceiveData(USARTx);
}
/*******************************************************************************************************/

//char 	vrc_Getc; 			// bien kieu char, dung de nhan du lieu tu PC gui xuong;
//extern int vri_Stt; 			// bien danh dau trang thai. 
//int 	vri_Count = 0; 		// bien diem
//char	vrc_Res[MAX]; 		//Mang kieu char vrc_Res[MAX]: mang luu tru tam thoi;

/*Use interrupt to receive data*/
//void USART1_IRQHandler(){

//	#if SYSTEM_SUPPORT_OS 		//
//	OSIntEnter();    
//	#endif
//	
//	if(USART_GetITStatus(USART1, USART_IT_RXNE)!=RESET){
//		vrc_Getc = UARTx_Getc(USART1);
//		if(vrc_Getc == 13){ // 13: enter; bao hieu ket thuc chuoi
//			vri_Stt = 1; // dieu kien kiem tra de thuc hien cac chuong trinh theo yeu cau.
//			vrc_Res[vri_Count] = NULL;
//			vri_Count = 0;
//		}
//		else{
//			vrc_Res[vri_Count] = vrc_Getc;
//			//USARTx_Sendc(USART1, vrc_Res[vri_Count]);
//			vri_Count++;
//		}
//	}
// 
//}

/*******************************************************************************************************/

///*Use interrupt to receive data*/
//void USART2_IRQHandler(){
//	
//	#if SYSTEM_SUPPORT_OS 		//
//	OSIntEnter();    
//	#endif	
//	
//	if(USART_GetITStatus(USART2, USART_IT_RXNE) != RESET){
//		vrc_Getc = UARTx_Getc(USART2);
//		if(vrc_Getc == 13){// 13: enter; bao hieu ket thuc chuoi
//			vri_Stt = 1; // dieu kien kiem tra de thuc hien cac chuong trinh theo yeu cau.
//			vrc_Res[vri_Count] = NULL;
//			vri_Count = 0;
//		}
//		else{
//			vrc_Res[vri_Count] = vrc_Getc;
//			USARTx_Sendc(USART2, vrc_Res[vri_Count]);
//			vri_Count++;
//		}
//	}
//	#if SYSTEM_SUPPORT_OS 	//如果SYSTEM_SUPPORT_OS为真，则需要支持OS.
//	OSIntExit();  											 
//	#endif
//}
///*******************************************************************************************************/
///*Use interrupt to receive data*/
//void USART3_IRQHandler(){
//	#if SYSTEM_SUPPORT_OS 		//
//	OSIntEnter();    
//	#endif
//	if(USART_GetITStatus(USART3, USART_IT_RXNE) != RESET){
//		vrc_Getc = UARTx_Getc(USART3);
//		if(vrc_Getc == 13){// 13: enter; bao hieu ket thuc chuoi
//			vri_Stt = 1; // dieu kien kiem tra de thuc hien cac chuong trinh theo yeu cau.
//			vrc_Res[vri_Count] = NULL;
//			vri_Count = 0;
//		}
//		else{
//			vrc_Res[vri_Count] = vrc_Getc;
//			USARTx_Sendc(USART3, vrc_Res[vri_Count]);
//			vri_Count++;
//		}
//	}
//	#if SYSTEM_SUPPORT_OS 	//如果SYSTEM_SUPPORT_OS为真，则需要支持OS.
//	OSIntExit();  											 
//	#endif
//}
///*******************************************************************************************************/

//extern int 		vri_Number; 			// chua gia tri can chuyen doi.
//extern int 		vri_CountPtr; 		// dem so luong cua mang vrc_Ptr.
//extern int  	vri_CountArr; 		// dem so luong phan tu cua mang vrc_Arr.
//extern int 		vri_Countemp;
//char  	vrc_Ptr[100];			//mang nhan gia tri (chuan vi tri) sau khi chuyen doi int->string.
//char  	vrc_Arr[100]; 		//mang nhan gia tri (sai vi tri) sau khi chuyen doi tu int->string.

//// chuyen tu int -> string.
//void USARTx_InStr(unsigned int vri_Number){
// int vri_CountArr = 0, vri_CountPtr = 0;
//	while(vri_Number>0){
//		vrc_Arr[vri_CountArr] = ((vri_Number % 10) + 48);
//		vri_CountArr++;
//		vri_Number /= 10;
//	}
//	vrc_Arr[vri_CountArr]=NULL;
//	for(vri_CountArr = strlen(vrc_Arr)-1; vri_CountArr >= 0; vri_CountArr--){
//		vrc_Ptr[vri_CountPtr] = vrc_Arr[vri_CountArr];
//		vri_CountPtr++;
//	}
//	vrc_Ptr[vri_CountPtr]=NULL;
//}
/*********************************************************************************************************/
/*the function compare two strings*/
int USARTx_Compare(char vrc_CpStr[],char vrc_CpQtr[]){
	if(strstr(vrc_CpStr,vrc_CpQtr)!=NULL){
		return 1;
	}
	else{ 
		return 0;
	}
}


/*-----------------------DMA - USART-----------------------*/
/*
			USART - DMA - CHANNEL
			
			USART1  TX	- channel4
						  RX	- channel5
		
			USART2  TX	- channel7
						  RX	- channel6
						 
			USART3  TX	- channel2
						  RX	- channel3
*/


//NVIC_InitTypeDef NVIC_InitStructure;
DMA_InitTypeDef DMA_InitStructure;

void USARTx_Init_DMA(USART_TypeDef* USARTx){
	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_DMA1,ENABLE);

//	/* Configure the Priority Group to 2 bits */
//	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
//	/* Enable the USART1 TX DMA Interrupt */
//	NVIC_InitStructure.NVIC_IRQChannel = DMA1_Channel4_IRQn;
//	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
//	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
//	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
//	NVIC_Init(&NVIC_InitStructure);
//	/* Enable the USART1 RX DMA Interrupt */
//	NVIC_InitStructure.NVIC_IRQChannel = DMA1_Channel5_IRQn;
//	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
//	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
//	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
//	NVIC_Init(&NVIC_InitStructure);
	
	
//	if(USARTx == USART1){
//		NVIC_EnableIRQ(DMA1_Channel5_IRQn|DMA1_Channel4_IRQn);
//	}
//	else if(USARTx == USART2){
//		NVIC_EnableIRQ(DMA1_Channel7_IRQn|DMA1_Channel6_IRQn);
//	}
//	else if(USARTx == USART3){
//		NVIC_EnableIRQ(DMA1_Channel2_IRQn|DMA1_Channel3_IRQn);
//	}
}

void USARTx_Receive_DMA(USART_TypeDef* USARTx,char *pData, uint16_t len){
		
			/* USART1_RX DMA1 Channel 5 (See RM0008) */
		if(USARTx == USART1){
			DMA_DeInit(DMA1_Channel5);
		}
		else if(USARTx == USART2){
			DMA_DeInit(DMA1_Channel6);
		}
		else if(USARTx == USART3){
			DMA_DeInit(DMA1_Channel3);
		}
		DMA_InitStructure.DMA_PeripheralBaseAddr = (uint32_t)&USARTx->DR;
		DMA_InitStructure.DMA_MemoryBaseAddr = (uint32_t)pData;
		DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralSRC;
		DMA_InitStructure.DMA_BufferSize = len - 1;
		DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable;
		DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable;
		DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_Byte;
		DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_Byte;
		DMA_InitStructure.DMA_Mode = DMA_Mode_Circular;
		DMA_InitStructure.DMA_Priority = DMA_Priority_Low;
		DMA_InitStructure.DMA_M2M = DMA_M2M_Disable;	
		USART_DMACmd(USARTx, USART_DMAReq_Rx, ENABLE);
		
		if(USARTx == USART1){
			
			DMA_Init(DMA1_Channel5, &DMA_InitStructure);
					/* Enable DMA Stream Transfer Complete interrupt */
			DMA_ITConfig(DMA1_Channel5, DMA_IT_TC, ENABLE);
			
			DMA_Cmd(DMA1_Channel5, ENABLE);
		}
		else if(USARTx == USART2){
			
			DMA_Init(DMA1_Channel6, &DMA_InitStructure);
					/* Enable DMA Stream Transfer Complete interrupt */
			DMA_ITConfig(DMA1_Channel6, DMA_IT_TC, ENABLE);
			
			DMA_Cmd(DMA1_Channel6, ENABLE);
		}
		else if(USARTx == USART3){
			
			DMA_Init(DMA1_Channel3, &DMA_InitStructure);
					/* Enable DMA Stream Transfer Complete interrupt */
			DMA_ITConfig(DMA1_Channel3, DMA_IT_TC, ENABLE);
			
			DMA_Cmd(DMA1_Channel3, ENABLE);
		}
}


uint8_t USARTx_DMA_Send(USART_TypeDef* USARTx, char* DataArray, uint16_t count) {
	
		DMA_InitTypeDef DMA_InitStructure;
/* USART1_TX DMA1 Channel 4 (See RM0008) */
		if(USARTx == USART1){
			DMA_DeInit(DMA1_Channel4);
		}
		else if(USARTx == USART2){
			DMA_DeInit(DMA1_Channel7);
		}
		else if(USARTx == USART3){
			DMA_DeInit(DMA1_Channel2);
		}
		DMA_InitStructure.DMA_PeripheralBaseAddr = (uint32_t)&USARTx->DR;
		DMA_InitStructure.DMA_MemoryBaseAddr = (uint32_t)DataArray;
		DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralDST;
		DMA_InitStructure.DMA_BufferSize = count - 1;
		DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable;
		DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable;
		DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_Byte;
		DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_Byte;
		DMA_InitStructure.DMA_Mode = DMA_Mode_Normal;//DMA_Mode_Circular;//
		DMA_InitStructure.DMA_Priority = DMA_Priority_Low;
		DMA_InitStructure.DMA_M2M = DMA_M2M_Disable;
		USART_DMACmd(USARTx, USART_DMAReq_Tx, ENABLE);
	
		/* Enable USART TX DMA */
		USARTx->CR3 |= USART_CR3_DMAT;
		
		if(USARTx == USART1){
			
			DMA_Init(DMA1_Channel4, &DMA_InitStructure);
			/* Enable DMA Stream Transfer Complete interrupt */
			DMA_ITConfig(DMA1_Channel4, DMA_IT_TC, ENABLE);
			
			DMA_Cmd(DMA1_Channel4, ENABLE);
		}
		else if(USARTx == USART2){
			
			DMA_Init(DMA1_Channel7, &DMA_InitStructure);
			/* Enable DMA Stream Transfer Complete interrupt */
			DMA_ITConfig(DMA1_Channel7, DMA_IT_TC, ENABLE);
			
			DMA_Cmd(DMA1_Channel7, ENABLE);
		}
		else if(USARTx == USART3){
			
			DMA_Init(DMA1_Channel2, &DMA_InitStructure);
					/* Enable DMA Stream Transfer Complete interrupt */
			DMA_ITConfig(DMA1_Channel2, DMA_IT_TC, ENABLE);
			
			DMA_Cmd(DMA1_Channel2, ENABLE);
		}
		
	/* DMA has started */
	return 1;
}

//void DMA1_Channel2_IRQHandler(void){ // USART3_TX
///* Test on DMA Transfer Complete interrupt */
//	if(DMA_GetITStatus(DMA1_IT_TC2)){
///* Clear DMA Transfer Complete interrupt pending bit */
//		DMA_ClearITPendingBit(DMA1_IT_TC2);
///* ... */
//	}
//}

//void DMA1_Channel3_IRQHandler(void){ // USART3_RX
///* Test on DMA Transfer Complete interrupt */
//	if(DMA_GetITStatus(DMA1_IT_TC3)){
///* Clear DMA Transfer Complete interrupt pending bit */
//		DMA_ClearITPendingBit(DMA1_IT_TC3);
///* ... */
//	}
//}

//void DMA1_Channel4_IRQHandler(void){ // USART1_TX
///* Test on DMA Transfer Complete interrupt */
//	if(DMA_GetITStatus(DMA1_IT_TC4)){
///* Clear DMA Transfer Complete interrupt pending bit */
//		DMA_ClearITPendingBit(DMA1_IT_TC4);
///* ... */
//	}
//}
///**************************************************************************************/
//void DMA1_Channel5_IRQHandler(void){ // USART1_RX

///* Test on DMA Transfer Complete interrupt */
//	if (DMA_GetITStatus(DMA1_IT_TC5)){
//	/* Clear DMA Transfer Complete interrupt pending bit */
//		DMA_ClearITPendingBit(DMA1_IT_TC5);
//	/* ... */
//	}
//}

//void DMA1_Channel6_IRQHandler(void){ // USART2_RX
///* Test on DMA Transfer Complete interrupt */
//	if(DMA_GetITStatus(DMA1_IT_TC6)){
///* Clear DMA Transfer Complete interrupt pending bit */
//		DMA_ClearITPendingBit(DMA1_IT_TC6);
///* ... */
//	}
//}

//void DMA1_Channel7_IRQHandler(void){ // USART2_TX
///* Test on DMA Transfer Complete interrupt */
//	if(DMA_GetITStatus(DMA1_IT_TC7)){
///* Clear DMA Transfer Complete interrupt pending bit */
//		DMA_ClearITPendingBit(DMA1_IT_TC7);
///* ... */
//	}
//}

uint8_t USARTx_DMA_Puts(USART_TypeDef* USARTx, char* DataArray) {
	/* Call DMA Send function */
	return USARTx_DMA_Send(USARTx, DataArray, sizeof(DataArray));
}


#include <stdint.h>



#ifndef NVIC
#define NVIC

typedef enum{
	WWDG=0,
	PVD,
	TAMPER,
	RTC,
	FLASH,
	RCC,
	EXTI0,
	EXTI1,
	EXTI2,
	EXTI3,
	EXTI4,
	DMA1_Stream0,
	DMA1_Stream1,
	DMA1_Stream2,
	DMA1_Stream3,
	DMA1_Stream4,
	DMA1_Stream5,
	DMA1_Stream6,
	DMA1_Stream7,
	ADC1_2,
	Can1_Tx
	,USART2=38
	,USART3
	,DMA2_Stream0=56
	,DMA2_Stream1
	,DMA2_Stream2
	,DMA2_Stream3
	,DMA2_Stream4
	, OTG_FS
	,DMA2_Stream5
	,DMA2_Stream6
	,DMA2_Stream7



}IRQ_t ;



void NVIC_Pref_en(IRQ_t);
void NVIC_Pref_dis(IRQ_t);
void NVIC_Pref_Flag_en(IRQ_t);
void NVIC_Pref_Flag_dis(IRQ_t);
void NVIC_Priority_set(uint8_t ,uint8_t );



#endif



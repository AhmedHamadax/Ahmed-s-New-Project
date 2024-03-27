/*
 * DMA.h
 *
 *  Created on: Aug 29, 2023
 *      Author: Ahmed
 */

#ifndef DMA_H_
#define DMA_H_
#include "NVIC.h"
#include "RCC.h"
#include "RCC_Config.h"
#include "GPIO.h"
#include "Error.h"
#include "stm32f446re.h"
#include <stdlib.h>

typedef enum{
	dma1,
	dma2
} DMA_t;
typedef enum{
	No_inc,
	Prefinc=1,
	Meminc,
	Meminc_Prefinc
} Inc_Mode_t;

typedef enum{
	byte,
	half_word,
	word

} Mem_width_t;

typedef enum{
	Channel0,
	Channel1,
	Channel2,
	Channel3,
	Channel4,
	Channel5,
	Channel6,
	Channel7

} Channel_t;
typedef enum{
	Stream0,
	Stream1,
	Stream2,
	Stream3,
	Stream4,
	Stream5,
	Stream6,
	Stream7,

} Stream_t;

typedef enum{
	Low,
	Medium,
	High,
	Very_High
} Priority_t;

typedef enum{
	P2M,
	M2P,
	M2M
} Direction_t;

typedef enum{
	Half_Trans,
	Full_Trans

} Int_Trans_t;


typedef enum{
	Direct,
	FIFO
} DMA_Mode_t_T;


typedef enum{
	Quarter_Threshold,
	Half_Threshold,
	Three_Quarter_Threshold,
	Full_Threshold
} Threshold_t;

typedef enum{
	Memory0,
	Memory1
} Mem_Target_t;

typedef enum{
	FE_int_dis,
	FE_int_en
} FE_en;

typedef enum{
	en,
	dis
	
} Direct_int_en;



typedef struct {
	DMA_t DMA;
	Stream_t stream;
	Channel_t Channel;
	Inc_Mode_t Incmode;
	Priority_t Priority;
	Direction_t Direction;
	DMA_Mode_t_T Mode;
	Threshold_t Threshold;
	Int_Trans_t Transfer;
	Status_t status;
	Mem_Target_t Memory;
	FE_en FE_int;
	Direct_int_en direct_int;
	Mem_width_t Mem_size;
}DMA_Handle_t;

#define DMA1_ptr ((DMA_Reg_t*) DMA1_Base_Add )
#define DMA2_ptr ((DMA_Reg_t*) DMA2_Base_Add )



Err_Status DMA_Sys_Init(IRQ_t,uint8_t);
Err_Status DMA_Stream_Init(DMA_Handle_t*);
Err_Status DMA1_Handle_Init(DMA_Handle_t*,Stream_t,Channel_t,Direction_t);
Err_Status DMA_Transfer_M2M(DMA_Handle_t*,uint32_t  ,uint32_t , uint16_t );
Err_Status DMA_Transfer_P2M(DMA_Handle_t*,uint32_t  ,uint32_t , uint16_t );
Err_Status DMA_Transfer_M2P(DMA_Handle_t*,uint32_t  ,uint32_t , uint16_t );





#endif /* DMA_H_ */

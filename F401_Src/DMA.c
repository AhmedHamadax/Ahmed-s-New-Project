/*
 * DMA.c
 *
 *  Created on: Aug 29, 2023
 *      Author: Ahmed
 */

#include <stdint.h>
#include "DMA.h"
#include "SPI.h"
#include "stm32f446re.h"

//extern SPI_Reg_t * SPI[4];
DMA_Reg_t *DMA[2]={DMA1_ptr,DMA2_ptr};

Err_Status DMA_Sys_Init(IRQ_t y,uint8_t p){
	Err_Status er=OK;
	if(  (y>=11 && y<=18)  ||   (y>=56 && y<=70)  ){
			if(y>=56) y-=34;

	RCC_AHBEnableClock(DMA1+((y)/18) );
		y+=34;
	NVIC_Pref_en( y );
	NVIC_Priority_set(y,p);

	}
	else er=NOK;







return er;
}

Err_Status DMA_Stream_Init(DMA_Handle_t* hdma){
	Err_Status er=OK;

	if( hdma!=NULL  ){

	DMA[hdma->DMA]->Stream[SxCR+((hdma->stream)*6) ]= 0;
	DMA[hdma->DMA]->Stream[SxCR+((hdma->stream)*6) ]|= ( (hdma->Channel)  <<25  );
	DMA[hdma->DMA]->Stream[SxCR+((hdma->stream)*6) ]|= ( (hdma->Priority)  <<16  );
	DMA[hdma->DMA]->Stream[SxCR+((hdma->stream)*6) ]|= ( (hdma->Direction)  <<6  );
//	DMA[hdma->DMA]->Stream[SxCR+((hdma->stream)*6) ]|= (  0b1 <<(3+(hdma->Transfer))  );
	DMA[hdma->DMA]->Stream[SxCR+((hdma->stream)*6) ]|= ( hdma->Incmode  )<<9;
	DMA[hdma->DMA]->Stream[SxCR+((hdma->stream)*6) ]|= ( (hdma->Mem_size)  <<13  );


	DMA[hdma->DMA]->Stream[SxFCR+((hdma->stream)*6) ]= 0;
	DMA[hdma->DMA]->Stream[SxFCR+((hdma->stream)*6) ]|= ( hdma->Mode  )<<2;
	DMA[hdma->DMA]->Stream[SxFCR+((hdma->stream)*6) ]|= ( hdma->Threshold  );
	DMA[hdma->DMA]->Stream[SxFCR+((hdma->stream)*6) ]|= ( hdma->FE_int   )<<7;
	DMA[hdma->DMA]->Stream[SxFCR+((hdma->stream)*6) ]|= ( hdma->direct_int   )<<2;

	DMA[hdma->DMA]->Stream[SxCR+((hdma->stream)*6) ]|= ( 1  )<<4;


//	DMA[hdma->DMA]->Stream[SxCR+((hdma->stream)*6) ]|= ( hdma->status  );
	}
	else er=NOK;
return er;

}

Err_Status DMA1_Handle_Init(DMA_Handle_t*HDMA,Stream_t Stream,Channel_t Channel,Direction_t Dir){
	Err_Status er=OK;

		if( HDMA!=NULL  ){

//	HDMA->Channel=Channel4;
	HDMA->DMA=dma1;
	HDMA->Direction=Dir;
	HDMA->Mode=Direct;
	HDMA->Priority=Very_High;
	HDMA->stream=Stream;
	HDMA->Channel=Channel;
	HDMA->Threshold=Full_Threshold;
	HDMA->Transfer=Full_Trans;
	HDMA->Incmode=Meminc;
	HDMA->status=on;
	HDMA->Memory =Memory0;
	HDMA->FE_int=FE_int_dis;
	HDMA->direct_int=en;
	HDMA->Mem_size=byte;
		}
		else er=NOK;
		return er;

}
Err_Status DMA2_Handle_Init(DMA_Handle_t*HDMA){
	Err_Status er=OK;

		if( HDMA!=NULL  ){

//	HDMA->Channel=Channel4;
	HDMA->DMA=dma1;
	HDMA->Direction=P2M;
	HDMA->Mode=Direct;
	HDMA->Priority=Very_High;
	HDMA->stream=Stream2;
	HDMA->Channel=Channel7;
	HDMA->Threshold=Full_Threshold;
	HDMA->Transfer=Full_Trans;
	HDMA->Incmode=Meminc;
	HDMA->status=on;
	HDMA->Memory =Memory0;
	HDMA->FE_int=FE_int_dis;
	HDMA->direct_int=en;
	HDMA->Mem_size=byte;
		}
		else er=NOK;
		return er;

}




Err_Status DMA_Transfer_M2M(DMA_Handle_t*HDMA_Copy,uint32_t addressR ,uint32_t addressT, uint16_t length){
	Err_Status er=OK;

				if( HDMA_Copy!=NULL  ){

	DMA[HDMA_Copy->DMA]->Stream[SxNDTR+((HDMA_Copy->stream)*6) ]=length;

	if (   HDMA_Copy->Memory ==Memory0  ){
	DMA[HDMA_Copy->DMA]->Stream[SxM0AR+((HDMA_Copy->stream)*6) ]=addressR;
	DMA[HDMA_Copy->DMA]->Stream[SxM1AR+((HDMA_Copy->stream)*6) ]=addressT;
	}
	else if (   HDMA_Copy->Memory ==Memory1  ){
		DMA[HDMA_Copy->DMA]->Stream[SxM0AR+((HDMA_Copy->stream)*6) ]=addressT;
		DMA[HDMA_Copy->DMA]->Stream[SxM1AR+((HDMA_Copy->stream)*6) ]=addressR;


	}




	if( (HDMA_Copy->stream) <=3){
	DMA[HDMA_Copy->DMA]->LIFCR|= 0b1<<HDMA_Copy->stream;
	}
	else if( (HDMA_Copy->stream) >3){
		DMA[HDMA_Copy->DMA]->HIFCR|= 0b1<<HDMA_Copy->stream;
		}
	DMA[HDMA_Copy->DMA]->Stream[SxCR+((HDMA_Copy->stream)*6) ]|= ( 0b1  );
				}
				else er=NOK;

	return er;



}


Err_Status DMA_Transfer_P2M(DMA_Handle_t*HDMA_Copy,uint32_t addressP ,uint32_t addressM, uint16_t length){
	Err_Status er=OK;

				if( HDMA_Copy!=NULL  ){

	DMA[HDMA_Copy->DMA]->Stream[SxNDTR+((HDMA_Copy->stream)*6) ]=length;


		DMA[HDMA_Copy->DMA]->Stream[SxM0AR+((HDMA_Copy->stream)*6) ]=addressM;

		DMA[HDMA_Copy->DMA]->Stream[SxPAR+((HDMA_Copy->stream)*6) ]=0x4001300c;

		if( (HDMA_Copy->stream) <=3){
		DMA[HDMA_Copy->DMA]->LIFCR|= 0b1<<HDMA_Copy->stream;
		}
		else if( (HDMA_Copy->stream) >3){
			DMA[HDMA_Copy->DMA]->HIFCR|= 0b1<<HDMA_Copy->stream;
			}
			DMA[HDMA_Copy->DMA]->Stream[SxCR+((HDMA_Copy->stream)*6) ]|= (  0b1 <<(3+(HDMA_Copy->Transfer))  );

		DMA[HDMA_Copy->DMA]->Stream[SxCR+((HDMA_Copy->stream)*6) ]|= ( 0b1  );
				}
				else er=NOK;

		return er;


}



Err_Status DMA_Transfer_M2P(DMA_Handle_t*HDMA_Copy,uint32_t addressR ,uint32_t addressT, uint16_t length){

	Err_Status er=OK;

			if( HDMA_Copy!=NULL  ){


	DMA[HDMA_Copy->DMA]->Stream[SxNDTR+((HDMA_Copy->stream)*6) ]=length;


	DMA[HDMA_Copy->DMA]->Stream[SxPAR+((HDMA_Copy->stream)*6) ]=addressR;

	DMA[HDMA_Copy->DMA]->Stream[SxM0AR+((HDMA_Copy->stream)*6) ]=addressT;

	if( (HDMA_Copy->stream) <=3){
	DMA[HDMA_Copy->DMA]->LIFCR|= 0b1<<HDMA_Copy->stream;
	}
	else if( (HDMA_Copy->stream) >3){
		DMA[HDMA_Copy->DMA]->HIFCR|= 0b1<<HDMA_Copy->stream;
		}
	DMA[HDMA_Copy->DMA]->Stream[SxCR+((HDMA_Copy->stream)*6) ]|= ( 0b1  );

			}
			else	er=NOK;
			return er;
}








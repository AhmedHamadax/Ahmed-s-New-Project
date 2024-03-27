/*
 * SPI.c
 *
 *  Created on: Sep 13, 2023
 *      Author: Ahmed
 */


#include "SPI.h"
#include "DMA.h"
#define READ_BIT(num, position) ((num >> position) & 1)


SPI_Reg_t * SPI[4]={(SPI_Reg_t*)SPI1_Base_Address,(SPI_Reg_t*)SPI2_Base_Address,(SPI_Reg_t*)SPI3_Base_Address,(SPI_Reg_t*)SPI4_Base_Address};

extern DMA_Reg_t *DMA[2];

uint32_t * dest_ptr=NULL;


Err_Status SPI_Init(SPI_Handle_t*SPI_handle){

	Err_Status err=OK;
	if(SPI_handle!=NULL){


		SPI[SPI_handle->SPI_Number]->CR1|=(SPI_handle->Master_Slave)<<2;

		SPI[SPI_handle->SPI_Number]->CR1|=(SPI_handle->Duplex)<<15;
		SPI[SPI_handle->SPI_Number]->CR1|=(SPI_handle->One_Direction_Mode)<<14;
		SPI[SPI_handle->SPI_Number]->CR1|=(SPI_handle->CRC)<<13;
		SPI[SPI_handle->SPI_Number]->CR1|=(SPI_handle->Frame_Size)<<11;
		SPI[SPI_handle->SPI_Number]->CR1|=(SPI_handle->Recieve_Only)<<10;
		SPI[SPI_handle->SPI_Number]->CR1|=(SPI_handle->SW_Slave_Managament)<<9;
		SPI[SPI_handle->SPI_Number]->CR1|=(SPI_handle->SSI)<<8;
		SPI[SPI_handle->SPI_Number]->CR1|=(SPI_handle->TXEIE)<<7;
		SPI[SPI_handle->SPI_Number]->CR1|=(SPI_handle->RXNEIE)<<6;



		SPI[SPI_handle->SPI_Number]->CR2|=(SPI_handle->DMA_TX_IT)<<1;
		SPI[SPI_handle->SPI_Number]->CR2|=(SPI_handle->DMA_RX_IT)<<0;



		SPI[SPI_handle->SPI_Number]->CR1|=(1)<<6;// Enable

	}
	else err=NOK;





	return err;
}



Err_Status SPI_Send_Data_IT(SPI_Handle_t*SPI_handle,uint8_t* Data){
	Err_Status err=OK;
		if(SPI_handle!=NULL){
	SPI[SPI_handle->SPI_Number]->DR=*Data;

		}

		return err;

}
uint32_t SR=5;



Err_Status SPI_Transfer_P2M_DMA(DMA_Handle_t*HDMA_Copy,SPI_Handle_t*SPI_handle,uint32_t addressM, uint16_t length){
	Err_Status er=OK;
				if( HDMA_Copy!=NULL  ){

	DMA[HDMA_Copy->DMA]->Stream[SxNDTR+((HDMA_Copy->stream)*6) ]=length;

		DMA[HDMA_Copy->DMA]->Stream[SxM0AR+((HDMA_Copy->stream)*6) ]=addressM;
		DMA[HDMA_Copy->DMA]->Stream[SxPAR+((HDMA_Copy->stream)*6) ]=&(SPI[SPI_handle->SPI_Number]->DR);

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


Err_Status SPI_Recieve_Data_IT(SPI_Handle_t*SPI_handle,uint32_t*Destination){

	Err_Status err=OK;
	if(SPI_handle!=NULL){


	SPI[SPI_handle->SPI_Number]->CR2|=(0b1)<<6;
	dest_ptr=Destination;

	}

	else err=NOK;

	return err;

}








void SPI1_IRQHandler(void){
	if (   READ_BIT(SPI[0]->SR,0)==1   ){
		*dest_ptr=SPI[0]->DR;
		SPI[0]->CR2&=~(1<<6);

		}
	if (  READ_BIT(SPI[0]->SR,1)==1   ){
	SPI[0]->CR2&=~(1<<7);
	}



}

void SPI2_IRQHandler(void){
	int x=0;
}

void SPI3_IRQHandler(void){
	int x=0;
}

void SPI4_IRQHandler(void){
	int x=0;
}







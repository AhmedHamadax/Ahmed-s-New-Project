/*
 * SPI.c
 *
 *  Created on: Sep 13, 2023
 *      Author: Ahmed
 */


#include "SPI.h"
#include "rcc.h"
#include "GPIO_interface.h"
#include "Timer.h"
SPI_Reg_t * SPI[4]={(SPI_Reg_t*)SPI1_Base_Address,(SPI_Reg_t*)SPI2_Base_Address,(SPI_Reg_t*)SPI3_Base_Address,(SPI_Reg_t*)SPI4_Base_Address};

uint32_t * dest_ptr=NULL;

uint32_t * send_ptr=NULL;
uint8_t speed;
uint8_t flag_for_alarm=0;
Err_Status SPI_Init(SPI_Handle_t*SPI_handle){

	Err_Status err=OK;
	if(SPI_handle!=NULL){
		SPI[SPI_handle->SPI_Number]->CR1|=(SPI_handle->SPI_En)<<6;// Enable



		SPI[SPI_handle->SPI_Number]->CR1|=(SPI_handle->Duplex)<<15;
		SPI[SPI_handle->SPI_Number]->CR1|=(SPI_handle->One_Direction_Mode)<<14;
		SPI[SPI_handle->SPI_Number]->CR1|=(SPI_handle->CRC)<<13;
		SPI[SPI_handle->SPI_Number]->CR1|=(SPI_handle->Frame_Size)<<12;
		SPI[SPI_handle->SPI_Number]->CR1|=(SPI_handle->Recieve_Only)<<11;
		SPI[SPI_handle->SPI_Number]->CR1|=(SPI_handle->SW_Slave_Managament)<<9;
		SPI[SPI_handle->SPI_Number]->CR1|=(SPI_handle->SSI)<<8;
		SPI[SPI_handle->SPI_Number]->CR2|=(SPI_handle->SS_En)<<2;
		SPI[SPI_handle->SPI_Number]->CR2|=(SPI_handle->SPI_TXEIE)<<7;
		SPI[SPI_handle->SPI_Number]->CR2|=(SPI_handle->SPI_RXEIE)<<6;
		SPI[SPI_handle->SPI_Number]->CR1|=(SPI_handle->Master_Slave)<<2;

		SPI[SPI_handle->SPI_Number]->CR1|=(SPI_handle->SPI_En)<<6;// Enable

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


Err_Status SPI_Send_Data_DMA(SPI_Handle_t*SPI_handle,uint32_t Data){
	Err_Status err=OK;

   if(SPI_handle!=NULL){

	send_ptr=&Data;


   }
		else err=NOK;

	return err;

}


Err_Status SPI_Recieve_Data_DMA(SPI_Handle_t*SPI_handle,uint32_t*Destination){

	Err_Status err=OK;

	if( (SPI_handle!=NULL) &&(Destination!=NULL)  ){

	dest_ptr=Destination;

	SPI[SPI_handle->SPI_Number]->CR2|=(0b1); //Enabling RX DMA Interrupt


	}

	else err=NOK;

	return err;

}


Err_Status SPI_Recieve_Data_IT(SPI_Handle_t*SPI_handle,uint32_t*Destination){

	Err_Status err=OK;

	if(SPI_handle!=NULL){

	dest_ptr=Destination;

	SPI[SPI_handle->SPI_Number]->CR2|=(0b1)<<6;// RX Global_Interrupt Enable


	}

	else err=NOK;

	return err;

}

/*******         DMA_RX IRQ Handlers                   *****/
void DMA1_Channel2_IRQHandler(void){

	if(dest_ptr!=NULL  &&(((SPI[0]->SR))&0b1==1) ){

	*dest_ptr=SPI[0]->DR;
	SPI[1]->CR1&=~(0b1)<<6;// Disable&Reset

	}
}


void DMA1_Channel4_IRQHandler(void){

	if(dest_ptr!=NULL  &&(((SPI[1]->SR))&0b1==1) ){

	*dest_ptr=SPI[1]->DR;
	SPI[1]->CR1&=~(0b1)<<6;// Disable&Reset

	}
}

void DMA2_Channel1_IRQHandler(void){

	if(dest_ptr!=NULL  &&(((SPI[2]->SR))&0b1==1) ){

	*dest_ptr=SPI[2]->DR;
	SPI[2]->CR1&=~(0b1)<<6;// Disable&Reset

	}
}

/*******         DMA_TX IRQ Handlers                   *****/

void DMA2_Channel2_IRQHandler(void){

	if  (  ((SPI[2]->SR)>>1)&0b1==1    ){
		SPI[2]->DR=*send_ptr;
		SPI[2]->CR1&=~(0b1)<<6;// Disable&Reset

	}
}

void DMA1_Channel3_IRQHandler(void){

	if  (  ((SPI[0]->SR)>>1)&0b1==1    ){
		SPI[0]->DR=*send_ptr;
		SPI[0]->CR1&=~(0b1)<<6;// Disable&Reset

	}
}

void DMA1_Channel5_IRQHandler(void){

	if  (  ((SPI[1]->SR)>>1)&0b1==1    ){
		SPI[1]->DR=*send_ptr;
		SPI[1]->CR1&=~(0b1)<<6;// Disable&Reset

	}
}



/**************************/









/*******         GLOBAL_SPI_IRQ Handlers                   *****/

void SPI1_IRQHandler(void){
if  (  ((SPI[0]->SR)>>1)&0b1==1    ){
//	SPI[0]->DR=*send_ptr;


}

if  (  ((SPI[0]->SR)&0b1)==1    ){
	*dest_ptr=SPI[0]->DR;
	if(((*dest_ptr)==101)){
		flag_for_alarm=1;
		set_reset_pin(PORTC,PIN13,On);	/* Loop forever */
		Timer4_Set_Channel_Duty_Cycle(Channel1_Timer,speed);// 50->25k  100->122000
	}
	else if((*dest_ptr)==102) {
			flag_for_alarm=0;
			Timer4_Set_Channel_Duty_Cycle(Channel1_Timer,0);// 50->25k  100->122000

			}
	else if((flag_for_alarm==1)){
		speed=*dest_ptr;
		Timer4_Set_Channel_Duty_Cycle(Channel1_Timer,speed);// 50->25k  100->122000

	}

	else {
		speed=*dest_ptr;

	}

}

}

void SPI2_IRQHandler(void){
	if  (  ((SPI[1]->SR)>>1)&0b1==1    ){
		SPI[1]->DR=*send_ptr;
		SPI[1]->CR1&=~(0b1)<<6;// Disable&Reset

	}
	if  (  ((SPI[1]->SR))&0b1==1    ){
		*dest_ptr=SPI[1]->DR;
		SPI[1]->CR1&=~(0b1)<<6;// Disable&Reset

	}

}

void SPI3_IRQHandler(void){
	if  (  ((SPI[2]->SR)>>1)&0b1==1    ){
		SPI[2]->DR=*send_ptr;
		SPI[2]->CR1&=~(0b1)<<6;// Disable&Reset

	}
	if  (  ((SPI[2]->SR))&0b1==1    ){
		*dest_ptr=SPI[2]->DR;
		SPI[2]->CR1&=~(0b1)<<6;// Disable&Reset

	}
}

void SPI4_IRQHandler(void){
	if  (  ((SPI[3]->SR)>>1)&0b1==1    ){
		SPI[3]->DR=*send_ptr;
		SPI[3]->CR1&=~(0b1)<<6;// Disable&Reset

	}
	if  (  ((SPI[3]->SR))&0b1==1    ){
		*dest_ptr=SPI[3]->DR;
		SPI[3]->CR1&=~(0b1)<<6;// Disable&Reset

	}
}























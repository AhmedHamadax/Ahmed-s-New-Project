/*
 * I2C.c
 *
 *  Created on: Sep 12, 2023
 *      Author: Ahmed
 */

//#include "DMA.h"

#include "I2C.h"
#include <stdlib.h>
#include "std_macro.h"
#include "sytick.h"
extern DMA_Reg_t *DMA[2];
#define System_Clock 16UL
i2c_reg_t * I2C[3]={(i2c_reg_t * )i2c1_Base_Address,(i2c_reg_t * )i2c2_Base_Address,(i2c_reg_t * )i2c3_Base_Address};
uint32_t status;



Err_Status i2c_init(i2c_handle_t*i2c_h){
uint8_t x=i2c_h->i2c_number-1;

I2C[x]->CR1|=0b1<<15;
I2C[x]->CR1&=~(0b1<<15);
I2C[x]->TRISE= 17; //Ack en


	// reseting





	I2C[x]->CCR|=(i2c_h->mode)<<15;
	// FM MODE

	I2C[x]->CR2|=i2c_h->clock;//Set Sys Clock

	I2C[x]->CR2|=(i2c_h->sys_int)<<(9);
	I2C[x]->CR2|=(i2c_h->DMA_int)<<(11);
//	I2C[x]->CR2|=(1)<<(10);
//	I2C[x]->CR2|=(1)<<(9);



	if(i2c_h->mode==SM){

	I2C[x]->CCR|=System_Clock*5;

	}
	else if (i2c_h->mode==FM){

		I2C[x]->CCR|=(System_Clock*125)/100;

	}

	I2C[x]->CR1|=0b1;
	I2C[i2c_h->i2c_number-1]->CR1|= 0b1<<10; //Ack en


}

Err_Status i2c_set_add(i2c_handle_t*i2c_handle,uint16_t add){
	Err_Status err=OK;
	uint8_t x=i2c_handle->i2c_number-1;

		if(i2c_handle!=NULL){

			if ( (i2c_handle->Add_Mode)==seven_bit){

				I2C[x]->OAR1&=~(0b1111111);
				I2C[x]->OAR1|=(add)<<1;

			}
			else if((i2c_handle->Add_Mode)==ten_bit){

				I2C[x]->OAR1&=~(0b1111111111);
				I2C[x]->OAR1|=(add);

			}
			else{
				err=NOK;

			}


		}

	else err=NOK;
	return err;
}



Err_Status i2c_start_it(i2c_handle_t*i2c_h,uint32_t address,RW_t RW){

	Err_Status err=OK;
	if(i2c_h!=NULL){
		while(READBIT(  (I2C[i2c_h->i2c_number-1]->SR2) ,1   )==1);
	I2C[i2c_h->i2c_number-1]->CR1|= 0b1<<10; //Ack en

	I2C[i2c_h->i2c_number-1]->CR1|=0b1<<8;

		while(READBIT(  (I2C[i2c_h->i2c_number-1]->SR1) ,0   )==0);

	I2C[i2c_h->i2c_number-1]->DR=(address<<1)|RW;
	while(READBIT(  (I2C[i2c_h->i2c_number-1]->SR1) ,1   )==0);
	while(READBIT(  (I2C[i2c_h->i2c_number-1]->SR2) ,1   )==0);


	}
	else err=NOK;
	return err;
}


Err_Status i2c_write_data_DMA(i2c_handle_t*i2c_h,uint8_t* data_address,DMA_Handle_t*HDMA_Copy,uint8_t Length){
	Err_Status er=OK;
					if( HDMA_Copy!=NULL  ){

						DMA[HDMA_Copy->DMA]->Stream[SxCR+((HDMA_Copy->stream)*6) ]|= ( (M2P)  <<6  );

			I2C[i2c_h->i2c_number-1]->CR2|=(1)<<(11);

			DMA[HDMA_Copy->DMA]->Stream[SxNDTR+((HDMA_Copy->stream)*6) ]=Length;
				DMA[HDMA_Copy->DMA]->Stream[SxM0AR+((HDMA_Copy->stream)*6) ]=data_address;
				DMA[HDMA_Copy->DMA]->Stream[SxPAR+((HDMA_Copy->stream)*6) ]=&(I2C[i2c_h->i2c_number-1]->DR);

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


Err_Status i2c_write_data_IT(i2c_handle_t*i2c_h,uint32_t Data){


	Err_Status err=OK;

	if(i2c_h!=NULL){

		if(  1 ){

           	I2C[i2c_h->i2c_number-1]->DR=Data;
           	I2C[i2c_h->i2c_number-1]->CR2|=(1)<<(9);
           	I2C[i2c_h->i2c_number-1]->CR2|=(1)<<(10);

		}
		else err=NACK_err;


		}
		else err=NOK;
		return err;

	}

uint32_t* Dest_ptr;


Err_Status i2c_recieve_data_IT(i2c_handle_t*i2c_h,uint32_t* Data){


	Err_Status err=OK;
	if(i2c_h!=NULL){

       	I2C[i2c_h->i2c_number-1]->CR2|=(1)<<(9);
       	I2C[i2c_h->i2c_number-1]->CR2|=(1)<<(10);

			Dest_ptr=Data;

		}



		else err=NOK;
		return err;

	}


Err_Status i2c_recieve_data_DMA(i2c_handle_t*i2c_h,uint32_t* data_address,DMA_Handle_t*HDMA_Copy,uint8_t Length){


	Err_Status er=OK;
						if( HDMA_Copy!=NULL  ){
//							while(READBIT(  (I2C[i2c_h->i2c_number-1]->SR1) ,6   )==0);

							DMA[HDMA_Copy->DMA]->Stream[SxCR+((HDMA_Copy->stream)*6) ]|= ( (P2M)  <<6  );

							I2C[i2c_h->i2c_number-1]->CR2|=(1)<<(11);

							DMA[HDMA_Copy->DMA]->Stream[SxNDTR+((HDMA_Copy->stream)*6) ]=Length;

				DMA[HDMA_Copy->DMA]->Stream[SxM0AR+((HDMA_Copy->stream)*6) ]=data_address;
				DMA[HDMA_Copy->DMA]->Stream[SxPAR+((HDMA_Copy->stream)*6) ]=&(I2C[i2c_h->i2c_number-1]->DR);

				if( (HDMA_Copy->stream) <=3){
				DMA[HDMA_Copy->DMA]->LIFCR|= 0b1<<HDMA_Copy->stream;
				}
				else if( (HDMA_Copy->stream) >3){
					DMA[HDMA_Copy->DMA]->HIFCR|= 0b1<<HDMA_Copy->stream;
					}

				DMA[HDMA_Copy->DMA]->Stream[SxCR+((HDMA_Copy->stream)*6) ]|= ( 0b1  );
				DMA[HDMA_Copy->DMA]->HIFCR|=(0b1<<11);
				DMA[HDMA_Copy->DMA]->HIFCR|=(0b1<<10);
						}
						else er=NOK;
				return er;

	}



Err_Status i2c_stop(i2c_handle_t*i2c_h){

	Err_Status err=OK;

	if(i2c_h!=NULL){
		while(READBIT(  (I2C[i2c_h->i2c_number-1]->SR1) ,2   )==0);
		I2C[i2c_h->i2c_number-1]->CR1&= ~(0b1<<10); //Ack en

		(I2C[i2c_h->i2c_number-1]->SR1)&=~(0b1<<1);
//		while(READBIT(  (I2C[i2c_h->i2c_number-1]->SR1) ,2   )==1);

		I2C[i2c_h->i2c_number-1]->CR1|=0b1<<9;
//		while(READBIT(  (I2C[i2c_h->i2c_number-1]->SR1) ,2   )==1);



	}

	else err=NOK;


}

Err_Status i2c_stop_recieve(i2c_handle_t*i2c_h){

	Err_Status err=OK;
	uint32_t recdata=9;
	if(i2c_h!=NULL){
		while(READBIT(  (I2C[i2c_h->i2c_number-1]->SR1) ,2   )==0);

		I2C[i2c_h->i2c_number-1]->CR1&= ~(0b1<<10); //Ack en
		while(READBIT(  (I2C[i2c_h->i2c_number-1]->CR1) ,10   )==1);
		recdata=I2C[i2c_h->i2c_number-1]->DR;
		(I2C[i2c_h->i2c_number-1]->SR1)&=~(0b1<<1);
//		while(READBIT(  (I2C[i2c_h->i2c_number-1]->SR1) ,2   )==1);
//		while(READBIT(  (I2C[i2c_h->i2c_number-1]->SR1) ,2   )==0);

		I2C[i2c_h->i2c_number-1]->CR1|=0b1<<9;
//		while(READBIT(  (I2C[i2c_h->i2c_number-1]->SR1) ,2   )==1);



	}

	else err=NOK;


}

uint8_t current_stream_running;


void I2C_IRQ_Handler(uint8_t num){
uint32_t SR= I2C[num]->SR1;
if(   (READBIT(  (I2C[num]->SR1) ,0   )) ==1    ){

	status=Start;



					}

	if(   (READBIT(  (I2C[num]->SR1) ,6   )) ==1    ){


//								*Dest_ptr=I2C[num]->DR; set with sys int
//								DMA[0]->Stream[SxCR+((5)*6) ]|= ( 0b1  );
//								uint32_t data_re=(I2C[0]->DR);
//								data_re=(I2C[0]->DR);
//								status=Data_Recieved;


				}




		if(     READBIT(  (I2C[num]->SR1) ,1   )     ){

					status=Address_Sent;

					if(     READBIT(  (I2C[num]->SR1) ,10   )!=1     ){

							status=Address_Sent_Ack;

						}
					else {
						status=Address_Sent_NAck;
					}
		}


		if(   (READBIT(  (I2C[num]->SR1) ,7   )) ==1    ){

					status=Data_Sent;
					if(     READBIT(  (I2C[num]->SR1) ,10   )!=1     ){

						status=Data_Sent_Ack;

							}
						else {
							status=Data_Sent_NAck;
						}

		}







		if(     READBIT(  (I2C[num]->SR1) ,4   )     ){

						status=0;

					}

		I2C[num]->CR2&=~(0b1<<9);
//		I2C[num]->CR2&=~(0b1<<10);
//		I2C[num]->CR2&=~(0b1<<11);
		DMA[num]->Stream[SxCR+((current_stream_running)*6) ]|= ( 0b1  );


		}


void I2C_IRQ_Handler_DMA(uint8_t num){
//uint32_t SR= I2C[num]->SR1;





}

uint8_t current_stream_running;

void 	DMA1_Stream4_IRQHandler(void){

	uint8_t num=2;

	I2C_IRQ_Handler(num);



}

void 	DMA1_Stream5_IRQHandler(void){

	uint8_t num=0;
	current_stream_running=5;
	I2C_IRQ_Handler_DMA(num);
	DMA[num]->HIFCR|=(0b1<<11);
	DMA[num]->HIFCR|=(0b1<<10);


}

void 	DMA1_Stream6_IRQHandler(void){

	uint8_t num=0;
	current_stream_running=6;
	I2C_IRQ_Handler_DMA(num);
	DMA[num]->HIFCR|=(0b1<<21);
	DMA[num]->HIFCR|=(0b1<<20);
//		I2C[num]->CR2&=~(0b1<<11);


}


void 	DMA1_Stream7_IRQHandler(void){

	uint8_t num=1;

		I2C_IRQ_Handler(num);


}
void I2C1_EV_IRQHandler(void){


	uint8_t num=0;

			I2C_IRQ_Handler(num);


}

void I2C1_ER_IRQHandler(void){



			I2C_IRQ_Handler(0);

}


void I2C2_EV_IRQHandler(void){


	uint8_t num=1;

			I2C_IRQ_Handler(num);





}

void I2C3_EV_IRQHandler(void){


	uint8_t num=2;

			I2C_IRQ_Handler(num);





}










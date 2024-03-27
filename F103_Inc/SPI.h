/*
 * SPI.h
 *
 *  Created on: Sep 13, 2023
 *      Author: Ahmed
 */

#ifndef SPI_H_
#define SPI_H_

#include "stm32f103.h"
#include "Error.h"
#include <stdint.h>
#include <stdlib.h>
typedef enum{SPI1,SPI2,SPI3,SPI4}SPI_Number_t;

typedef enum{Full_Duplex,Half_Duplex}Duplex_t;

typedef enum{Recieve_Only,Transmit_Only}One_Direction_Mode_t;

typedef enum{Slave,Master}Master_Slave_t;

typedef enum{Dis,En}En_t;

typedef enum{Eight_Bit,Sixteen_Bit}Frame_Size_t;




typedef struct {

	SPI_Number_t SPI_Number;
	Duplex_t Duplex;
	One_Direction_Mode_t One_Direction_Mode;
	Frame_Size_t Frame_Size;
	En_t Recieve_Only;
	En_t SW_Slave_Managament;
	En_t Internal_Slave_Select;
	En_t SPI_En;
	uint8_t baud;
	Master_Slave_t Master_Slave;
	En_t SS_En;
	En_t SPI_TXEIE;
	En_t SPI_RXEIE;
	En_t CRC;
	En_t SSI;


}SPI_Handle_t;





Err_Status SPI_Init(SPI_Handle_t*SPI_handle);

Err_Status SPI_Send_Data_IT(SPI_Handle_t*,uint8_t*);

Err_Status SPI_Send_Data_DMA(SPI_Handle_t*,uint32_t);

void SPI_IRQ_Handler(uint8_t Num);




#endif /* SPI_H_ */

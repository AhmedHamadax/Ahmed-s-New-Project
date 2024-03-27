/*
 * SPI.h
 *
 *  Created on: Sep 13, 2023
 *      Author: Ahmed
 */

#ifndef SPI_H_
#define SPI_H_

#include "Error.h"
#include <stdint.h>
#include <stdlib.h>
#include "DMA.h"
#include "stm32f446re.h"
#define SPI1_Base_Address 0x40013000
#define SPI2_Base_Address 0x40003800
#define SPI3_Base_Address 0x40003C00
#define SPI4_Base_Address 0x40013400


typedef enum{SPI1,SPI2,SPI3,SPI4}SPI_Number_t;

typedef enum{Full_Duplex_SPI,Half_Duplex_SPI}Duplex_t;

typedef enum{spi1,spi2,spi3,spi4}One_Direction_Mode_t;

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
	En_t TXEIE;
	En_t RXNEIE;

	En_t CRC;

	En_t SSI;
	En_t DMA_TX_IT;
	En_t DMA_RX_IT;

}SPI_Handle_t;





Err_Status SPI_Init(SPI_Handle_t*SPI_handle);

Err_Status SPI_Send_Data_IT(SPI_Handle_t*,uint8_t*);

Err_Status SPI_Recieve_Data_IT(SPI_Handle_t*SPI_handle,uint32_t*Destination);

Err_Status SPI_Transfer_P2M_DMA(DMA_Handle_t*,SPI_Handle_t*,uint32_t , uint16_t );


#endif /* SPI_H_ */

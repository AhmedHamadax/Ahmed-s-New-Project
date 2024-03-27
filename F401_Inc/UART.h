/*
 * UART.h
 *
 *  Created on: Sep 8, 2023
 *      Author: Ahmed
 */

#ifndef UART_H_
#define UART_H_
#include "stm32f446re.h"
#include "Error.h"
#include <stdint.h>
#include <stdlib.h>
#define SysClk_Mask 16000000000
typedef enum{OVS_16,OVS_8}Oversampling_t;
typedef enum{Eight_Data_Bits,Nine_Data_Bits}Word_Length_t;
typedef enum{Parity_Dis,Parity_En}Parity_En_t;
typedef enum{Even_Parity,Odd_Parity}Parity_Type_t;
typedef enum{PE_Interrupt_Dis,PE_Interrupt_En}PE_Interrupt_En_t;
typedef enum{TXE_Interrupt_Dis,TXE_Interrupt_En}TXE_Interrupt_En_t;
typedef enum{TC_Interrupt_Dis,TC_Interrupt_En}TC_Interrupt_En_t;
typedef enum{RXNEIE_Interrupt_Dis,RXNEIE_Interrupt_En}RXNEIE_Interrupt_En_t;
typedef enum{Transmit_Dis,Transmit_En}Transmit_En_t;
typedef enum{Recieve_Dis,Recieve_En}Recieve_En_t;
typedef enum{one,half,two,oneAndAhalf}Stop_Bit_Mode_t;
typedef enum{Clock_Dis,Clock1_En}Clock_En_t;
typedef enum{Full_Duplex,Half_Duplex}Duplex_Mode_t;
typedef enum{USART_1,USART_2,USART_3,USART_4,USART_5}USART_t;
typedef enum{CTS_Dis,CTS_En}CTSE_t;
typedef enum{RTS_Dis,RTS_En}RTSE_t	;


typedef struct {
	USART_t USART_Type;
	Oversampling_t OS;
	Word_Length_t Word_Length;
	Parity_Type_t Parity_Type;
	Parity_En_t Parity_Status;
	PE_Interrupt_En_t PE_int_en;
	TXE_Interrupt_En_t TXE_Interrupt;
	TC_Interrupt_En_t TC_Interrupt;
	RXNEIE_Interrupt_En_t RXNEIE_Interrupt;
	Transmit_En_t Transmit_Status;
	Recieve_En_t Recieve_Status;
	Stop_Bit_Mode_t Stop_Bit_Mode;
	Clock_En_t Clock_Status;
	Duplex_Mode_t Duplex_Mode;
	uint32_t BaudRate;
	CTSE_t CTSE;
	RTSE_t RTSE;
}UART_Handle_t;




Err_Status USART_init(UART_Handle_t*);

Err_Status USART_Send_Poll(UART_Handle_t*,uint8_t,char*);
Err_Status USART_Rec_Poll(UART_Handle_t*,uint8_t size,uint8_t*);
Err_Status USART_Rec_Poll_Menu(UART_Handle_t*,uint8_t size,uint8_t*);


Err_Status USART_Send_DMA(UART_Handle_t*,uint32_t);

Err_Status USART_Send_IT(UART_Handle_t*,uint32_t);

Err_Status USART_Poll_For_Transfer(UART_Handle_t*,uint32_t);


#endif /* UART_H_ */

/*
 * Menu.h
 *
 *  Created on: Mar 22, 2024
 *      Author: Ahmed
 */

#ifndef MENU_H_
#define MENU_H_
#include "rtc.h"

#include "UART.h"

#include "DMA.h"
#include "SPI.h"
extern UART_Handle_t USART_Handle;
void Start_Menu(void);

uint8_t Display_Main_Menu(void);
void str2num(uint8_t * arr,uint8_t);
void num2str(uint8_t * arr,uint8_t size);
uint8_t Str2toTime(uint8_t*);
#endif /* MENU_H_ */

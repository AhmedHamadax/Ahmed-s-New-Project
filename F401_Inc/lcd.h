/*
 * lcdHeader.h
 *
 * Created: 11/14/2022 1:17:37 AM
 *  Author: Ahmed Hamada
 */ 


#ifndef LCDHEAD_H_
#define LCDHEAD_H_
#include "std_macro.h"
//#include "GPIO_interface.h"
#include "GPIO.h"
#include <stdint.h>

#define RS_lcd(x) if(x==1) pin_set_reset(PortA,Pin1,on) ; else pin_set_reset(PortA,Pin1,off)

#define EN_LCD(x) if(x==1) pin_set_reset(PortA,Pin2,on) ; else pin_set_reset(PortA,Pin2,off)

#define D7(x) if(x==1) pin_set_reset(PortA,Pin6,on) ; else pin_set_reset(PortA,Pin6,off)
#define D6(x) if(x==1) pin_set_reset(PortA,Pin5,on) ; else pin_set_reset(PortA,Pin5,off)
#define D5(x) if(x==1) pin_set_reset(PortA,Pin4,on) ; else pin_set_reset(PortA,Pin4,off)
#define D4(x) if(x==1) pin_set_reset(PortA,Pin3,on) ; else pin_set_reset(PortA,Pin3,off)


void LCD_PIN_INIT(void);

void LCD_write_char(uint8_t);
void LCD_write_string(uint8_t *);
void LCD_write_command(uint32_t);
void LCD_write_number(uint32_t num);
void LCD_INIT(void);



#endif /* LCDHEADER_H_ */

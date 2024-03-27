/*
 * lcdApp.c
 *
 * Created: 11/14/2022 1:17:19 AM
 *  Author: Ahmed Hamada
 */ 
#include "lcd.h"
#include "sytick.h"
#include "GPIO.h"
#include "RCC.h"
void LCD_INIT(void){
	LCD_PIN_INIT();
	LCD_write_command(0x3);
	Systick_Delay_ms(1);
	LCD_write_command(0x3);
	Systick_Delay_ms(1);

	LCD_write_command(0x3);
	Systick_Delay_ms(1);
	
	LCD_write_command(0x2);
	Systick_Delay_ms(1);
	LCD_write_command(0x28);
	Systick_Delay_ms(1);
	LCD_write_command(0x1);
	Systick_Delay_ms(1);
	LCD_write_command(0x06);
	Systick_Delay_ms(1);
	LCD_write_command(0xC);
	//LCD_write_command(0x0E);
}


void LCD_write_char(uint8_t data){
	RS_lcd(1);
	D7( READBIT(data,7) );
	D6( READBIT(data,6) );
	D5( READBIT(data,5) );
	D4( READBIT(data,4) );
	EN_LCD(1);
	Systick_Delay_ms(10);

	EN_LCD(0);
	Systick_Delay_ms(10);

	D7( READBIT(data,3) );
	D6( READBIT(data,2) );
	D5( READBIT(data,1) );
	D4( READBIT(data,0) );
	Systick_Delay_ms(10);

	EN_LCD(1);
	Systick_Delay_ms(10);

	EN_LCD(0);
	
	
	
	
}


void LCD_write_command(uint32_t cmd){
		RS_lcd(0);
		D7( READBIT(cmd,7) );
		D6( READBIT(cmd,6) );
		D5( READBIT(cmd,5) );
		D4( READBIT(cmd,4) );
		EN_LCD(1);
		EN_LCD(0);
		D7( READBIT(cmd,3) );
		D6( READBIT(cmd,2) );
		D5( READBIT(cmd,1) );
		D4( READBIT(cmd,0) );
		EN_LCD(1);
		EN_LCD(0);
		
		
		
	
	
	
}
	uint8_t a,y,num;

void LCD_write_string(uint8_t * p_data){
	
	for(a=0;p_data[a]!='\0'; a++);
	
	y=0;
	while(y<a){
		RS_lcd(1);
		D7( READBIT( (*p_data),7) );
		D6( READBIT( (*p_data),6) );
		D5( READBIT( (*p_data),5) );
		D4( READBIT( (*p_data),4) );
		EN_LCD(1);
		EN_LCD(0);
		D7( READBIT(  (*p_data),3) );
		D6( READBIT(  (*p_data),2) );
		D5( READBIT(  (*p_data),1) );
		D4( READBIT(  (*p_data),0) );
		EN_LCD(1);
		EN_LCD(0);
		p_data++;
		y++;
		
	}
}

void LCD_write_number(uint32_t num){
	int8_t i = 0;
	uint8_t num_arr[10];
	
	if(num == 0) {
		LCD_write_char('0');
		return;
	}
	
	for(i = 0; num != 0 ;i++){ // 6,5,2,1
		num_arr[i] = num % 10 + '0';
		num /= 10;
	}
	i--;
	while (i >= 0){
		LCD_write_char(num_arr[i]);
		i--;
	}
}


void LCD_PIN_INIT(void){

	Pin_Config_t led_pin1=
{

.Port=PortA,
.Pin=Pin1,
.mode=output,
.output_mode=push_pull,

};


	Pin_Config_t led_pin2=
{

.Port=PortA,
.Pin=Pin2,
.mode=output,
.output_mode=push_pull,

};
	Pin_Config_t led_pin3=
{

.Port=PortA,
.Pin=Pin3,
.mode=output,
.output_mode=push_pull,

};
	Pin_Config_t led_pin4=
{

.Port=PortA,
.Pin=Pin4,
.mode=output,
.output_mode=push_pull,

};
	Pin_Config_t led_pin5=
{

.Port=PortA,
.Pin=Pin5,
.mode=output,
.output_mode=push_pull,

};
	Pin_Config_t led_pin6=
{

.Port=PortA,
.Pin=Pin6,
.mode=output,
.output_mode=push_pull,

};

RCC_AHBEnableClock(PortA);
GPIO_INIT(&led_pin1);
GPIO_INIT(&led_pin2);
GPIO_INIT(&led_pin3);
GPIO_INIT(&led_pin4);
GPIO_INIT(&led_pin5);
GPIO_INIT(&led_pin6);









}





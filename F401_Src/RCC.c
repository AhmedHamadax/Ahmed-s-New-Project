#include <stdint.h>
#include "rcc.h"
#include "Error.h"
#include "stm32f446re.h"
#define RCC ( (RCC_reg_t*)RCC_Base_Add   )

void RCC_set_CLKStatus(CLK_Type_t CLK,Status Status){
	switch(CLK ){
	case HSE:
		if(Status){
			RCC->CR|=(0b1<<16);
			while( ( ( (RCC->CR)>>17 )&0b1)!=1 );

		}
		else{
			RCC->CR&= ~(0b1<<16);

		}
		break;



	case HSI:
		if(Status){
			RCC->CR|=(0b1<<0);
			while( ( ( (RCC->CR)>>1 )&0b1)!=1 );

		}
		else{
			RCC->CR&= ~(0b1<<0);

		}
		break;



	case PLL:
		if(Status){
			RCC->CR|=(0b1<<24);
			while( ( ( (RCC->CR)>>25 )&0b1)!=1 );

		}
		else{
			RCC->CR&= ~(0b1<<24);

		}
		break;




	}


}

void RCC_set_Sys_clk(CLK_Type_t CLK){

	RCC->CFGR&= ~(0b11) ;
	RCC->CFGR|= CLK;


}

uint8_t RCC_HSE_Config(HSE_Config_t div){

uint8_t Error_Status=OK;

	if(div==Half){

		RCC->CFGR|= (0b1<<17);

	}
	else if(div==Same){
		RCC->CFGR&= ~(0b1<<17);

	}

	else {Error_Status=NOK;}

	 return Error_Status;
}


/**************
 * Mux:
 * *********/




uint8_t RCC_Pllconfig(uint8_t MUX,CLK_Type_t CLK){
	uint8_t Error_Status=OK;

if( (MUX>=2) && (MUX<=16)   &&( (CLK==HSI)||(CLK==HSE)||(CLK==PLL) )){
	MUX-=2;

	RCC->CFGR= ~((0b1111)<<18);
	RCC->CFGR= (MUX<<18);
}
else Error_Status=NOK;
return Error_Status;


}

void RCC_AHBEnableClock(AHB_Prefs_t Pref){

	RCC->AHB1ENR|= 0b1<<Pref;

}

void RCC_AHBDisableClock(AHB_Prefs_t Pref){
	RCC->AHB1ENR&= ~(0b1<<Pref);


}


void RCC_APB1_EnableClock(uint8_t Pref){
	RCC->APB1ENR|= 0b1<<Pref;


}

void RCC_APB1_DisableClock(uint8_t Pref);


void RCC_APB2_enableClock(uint8_t Pref){

	RCC->APB2ENR|= 0b1<<Pref;


}

void RCC_APB2_disableClock(uint8_t Pref);

/*
 * EXTI.c
 *
 *  Created on: Nov 28, 2023
 *      Author: Ahmed
 */
#include "EXTI.h"

#include "stm32f446re.h"

#define EXTI    ( (EXTI_Reg_t*)EXTI_Base_Address )

Err_Status EXTI_Init(EXTI_Handle_t*hdmi){
	Err_Status err=OK;
	if ( (hdmi->EXTI_num >=0)||(hdmi->EXTI_num <=22) ){



	EXTI->IMR&=~(0b1<<(hdmi->EXTI_num));
	EXTI->IMR|=((hdmi->INT_status)<<(hdmi->EXTI_num));

	EXTI->EMR&=~(0b1<<(hdmi->EXTI_num));
	EXTI->EMR|=((hdmi->Event_Status)<<(hdmi->EXTI_num));

	EXTI->RTSR&=~(0b1<<(hdmi->EXTI_num));
	EXTI->RTSR|=((hdmi->Rising_Edge)<<(hdmi->EXTI_num));

	EXTI->FTSR&=~(0b1<<(hdmi->EXTI_num));
	EXTI->FTSR|=((hdmi->Falling_Edge)<<(hdmi->EXTI_num));
	}
	else err=NOK;
	return err;
}
Err_Status EXTI_Stop(EXTI_Handle_t*hdmi){
	Err_Status err=OK;
	if ( (hdmi->EXTI_num >=0)||(hdmi->EXTI_num <=22) ){



	EXTI->IMR&=~(0b1<<(hdmi->EXTI_num));
	EXTI->IMR&=~(0b1<<(hdmi->EXTI_num));

	}
	else err=NOK;
	return err;
}


Err_Status EXTI_Generate_Init(EXTI_num_t num){
	Err_Status err=OK;
	if ( (num <0)||(num >22) ){

	EXTI->SWIER&=~(0b1<<(num));
	EXTI->FTSR|=(0b1<<(num));
	}

	else err=NOK;
	return err;


}








void EXTI2_IRQHandler(void){
	int x=32;
	x++;
	EXTI->PR|=(0b1<<1);

}

void EXTI3_IRQHandler(void){
	int x=32;
	x++;
	EXTI->PR|=(0b1<<1);

}

void EXTI13_IRQHandler(void){
	int x=32;
	x++;
	EXTI->PR|=(0b1<<1);

}








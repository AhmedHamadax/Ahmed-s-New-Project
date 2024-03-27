/*
 * sytick.c
 *
 *  Created on: Jul 22, 2023
 *      Author: Ahmed
 */

#include "sytick.h"
#include <stdio.h>
#include <math.h>
Systick_config_t*Systick =((Systick_config_t*) Systick_Base_Address);

void Systick_Delay_ms(uint32_t time){

	uint32_t count=0;
	uint32_t rem=time%1000;
	while( (time%1000)!=0 ) time++;
	Systick->Load=1000;
	Systick->Ctrl|= (0b1);
	Systick->Val=rem;
	while(count!=time){

		if( (( (Systick->Ctrl)>>16 )&1)==1   ){
			count++;
			(Systick->Ctrl)&= ~(0b1>>16) ;
		}
	}

	Systick->Ctrl&= ~(0b1);
	(Systick->Ctrl)&= ~(0b1>>16) ;
	int x=0;
}

/*
 * Timer.c
 *
 *  Created on: Dec 9, 2023
 *      Author: Ahmed
 */


#include "Timer.h"

extern uint32_t Auto_Load_Reg;


/*TIMER2*/



void Timer2_Init(Timer_Handle*hdmi){

	hTimer2->CR1|=(hdmi->Counting_Direction);
	hTimer2->DIER|=((hdmi->sys_int)<<0);
	hTimer2->DIER|=((hdmi->comp_int)<<(1+(hdmi->channel)));
	hTimer2->PSC=hdmi->prescaling;
	hTimer2->ARR=hdmi->Auto_Reload_Reg;
	hTimer2->CR1|=(1<<2);

}


void Timer2_PWM_Mode_Init(Channel_Number_t Channel_Num,PWM_Mode_t Mode){

	hTimer2->CCMRx[(Channel_Num)/2]|=((Mode)<<4);
	hTimer2->CCER|=(0b1<<((Channel_Num)*4));


}


void Timer2_Set_Channel_Duty_Cycle(Channel_Number_t Channel_Num,uint32_t duty){

uint32_t comp=(Auto_Load_Reg*duty)/100;
	hTimer2->CCRx[Channel_Num]=comp;


}





void Timer2_Input_Capture_Mode_Init(Channel_Number_t Channel_Num){
	if(Channel_Num>2) Channel_Num-=2;

	hTimer2->CCMRx[(Channel_Num)/2]|=((0b01)<<(8*(Channel_Num)));
	hTimer2->CCER|=(Rising_Edge_Polarity)<<1;

	hTimer2->SMCR&=~(0b111);
	hTimer2->SMCR|=External_Trigger_input;

	hTimer2->SMCR|=((0b101+Channel_Num)<<4);


}


/*TIMER3*/



void Timer3_Init(Timer_Handle*hdmi){

	hTimer3->CR1|=(hdmi->Counting_Direction);
	hTimer3->DIER|=((hdmi->sys_int)<<0);
	hTimer3->DIER|=((hdmi->comp_int)<<(1+(hdmi->channel)));
	hTimer3->PSC=hdmi->prescaling;
	hTimer3->ARR=hdmi->Auto_Reload_Reg;
	hTimer3->CR1|=(1<<2);

}


void Timer3_PWM_Mode_Init(Channel_Number_t Channel_Num,PWM_Mode_t Mode){

	hTimer3->CCMRx[(Channel_Num)/2]|=((Mode)<<4);
	hTimer3->CCMRx[(Channel_Num)/2]|=((Mode)<<12);
	hTimer3->CCER|=(0b1<<((Channel_Num)*4));


}

void Timer3_Set_Channel_Duty_Cycle(Channel_Number_t Channel_Num,uint32_t duty){

uint32_t comp=(Auto_Load_Reg*duty)/100;
	hTimer3->CCRx[Channel_Num]=comp;


}





void Timer3_Input_Capture_Mode_Init(Channel_Number_t Channel_Num){
	if(Channel_Num>2) Channel_Num-=2;

	hTimer3->CCMRx[(Channel_Num)/2]|=((0b01)<<(8*(Channel_Num)));
	hTimer3->CCER|=(Rising_Edge_Polarity)<<1;

	hTimer3->SMCR&=~(0b111);
	hTimer3->SMCR|=External_Trigger_input;

	hTimer3->SMCR|=((0b101+Channel_Num)<<4);

	hTimer3->CR1|=1;

}


void Timer4_Init(Timer_Handle*hdmi){

	hTimer4->CR1|=(hdmi->Counting_Direction);
	hTimer4->DIER|=((hdmi->sys_int)<<0);
	hTimer4->DIER|=((hdmi->comp_int)<<(1+(hdmi->channel)));
	hTimer4->PSC=hdmi->prescaling;
	hTimer4->ARR=hdmi->Auto_Reload_Reg;
	hTimer4->CR1|=(1<<2);

}

void Timer4_PWM_Mode_Init(Channel_Number_t Channel_Num,PWM_Mode_t Mode){

	hTimer4->CCMRx[(Channel_Num)/2]|=((Mode)<<4);
	hTimer4->CCER|=(0b1<<((Channel_Num)*4));


}


void Timer4_Set_Channel_Duty_Cycle(Channel_Number_t Channel_Num,uint32_t duty){

uint32_t comp=(Auto_Load_Reg*duty)/100;
	hTimer4->CCRx[Channel_Num]=comp;


}
void Timer2_Start(void){
	hTimer2->CR1|=1;

}

void Timer3_Start(void){
	hTimer3->CR1|=1;

}
void Timer4_Start(void){
	hTimer4->CR1|=1;

}






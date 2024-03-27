/*
 * Timer.h
 *
 *  Created on: Dec 9, 2023
 *      Author: Ahmed
 */

#ifndef TIMER_H_
#define TIMER_H_
#include <stdint.h>
#include "Error.h"

#define Timer2_Base_Address 0x40000000
#define Timer3_Base_Address 0x40000400
#define Timer4_Base_Address 0x40000800
//#define Auto_Load_Reg 36000UL

typedef enum{Timer2,Timer3,Timer4,Timer5,Timer6,Timer7} Timer_Number_t;

typedef enum{Channel1_Timer,Channel2_Timer,Channel3_Timer,Channel4_Timer} Channel_Number_t;

typedef enum{Slave_Mode=1,EncoderMode1,EncoderMode2,EncoderMode3,GatedMode,TriggerMode} Count_Mote_t;
typedef enum{upcounter,downcounter} Count_Dir_t;
typedef enum{Prescale_Off,Prescale_by2,Prescale_by4,Prescale_by8} Prescale_t;

typedef enum{Dis_timer2_int,En_timer2_int}trig_int_en_timer2_t;
typedef enum{Dis_timer2_comp_int,En_timer2_comp_int}comp_int_en_timer2_t;


typedef enum{En_timer2_PWM_mode1=0b110,En_timer2_PWM_mode2=0b111}pwm_en_timer2_t;

typedef enum{Output_Channel,input_TL1,input_TL2,input_TRC}channel_mode_t;

typedef enum{External_Trigger_input=0b111}Trigger_Selection_t;

typedef enum{PWM_Mode1=0b110,PWM_Mode2=0b111}PWM_Mode_t;

typedef enum{Rising_Edge_Polarity=0b000,Falling_Edge_Polarity=0b001,Both_Edges_Polarity=0b101}Polarity_Selection_t;

typedef struct{
	Timer_Number_t Timer_Num;
	uint32_t auto_reload;
	uint32_t compare_value;
	Channel_Number_t channel;
	pwm_en_timer2_t pwm_mode;
	trig_int_en_timer2_t sys_int;
	comp_int_en_timer2_t comp_int;
	uint16_t prescaling;
	uint16_t Auto_Reload_Reg;
	Count_Dir_t Counting_Direction;
	channel_mode_t channel_Mode;
	Count_Mote_t Counter_Mode;
	Trigger_Selection_t Trigger_Selection;
}Timer_Handle;

typedef struct{
	uint32_t CR1;
	uint32_t CR2;
	uint32_t SMCR;
	uint32_t DIER;
	uint32_t SR;
	uint32_t EGR;
	uint32_t CCMRx[2];
	uint32_t CCER;
	uint32_t CNT;
	uint32_t PSC;
	uint32_t ARR;
	uint32_t Rev1;
	uint32_t CCRx[4];
	uint32_t Rev2;
	uint32_t DCR;
	uint32_t DMAR;
	uint32_t OR;



}Timer_Reg_t;



#define hTimer2 ((Timer_Reg_t *)Timer2_Base_Address)
#define hTimer3 ((Timer_Reg_t *)Timer3_Base_Address)
#define hTimer4 ((Timer_Reg_t *)Timer4_Base_Address)



void Timer2_Init(Timer_Handle*);
void Timer2_Set_Channel_Duty_Cycle(Channel_Number_t Channel_Num,uint32_t duty);
void Timer2_Input_Capture_Mode_Init(Channel_Number_t Channel_Num);
void Timer2_PWM_Mode_Init(Channel_Number_t Channel_Num,PWM_Mode_t Mode);

void Timer3_Init(Timer_Handle*);
void Timer3_Set_Channel_Duty_Cycle(Channel_Number_t Channel_Num,uint32_t duty);
void Timer3_Input_Capture_Mode_Init(Channel_Number_t Channel_Num);
void Timer3_PWM_Mode_Init(Channel_Number_t Channel_Num,PWM_Mode_t Mode);
void Timer_Start(void);

#endif /* TIMER_H_ */

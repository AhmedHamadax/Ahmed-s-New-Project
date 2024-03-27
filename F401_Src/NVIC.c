#include "NVIC.h"
#include "stm32f446re.h"


void NVIC_Pref_en(IRQ_t Pref){
	uint8_t RegNum=Pref/32;
	uint8_t BitNum=Pref%32;

	NVIC->ISER[RegNum]|=1<<BitNum;


}

void NVIC_Pref_Dis(IRQ_t Pref){
	uint8_t RegNum=Pref/32;
	uint8_t BitNum=Pref%32;

	NVIC->ICER[RegNum]|=1<<BitNum;


}


void NVIC_Pref_Flag_en(IRQ_t Pref){
	uint8_t RegNum=Pref/32;
	uint8_t BitNum=Pref%32;

		NVIC->ISPR[RegNum]|=1<<BitNum;




}
void NVIC_Pref_Flag_dis(IRQ_t Pref){

	uint8_t RegNum=Pref/32;
	uint8_t BitNum=Pref%32;

	NVIC->ICPR[RegNum]|=1<<BitNum;

}


void NVIC_Priority_set(uint8_t IRQ ,uint8_t Pri ){


	NVIC->IPR[IRQ]=Pri<<4;


}


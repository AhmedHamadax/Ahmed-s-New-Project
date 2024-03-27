#include "GPIO_interface.h"
#include "stm32f103.h"
#include "Err_Typ.h"
#include <stdint.h>
#include <stdio.h>
static GPIO_RegDef_t * GPIOPort[7]={GPIOA,GPIOB,GPIOC,GPIOD,GPIOE,GPIOF,GPIOG};

uint8_t GPIO_INIT(Pin_Config_t* Pin_config){

uint8_t Local_error_status=OK;


if(Pin_config!=NULL){

	Local_error_status=OK;
	if( (Pin_config->Port)<=PORTG  &&( (Pin_config->Port)>=PORTA )  && ((Pin_config->Pin)>=PIN0) && ((Pin_config->Pin)<=PIN15)  ){
		uint8_t u8RegNum=(Pin_config->Pin)/8;
		uint8_t u8BitNum=(Pin_config->Pin)%8;

		GPIOPort[Pin_config->Port]->_CR[u8RegNum]&= ~(0b1111<<(u8BitNum) );
		GPIOPort[Pin_config->Port]->_CR[u8RegNum]|= (Pin_config->Mode)<<( u8BitNum*4);


				if( (Pin_config->Mode) == Input){
					GPIOPort[Pin_config->Port]->_CR[u8RegNum]&= ~(0b11)<< (( u8BitNum*4)+2);
					GPIOPort[Pin_config->Port]->_CR[u8RegNum]|= (Pin_config->input_mode)<< (( u8BitNum*4)+2);

		

				}
				else if(   ( (Pin_config->Mode) ==Output_10MHZ) ||( (Pin_config->Mode) ==Output_50MHZ)||( (Pin_config->Mode) ==Output_2MHZ) ){
					GPIOPort[Pin_config->Port]->_CR[u8RegNum]&= ~( (0b11)<< (( u8BitNum*4)+2));
					GPIOPort[Pin_config->Port]->_CR[u8RegNum]|= (Pin_config->output_mode)<< (( u8BitNum*4)+2);


				}
	}
	else{
		Local_error_status=NOK;
	}
}
else {
	Local_error_status=Null_Ptr;

}
return Local_error_status;
	// ALT FUNC is still remaining
}


uint8_t set_reset_pin(Port_t Por,Pin_t Pi,Pin_Status St){
	uint8_t Local_error_status=OK;
	if( (Por>=PORTA)&&(Por<=PORTG) &&(Pi>=0) &&(Pi<=15) ){
		

		if(St==1){
		
			GPIOPort[Por]->_BSRR= (0b1)<<Pi;
		
		}
		
		else if(St==0) {
			GPIOPort[Por]->_BSRR= (0b1)<<(Pi+16);

		}
		else {
			Local_error_status=NOK;
		}
	}
	else Local_error_status=NOK;
		
return Local_error_status;
}

uint8_t Read_Pin(Port_t Por,Pin_t Pi,uint32_t*var ){
	uint8_t Local_error_status=OK;
if(var==NULL){
	Local_error_status=Null_Ptr;
}
else{
	if( (Por>=PORTA)&&(Por<=PORTG) &&(Pi>=0) &&(Pi<=15) ){
	var=  ((GPIOPort[Por]->_IDR)>>Pi)&1;
	}
	else Local_error_status=NOK;
}

	return Local_error_status;
}

uint8_t Tog_Pin(Port_t Por,Pin_t Pi){
	uint8_t Local_error_status=OK;
	if( (Por>=PORTA)&&(Por<=PORTG) &&(Pi>=0) &&(Pi<=15) ){

		GPIOPort[Por]->_ODR^= 0b1<<Pi;

	}
	else Local_error_status=NOK;

	return Local_error_status;

}






		




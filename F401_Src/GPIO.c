



#include "stm32f446re.h"
#include "GPIO.h"

Pin_Config_t mypin;

static Pin_reg_t * GPIOPort[7]={GPIOA,GPIOB,GPIOC,GPIOD,GPIOE,GPIOF,GPIOG};


uint8_t GPIO_INIT( Pin_Config_t* Pin_Struct){

		(GPIOPort[Pin_Struct->Port]->MODER)&= ~(0b11<< ((Pin_Struct->Pin)*2) );
		(GPIOPort[Pin_Struct->Port]->MODER)|= (Pin_Struct->mode)<< ((Pin_Struct->Pin)*2)		;
				GPIOPort[Pin_Struct->Port]->PUPDR &=  ~(0b11<<(  (Pin_Struct->Pin)*2)	);
				GPIOPort[Pin_Struct->Port]->PUPDR |=  (Pin_Struct->pullmode)<< ( (Pin_Struct->Pin)*2 );

// Note that What applies for Output also applies for Alt funcs
			if((Pin_Struct->mode)==output  ||((Pin_Struct->mode)==altfun)  )  {

				(GPIOPort[Pin_Struct->Port]->OTYPER)&= ~( 0b1  << ((Pin_Struct->Pin)))	;
				(GPIOPort[Pin_Struct->Port]->OSPEEDER)&= ~(0b11  << ((Pin_Struct->Pin)*2))	;


				GPIOPort[Pin_Struct->Port]->OTYPER |= (Pin_Struct->output_mode) << ( (Pin_Struct->Pin) );
				GPIOPort[Pin_Struct->Port]->OSPEEDER |= (Pin_Struct->speed) << ( (Pin_Struct->Pin)*2 );


				 if( (Pin_Struct->mode)==altfun     ){
					if( (Pin_Struct->Pin)<=7 ){
					(GPIOPort[Pin_Struct->Port]->AFRL)&= ~(0b1111<<( (Pin_Struct->Pin)*4)  );
					GPIOPort[Pin_Struct->Port]->AFRL |= (Pin_Struct->AltFun)<<(  ( (Pin_Struct->Pin)*4 )  );
					}
					else{
						(GPIOPort[Pin_Struct->Port]->AFRH)&= ~(0b1111<<( (Pin_Struct->Pin)*4)  );
					GPIOPort[Pin_Struct->Port]->AFRH |= (Pin_Struct->AltFun)<<(  ( (Pin_Struct->Pin-8)*4 )  );

					}
				}
	}




}

uint8_t pin_set_reset(Port_t Por,Pin_t Pi,Status_t St){


	 if (St==on)
	 {
		(GPIOPort[Por]->ODR)&= ~(0b1<<Pi);
		 (GPIOPort[Por]->ODR)|= (0b1)<<Pi;
	 }
	 else if(St==off){
		 GPIOPort[Por]->BSRR&= ~(0b1<<(Pi+16));
		 GPIOPort[Por]->BSRR|= (0b1)<<(Pi+16);
	 }


}



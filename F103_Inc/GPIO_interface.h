#ifndef GPIO_INTERFACE_H
 #define GPIO_INTERFACE_H
 #include "stm32f103.h"
#include "Err_Typ.h"
#include <stdint.h>
 typedef enum{
	 
	 PORTA=0,
	 PORTB,
	 PORTC,
	 PORTD,
	 PORTE,
	 PORTF,
	 PORTG
	 
	 }Port_t;
 
 typedef enum{
	  PIN0=0
	 ,PIN1
	 ,PIN2
	 ,PIN3
	 ,PIN4
	 ,PIN5
	 ,PIN6
	 ,PIN7
	 ,PIN8
	 ,PIN9
	 ,PIN10
	 ,PIN11
	 ,PIN12
	 ,PIN13
	 ,PIN14
	 ,PIN15

	 }Pin_t;
 
 typedef enum{
	 Input=0,
	 Output_10MHZ,
	 Output_2MHZ,
	 Output_50MHZ,
	 
	 }Pin_Mode_t;
	 
typedef enum{
	analog=0,
	floating,
	normal,
	reserved
	
	}input_type_t;	
	
	
typedef enum{
	Off
	,On
	
}Pin_Status;	
	
typedef enum{
	GP_output_PP=0,
	GP_output_OD,
	AF_output_PP,
	AF_output_OD,

	
}output_type_t;



typedef struct {
Port_t Port;
Pin_t  Pin;	
Pin_Mode_t Mode;
input_type_t input_mode;
output_type_t output_mode;
Pin_Status Status;


}Pin_Config_t;

uint8_t GPIO_INIT(Pin_Config_t* Pin_config);	
uint8_t set_reset_pin(Port_t Por,Pin_t Pi,Pin_Status St);
uint8_t Read_Pin(Port_t Por,Pin_t Pi,uint32_t*var );

uint8_t Tog_Pin(Port_t Por,Pin_t Pi);

	 
 #endif
 

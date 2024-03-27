/*
 * RCC_Config.h
 *
 *  Created on: Aug 29, 2023
 *      Author: Ahmed
 */

#ifndef RCC_CONFIG_H_
#define RCC_CONFIG_H_
#ifndef RCC_config
#define RCC_config








typedef enum{

	HSI=0,
	HSE,
	PLL


}CLK_Type_t;

typedef enum{

	OFF=0,
	ON

}Status;

typedef enum{

	Half,
	Same

}HSE_Config_t;





typedef enum{

	PORTA,
	PORTB,
	PORTC,
	PORTD,
	PORTE,
	REV,
	REV2,
	GPIOH=7,
	CRC=12,
	DMA1=21,
	DMA2


}AHB_Prefs_t;






















#endif



#endif /* RCC_CONFIG_H_ */

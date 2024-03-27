#ifndef stm32f446re_H
#define stm32f446re_H
#include <stdint.h>
//#include "DMA.h"

/*Memory Base Adds*/
#define Flash_B_Add    0x08000000UL
#define SRAM_B_Add     0x20000000UL 
/*   GPIO Base_Adds          */
#define System_Clock 16000000
/**      Clock      ***/

#define GPIOA_Base_Add 0x40020000UL
#define GPIOB_Base_Add 0x40020400UL
#define GPIOC_Base_Add 0x40020800UL
#define GPIOD_Base_Add 0x40020C00UL
#define GPIOE_Base_Add 0x40021000UL
#define GPIOF_Base_Add 0x40021400UL
#define GPIOG_Base_Add 0x40021800UL
#define GPIOH_Base_Add 0x40021C00UL

/*RCC Base Address*/
#define RCC_Base_Add   0x40023800UL
#define NVIC_Base_Add 0xE000E100

/* DMA Base Address*/
#define DMA1_Base_Add 0x40026000UL
#define DMA2_Base_Add 0x40026400UL
/* UART Base Address*/

#define UART1_Base_Address 0x40011000
#define UART2_Base_Address 0x40004400
#define UART3_Base_Address 0x40004800
#define UART4_Base_Address 0x40004C00
#define UART5_Base_Address 0x40005000
#define UART6_Base_Address 0x40011400

/*      i2c Base Address            */
#define i2c1_Base_Address 0x40005400
#define i2c2_Base_Address 0x40005800
#define i2c3_Base_Address 0x40005C00
/*************/
#define SPI1_Base_Address 0x40013000
#define SPI2_Base_Address 0x40003800
#define SPI3_Base_Address 0x40003C00
#define SPI4_Base_Address 0x40013400
/***********************************
 * *********/


#define EXTI_Base_Address 0x40013C00


typedef struct {
	
	volatile	uint32_t MODER;
	volatile	uint32_t OTYPER;
	volatile	uint32_t OSPEEDER;
	volatile	uint32_t PUPDR;
	volatile	uint32_t IDR;
	volatile	uint32_t ODR;
	volatile	uint32_t BSRR;
	volatile	uint32_t LCKR;
	volatile	uint32_t AFRL;
	volatile	uint32_t AFRH;

}Pin_reg_t;



typedef struct {
	
	volatile	uint32_t CR;
	volatile	uint32_t PLLCFGR;
	volatile	uint32_t CFGR;
	volatile	uint32_t CIR;
	volatile	uint32_t AHB1RSTR;
	volatile	uint32_t AHB2RSTR;
	volatile	uint32_t Rev[2];
	volatile	uint32_t APB1RSTR;
	volatile	uint32_t APB2RSTR;
	volatile	uint32_t Rev2[2];
	volatile	uint32_t AHB1ENR;
	volatile	uint32_t AHB2ENR;
	volatile	uint32_t Rev3[2];
	volatile	uint32_t APB1ENR;
	volatile	uint32_t APB2ENR;
	volatile	uint32_t Rev4[2];
	volatile	uint32_t AHB1LPENR;
	volatile	uint32_t AHB2LPENR;
	volatile	uint32_t Rev5[2];
	volatile	uint32_t APB1LPENR;
	volatile	uint32_t APB2LPENR;
	volatile	uint32_t Rev6[2];
	volatile	uint32_t BDCR;
	volatile	uint32_t CSR;
	volatile	uint32_t Rev7[2];
	volatile	uint32_t SSCGR;
	volatile	uint32_t PLLI2SCFGR;


}RCC_reg_t;



typedef enum{
		SxCR=0,
		SxNDTR,
		SxPAR,
		SxM0AR,
		SxM1AR,
		SxFCR,


} SreamReg_Name_t;

typedef struct {

	volatile	uint32_t LISR;
	volatile	uint32_t HISR;
	volatile	uint32_t LIFCR;
	volatile	uint32_t HIFCR;
	volatile	uint32_t Stream[48];

}DMA_Reg_t;



typedef struct {

	uint32_t ISER[8];
	uint32_t rev[24];
	uint32_t ICER[8];
	uint32_t rev2[24];
	uint32_t ISPR[8];
	uint32_t rev3[24];
	uint32_t ICPR[8];
	uint32_t rev4[24];
	uint32_t IABR[8];
	uint32_t rev5[56];
	uint8_t IPR[239];

}NVIC_reg_t;

typedef struct {

	uint32_t SR;
	uint32_t DR;
	uint32_t BRR;
	uint32_t CR1;
	uint32_t CR2;
	uint32_t CR3;
	uint32_t GTPR;

}UART_reg_t;





typedef struct {

	uint32_t IMR;
	uint32_t EMR;
	uint32_t RTSR;
	uint32_t FTSR;
	uint32_t SWIER;
	uint32_t PR;

}EXTI_Reg_t;

typedef struct {

	uint32_t CR1;
	uint32_t CR2;
	uint32_t SR;
	uint32_t DR;
	uint32_t CRCPR;
	uint32_t RXCRCR;
	uint32_t TXCRCR;
	uint32_t I2SCFGR;
	uint32_t I2SPR;


}SPI_Reg_t;

/*****      SCB pref def       ****/

#define NVIC ( (NVIC_reg_t*) NVIC_Base_Add )


#define GPIOA   ( (Pin_reg_t*)GPIOA_Base_Add  )
#define GPIOB   ( (Pin_reg_t*)GPIOB_Base_Add  )
#define GPIOC   ( (Pin_reg_t*)GPIOC_Base_Add  )
#define GPIOD   ( (Pin_reg_t*)GPIOD_Base_Add  )
#define GPIOE   ( (Pin_reg_t*)GPIOE_Base_Add  )
#define GPIOF   ( (Pin_reg_t*)GPIOF_Base_Add  )
#define GPIOG   ( (Pin_reg_t*)GPIOG_Base_Add  )
#define GPIOH   ( (Pin_reg_t*)GPIOH_Base_Add  )





#endif

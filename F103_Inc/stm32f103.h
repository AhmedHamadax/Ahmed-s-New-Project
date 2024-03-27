#ifndef stm32f446re_H
#define stm32f446re_H
#include <stdint.h>

/************    Memory Base Add     ***********/
#define Flash_B_Add    0x08000000UL
#define SRAM_B_Add     0x20000000UL

/************    AHB1 Prepherials Base Address     ***********/

#define  Rcc_Base_Address    0x40021000UL

/************    APB2 Prepherials Base Address     ***********/


//#define  GPIOA_Base_Address  5//(0x40010800UL)
//#define  GPIOB_Base_Address  6//(0x40010C00UL)
#define  GPIOA_Base_Address  0x40010800UL
#define  GPIOB_Base_Address  0x40010C00UL

#define  GPIOC_Base_Address  0x40011000UL
#define  GPIOD_Base_Address	 0x40011400UL
#define  GPIOE_Base_Address	 0x40011800UL
#define  GPIOF_Base_Address	 0x40011C00UL
#define  GPIOG_Base_Address  0x40012000UL
#define  Alternate_Fun_Base_Address 0x40010000UL
/************    GPIO Struct     ***********/
typedef struct AFR{

volatile	uint32_t EVCR;
volatile	uint32_t MAPR;
volatile	uint32_t EXTICR1;
volatile 	uint32_t EXTICR2;
volatile	uint32_t EXTICR3;
volatile	uint32_t EXTICR4;
volatile	uint32_t MAPR2;

	}AFT_t;


	/************    AFR Struct     ***********/

	typedef struct gpio{
		volatile uint32_t _CR[2] ;     /**/
		//volatile uint32_t _CRH;	 /**/
		volatile uint32_t _IDR;	 /**/
		volatile uint32_t _ODR;	 /**/
		volatile uint32_t _BSRR;	 /**/
		volatile uint32_t _BRR;	 /**/
		volatile uint32_t _LCKR;	 /**/


		}GPIO_RegDef_t;

	/************    GPIO Peripheral Def     ***********/
#define GPIOA               ((GPIO_RegDef_t*)GPIOA_Base_Address)
#define GPIOB			    ((GPIO_RegDef_t*)GPIOB_Base_Address)
#define GPIOC				((GPIO_RegDef_t*)GPIOC_Base_Address)
#define GPIOD				((GPIO_RegDef_t*)GPIOD_Base_Address)
#define GPIOE				((GPIO_RegDef_t*)GPIOE_Base_Address)
#define GPIOF				((GPIO_RegDef_t*)GPIOF_Base_Address)
#define GPIOG			    ((GPIO_RegDef_t*)GPIOG_Base_Address)
#define AltFun              ((AFT_t*) Alternate_Fun_Base_Address)


/**********************************************************************************/



/*********          RCC Peripheral            ********/

typedef struct rcc{
	uint32_t RCC_CR;
	uint32_t RCC_CFGR;

	uint32_t RCC_CIR;

	uint32_t RCC_APB2RSTR;

	uint32_t RCC_APB1RSTR;
	uint32_t RCC_BDCR;
	uint32_t RCC_CSR;


	}RCC_Regdef_t;


/*****      RCC pref def       ****/
#define  RCC      (RCC_Regdef_t*) Rcc_Base_Address



/**********************************************************************************/



	/*****      SCB pref def       ****/

#define SCB_Base_Address  0xE000ED00//0xE000ED10//0xE000E008..0xE000 ED00

	/*********          SCB Peripheral            ********/


typedef struct {
	uint32_t CPUID;
	uint32_t ICSR;
	uint32_t VTOR;
	uint32_t AIRCR;
	uint32_t SCR;
	uint32_t CCR;
	uint32_t SHPR1;
	uint32_t SHPR2;
	uint32_t SHPR3;
	uint32_t SHCRS;
	uint32_t CFSR;
	uint32_t HFSR;
	uint32_t rev;
	uint32_t MMAR;
	uint32_t BFAR;

}SCB_reg_t;
/*****      SCB pref def       ****/

#define SCB      ((SCB_reg_t*) SCB_Base_Address )



/**********************************************************************************/


/************    NVIC Base Add     ***********/

#define NVIC_Base_Add 0xE000E100
/*********          NVIC Peripheral            ********/

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

/*****      SCB pref def       ****/

#define NVIC ( (NVIC_reg_t*) NVIC_Base_Add )




#define SPI1_Base_Address 0x40013000
#define SPI2_Base_Address 0x40003800
#define SPI3_Base_Address 0x40003C00
#define SPI4_Base_Address 0x40013400
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







#endif

#ifndef RCC_config
#define RCC_config


#define RCC_Base_Add 0x40021000UL


typedef struct Rcc{
	uint32_t CR;
	uint32_t CFGR;
	uint32_t CIR;
	uint32_t APB2RSTR;
	uint32_t APB1RSTR;
	uint32_t AHBENR;
	uint32_t APB2ENR;
	uint32_t APB1ENR;
	uint32_t BDCR;
	uint32_t CSR;




}RCC_Reg_t;


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

	DMA1=0,
	DMA2,
	SRAM,
	Res,
	FLITF,
	Ress,
	CRCE,
	Res1,
	FSMC,
	Resss,
	SDIO


}AHB_Prefs_t;






















#endif

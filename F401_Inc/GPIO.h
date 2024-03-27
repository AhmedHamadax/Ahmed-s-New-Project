#ifndef F44
#define F44
#include <stdint.h>
typedef enum{
	PortA=0,
	PortB,
	PortC,
	PortD,
	PortE,
	PortF,
	PortG,
	PortH,

	}Port_t;

typedef enum{

	Pin0=0,
	Pin1,
	Pin2,
	Pin3,
	Pin4,
	Pin5,
	Pin6,
	Pin7,
	Pin8,
	Pin9,
	Pin10,
	Pin11,
	Pin12,
	Pin13,
	Pin14,
	Pin15

}Pin_t;


typedef enum {
	input=0,
	output,
	altfun,
	analog


	}Mode_t;
typedef enum {
	push_pull=0,
	open_drain

}output_mode_t;

typedef enum {
	low_speed=0,
	medium_speed,
	fast_speed,
	high_speed


}speed_t;

typedef enum {
	floating=0,
	pull_up,
	pull_down,
	reserved

}pUpD_t;

typedef enum {
	reset=0,
	set=1

}SetReset_t;

typedef enum{
	AF0=0,
	AF1,
	AF2,
	AF3,
	AF4,
	AF5,
	AF6,
	AF7,
	AF8,
	AF9,
	AF10,
	AF11,
	AF12,
	AF13,
	AF14,
	AF15,



	}AF_t;

typedef enum{
	off=0,
	on


	}Status_t;


	typedef struct {
		Port_t Port;
		Pin_t Pin;
		Mode_t mode;
		output_mode_t output_mode;
		speed_t speed;
		pUpD_t pullmode;
		SetReset_t SetReset;
		AF_t AltFun;



		}Pin_Config_t;


uint8_t GPIO_INIT(Pin_Config_t*);
uint8_t pin_set_reset(Port_t Por,Pin_t Pi,Status_t St);








#endif

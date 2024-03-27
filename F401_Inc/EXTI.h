/*
 * EXTI.h
 *
 *  Created on: Nov 28, 2023
 *      Author: Ahmed
 */

#ifndef EXTI_H_
#define EXTI_H_
#include <stdint.h>
#include "Error.h"

#define EXTI    ( (EXTI_Reg_t*)EXTI_Base_Address )



typedef enum{EXTI0,EXTI1,EXTI2,EXTI3,EXTI4,EXTI5,EXTI6,EXTI7,EXTI8,EXTI9,EXTI10,EXTI11,EXTI12,EXTI13,EXTI14,EXTI15}EXTI_num_t;
typedef enum{EXTI_Int_Dis,EXTI_Int_En}INT_St_t;
typedef enum{EXTI_Event_Dis,EXTI_Event_En}Event_St_t;
typedef enum{Rising_Edge_Dis,Rising_Edge_En}Rising_Edge_St_t;
typedef enum{Falling_Edge_Dis,Falling_Edge_En}Falling_Edge_St_t;

typedef struct {

	EXTI_num_t EXTI_num;
	INT_St_t INT_status;
	Event_St_t Event_Status;
	Rising_Edge_St_t Rising_Edge;
	Falling_Edge_St_t Falling_Edge;

}EXTI_Handle_t;





Err_Status EXTI_Init(EXTI_Handle_t*);

Err_Status EXTI_Generate_Init(EXTI_num_t);





#endif /* EXTI_H_ */

/*
 * std_macro.h
 *
 * Created: 11/13/2022 11:42:15 PM
 *  Author: LOGO
 */ 


#ifndef STD_MACRO_H_
#define STD_MACRO_H_

#define F_CPU 16000000UL



#define SETBIT(REG,BIT) (REG |= 1<<BIT)
#define CLRBIT(REG,BIT) (REG &= ~(1<<BIT))
#define TOGBIT(REG,BIT) (REG ^= 1<<BIT)
#define READBIT(REG,BIT) ((REG>>BIT) &1)




#endif /* STD_MACRO_H_ */
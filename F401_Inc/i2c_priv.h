/*
 * i2c_priv.h
 *
 *  Created on: Sep 12, 2023
 *      Author: Ahmed
 */

#ifndef I2C_PRIV_H_
#define I2C_PRIV_H_

typedef enum{


	Address_Sent,
	Address_Sent_Ack,
	Address_Sent_NAck
	,Data_Sent,
	Data_Sent_Ack,
	Data_Sent_NAck,
	Start,
	Stop,
	Data_Recieved

}i2c_status_t;






#endif /* I2C_PRIV_H_ */

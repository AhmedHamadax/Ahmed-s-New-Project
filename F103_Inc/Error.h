#ifndef Error_h
#define Error_h


typedef enum {
	NOK=0,
	OK,
	start_error,
	Null_Ptr,
	NACK_err,
		NAddress,
		NData

}Err_Status;


#endif

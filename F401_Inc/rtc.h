#include <stdint.h>
#include "i2c.h"

uint8_t val2bcd(x);
uint8_t bcdToDec(uint8_t val) ;



typedef struct{

	uint8_t sec;
	uint8_t min;
	uint8_t hou;
	uint8_t day_of_the_week;
	uint8_t day_of_the_month;
	uint8_t month;
	uint8_t year;








} Date_Time_t;




uint8_t send_time_to_rtc_DMA(i2c_handle_t*,uint8_t * );
uint8_t recieve_time_from_rtc_DMA(i2c_handle_t* ,uint8_t *);
uint8_t Set_RTC_Alarm_DMA(i2c_handle_t*,uint8_t * );
uint8_t recieve_alarm1_time_from_rtc_DMA(i2c_handle_t* i2c_hdmi ,uint8_t *recived_data );
uint8_t RTC_Control_Init(i2c_handle_t* i2c_hdmi);
uint8_t recieve_ControlReg_from_rtc_DMA(i2c_handle_t* i2c_hdmi ,uint8_t *recived_data,uint8_t );
uint8_t RTC_Reset_Status(i2c_handle_t* i2c_hdmi );
uint8_t RTC_Status_Init(i2c_handle_t* i2c_hdmi );
uint8_t RTC_Control_ReInit(i2c_handle_t* i2c_hdmi );
uint8_t RTC_Reset_Ctrl(i2c_handle_t* i2c_hdmi );

#include "rtc.h"
#include "i2c.h"
#include "DMA.h"
#include "EXTI.h"
extern 	DMA_Handle_t HDMA_Stream6;
extern	DMA_Handle_t HDMA_Stream5;
extern EXTI_Handle_t EXTI_1;

uint8_t val2bcd(x){
//	12-12-2013-9:50:30:
    return ((x / 10) << 4) | (x % 10);


}
uint8_t bcdToDec(uint8_t val) {
    return ((val >> 4) * 10) + (val & 0x0F);
}

uint8_t send_time_to_rtc_DMA(i2c_handle_t* i2c_hdmi ,uint8_t *time_tobe_sent ){
//
	uint8_t i;
	uint8_t dma_packet[8];

	for (i=1;i<8;i++){
		*(time_tobe_sent+i)=val2bcd(*(time_tobe_sent+i));
	}
	dma_packet[0]=0;
	for (i=1;i<8;i++){
		dma_packet[i]=*(time_tobe_sent+(i-1));
	}

	EXTI_Stop(&EXTI_1);
	i2c_start_it(i2c_hdmi,0x68,0);
	i2c_write_data_DMA(i2c_hdmi,dma_packet,&HDMA_Stream6,8);
	i2c_stop_recieve(i2c_hdmi);
}







uint8_t Set_RTC_Alarm_DMA(i2c_handle_t* i2c_hdmi ,uint8_t *time_tobe_sent ){
//
	uint8_t i;
	uint8_t dma_packet2[6];

	for (i=1;i<8;i++){
		*(time_tobe_sent+i)=val2bcd(*(time_tobe_sent+i));
	}
	dma_packet2[0]=7;
	for (i=1;i<7;i++){

		dma_packet2[i]=*(time_tobe_sent+(i-1));

	}

	i2c_start_it(i2c_hdmi,0x68,0);
	i2c_write_data_DMA(i2c_hdmi,dma_packet2,&HDMA_Stream6,6);
	i2c_stop(i2c_hdmi);
	EXTI_Init(&EXTI_1);

}




uint8_t recieve_time_from_rtc_DMA(i2c_handle_t* i2c_hdmi ,uint8_t *recived_data ){
//
	uint8_t start_reg=0,i=0;
	i2c_start_it(i2c_hdmi,0x68,0);
	i2c_write_data_DMA(i2c_hdmi,&start_reg,&HDMA_Stream6,1);
	i2c_stop(i2c_hdmi);

	i2c_recieve_data_DMA(i2c_hdmi,recived_data,&HDMA_Stream5,7);
	i2c_start_it(i2c_hdmi,0x68,1);
	uint8_t sec=bcdToDec(recived_data[0]);
	i2c_stop_recieve(i2c_hdmi);


	for (i=0;i<7;i++){
			*(recived_data+i)=bcdToDec(*(recived_data+i));
		}
}

uint8_t recieve_alarm1_time_from_rtc_DMA(i2c_handle_t* i2c_hdmi ,uint8_t *recived_data ){
//
	uint8_t start_reg=7,i=0;
	i2c_start_it(i2c_hdmi,0x68,0);
	i2c_write_data_DMA(i2c_hdmi,&start_reg,&HDMA_Stream6,1);
	i2c_stop(i2c_hdmi);

	i2c_recieve_data_DMA(i2c_hdmi,recived_data,&HDMA_Stream5,6);
	i2c_start_it(i2c_hdmi,0x68,1);
	uint8_t sec=bcdToDec(recived_data[0]);
	i2c_stop_recieve(i2c_hdmi);


	for (i=0;i<7;i++){
			*(recived_data+i)=bcdToDec(*(recived_data+i));
		}
}

uint8_t recieve_ControlReg_from_rtc_DMA(i2c_handle_t* i2c_hdmi ,uint8_t *recived_data ,uint8_t reg_read){
//
	uint8_t start_reg=reg_read,i=0;
	i2c_start_it(i2c_hdmi,0x68,0);
	i2c_write_data_DMA(i2c_hdmi,&start_reg,&HDMA_Stream6,1);
	i2c_stop(i2c_hdmi);

	i2c_recieve_data_DMA(i2c_hdmi,recived_data,&HDMA_Stream5,1);
	i2c_start_it(i2c_hdmi,0x68,1);
	uint8_t sec=bcdToDec(recived_data[0]);
	i2c_stop_recieve(i2c_hdmi);



}




uint8_t RTC_Control_Init(i2c_handle_t* i2c_hdmi ){
	RTC_Status_Init(i2c_hdmi);

uint8_t i;
	uint8_t dma_packet1[2]={14,0b111};
	i2c_start_it(i2c_hdmi,0x68,0);
	i2c_write_data_DMA(i2c_hdmi,dma_packet1,&HDMA_Stream6,2);
	i2c_stop(i2c_hdmi);

}
uint8_t RTC_Control_ReInit(i2c_handle_t* i2c_hdmi ){

uint8_t i;
	uint8_t dma_packet1[2]={14,0b111};
	i2c_start_it(i2c_hdmi,0x68,0);
	i2c_write_data_DMA(i2c_hdmi,dma_packet1,&HDMA_Stream6,2);
	i2c_stop_recieve(i2c_hdmi);

}


uint8_t RTC_Reset_Status(i2c_handle_t* i2c_hdmi ){

uint8_t i;
	uint8_t dma_packet1[2]={15,0};
	i2c_start_it(i2c_hdmi,0x68,0);
	i2c_write_data_DMA(i2c_hdmi,dma_packet1,&HDMA_Stream6,2);
	i2c_stop_recieve(i2c_hdmi);

}
uint8_t RTC_Status_Init(i2c_handle_t* i2c_hdmi ){

uint8_t i;
	uint8_t dma_packet1[2]={15,0};
	i2c_start_it(i2c_hdmi,0x68,0);
	i2c_write_data_DMA(i2c_hdmi,dma_packet1,&HDMA_Stream6,2);
	i2c_stop(i2c_hdmi);

}


uint8_t RTC_Reset_Ctrl(i2c_handle_t* i2c_hdmi ){

uint8_t i;
	uint8_t dma_packet1[2]={14,0b100};



}



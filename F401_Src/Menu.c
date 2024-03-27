/*
 * Menu.c
 *
 *  Created on: Mar 22, 2024
 *      Author: Ahmed
 */

#include "Menu.h"
extern 	DMA_Handle_t HDMA_Stream6;
extern	DMA_Handle_t HDMA_Stream5;
extern i2c_handle_t i2c_hdmi;
extern SPI_Handle_t SPI_Handle;
 uint8_t flag_for_alarm;

char date_time_str[]="SS:MM:HH-dd/DD/MM/20YY";
char recieved_set_time[22];
void Start_Menu(void){
	char disp_time_message[]="\nThe current time is\n\r";
	char set_time_message[]="\nSe-Mi-Ho-DW-DM/MO/20YY\n\r ";
	char set_alarm_message[]="\nSe-Mi-Ho-DW-DM\n\r ";
	char Choose_Motor_Speed_msg[]="\nPlease choose the light intensity\n\r";
	char time_successfully_set_msg[]="\nTime Set Successfully\n\r";
	char alarm_successfully_set_msg[]="\nAlarm Set Successfully\n\r";
	char anybutton;
	uint8_t recieved_time[7];
	uint8_t motor_speed=0;
	uint8_t speed_to_send;
	uint8_t turn_on_light_flag=102;
	uint8_t recived_data=99;
	while(1){
		uint8_t answer =Display_Main_Menu();
		if(answer==1){
			USART_Send_Poll(&USART_Handle,23,&disp_time_message);
			recieve_time_from_rtc_DMA(&i2c_hdmi,&recieved_time);
			RtcTime2toStr(recieved_time);
			USART_Send_Poll(&USART_Handle,22,&date_time_str);
			USART_Rec_Poll(&USART_Handle,1,&anybutton);
		}
		else if(answer==2){

			USART_Send_Poll(&USART_Handle,26,&set_time_message);
			USART_Rec_Poll_Menu(&USART_Handle,22,&recieved_set_time);
			RtcStr2toTime(recieved_set_time);
			if(validate_data_forRTC(recieved_set_time)){


				send_time_to_rtc_DMA(&i2c_hdmi,&recieved_set_time);

				USART_Send_Poll(&USART_Handle,25,&time_successfully_set_msg);
			}
			else{
				Display_Error();
			}


		}
		else if(answer==3){
			USART_Send_Poll(&USART_Handle,19,&set_alarm_message);
			USART_Rec_Poll_Menu(&USART_Handle,14,&recieved_set_time);
			RtcStr2toTime(recieved_set_time);
			if(validate_data_forRTC(recieved_set_time)){
				Set_RTC_Alarm_DMA(&i2c_hdmi,&recieved_set_time);
				USART_Send_Poll(&USART_Handle,25,&alarm_successfully_set_msg);
				SPI_Send_Data_IT(&SPI_Handle,&turn_on_light_flag);

			}
			else{
				Display_Error();
			}

		}
		else if(answer==4){
					USART_Send_Poll(&USART_Handle,39,&Choose_Motor_Speed_msg);
					USART_Rec_Poll(&USART_Handle,2,&motor_speed);
					speed_to_send=Str2toTime(&motor_speed);
					SPI_Send_Data_IT(&SPI_Handle,&speed_to_send);


				}
		else{
			Display_Error();
		}
	}
}


uint8_t Display_Main_Menu(void){
	char Recieved_Data;
	char Sent_Data[]="\n\rChoose From the following List \n\r 1.Display time \n\r 2.Set time \n\r 3.Set Alarm \n\r 4.Set the light intensity \n\r";
	uint8_t size=(sizeof(Sent_Data)/sizeof(Sent_Data[0]))-1;
	USART_Send_Poll(&USART_Handle,size,&Sent_Data);
	size=1;
	USART_Rec_Poll(&USART_Handle,size,&Recieved_Data);
	str2num(&Recieved_Data,1);
return Recieved_Data;
}

void Display_Error(void){
	char Sent_Data[]="\n\runrecognized input \n\r";
	uint8_t size=(sizeof(Sent_Data)/sizeof(Sent_Data[0]))-1;
	USART_Send_Poll(&USART_Handle,size,&Sent_Data);

return 1;
}

void str2num(uint8_t * arr,uint8_t size){
uint8_t i=0;
while(i<size){
	arr[i]=arr[i]-48;
	i++;
}

}

void num2str(uint8_t * arr,uint8_t size){
uint8_t i=0;
while(i<size){
	arr[i]=arr[i]+48;
	i++;
}

}

//char date_time_str[]="SS/MM/HH/dd/DD/MM/20YY";


void RtcTime2toStr(uint8_t*arr){
	uint8_t i=0,j=0;
	while(i<22){
	date_time_str[i]=(arr[j]/10)+48;
	date_time_str[i+1]=(arr[j]%10)+48;
	i+=3;
	j++;
	if(i==18){
		i=20;
	}
	}


}

void RtcStr2toTime(uint8_t*arr){
	uint8_t i=0,j=0,val=0;
	while(i<22){
	val=(uint8_t)((arr[i]-48)*10);
	val+=(uint8_t)((arr[i+1]-48)%10);
	i+=3;
	if(i==18){
		i=20;
	}
	arr[j]=val;
	j++;
	}


}
uint8_t Str2toTime(uint8_t*arr){
	uint8_t i=0,j=0,val=0;
	val=(uint8_t)((arr[i]-48)*10);
	val+=(uint8_t)((arr[i+1]-48)%10);

	return val;

}

void validate_data_forRTC(uint8_t*arr){
	uint8_t i=0,flag=1;

	if(!(arr[0]>=0)&&(arr[0]<60)){//ss
		flag=0;
	}
	if(!((arr[1]>=0)&&(arr[1]<60))){//mm
		flag=0;

		}
	if(!((arr[2]>=0)&&(arr[2]<24))){//hh
		flag=0;

		}
	if(!((arr[3]>0)&&(arr[3]<8))){//dw
		flag=0;

		}
	if(!((arr[5]>=0)&&(arr[5]<31))){//dm
		flag=0;

		}
	if(!((arr[6]>=0)&&(arr[6]<32))){//mm
		flag=0;

			}
	if(!((arr[7]>=0)&&(arr[7]<99))){//yy
		flag=0;
return flag;
}


}

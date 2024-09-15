/*
 * Alarm.c
 *
 *  Created on: Sep 15, 2024
 *      Author: Ziad Ragab
 */

/** LIB **/
#include"../LIB/std_types.h"
/** HAL **/
#include"../HAL/HLCD/HLCD_interface.h"
#include"../HAL/HDELAY/HDELAY_Interface.h"
#include "stm32f4xx_hal.h"

/** APP **/
#include"Clock.h"
#include"Alarm.h"

u8 G_u8AlarmMins=0;
u8 G_u8AlarmHours=0;


u8 G_u8AlarmON=0;
u8 G_u8AlarmRinging=0;

extern u8 G_u8DisaplayFlag;



/**
 * @brief if it's time to ring -> turn on buzzer
 *        gets called by Systick
 * 
 */
void Alarm_Ring(){
	if(Clock_compareTime(G_u8AlarmHours,G_u8AlarmMins)){
		HAL_GPIO_WritePin(GPIOB, GPIO_PIN_0, GPIO_PIN_SET);
		G_u8AlarmRinging=1;
	}
}



/**
 * @brief snoozes the alarm for 5 minutes if the alarm is ringing
 * 
 */
void Alarm_Snooze(){
	/** wait for debounce **/
	HDELAY_delay_ms(30);
	if(G_u8AlarmRinging){
		/** turn off alarm buzzer **/
		HAL_GPIO_WritePin(GPIOB, GPIO_PIN_0, GPIO_PIN_RESET);
		G_u8AlarmMins+=5;
		if(G_u8AlarmMins>59){
			G_u8AlarmMins=G_u8AlarmMins-59;
			G_u8AlarmHours++;
			if(G_u8AlarmHours>23){
				G_u8AlarmHours=0;
			}
		}
	}
}



/**
 * @brief stops the alarm from ringing if the alarm is ringing
 * 
 */
void Alarm_Stop(){
	/** wait for debounce **/
	HDELAY_delay_ms(30);
	if(G_u8AlarmRinging){
		/** Turn off alarm buzzer **/
		HAL_GPIO_WritePin(GPIOB, GPIO_PIN_0, GPIO_PIN_RESET);
		/**set alarm state to off **/
		HAL_GPIO_WritePin(GPIOB, GPIO_PIN_1, GPIO_PIN_RESET);
		G_u8AlarmON=0;
	}
}



/**
 * @brief toggles the alarm state On/OFF
 * 
 */
void Alarm_ON_OFF(){
	/** wait for debounce **/
	HDELAY_delay_ms(30);
	/** Toggle Alarm indicator and alarm state **/
	G_u8AlarmON=!G_u8AlarmON;
	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_1, G_u8AlarmON);
}



/**
 * @brief Setting alarm mode gets called by pressing set Alarm button
 * sets the alarm using 6 buttons
 * up 			:to increment the value indicated by the cursor on the LCD
 * down 		:to decrement the value indicated by the cursor on the LCD
 * right 		:to move the cursor to the right
 * left			:to move the cursor to the left
 * cancel 		:to cancel setting the alarm and redisplay the clock
 * set alarm 	:to set the global alarm variables and redisplay the clock
 */
void Alaram_setAlarm(){
	/** wait for debounce **/
	HDELAY_delay_ms(30);
	/** Cursor positions without the ':' **/
	u8 L_u8Cursor[4]={0,1,3,4};
	s8 L_s8CursorPos=0;

	u8 L_u8Time[4]={G_u8AlarmHours/10,G_u8AlarmHours%10,G_u8AlarmMins/10,G_u8AlarmMins%10};
	G_u8DisaplayFlag=0;
	/** set setting clock display to only hours and minutes **/
	HLCD_u8ClearDisplay();
	HLCD_u8SetCursor(0);
	HLCD_u8SendNumber(L_u8Time[0]);
	HLCD_u8SendNumber(L_u8Time[1]);
	HLCD_u8SendChar(':');
	HLCD_u8SendNumber(L_u8Time[2]);
	HLCD_u8SendNumber(L_u8Time[3]);
	HLCD_u8SetCursor(0);
	while(HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_8)!=0){
		/** UP **/
		if(HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_4)==0){
			L_u8Time[L_s8CursorPos]++;
			switch(L_s8CursorPos){
			case 0:
				if(L_u8Time[0]==3) L_u8Time[0]=0;
				else if(L_u8Time[0]==2 && L_u8Time[1]>=4){
					L_u8Time[1]=3;
					HLCD_u8SetCursor(L_u8Cursor[1]);
					HLCD_u8SendNumber(L_u8Time[1]);
					HLCD_u8SetCursor(L_u8Cursor[L_s8CursorPos]);
				}
				break;
			case 1:
				if(L_u8Time[0]<2){
					if(L_u8Time[1]==10) L_u8Time[1]=0;
				}else{
					if(L_u8Time[1]>=4) L_u8Time[1]=0;
				}
			break;
			case 2: if(L_u8Time[2]==6) L_u8Time[2]=0;
			break;
			case 3: if(L_u8Time[3]==10) L_u8Time[3]=0;
			break;
			}
			HLCD_u8SendNumber(L_u8Time[L_s8CursorPos]);
			HLCD_u8SetCursor(L_u8Cursor[L_s8CursorPos]);
			/** wait for debounce **/
			HDELAY_delay_ms(30);
		}
		/** Down **/
		else if(HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_5)==0){
				L_u8Time[L_s8CursorPos]--;
				switch(L_s8CursorPos){
				case 0:
					if(L_u8Time[0]==0xff){
						L_u8Time[0]=2;
						if(L_u8Time[1]>=4){
							L_u8Time[1]=3;
							HLCD_u8SetCursor(L_u8Cursor[1]);
							HLCD_u8SendNumber(L_u8Time[1]);
							HLCD_u8SetCursor(L_u8Cursor[L_s8CursorPos]);
						}
					}
					break;
				case 1:
					if(L_u8Time[0]<2){
						if(L_u8Time[1]==0xff) L_u8Time[1]=9;
					}else{
						if(L_u8Time[1]==0xff) L_u8Time[1]=3;
					}
					break;
				case 2: if(L_u8Time[2]==0xff) L_u8Time[2]=5;
				break;
				case 3: if(L_u8Time[3]==0xff) L_u8Time[3]=9;
				break;
				}
				HLCD_u8SendNumber(L_u8Time[L_s8CursorPos]);
				HLCD_u8SetCursor(L_u8Cursor[L_s8CursorPos]);
				/** wait for debounce **/
				HDELAY_delay_ms(30);
		}
		/** Right **/
		else if(HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_6)==0){
			++L_s8CursorPos;
			if(L_s8CursorPos==4) L_s8CursorPos=0;
			HLCD_u8SetCursor(L_u8Cursor[L_s8CursorPos]);
			/** wait for debounce **/
			HDELAY_delay_ms(30);

		}
		/** Left **/
		else if(HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_7)==0){
			--L_s8CursorPos;
			if(L_s8CursorPos==-1) L_s8CursorPos=3;
			HLCD_u8SetCursor(L_u8Cursor[L_s8CursorPos]);
			/** wait for debounce **/
			HDELAY_delay_ms(30);
		}
		/** Set Alarm **/
		else if(HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_9)==0){
			G_u8AlarmHours=L_u8Time[0]*10+L_u8Time[1];
			G_u8AlarmMins=L_u8Time[2]*10+L_u8Time[3];
			G_u8AlarmON=1;
			HAL_GPIO_WritePin(GPIOB, GPIO_PIN_1, GPIO_PIN_SET);
			/** wait for debounce **/
			HDELAY_delay_ms(30);
			break;
		}

	}
	/* call Clock_Init() to redisplay time */
	Clock_init();
	G_u8DisaplayFlag=1;

}

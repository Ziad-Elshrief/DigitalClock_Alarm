/*
 * Clock.c
 *
 *  Created on: Sep 10, 2024
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


u8 G_u8Secs=0;
u8 G_u8Mins=0;
u8 G_u8Hours=0;

/* the clock will display if it's not in setting mode */
u8 G_u8DisaplayFlag =1;

/**
 * @brief displayes time in hh:mm:ss format on LCD using global time variables
 * 		 gets called in the start of the program from main -> 00:00:00
 * 		 and after the end of setting process
 */
void Clock_init(){
	HLCD_u8SetCursor(0);
	HLCD_u8SendNumber(G_u8Hours/10);
	HLCD_u8SendNumber(G_u8Hours%10);
	HLCD_u8SendChar(':');
	HLCD_u8SendNumber(G_u8Mins/10);
	HLCD_u8SendNumber(G_u8Mins%10);
	HLCD_u8SendChar(':');
	HLCD_u8SendNumber(G_u8Secs/10);
	HLCD_u8SendNumber(G_u8Secs%10);
}

/**
 * @brief updates time global variables every 1 second 
 * called by systick interrupt 
 * calls Clock_display() if G_u8DisaplayFlag==1
 * 
 */
void Clock_updateTime(){

    if(G_u8Secs==59){
    	G_u8Secs=0;
    	G_u8Mins++;
    }else{
    	G_u8Secs++;
    }
    if(G_u8Mins==59){
    	G_u8Mins=0;
        if(G_u8Hours==23){
        	G_u8Hours=0;
        }else{
        	G_u8Hours++;
        }
    }
    if(G_u8DisaplayFlag){
    	Clock_display(G_u8Hours,G_u8Mins,G_u8Secs);
    }
}


/**
 * @brief updates the display of the current time on the LCD
 * 		 gets called every 1 second if G_u8DisaplayFlag ==1
 * 
 * @param hr hours to be displayed from Clock_updateTime()
 * @param min minutes to be displayed from Clock_updateTime()
 * @param sec seconds to be displayed from Clock_updateTime()
 */
void Clock_display(u8 hr , u8 min , u8 sec){
	u8 L_u8SecDig1 = (sec/10)+'0';
	u8 L_u8SecDig2 = (sec%10)+'0';
	if(sec==0){
		u8 L_u8MinDig1 = (min/10)+'0';
		u8 L_u8MinDig2 = (min%10)+'0';
		HLCD_u8SetCursor(3);
		HLCD_u8SendChar(L_u8MinDig1);
		HLCD_u8SendChar(L_u8MinDig2);
		if(min==0){
			u8 L_u8HrDig1 = (hr/10)+'0';
			u8 L_u8HrDig2 = (hr%10)+'0';
			HLCD_u8SetCursor(0);
			HLCD_u8SendChar(L_u8HrDig1);
			HLCD_u8SendChar(L_u8HrDig2);
		}
	}
		HLCD_u8SetCursor(6);
		HLCD_u8SendChar(L_u8SecDig1);
		HLCD_u8SendChar(L_u8SecDig2);

}

/**
 * @brief Setting clock mode gets called by pressing set Clock button
 * sets the clock using 6 buttons
 * up 			:to increment the value indicated by the cursor on the LCD
 * down 		:to decrement the value indicated by the cursor on the LCD
 * right 		:to move the cursor to the right 
 * left			:to move the cursor to the left
 * cancel 		:to cancel setting the clock and redisplay the clock
 * set clock 	:to set the global time variables and display the updated time 
 */
void Clock_setClock(){
	/** wait for debounce **/
	HDELAY_delay_ms(30);
	/** Cursor positions without the ':' **/
	u8 L_u8Cursor[4]={0,1,3,4};
	s8 L_s8CursorPos=0;
	/** Clock current displayed values **/
	u8 L_u8Time[4]={G_u8Hours/10,G_u8Hours%10,G_u8Mins/10,G_u8Mins%10};
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
		/** Set Clock **/
		else if(HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_3)==0){
			G_u8Hours=L_u8Time[0]*10+L_u8Time[1];
			G_u8Mins=L_u8Time[2]*10+L_u8Time[3];
			G_u8Secs=0;
			/** wait for debounce **/
			HDELAY_delay_ms(30);
			break;
		}

	}
	/* call Clock_Init() to redisplay time */
	Clock_init();
	G_u8DisaplayFlag=1;
}

/**
 * @brief compare hours and minutes to current time 
 * 
 * @param A_u8Hours :hours to be compared
 * @param A_u8Mins 	:minutes to be compared
 * @return u8 : true or false
 */
u8 Clock_compareTime(u8 A_u8Hours,u8 A_u8Mins){
	return (u8)(A_u8Hours==G_u8Hours && A_u8Mins == G_u8Mins);
}

/*
 * Clock.h
 *
 *  Created on: Sep 10, 2024
 *      Author: Ziad Ragab
 */

#ifndef SRC_APPLICATION_CLOCK_H_
#define SRC_APPLICATION_CLOCK_H_


/**
 * @brief displayes time in hh:mm:ss format on LCD using global time variables
 * 		 gets called in the start of the program from main -> 00:00:00
 * 		 and after the end of setting process
 */
void Clock_init();


/**
 * @brief updates time global variables every 1 second 
 * called by systick interrupt 
 * calls Clock_display() if G_u8DisaplayFlag==1
 * 
 */
void Clock_updateTime();


/**
 * @brief updates the display of the current time on the LCD
 * 		 gets called every 1 second if G_u8DisaplayFlag ==1
 * 
 * @param hr hours to be displayed from Clock_updateTime()
 * @param min minutes to be displayed from Clock_updateTime()
 * @param sec seconds to be displayed from Clock_updateTime()
 */
void Clock_display(u8 hr , u8 min , u8 sec);


/**
 * @brief Setting clock mode gets called by pressing set Clock button
 * sets the clock using 6 buttons
 * up 			:to increment the value indecated by the cursor on the LCD
 * down 		:to decrement the value indecated by the cursor on the LCD
 * right 		:to move the cursor to the right 
 * left			:to move the cursor to the left
 * cancel 		:to cancel setting the clock and redisplay the clock
 * set clock 	:to set the global time variables and display the updated time 
 */
void Clock_setClock();



/**
 * @brief compare hours and minutes to current time 
 * 
 * @param A_u8Hours :hours to be compared
 * @param A_u8Mins 	:minutes to be compared
 * @return u8 : true or false
 */
u8 Clock_compareTime(u8 A_u8Hours,u8 A_u8Mins);

#endif /* SRC_APPLICATION_CLOCK_H_ */

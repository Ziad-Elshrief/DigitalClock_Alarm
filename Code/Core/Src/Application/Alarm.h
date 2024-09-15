/*
 * Alarm.h
 *
 *  Created on: Sep 15, 2024
 *      Author:Ziad Ragab
 */

#ifndef ALARM_H_
#define ALARM_H_

/**
 * @brief snoozes the alarm for 5 minutes if the alarm is ringing
 * 
 */
void Alarm_Snooze();



/**
 * @brief stops the alarm from ringing if the alarm is ringing
 * 
 */
void Alarm_Stop();



/**
 * @brief if it's time to ring -> turn on buzzer
 *        gets called by Systick
 * 
 */
void Alarm_Ring();



/**
 * @brief toggles the alarm state On/OFF
 * 
 */
void Alarm_ON_OFF();



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
void Alaram_setAlarm();

#endif /* ALARM_H_ */

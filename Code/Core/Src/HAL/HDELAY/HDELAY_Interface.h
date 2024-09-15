/*
 * HDELAY_Interface.h
 *
 *  Created on: Sep 10, 2024
 *      Author: Ziad Ragab
 */

#ifndef HDELAY_INTERFACE_H_
#define HDELAY_INTERFACE_H_

/**
 * @brief creates a delay  in microsecond using Tim4
 * 
 * @param us_time :time in microsecond
 */
void HDELAY_delay_us(u16 us_time);


/**
 * @brief creates a delay  in millisecond using Tim4
 * 
 * @param ms_time : time in millisecond
 */
void HDELAY_delay_ms(u16 ms_time);




#endif /* HDELAY_INTERFACE_H_ */

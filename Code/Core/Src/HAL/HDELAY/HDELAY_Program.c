/*
 * HDELAY_Program.c
 *
 *  Created on: Sep 10, 2024
 *      Author: Ziad Ragab
 */


/*Library Layer*/
#include"../../LIB/std_types.h"




/*HAL*/
#include"HDELAY_Interface.h"


#include"stm32f4xx_hal.h"
#include"stm32f4xx_hal_tim.h"




/**
 * @brief creates a delay  in microsecond using Tim4
 * 
 * @param us_time :time in microsecond
 */
void HDELAY_delay_us(u16 us_time){
	TIM4->CNT=0;
	while(TIM4->CNT < us_time);
}



/**
 * @brief creates a delay  in millisecond using Tim4
 * 
 * @param ms_time : time in millisecond
 */
void HDELAY_delay_ms(u16 ms_time){
	ms_time*=1000;
	TIM4->CNT=0;
	while(TIM4->CNT< ms_time);
}

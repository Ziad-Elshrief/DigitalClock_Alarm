/*
 * HLCD_config.h
 *
 *  Created on: Sep 10, 2024
 *      Author: Ziad Ragab
 */
#ifndef HLCD_CONFIG_H
#define HLCD_CONFIG_H

//CONFIG for Control Pins
#define HLCD_u8_RS_PIN       GPIO_PIN_0
#define HLCD_u8_RS_PORT		 GPIOA

#define HLCD_u8_RW_PIN       GPIO_PIN_1
#define HLCD_u8_RW_PORT		 GPIOA

#define HLCD_u8_EN_PIN       GPIO_PIN_2
#define HLCD_u8_EN_PORT		 GPIOA

/** 1 Line HLCD **/
#define FunctionSet          0X30


#define DisplayControl       0x0e
#define DisplayClear         0x01
#define EntryMode            0x06
#define ReturnCGROM          0x02

/*Data Pins*/
#define HCLD_u8_DATA_PORT    GPIOA

#define HLCD_u8DATA_PIN0	GPIO_PIN_3
#define HLCD_u8DATA_PIN1	GPIO_PIN_4
#define HLCD_u8DATA_PIN2	GPIO_PIN_5
#define HLCD_u8DATA_PIN3	GPIO_PIN_11
#define HLCD_u8DATA_PIN4	GPIO_PIN_12
#define HLCD_u8DATA_PIN5	GPIO_PIN_13
#define HLCD_u8DATA_PIN6	GPIO_PIN_14
#define HLCD_u8DATA_PIN7	GPIO_PIN_15

#endif

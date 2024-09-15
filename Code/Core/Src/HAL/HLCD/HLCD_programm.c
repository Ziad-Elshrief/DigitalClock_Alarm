/*
 * HLCD_programm.c
 *
 *  Created on: Sep 10, 2024
 *      Author: Ziad Ragab
 */


/*Library Layer*/
#include"../../LIB/std_types.h"
#include"../../LIB/bit_math.h"




/*HAL*/
#include"HLCD_interface.h"
#include"HLCD_private.h"
#include"HLCD_config.h"

#include"stm32f4xx_hal.h"
//#include"stm32f4xx_hal_tim.h"

#include"../HDELAY/HDELAY_Interface.h"


/**
 * @brief function to init lcd module
 * 
 */
void HLCD_voidINIT(void)
{

	HDELAY_delay_us(31);
	/*Function set command*/
	HLCD_u8SendCmnd(FunctionSet);
	HDELAY_delay_us(40);
	/*Display on/off Control*/
	HLCD_u8SendCmnd(DisplayControl);
	HDELAY_delay_us(40);
	/*Display Clear*/
	HLCD_u8SendCmnd(DisplayClear);
	HDELAY_delay_ms(2);
	/*Entry Mode Set*/
	HLCD_u8SendCmnd(EntryMode);
}



/**
 * @brief function to send command to LCD
 * 
 * @param Copy_u8Cmnd :the command to be sent
 * @return u8 : Error state 
 */
u8 HLCD_u8SendCmnd(u8 Copy_u8Cmnd)
{
	u8 Local_u8ErrorState=STD_TYPES_OK;
	/*1- set Rs pin=> Low (command)*/
	HAL_GPIO_WritePin(HLCD_u8_RS_PORT,HLCD_u8_RS_PIN,GPIO_PIN_RESET);
	/*2- set Rw pin=>low (write)*/
	HAL_GPIO_WritePin(HLCD_u8_RW_PORT,HLCD_u8_RW_PIN,GPIO_PIN_RESET);
	/*3- send command to LCD on data Pins*/
	HAL_GPIO_WritePin(HCLD_u8_DATA_PORT, HLCD_u8DATA_PIN0, GET_BIT(Copy_u8Cmnd,0));
	HAL_GPIO_WritePin(HCLD_u8_DATA_PORT, HLCD_u8DATA_PIN1, GET_BIT(Copy_u8Cmnd,1));
	HAL_GPIO_WritePin(HCLD_u8_DATA_PORT, HLCD_u8DATA_PIN2, GET_BIT(Copy_u8Cmnd,2));
	HAL_GPIO_WritePin(HCLD_u8_DATA_PORT, HLCD_u8DATA_PIN3, GET_BIT(Copy_u8Cmnd,3));
	HAL_GPIO_WritePin(HCLD_u8_DATA_PORT, HLCD_u8DATA_PIN4, GET_BIT(Copy_u8Cmnd,4));
	HAL_GPIO_WritePin(HCLD_u8_DATA_PORT, HLCD_u8DATA_PIN5, GET_BIT(Copy_u8Cmnd,5));
	HAL_GPIO_WritePin(HCLD_u8_DATA_PORT, HLCD_u8DATA_PIN6, GET_BIT(Copy_u8Cmnd,6));
	HAL_GPIO_WritePin(HCLD_u8_DATA_PORT, HLCD_u8DATA_PIN7, GET_BIT(Copy_u8Cmnd,7));
	/*4- set Enable pulse*/
	HAL_GPIO_WritePin(HLCD_u8_EN_PORT,HLCD_u8_EN_PIN, GPIO_PIN_SET);
	HDELAY_delay_us(5);
	HAL_GPIO_WritePin(HLCD_u8_EN_PORT,HLCD_u8_EN_PIN, GPIO_PIN_RESET);
	return Local_u8ErrorState;
}



/**
 * @brief function to send a char to be displayed on LCD
 * 
 * @param Copy_u8Char :the char to be sent
 * @return u8  : Error state 
 */
u8 HLCD_u8SendChar (u8 Copy_u8Char)
{
	u8 Local_u8ErrorState=STD_TYPES_OK;
	/*1- set Rs pin=> high (char)*/
	HAL_GPIO_WritePin(HLCD_u8_RS_PORT,HLCD_u8_RS_PIN, GPIO_PIN_SET);
	/*2- set Rw pin=>low (write)*/
	HAL_GPIO_WritePin(HLCD_u8_RW_PORT,HLCD_u8_RW_PIN, GPIO_PIN_RESET);
	/*3- send command to LCD on data Pins*/
	HAL_GPIO_WritePin(HCLD_u8_DATA_PORT, HLCD_u8DATA_PIN0, GET_BIT(Copy_u8Char,0));
	HAL_GPIO_WritePin(HCLD_u8_DATA_PORT, HLCD_u8DATA_PIN1, GET_BIT(Copy_u8Char,1));
	HAL_GPIO_WritePin(HCLD_u8_DATA_PORT, HLCD_u8DATA_PIN2, GET_BIT(Copy_u8Char,2));
	HAL_GPIO_WritePin(HCLD_u8_DATA_PORT, HLCD_u8DATA_PIN3, GET_BIT(Copy_u8Char,3));
	HAL_GPIO_WritePin(HCLD_u8_DATA_PORT, HLCD_u8DATA_PIN4, GET_BIT(Copy_u8Char,4));
	HAL_GPIO_WritePin(HCLD_u8_DATA_PORT, HLCD_u8DATA_PIN5, GET_BIT(Copy_u8Char,5));
	HAL_GPIO_WritePin(HCLD_u8_DATA_PORT, HLCD_u8DATA_PIN6, GET_BIT(Copy_u8Char,6));
	HAL_GPIO_WritePin(HCLD_u8_DATA_PORT, HLCD_u8DATA_PIN7, GET_BIT(Copy_u8Char,7));
	/*4- set Enable pulse*/
	HAL_GPIO_WritePin(HLCD_u8_EN_PORT,HLCD_u8_EN_PIN, GPIO_PIN_SET);
	HDELAY_delay_us(5);
	HAL_GPIO_WritePin(HLCD_u8_EN_PORT,HLCD_u8_EN_PIN, GPIO_PIN_RESET);
	/* wait until process is done */
	HDELAY_delay_us(40);
	return Local_u8ErrorState;
}



/**
 * @brief sets the cursor in the specified location
 * 
 * @param Copy_u8CharNum : cursor position
 * @return u8 : Error state 
 */
u8 HLCD_u8SetCursor(u8 Copy_u8CharNum)
{
	u8 Local_u8ErrorState=STD_TYPES_OK;
		HLCD_u8SendCmnd(0x80+Copy_u8CharNum);
		/* wait until process is done */
			HDELAY_delay_us(40);
	return Local_u8ErrorState;
}



/**
 * @brief function to display a string on LCD 
 * 
 * @param Copy_u8String : string to be displayed on LCD
 * @param Copy_u8Cursor : the cursor position the string starts at
 * @return u8 : Error state 
 */
u8 HLCD_u8SendString(u8 Copy_u8String[16],u8 Copy_u8Cursor)
{
	u8 Local_u8ErrorState=STD_TYPES_OK;
	for(u8 i=0;Copy_u8String[i] !='\0'; i++)
	{
		HLCD_u8SendChar(Copy_u8String[i]);
	}

	return Local_u8ErrorState;
}



/**
 * @brief function to display a number on LCD
 * 
 * @param Copy_u8Number the number to be converted to ascii
 * @return u8 : Error state 
 */
u8 HLCD_u8SendNumber(u16 Copy_u8Number)
{
	u8 Local_u8ErrorState=STD_TYPES_OK;
	u8 temp1;
	u16 temp2=Copy_u8Number;
	u16 temp3=1;
	u8 counter=0;
	if(Copy_u8Number==0)
		HLCD_u8SendChar('0');
	else{
	while(temp2!=0)
	{
		temp2=temp2/10;
		counter++;
	}
	for(u8 i=0;i<(counter-1);i++)
			temp3=temp3*10;
	for(u8 i=0;i<counter; i++)
	{
		temp1=(Copy_u8Number)/temp3;
		Copy_u8Number=(Copy_u8Number)%temp3;
		temp3=temp3/10;
		HLCD_u8SendChar(48+temp1);
	}
	}
	return Local_u8ErrorState;
}



/**
 * @brief generates a special charcter 5*8 using a pattern and an index
 * 
 * @param Copy_Pu8_pattern : array of 8 elements each element represents a row 
 * @param Copy_u8_CGROM_Index : the array to save the character at 
 * starting at 0x40 index can be 0,8,16,24,32 etc.
 * @return u8 : Error state 
 */
u8 HLCD_u8GenerateSpecialCharacter(u8* Copy_Pu8_pattern,u8 Copy_u8_CGROM_Index)
{
	u8 Local_u8ErrorState=STD_TYPES_OK;
	HLCD_u8SendCmnd((0x40+Copy_u8_CGROM_Index));
	for(u8 i=0;i<8;i++)
		HLCD_u8SendChar(Copy_Pu8_pattern[i]);

	return Local_u8ErrorState;
}



/**
 * @brief displayes the special character that was written to an address
 * 
 * @param Copy_u8_PatternId : character address
 * @param Copy_u8CharNum : cursor positon
 * @return u8 : Error state 
 */
u8 HLCD_u8DisplaySpecialCharacter(u8 Copy_u8_PatternId,u8 Copy_u8CharNum)
{
	u8 Local_u8ErrorState=STD_TYPES_OK;
	HLCD_u8SetCursor(Copy_u8CharNum);
	HLCD_u8SendChar(Copy_u8_PatternId);
	return Local_u8ErrorState;
}



/**
 * @brief clears the characters displayed on the LCD
 * 
 * @return u8 : Error state 
 */
u8 HLCD_u8ClearDisplay(void)
{
	HLCD_u8SendCmnd(0x01);
	HDELAY_delay_ms(5);
	return 1;
}

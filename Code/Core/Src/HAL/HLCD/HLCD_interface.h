/*
 * HLCD_Interface.h
 *
 *	Works on LM020L module using CubeMX drivers
 *  Created on: Sep 10, 2024
 *      Author: Ziad Ragab
 */

#ifndef HLCD_INTERFACE_H
#define HLCD_INTERFACE_H

/*prototype of lcd functions*/


/**
 * @brief function to init lcd module
 * 
 */
void HLCD_voidINIT(void);



/**
 * @brief function to send command to LCD
 * 
 * @param Copy_u8Cmnd :the command to be sent
 * @return u8 : Error state 
 */
u8 HLCD_u8SendCmnd(u8 Copy_u8Cmnd);



/**
 * @brief function to send a char to be displayed on LCD
 * 
 * @param Copy_u8Char :the char to be sent
 * @return u8  : Error state 
 */
u8 HLCD_u8SendChar (u8 Copy_u8Char);



/**
 * @brief sets the cursor in the specified location
 * 
 * @param Copy_u8CharNum : cursor position
 * @return u8 : Error state 
 */
u8 HLCD_u8SetCursor(u8 Copy_u8CharNum);



/**
 * @brief function to display a string on LCD 
 * 
 * @param Copy_u8String : string to be displayed on LCD
 * @param Copy_u8Cursor : the cursor position the string starts at
 * @return u8 : Error state 
 */
u8 HLCD_u8SendString(u8 Copy_u8String[16],u8 Copy_u8Cursor);



/**
 * @brief function to display a number on LCD
 * 
 * @param Copy_u8Number the number to be converted to ascii
 * @return u8 : Error state 
 */
u8 HLCD_u8SendNumber(u16 Copy_u8Number);



/**
 * @brief generates a special charcter 5*8 using a pattern and an index
 * 
 * @param Copy_Pu8_pattern : array of 8 elements each element represents a row 
 * @param Copy_u8_CGROM_Index : the array to save the character at 
 * starting at 0x40 index can be 0,8,16,24,32 etc.
 * @return u8 : Error state 
 */
u8 HLCD_u8GenerateSpecialCharacter(u8* Copy_Pu8_pattern,u8 Copy_u8_CGROM_Index);



/**
 * @brief displayes the special character that was written to an address
 * 
 * @param Copy_u8_PatternId : character address
 * @param Copy_u8CharNum : cursor positon
 * @return u8 : Error state 
 */
u8 HLCD_u8DisplaySpecialCharacter(u8 Copy_u8_PatternId,u8 Copy_u8CharNum);



/**
 * @brief clears the characters displayed on the LCD
 * 
 * @return u8 : Error state 
 */
u8 HLCD_u8ClearDisplay(void);



#define HLCD_u8_Position_0   0
#define HLCD_u8_Position_1   1
#define HLCD_u8_Position_2   2
#define HLCD_u8_Position_3   3
#define HLCD_u8_Position_4   4
#define HLCD_u8_Position_5   5
#define HLCD_u8_Position_6   6
#define HLCD_u8_Position_7   7
#define HLCD_u8_Position_8   8
#define HLCD_u8_Position_9   9
#define HLCD_u8_Position_10  10
#define HLCD_u8_Position_11  11
#define HLCD_u8_Position_12  12
#define HLCD_u8_Position_13  13
#define HLCD_u8_Position_14  14
#define HLCD_u8_Position_15  15

#endif

/*
 * <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<< LCD_interface.h >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
 * Author : ABDELHADY ELSHAHAT ABDELHADY
 * Layer  : HAL
 * SWC    : LCD
 */

#ifndef HAL_LCD_LCD_INTERFACE_H_
#define HAL_LCD_LCD_INTERFACE_H_

#include "STD_TYPES.h"
/**************************************************************/
/* Macros for go to a certain position on LCD */
#define CD_ROW_1   0
#define CD_ROW_2   1
#define CD_ROW_3   2
#define CD_ROW_4   3

#define CD_COL_1   1
#define CD_COL_2   2
#define CD_COL_3   3
#define CD_COL_4   4
#define CD_COL_5   5
#define CD_COL_6   6
#define CD_COL_7   7
#define CD_COL_8   8
#define CD_COL_9   9
#define CD_COL_10  10
#define CD_COL_11  11
#define CD_COL_12  12
#define CD_COL_13  13
#define CD_COL_14  14
#define CD_COL_15  15
#define CD_COL_16  16
#define CD_COL_17  17
#define CD_COL_18  18
#define CD_COL_19  19
#define CD_COL_20  20
/**************************************************/

/************* Functions Prototype  **************************/

/*<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<< 1- LCD Initialization  >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>*/
/*----------------------------------------------------------------------------------------------
 *  Function    : H_LCD_void_LCD_Init
 *  Arguments   : void
 * Return type  : void
 *  Description : This Function Initialize the LCD Pins [ 4 bits mode - 8 bits mode ]
 * ----------------------------------------------------------------------------------------------
 */

void H_LCD_void_LCD_Init (void);



/*<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<< 2- LCD Send Command  >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>*/
/*----------------------------------------------------------------------------------------------
 *  Function    : H_LCD_void_SendCommand
 *  Arguments   : => Copy_u8Command (The command)
 *  Return type  : void
 *  Description : This Function Send command to LCD
 * ----------------------------------------------------------------------------------------------
 */

void H_LCD_void_SendCommand(u8 Copy_u8Command);


/*<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<< 3- LCD Send char  >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>*/
/*----------------------------------------------------------------------------------------------
 *  Function    : H_LCD_void_SendChar
 *  Arguments   : => Copy_u8Data (The character)
 *  Return type  : void
 *  Description : This Function Send character to LCD
 * ----------------------------------------------------------------------------------------------
 */

void H_LCD_void_SendChar(u8 Copy_u8Data);


/*<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<< 4- LCD Send string  >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>*/
/*----------------------------------------------------------------------------------------------
 *  Function    : H_LCD_void_SendString
 *  Arguments   : => Copy_Pu8String (The string)
 *  Return type  : void
 *  Description : This Function Send string to LCD
 * ----------------------------------------------------------------------------------------------
 */

void H_LCD_void_SendString (const u8 * Copy_Pu8String);


/*<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<< 5- LCD Send Number  >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>*/
/*----------------------------------------------------------------------------------------------
 *  Function    : H_LCD_void_SendNumber
 *  Arguments   : => Copy_s32Number (The Number)
 *  Return type  : void
 *  Description : This Function Send Number to LCD
 * ----------------------------------------------------------------------------------------------
 */

void H_LCD_void_SendNumber (s32 Copy_s32Number);


/*<<<<<<<<<<<<<<<<<<<<<<<<<<<<< 6- LCD Clear screen  >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>*/
/*----------------------------------------------------------------------------------------------
 *  Function    : H_LCD_void_ClearScreen
 *  Arguments   : void
 *  Return type : void
 *  Description : This Function Clear the LCD
 * ----------------------------------------------------------------------------------------------
 */

void H_LCD_void_ClearScreen (void);


/*<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<< 7- Go to a specific position on LCD  >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>*/
/*----------------------------------------------------------------------------------------------
 *  Function    : H_LCD_voidGoToXY
 *  Arguments   : => Copy_u8Row    == Options : [CD_ROW_1 ,CD_ROW_2,CD_ROW_3 ,CD_ROW_24]
 *  			  => Copy_u8Col    ==Options  : [CD_COL_1 ,..... CD_COL_20]
 *  Return type : void
 *  Description : This Function Go to a specific position on LCD ( for 2 * 16 and 4 * 20 LCD)
 * ----------------------------------------------------------------------------------------------
 */

void H_LCD_voidGoToXY (u8 Copy_u8Row,u8 Copy_u8Col);


/*<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<< 10- Generate Latch on the LCD / Falling edge    >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>*/
/*----------------------------------------------------------------------------------------------
 *  Function    : H_LCD_void_EnableLatch
 *  Arguments   : void
 *  Return type : void
 *  Description : This Function Generate Latch on the LCD
 * ----------------------------------------------------------------------------------------------
 */

void H_LCD_void_EnableLatch(void);

/*****************************************************************/
#endif /* HAL_LCD_LCD_INTERFACE_H_ */

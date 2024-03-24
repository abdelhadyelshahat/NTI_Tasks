/*
 * <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<< LCD_privite.h >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
 * Author : ABDELHADY ELSHAHAT ABDELHADY
 * Layer  : HAL
 * SWC    : LCD
 */

#ifndef HAL_LCD_LCD_PRIVITE_H_
#define HAL_LCD_LCD_PRIVITE_H_



/* commands macros*/
#define LCD_u8_FUNCTION_SET_8BIT_2LINES_CMD          0x38
#define LCD_u8_DISPLAY__CURSOR_BLINK_ON_CMD       0x0f
#define LCD_u8_DISPLAY_ON_OFF_CURSOR_OFF_CMD         0x0c
#define LCD_u8_DISPLAY_ClEAR_CMD       				 0x01
#define LCD_u8_ENTRT_MODE_CMD       				 0x06
#define LCD_u8_LCD_HOME_CMD       				     0x02
#define LCD_u8_FOUR_BITS_CMD       				     0x28
#define LCD_u8_EIGHT_BITS_CMD       				 0x38

/* Positions Macros*/
#define LCD_u8_R0_CMD       						 0x80
#define LCD_u8_R1_CMD       						 0xC0
#define LCD_u8_R2_CMD       						 0x94
#define LCD_u8_R3_CMD       						 0xD4


/* private for Macros mode */
#define LCD_u8_4_BIT_MODE     1
#define LCD_u8_8_BIT_MODE     2


/*<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<< 8- Handle 4bit Mode instruction   >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>*/
/*----------------------------------------------------------------------------------------------
 *  Function    : H_LCD_void_4BitHandelCommand
 *  Arguments   : => Copy_u8Command
 *  Return type : void
 *  Description : This Function Handle 4bit Mode instructions
 * ----------------------------------------------------------------------------------------------
 */

static void H_LCD_void_4BitHandelCommand (u8 Copy_u8Command);
#endif /* HAL_LCD_LCD_PRIVITE_H_ */

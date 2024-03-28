/*
 * <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<< LCD_prog.c >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
 * Author : ABDELHADY ELSHAHAT ABDELHADY
 * Layer  : HAL
 * SWC    : LCD
 */

/* LIB includes */
#include "../../LIB/STD_TYPES.h"
#include "../../LIB/BIT_MATH.h"
#include <util/delay.h>

/*MCAL includes */
#include "../../MCAL/DIO/DIO_interface.h"

/* HAL includes */
#include "LCD_interface.h"
#include "LCD_config.h"
#include "LCD_privite.h"


/*<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<< 1- LCD Initialization  >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>*/
/*----------------------------------------------------------------------------------------------
 *  Function    : H_LCD_void_LCD_Init
 *  Arguments   : void
 * Return type  : void
 *  Description : This Function Initialize the LCD Pins [ 4 bits mode - 8 bits mode ]
 * ----------------------------------------------------------------------------------------------
 */

void H_LCD_void_LCD_Init (void)
{
	/* wait for more than 30ms after VDD rises to 4.5V*/
	_delay_ms(50);

	/* 1- Set Directions of Data LCD pins */

#if LCD_u8_Mode == LCD_u8_8_BIT_MODE 					/* check the MODE of the LCD */

	/* In 8 bits mode the PINs must be in the same port*/
	M_DIO_u8_SetPortDirection(LCD_u8_Data_PORT,DIO_u8_PORT_DIRECTION_OUTPUT);

#elif LCD_u8_MODE == LCD_u8_4_BIT_MODE                 /* check the MODE of the LCD */
	/* In 4 bits mode the pins can be from any port */
	M_DIO_u8_SetPinDirection(LCD_u8_D7_PORT,LCD_u8_D7_PIN,DIO_u8_PIN_OUTPUT_DIRECTION);
	M_DIO_u8_SetPinDirection(LCD_u8_D6_PORT,LCD_u8_D6_PIN,DIO_u8_PIN_OUTPUT_DIRECTION);
	M_DIO_u8_SetPinDirection(LCD_u8_D5_PORT,LCD_u8_D5_PIN,DIO_u8_PIN_OUTPUT_DIRECTION);
	M_DIO_u8_SetPinDirection(LCD_u8_D4_PORT,LCD_u8_D4_PIN,DIO_u8_PIN_OUTPUT_DIRECTION);

#endif
	/* 2-  Set the direction of LCD control Pins*/
	M_DIO_u8_SetPinDirection(LCD_u8_RS_PORT,LCD_u8_RS_PIN,DIO_u8_PIN_OUTPUT_DIRECTION);
	M_DIO_u8_SetPinDirection(LCD_u8_EN_PORT,LCD_u8_EN_PIN,DIO_u8_PIN_OUTPUT_DIRECTION);
	M_DIO_u8_SetPinDirection(LCD_u8_RW_PORT,LCD_u8_RW_PIN,DIO_u8_PIN_OUTPUT_DIRECTION);

	/* 3- LCD initialization sequence */
	H_LCD_void_SendCommand(LCD_u8_LCD_HOME_CMD);  				 /* 3i- Function set Send command */
	_delay_ms(30);


#if LCD_u8_Mode == LCD_u8_8_BIT_MODE				              /* 3ii- choose the command mode */
	H_LCD_void_SendCommand(LCD_u8_EIGHT_BITS_CMD);
#elif LCD_u8_MODE == LCD_u8_4_BIT_MODE
	H_LCD_void_SendCommand(LCD_u8_FOUR_BITS_CMD);
#endif
	_delay_ms(1);


	H_LCD_void_SendCommand(LCD_u8_DISPLAY_ON_OFF_CURSOR_OFF_CMD); /* 3iii- Display on / off control command */
	_delay_ms(1);


	H_LCD_void_SendCommand(LCD_u8_DISPLAY_ClEAR_CMD);			/* 3v-  Display clear command */
	_delay_ms(2);


	H_LCD_void_SendCommand(LCD_u8_ENTRT_MODE_CMD);				/* 3iv-  Entry mode command */
	_delay_ms(2);
}



/*<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<< 2- LCD Send Command  >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>*/
/*----------------------------------------------------------------------------------------------
 *  Function    : H_LCD_void_SendCommand
 *  Arguments   : => Copy_u8Command (The command)
 *  Return type  : void
 *  Description : This Function Send command to LCD
 * ----------------------------------------------------------------------------------------------
 */

void H_LCD_void_SendCommand(u8 Copy_u8Command)
{
	/* select command register ( RS = 0)*/
	M_DIO_u8_SetPinValue(LCD_u8_RS_PORT,LCD_u8_RS_PIN,DIO_u8_PIN_VALUE_LOW);

	/* select the operation  R or W ( make sure that RW pin always on Low) */
	/* M_DIO_u8_SetPinValue(LCD_u8_EN_PORT,LCD_u8_EN_PIN,DIO_u8_PIN_VALUE_LOW); */

#if LCD_u8_Mode == LCD_u8_8_BIT_MODE /* Check the mode of operation */

	M_DIO_u8_SetPortValue(LCD_u8_Data_PORT,Copy_u8Command); /* send the command direct to the LCD */
	H_LCD_void_EnableLatch();								/* send latch to LCD */

#elif LCD_u8_MODE == LCD_u8_4_BIT_MODE
	H_LCD_void_4BitHandelCommand(Copy_u8Command);   	/* function Handle the command for 4bits mode*/


#endif


}


/*<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<< 3- LCD Send char  >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>*/
/*----------------------------------------------------------------------------------------------
 *  Function    : H_LCD_void_SendChar
 *  Arguments   : => Copy_u8Data (The character)
 *  Return type  : void
 *  Description : This Function Send character to LCD
 * ----------------------------------------------------------------------------------------------
 */

void H_LCD_void_SendChar(u8 Copy_u8Data)
{
	/* select Data register ( RS = 1)*/
	M_DIO_u8_SetPinValue(LCD_u8_RS_PORT,LCD_u8_RS_PIN,DIO_u8_PIN_VALUE_HIGH);

	/* select the operation  R or W ( make sure that RW pin always on Low) */
	/* M_DIO_u8_SetPinValue(LCD_u8_EN_PORT,LCD_u8_EN_PIN,DIO_u8_PIN_VALUE_LOW); */
	/* select the operation  R or W ( make sure that RW pin always on Low) */
	/* M_DIO_u8_SetPinValue(LCD_u8_EN_PORT,LCD_u8_EN_PIN,DIO_u8_PIN_VALUE_LOW); */

#if LCD_u8_Mode == LCD_u8_8_BIT_MODE  		      			/* Check the mode of the operation */
	M_DIO_u8_SetPortValue(LCD_u8_Data_PORT,Copy_u8Data);	/* send the command directly to LCD i 8 bit mode */
	H_LCD_void_EnableLatch();								/* falling edge (latch)*/

#elif LCD_u8_MODE == LCD_u8_4_BIT_MODE
	H_LCD_void_4BitHandelCommand(Copy_u8Data);  /* function handle the data for 4bit mode and send it to LCD */

#endif

}

/*<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<< 4- LCD Send string  >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>*/
/*----------------------------------------------------------------------------------------------
 *  Function    : H_LCD_void_SendString
 *  Arguments   : => Copy_Pu8String (The string)
 *  Return type  : void
 *  Description : This Function Send string to LCD
 * ----------------------------------------------------------------------------------------------
 */

void H_LCD_void_SendString (const u8 * Copy_Pu8String)
{
	u8 Local_u8StringIterator = 0; /* string iterator*/
	while (Copy_Pu8String[Local_u8StringIterator] != '\0') /* loop on the string till find the Null character*/
	{
		/* Slice the string into characters and send it character by character*/
		H_LCD_void_SendChar(Copy_Pu8String[Local_u8StringIterator++]); /*Post increment to the string Iterator */
	}

}

/*<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<< 5- LCD Send Number  >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>*/
/*----------------------------------------------------------------------------------------------
 *  Function    : H_LCD_void_SendNumber
 *  Arguments   : => Copy_s32Number (The Number)
 *  Return type  : void
 *  Description : This Function Send Number to LCD
 * ----------------------------------------------------------------------------------------------
 */

void H_LCD_void_SendNumber (s32 Copy_s32Number)
{
	/* Slice the Digits of the Number */
	/* Store every single digit in the array */
	s8 Local_As8NumberDigits[10] = {0};  /*assign the array with initial values = Zeros*/
	u8 Local_u8Counter =0; 				/*Array counter to count the digits of the number  */
	if (Copy_s32Number < 0)				/* check if the Number id negative */
	{
		/* if negative convert to positive */
		Copy_s32Number *= -1 ;
		/* send char 'a' represent the sign (-)*/
		H_LCD_void_SendChar('-');
	}

	do
	{
		/*Slice the Last Digit and Store it in the array*/
		Local_As8NumberDigits[Local_u8Counter] = Copy_s32Number % 10;
		/*Cut the last digit from the Number */
		Copy_s32Number/= 10;
		/* increment the Digits counter */
		Local_u8Counter++;
	}
	while (Copy_s32Number != 0); /* check if the rest Digits of the Number */

	while (Local_u8Counter > 0)
	{
		/* send the Digits to The LCD in reverse */
		H_LCD_void_SendChar(Local_As8NumberDigits[--Local_u8Counter] + 48 );
	}


/*	<<< another method >>>
	u32 Local_32ReverseNumber= 1;
	u8 Local_u8SignleNum = 0;
	while (Copy_u32Number != 0)
	{
		Local_32ReverseNumber = (Local_32ReverseNumber * 10)  + (Copy_u32Number % 10 ) ;

		Copy_u32Number  /= 10;
	}

	while (Local_32ReverseNumber !=1 )
	{
		Local_u8SignleNum =Local_32ReverseNumber % 10 ;

		H_LCD_void_SendChar(48 +Local_u8SignleNum);
		Local_32ReverseNumber /= 10;
	}



 */
}



/*<<<<<<<<<<<<<<<<<<<<<<<<<<<<< 6- LCD Clear screen  >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>*/
/*----------------------------------------------------------------------------------------------
 *  Function    : H_LCD_void_ClearScreen
 *  Arguments   : void
 *  Return type : void
 *  Description : This Function Clear the LCD
 * ----------------------------------------------------------------------------------------------
 */

void H_LCD_void_ClearScreen (void)
{
	/* the LCD_u8_DISPLAY_ClEAR_CMD clear the Screen of the LCD */
	H_LCD_void_SendCommand(LCD_u8_DISPLAY_ClEAR_CMD);

}

/*<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<< 7- Go to a specific position on LCD  >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>*/
/*----------------------------------------------------------------------------------------------
 *  Function    : H_LCD_voidGoToXY
 *  Arguments   : => Copy_u8Row    == Options : [CD_ROW_1 ,CD_ROW_2,CD_ROW_3 ,CD_ROW_24]
 *  			  => Copy_u8Col    ==Options  : [CD_COL_1 ,..... CD_COL_20]
 *  Return type : void
 *  Description : This Function Go to a specific position on LCD ( for 2 * 16 and 4 * 20 LCD)
 * ----------------------------------------------------------------------------------------------
 */

void H_LCD_voidGoToXY (u8 Copy_u8Row,u8 Copy_u8Col)
{
	/* Array holding the positions of the Starting point for every row */
	u8 Copy_Au8Rows[4] ={LCD_u8_R0_CMD,LCD_u8_R1_CMD,LCD_u8_R2_CMD,LCD_u8_R3_CMD} ;

	H_LCD_void_SendCommand(Copy_Au8Rows[Copy_u8Row] + Copy_u8Col);

}


/*<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<< 8- Handle 4bit Mode instruction   >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>*/
/*----------------------------------------------------------------------------------------------
 *  Function    : H_LCD_void_4BitHandelCommand
 *  Arguments   : => Copy_u8Command
 *  Return type : void
 *  Description : This Function Handle 4bit Mode instructions
 * ----------------------------------------------------------------------------------------------
 */

static void H_LCD_void_4BitHandelCommand (u8 Copy_u8Command)
{
	/* Get the 4 MSB bits of the command and send it to the LCD */
	M_DIO_u8_SetPinValue(LCD_u8_D7_PORT,LCD_u8_D7_PIN,GET_BIT(Copy_u8Command,7));
	M_DIO_u8_SetPinValue(LCD_u8_D6_PORT,LCD_u8_D6_PIN,GET_BIT(Copy_u8Command,6));
	M_DIO_u8_SetPinValue(LCD_u8_D5_PORT,LCD_u8_D5_PIN,GET_BIT(Copy_u8Command,5));
	M_DIO_u8_SetPinValue(LCD_u8_D4_PORT,LCD_u8_D4_PIN,GET_BIT(Copy_u8Command,4));
	/*Falling edge */
	H_LCD_void_EnableLatch();
	/* get the LSB of the command and Send it to the LCD */
	M_DIO_u8_SetPinValue(LCD_u8_D7_PORT,LCD_u8_D7_PIN,GET_BIT(Copy_u8Command,3));
	M_DIO_u8_SetPinValue(LCD_u8_D6_PORT,LCD_u8_D6_PIN,GET_BIT(Copy_u8Command,2));
	M_DIO_u8_SetPinValue(LCD_u8_D5_PORT,LCD_u8_D5_PIN,GET_BIT(Copy_u8Command,1));
	M_DIO_u8_SetPinValue(LCD_u8_D4_PORT,LCD_u8_D4_PIN,GET_BIT(Copy_u8Command,0));
	/* Falling edge*/
	H_LCD_void_EnableLatch();

}

/*<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<< 10- Generate Latch on the LCD / Falling edge    >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>*/
/*----------------------------------------------------------------------------------------------
 *  Function    : H_LCD_void_EnableLatch
 *  Arguments   : void
 *  Return type : void
 *  Description : This Function Generate Latch on the LCD
 * ----------------------------------------------------------------------------------------------
 */

void H_LCD_void_EnableLatch(void)
{
	/* Making latch on LCD EN PIN */
	/* Set the pin on High, making delay then bring back to Low */
	M_DIO_u8_SetPinValue(LCD_u8_EN_PORT,LCD_u8_EN_PIN,DIO_u8_PIN_VALUE_HIGH);
	_delay_us(300);
	M_DIO_u8_SetPinValue(LCD_u8_EN_PORT,LCD_u8_EN_PIN,DIO_u8_PIN_VALUE_LOW);
}

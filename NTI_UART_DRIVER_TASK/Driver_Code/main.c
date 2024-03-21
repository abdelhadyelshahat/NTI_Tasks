/*
 * main.c
 *
 *  Created on: Mar 20, 2024
 *      Author: hady
 */

/* LIB includes */
#include <util/delay.h>
#include "STD_TYPES.h"

/* HAL includes*/
#include "LCD_interface.h"
/* MCAL includes */
#include "UART_interface.h"
#include "GIE_interface.h"
#include "DIO_interface.h"

/*Buffer Size*/
#define BUFFER_SIZE   10

void APP_NotificationFunction(void);
/* variable to hold the character*/
u8 APP_u8Caracter = 'n' ;

u8 APP_Au8Buffer[BUFFER_SIZE];
void main (void)
{
	M_DIO_void_DIOInit();
	GIE_voidGIEEnable();
	H_LCD_void_LCD_Init();
	M_UART_void_UARTInit();

	while (1)
	{


		/* Test the receive string Asynchronous*/
		M_UART_u8RecieveBufferASynch(APP_Au8Buffer,BUFFER_SIZE,&APP_NotificationFunction);
//
//		/* Test receive string Synch Function */
//		if (M_UART_u8RecieveBufferSynch(APP_Au8Buffer,BUFFER_SIZE) == STD_TYPES_OK)
//		{
//			H_LCD_void_SendString("UART Finish");
//			_delay_ms(1000);
//		}
//
//		/* Test send string Asynchronous*/
//		M_UART_u8SendStringAsynch("Hello",&APP_NotificationFunction);

//
//				/* Test Send string Synch Function */
//				M_UART_u8_SendStringSynch("Function is working ");
//				_delay_ms(1000);

		/* Test receive character function  */
		//	 if (M_UART_u8_Recievecharacter(&APP_u8Caracter) == STD_TYPES_OK)
		//		 H_LCD_void_SendChar(APP_u8Caracter);


		/* Test Send char function */
		//	M_UART_u8_UARTSendCharacter('a');
		//	_delay_ms(1000);


	 }
}

void APP_NotificationFunction()
{

	H_LCD_void_SendString(" UART Finish");
	M_DIO_u8_TogglePinValue(DIO_u8_PORTA,DIO_u8_PIN0);
	_delay_ms(1000);

}

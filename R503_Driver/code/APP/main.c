/*
 * main.c
 *
 *  Created on: Mar 22, 2024
 *      Author: hady
 */

/* LIB includes*/
#include "util/delay.h"

/* HAL includes */
#include "../HAL/R503_interface.h"
#include "../HAL/LCD/LCD_interface.h"

/*MCAL includes */
#include "../MCAL/UART_interface.h"


/* Application function prototypes*/
void App_void_Print_Error_Reason(u8 Local_u8ACKMasssage);



void main (void)
{
	/*Initialization */
	M_UART_void_UARTInit();
	H_LCD_void_LCD_Init();

	/* ACK holder massage variable */
	s8 Local_u8ACK;


	while(1)
	{
		/* vale -1 is just indication for the intial value*/
		 Local_u8ACK = -1 ;


		/* Led when Enrollment is flashing blue color*/
		FingerPs_AuraLedConfig(0x02,125,0X02,125);

		/* LCD Enrollment massage */
		H_LCD_void_ClearScreen();
		H_LCD_void_SendString(" Enrollment phase");
		H_LCD_void_ClearScreen();
		H_LCD_void_SendString("Put your finger ");
		_delay_ms(1000);

		/* Enrollment operation */
		Local_u8ACK = Finger_Ps_EnrollmentOpreation(0x0004);

		/* Check the ACK of the operation */
		if (Local_u8ACK == R503_PROCESS_COMPLETE)
		{
			/* LCD Enrollment success massage */
			_delay_ms(200);
			H_LCD_void_ClearScreen();
			_delay_ms(500);
			H_LCD_void_SendString("enrollment Success");
			/* Led when Enrollment success is flashing Purple color*/
			FingerPs_AuraLedConfig(0x02,125,0X03,125);
			_delay_ms(2000);
		}
		else
		{
			/* Enrollment Fail Get reason */
			H_LCD_void_ClearScreen();
			/* Led when Enrollment success is flashing Purple color*/
			FingerPs_AuraLedConfig(0x02,125,0X01,125);
			/* LCD Enrollment fail massage */
			H_LCD_void_SendString("enrollment fail");
			_delay_ms(1500);
			App_void_Print_Error_Reason(Local_u8ACK);
		}

		/* LCD Matching operation massage*/
		_delay_ms(1500);
		H_LCD_void_ClearScreen();;
		H_LCD_void_SendString(" now matching");
		_delay_ms(1500);
		H_LCD_void_SendString("Put your finger ");
		_delay_ms(1500);

		/* Now matching operation */
		Local_u8ACK=FingerPS_searchFinger(0x0004);

		/* check the ACK*/
		if (Local_u8ACK == R503_PROCESS_COMPLETE)
		{
			/* LCD matching appertain success massage*/
			H_LCD_void_ClearScreen();
			H_LCD_void_SendString("matching OK ");
			_delay_ms(1500);
		}
		else
		{
			/* LCD matching appertain fail massage*/
			H_LCD_void_SendString(" NO matching");
			_delay_ms(1500);}
		}


}

void App_void_Print_Error_Reason(u8 Local_u8ACKMasssage)
{
	H_LCD_void_ClearScreen()  ;
	switch (Local_u8ACKMasssage)
	{
		case R503_ERROR_WHEN_RECEIVING_DATA_PACKAGE  	        : H_LCD_void_SendString("R503_ERROR_WHEN_RECEIVING_DATA_PACKAGE  	");   break;
	    case R503_NO_FINGER_ON_THE_SENSOR			   	        : H_LCD_void_SendString("R503_NO_FINGER_ON_THE_SENSOR			   	");   break;
	    case R503_FAIL_TO_ENROLL_THE_FINGER			  	        : H_LCD_void_SendString("R503_FAIL_TO_ENROLL_THE_FINGER			  	");   break;
	    case R503_FAIL_TO_GEN_CHAR_FILE_DUE_TO_DISORDERLY       : H_LCD_void_SendString("R503_FAIL_TO_GEN_CHAR_FILE_DUE_TO_DISORDERLY");  break;
	    case R503_FAIL_TO_GEN_CHAR_FILE_DUE_TO_LACKNESS         : H_LCD_void_SendString("R503_FAIL_TO_GEN_CHAR_FILE_DUE_TO_LACKNESS  ");  break;
	    case R503_FINGER_DO_NOT_MATCH					        : H_LCD_void_SendString("R503_FINGER_DO_NOT_MATCH					");   break;
	    case R503_FAIL_TO_FIND_THE_MATCH_FINGER			        : H_LCD_void_SendString("R503_FAIL_TO_FIND_THE_MATCH_FINGER			");   break;
	    case R503_FAIL_TO_COMBINE_THE_CHAR_FILE			        : H_LCD_void_SendString("R503_FAIL_TO_COMBINE_THE_CHAR_FILE			");   break;
	    case R503_FAIL_TO_CLEAR_THE_FINGER_LIB		  	        : H_LCD_void_SendString("R503_FAIL_TO_CLEAR_THE_FINGER_LIB		  	");   break;
	    case R503_FAIL_TO_DELETE_THE_TEMPLATE		  	        : H_LCD_void_SendString("R503_FAIL_TO_DELETE_THE_TEMPLATE		  	");   break;


	}
	_delay_ms(1500);


}

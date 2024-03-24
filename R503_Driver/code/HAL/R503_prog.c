/*
 * File Name  : 	R503_prog.c
 * Layer	  :		HAL
 * Created on :		Mar 22, 2024
 * Author	  : 	Abdelhady Elshahat Abdelhady
 */

/* LIB includes*/
#include "../LIB/BIT_MATH.h"
#include "../LIB/STD_TYPES.h"
#include <util/delay.h>

/* HAL includes*/
#include "R503_interface.h"
#include "R503_config.h"
#include "R503_privite.h"

/* MCAL includes */
#include "../MCAL/UART_interface.h"

/*>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>*/
/************************* The third main functionality of the Finger Print **********************************/
/************************* ------ matching operation  1 : N --------   ********************************/

u8 Finger_Ps_Matchinf1toN (void)
{
	u8 Local_u8FunctionState;

	/* 1- Scan the finger and save the image in the image buffer*/
	Local_u8FunctionState =FingerPS_genImg();

	if (Local_u8FunctionState == R503_PROCESS_COMPLETE)
	{}
	else
	{ return Local_u8FunctionState; }


	/* 2i - convert the image in the image buffer to character file*/
	/*2ii - then save the character file in the character buffer 1 */
	Local_u8FunctionState =FingerPS_convertImg2CharFile(R503_CHARACTER_FILE_1);

	if (Local_u8FunctionState == R503_PROCESS_COMPLETE)
	{}
	else
	{return Local_u8FunctionState;}

	/* Search in the finger print library and */
	Local_u8FunctionState = FingerPS_searchFinger(R503_CHARACTER_FILE_1);

	/* return the state of the operation */
	return Local_u8FunctionState;

}


/************************* The second main functionality of the Finger Print **********************************/
/************************* ------ matching operation  1 : 1--------   ********************************/

u8 Finger_Ps_Matching1to1(u16 Copy_u16FingerPrintID)
{
	u8 Local_u8FunctionState;

	/* 1- Scan the finger and save the image in the image buffer*/
	Local_u8FunctionState =FingerPS_genImg();

	if (Local_u8FunctionState == R503_PROCESS_COMPLETE)
	{}
	else
	{ return Local_u8FunctionState; }


	/* 2i - convert the image in the image buffer to character file*/
	/*2ii - then save the character file in the character buffer 1 */
	Local_u8FunctionState =FingerPS_convertImg2CharFile(R503_CHARACTER_FILE_1);

	if (Local_u8FunctionState == R503_PROCESS_COMPLETE)
	{}
	else
	{return Local_u8FunctionState;}

	/* 3-  Load the template image from the finger Library to character file 2 */
	Local_u8FunctionState = FingerPS_LoadCharFile(Copy_u16FingerPrintID,R503_CHARACTER_FILE_2);

	if (Local_u8FunctionState == R503_PROCESS_COMPLETE)
	{}
	else
	{return Local_u8FunctionState;}

	/* matching between the 2 character files */
	Local_u8FunctionState = FingerPS_match();

	/* return the Function States */
	return Local_u8FunctionState;
}



/************************* The first main functionality of the Finger Print **********************************/
/************************* ------ Enrollment operation  --------   ********************************/

u8 Finger_Ps_EnrollmentOpreation( u16 Copy_u16FingerPrintID)
{
	u8 Local_u8FunctionState;

	/* Initialization delay */
	_delay_ms(500);

	/* 1- Just shake hands */
	Local_u8FunctionState = FingerPS_handShake();

	if (Local_u8FunctionState == R503_PROCESS_COMPLETE)
	{}
	else
	{ return Local_u8FunctionState; }

	/* 2- Scan the finger and save the image in the image buffer*/
	Local_u8FunctionState =FingerPS_genImg();

	if (Local_u8FunctionState == R503_PROCESS_COMPLETE)
	{}
	else
	{return Local_u8FunctionState;}

	/* 3i - convert the image in the image buffer to character file*/
	/*3ii - then save the character file in the character buffer 1 */
	Local_u8FunctionState =FingerPS_convertImg2CharFile(R503_CHARACTER_FILE_1);

	if (Local_u8FunctionState == R503_PROCESS_COMPLETE)
	{}
	else
	{return Local_u8FunctionState;}

	/* 4- Take another scan and save it in the image buffer */
	Local_u8FunctionState =FingerPS_genImg();

	if (Local_u8FunctionState == R503_PROCESS_COMPLETE)
	{}
	else
	{return Local_u8FunctionState;}

	/* 5i - convert the image in the image buffer to character file*/
	/*5ii - then save the character file in the character buffer 2 */
	Local_u8FunctionState =FingerPS_convertImg2CharFile(R503_CHARACTER_FILE_2);

	if (Local_u8FunctionState == R503_PROCESS_COMPLETE)
	{}
	else
	{return Local_u8FunctionState;}

	/* 6- Combine between the 2 characters buffers and override on the character buffer 1*/
	/*   - generate Finger print template */
	Local_u8FunctionState = FingerPS_genTemplate();

	if (Local_u8FunctionState == R503_PROCESS_COMPLETE)
	{}
	else
	{return Local_u8FunctionState;}

	/* 7- Store the Template in a certain position in the finger print library*/
	Local_u8FunctionState = FingerPS_strTemplate(Copy_u16FingerPrintID);

	if (Local_u8FunctionState == R503_PROCESS_COMPLETE)
	{}
	else
	{return Local_u8FunctionState;}

	/** Function finished **/


	return Local_u8FunctionState;

}

/*>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>*/



/* Brief : this function to turn on the Aura Led and playing with it */
u8 FingerPs_AuraLedConfig (u8 Copy_u8CtrlCode,u8 Copy_u8Speed, u8 Copy_u8ColorIndex , u8 Copy_u8Times)
{
	/* ACK variable */
	u8 Local_u8_ACKValue ;

	/* Delay for Being ready */
	_delay_ms(200);

	/* Data Array */
	u8 Local_Au8Data[5] = {0x035};

	/* Control Code */
	Local_Au8Data[1] = Copy_u8CtrlCode ;

	/* Speed */
	Local_Au8Data[2] = Copy_u8Speed ;

	/* Color */
	Local_Au8Data[3] = Copy_u8ColorIndex ;

	/* Color */
	Local_Au8Data[4] = Copy_u8Times ;

	/* Send Package */
	H_R503_void_SendPackage(R503_COMMAND_PACKET,0x0007,Local_Au8Data);

	/* Read the ACK form the sensor */
	Local_u8_ACKValue = R503_u8_CheckACK();

	return Local_u8_ACKValue;




}



/* Brief : to check if the collected image in character buffer1 is
*			matched with a certain template uploaded in
*			character buffer2
 * */


u8 FingerPS_match()
{
	/* ACK variable */
	u8 Local_u8_ACKValue ;

	/* Delay for Being ready */
	_delay_ms(200);

	/* Data Array */
	u8 Local_Au8Data[1] = {0x03};


	/* Send Package */
	H_R503_void_SendPackage(R503_COMMAND_PACKET,0x0003,Local_Au8Data);

	/* Read the ACK form the sensor */
	Local_u8_ACKValue = R503_u8_CheckACK();

	return Local_u8_ACKValue;


}



/** Brief : this function is used to load a template in a character file .
 */

u8 FingerPS_LoadCharFile(u16 Copy_u8FingurePrintTempleteID ,u8 Copy_u8CharcterFileNumber)
{
	/* ACK variable */
	u8 Local_u8_ACKValue ;

	/* Delay for Being ready */
	_delay_ms(200);

	/* Data Array */
	u8 Local_Au8Data[6] = {0x07};

	switch (Copy_u8CharcterFileNumber)
	{
	case R503_CHARACTER_FILE_1: Local_Au8Data[1] = R503_CHARACTER_FILE_1; break;
	case R503_CHARACTER_FILE_2: Local_Au8Data[1] = R503_CHARACTER_FILE_2; break;
	}

	Local_Au8Data[2] = (u8)(Copy_u8FingurePrintTempleteID >> R503_8_Bits_Shift);
	Local_Au8Data[3] = (u8)(Copy_u8FingurePrintTempleteID );


	/* Send Package */
	H_R503_void_SendPackage(R503_COMMAND_PACKET,0x0006,Local_Au8Data);

	/* Read the ACK form the sensor */
	Local_u8_ACKValue = R503_u8_CheckACK();

	return Local_u8_ACKValue;

}

/** Brief : this function is used to delete a certain template.
 *
 */

u8 FingerPS_deleteFinger(u16 Copy_u8FingurePrintTempleteID)
{
	/* ACK variable */
	u8 Local_u8_ACKValue ;

	/* Delay for Being ready */
	_delay_ms(200);

	/* Data Array */
	u8 Local_Au8Data[5] = {0x0c};

	Local_Au8Data[2] = (u8)(Copy_u8FingurePrintTempleteID >> R503_8_Bits_Shift);
	Local_Au8Data[3] = (u8)(Copy_u8FingurePrintTempleteID );

	Local_Au8Data[4] = 0x00;
	Local_Au8Data[5] = 0x01;



	/* Send Package */
	H_R503_void_SendPackage(R503_COMMAND_PACKET,0x0007,Local_Au8Data);

	/* Read the ACK form the sensor */
	Local_u8_ACKValue = R503_u8_CheckACK();

	return Local_u8_ACKValue;


}


/* Brief : this function is used to delete all templates in
 *			template library.
 * */

u8 FingerPS_emptyLibrary()
{
	/* ACK variable */
	u8 Local_u8_ACKValue ;

	/* Delay for Being ready */
	_delay_ms(200);

	/* Data Array */
	u8 Local_Au8Data[1] = {0x0d};


	/* Send Package */
	H_R503_void_SendPackage(R503_COMMAND_PACKET,0x0003,Local_Au8Data);

	/* Read the ACK form the sensor */
	Local_u8_ACKValue = R503_u8_CheckACK();

	return Local_u8_ACKValue;

}


/*Brief : this function search and match 1 : N
 * 		 compare the character file from of the Two characters buffers with the All Library Fingers
 * 		 if matching or not return an ACK for it
 * */

u8 FingerPS_searchFinger(u8 Copy_u8CharcterFileNumber)
{
	/* ACK variable */
	u8 Local_u8_ACKValue ;

	/* Delay for Being ready */
	_delay_ms(200);

	/* Data Array */
	u8 Local_Au8Data[6] = {0x04};

	/* check where to save the converted character file
	 * then save the its location in the Data Array */
	switch (Copy_u8CharcterFileNumber)
	{
	case R503_CHARACTER_FILE_1: Local_Au8Data[1] = R503_CHARACTER_FILE_1; break;
	case R503_CHARACTER_FILE_2: Local_Au8Data[1] = R503_CHARACTER_FILE_2; break;
	}

	/* Start searching Address (start page) */
	Local_Au8Data[2]= 0x00;
	Local_Au8Data[3]= 0x00;
	/* page Numbers ( Stop Number) */
	Local_Au8Data[4]= 0x00;
	Local_Au8Data[5]= 0xFF;


	/* Send Package */
	H_R503_void_SendPackage(R503_COMMAND_PACKET,0x0008,Local_Au8Data);

	/* Read the ACK form the sensor */
	Local_u8_ACKValue = R503_u8_CheckACK();

	return Local_u8_ACKValue;





}


/* Brief : this function is used to store template file in
*			template library saved in Flash Memory .
* */

u8 FingerPS_strTemplate(u16 Copy_u8FingurePrintTempleteID)
{
	/* ACK variable */
	u8 Local_u8_ACKValue ;

	/* Delay for Being ready */
	_delay_ms(200);

	/* Data Array */
	/* we always take the combined character files from the character file buffer 1*/
	u8 Local_Au8Data[4] = {0x06,R503_CHARACTER_FILE_1};

	Local_Au8Data[2] = (u8)(Copy_u8FingurePrintTempleteID >> R503_8_Bits_Shift);
	Local_Au8Data[3] = (u8)(Copy_u8FingurePrintTempleteID );


	/* Send Package */
	H_R503_void_SendPackage(R503_COMMAND_PACKET,0x0006,Local_Au8Data);

	/* Read the ACK form the sensor */
	Local_u8_ACKValue = R503_u8_CheckACK();

	return Local_u8_ACKValue;

}

/* Brief : This function is used to generate template file from
*			combined character buffers.
 * */
u8 FingerPS_genTemplate(void)
{
	/* ACK variable */
	u8 Local_u8_ACKValue ;

	/* Delay for Being ready */
	_delay_ms(200);

	/* Data Array */
	u8 Local_Au8Data[1] = {0x05};

	/* Send Package */
	H_R503_void_SendPackage(R503_COMMAND_PACKET,0x0003,Local_Au8Data);

	/* Read the ACK form the sensor */
	Local_u8_ACKValue = R503_u8_CheckACK();

	return Local_u8_ACKValue;


}

/*Brief : This function Convert the Image in the image Buffer to character file
 * 		  then save it in the Character file buffer (we have 2 characters bufffers )
 * */

u8 FingerPS_convertImg2CharFile(u8 Copy_u8CharcterFileNumber)
{
	/* ACK variable */
	u8 Local_u8_ACKValue ;

	/* Data Array */
	u8 Local_Au8Data[2] = {0x02};

	/* check where to save the converted character file
	 * then save the its location in the Data Array */
	switch (Copy_u8CharcterFileNumber)
	{
	case R503_CHARACTER_FILE_1: Local_Au8Data[1] = R503_CHARACTER_FILE_1; break;
	case R503_CHARACTER_FILE_2: Local_Au8Data[1] = R503_CHARACTER_FILE_2; break;
	}

	/* Send Package */
	H_R503_void_SendPackage(R503_COMMAND_PACKET,0x0004,Local_Au8Data);

	/* Read the ACK form the sensor */
	Local_u8_ACKValue = R503_u8_CheckACK();

	return Local_u8_ACKValue;

}


/* Brief : This function to Scan the Finger and save the image in the image buffer
 *
 * */
u8 FingerPS_genImg()
{
	/* ACK variable */
	u8 Local_u8_ACKValue ;

	/* Delay for Being ready */
	_delay_ms(200);

	/* Data Array */
	u8 Local_Au8Data[1] = {0x01};

	/* Send Package */
	H_R503_void_SendPackage(R503_COMMAND_PACKET,0x0003,Local_Au8Data);

	Local_u8_ACKValue = R503_u8_CheckACK();

	return Local_u8_ACKValue;



}

/* Brief : Perform handshake , this function is used to make
sure that communication is done successfully. */

u8 FingerPS_handShake()
{
	/* ACK variable */
	u8 Local_u8_ACKValue ;

	/* Delay for Being ready */
	_delay_ms(200);

	u8 Local_Au8Data[] = {0x40};

	/* Send Package */
	H_R503_void_SendPackage(R503_COMMAND_PACKET,0x0003,Local_Au8Data);

	Local_u8_ACKValue = R503_u8_CheckACK();


	return Local_u8_ACKValue;

}



/* Name		 : H_R503_void_SendPackage
 * Brief 	 : This function Send the data package format
 * Arguments : => Copy_u8PID (the package identifier) options : R503_COMMAND_PACKET ,R503_DATA_PACKET, R503_ACK_PACKET,R503_END_OF_PACKET
 *			   => Copy_u8PackageLenght
 *			   => Local_Au8
 * */

static void H_R503_void_SendPackage(u8 Copy_u8PID,u16 Copy_u8PackageLenght, u8 * Local_Au8)
{

	/* Variable for CheckSum*/
	u16 Local_u16CheckSum;


	/* Header Part*/
	M_UART_u8_UARTSendCharacter	(R503_HEADR_FIRST_BYTE);
	M_UART_u8_UARTSendCharacter	(R503_HEADR_SECOND_BYTE);

	/* Address Part */
	M_UART_u8_UARTSendCharacter(0xFF);
	M_UART_u8_UARTSendCharacter(0xFF);
	M_UART_u8_UARTSendCharacter(0xFF);
	M_UART_u8_UARTSendCharacter(0xFF);

	/* PID part */
	 M_UART_u8_UARTSendCharacter(Copy_u8PID);


	/*Package Length*/
	M_UART_u8_UARTSendCharacter( (u8) (Copy_u8PackageLenght >> R503_8_Bits_Shift));
	M_UART_u8_UARTSendCharacter( (u8) Copy_u8PackageLenght);


	/* Sending Data */
	for (u8 i = 0 ; i < ((u8) Copy_u8PackageLenght) -2  ; i++)
	M_UART_u8_UARTSendCharacter(Local_Au8[i]);


	/* Calculate the Check Sum */
	Local_u16CheckSum = R503_void_CheckSum(Copy_u8PID , Copy_u8PackageLenght ,Local_Au8);

	/* Check sum Sending*/
	M_UART_u8_UARTSendCharacter((u8)(Local_u16CheckSum >> R503_8_Bits_Shift));
	M_UART_u8_UARTSendCharacter(Local_u16CheckSum );



}

/* Brief : This function calculate the Check sum of the package */
static u16 R503_void_CheckSum(u8 Copy_u8PID,u16 Copy_u8PackageLenght, u8 * Local_Au8)
{
	u16 Local_u16CheckSum;

	Local_u16CheckSum = Copy_u8PID + Copy_u8PackageLenght ;

	for (u8 i = 0 ; i < ((u8) Copy_u8PackageLenght) -2  ; i++)
		Local_u16CheckSum+= Local_Au8[i];

	return Local_u16CheckSum;

}

/* Brief : This function receive the ACK massage from the sensor  */

 u8 R503_u8_CheckACK()
{
	u8 Local_u8ACKValue ;
	u8 Local_Au8Buffer[12];

	M_UART_u8RecieveBufferSynch(Local_Au8Buffer,12);
	Local_u8ACKValue = Local_Au8Buffer[9];

	return Local_u8ACKValue;

}


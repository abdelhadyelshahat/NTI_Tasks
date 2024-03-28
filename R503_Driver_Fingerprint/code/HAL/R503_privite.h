/*
 * R503_privite.h
 *
 *  Created on: Mar 22, 2024
 *      Author: hady
 */

#ifndef HAL_R503_PRIVITE_H_
#define HAL_R503_PRIVITE_H_


/* Name		 : H_R503_void_SendPackage
 * Brief 	 : This function Send the data package format
 * Arguments : => Copy_u8PID (the package identifier) options : R503_COMMAND_PACKET ,R503_DATA_PACKET, R503_ACK_PACKET,R503_END_OF_PACKET
 *			   => Copy_u8PackageLenght
 *			   => Local_Au8
 * */
static void H_R503_void_SendPackage(u8 Copy_u8PID,u16 Copy_u8PackageLenght, u8 * Local_Au8);




/* Brief : This function calculate the Check sum of the package */

static u16 R503_void_CheckSum(u8 Copy_u8PID,u16 Copy_u8PackageLenght, u8 * Local_Au8);


/* Package identifier macros */

#define R503_COMMAND_PACKET   0x01
#define R503_DATA_PACKET  	  0x02
#define R503_ACK_PACKET   	  0x07
#define R503_END_OF_PACKET    0x08

/* Header part macros*/
#define R503_HEADR_FIRST_BYTE  	0xEF
#define R503_HEADR_SECOND_BYTE  0x01

/* macro for shifting*/
#define R503_8_Bits_Shift    8


#endif /* HAL_R503_PRIVITE_H_ */

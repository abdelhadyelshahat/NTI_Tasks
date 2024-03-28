/*
 * UART_config.h
 *
 *  Created on: Mar 19, 2024
 *      Author: hady
 */

#ifndef UART_CONFIG_H_
#define UART_CONFIG_H_

/******************************* Baud rate configuration ***************/
/* CPU clock frequency */
#define F_CPU_SYS 16000000UL

/* Baud rate value */
#define UART_BAUD_RATE_VALUE  		57600UL


/******************** UART mode configuration *******************/
/* options :
 * 			1- UART_u8_ASYNCHRONOUS
 * 			2-UART_u8_SYNCHRONOUS  */
#define UART_u8_MODE_OPTION 		UART_u8_ASYNCHRONOUS


/************************* UART parity configuration ****************/
/* options :
 * 			1- DISABLED_PARITY_MODE
 *			2-EVEN_PARITY_MODE
 *			3- ODD_PARITY_MODE 	*/

#define UART_u8_PARITY_OPTION 		DISABLED_PARITY_MODE


/***************************** Stop bit configuration *******************/
/* options :
 * 			1- UART_u8_ONE_STOP_BIT
 * 			2- UART_u8_TWO_STOP_BIT
 * */

#define UART_STOP_BIT_OPTIONS 		UART_u8_ONE_STOP_BIT

/****************************** Character size configuration ***********/
/*oprions :
 * 			1- UART_DATA_5_BITS
 *			2-UART_DATA_6_BITS
 *	 		3-UART_DATA_7_BITS
 *			4-UART_DATA_8_BITS	*/

#define UART_u8_CHARACTER_SIZE_OPTION  UART_DATA_8_BITS


/********************************* TX circuit Configuration ******************/
/* options :
 * 			1-  UART_u8_TX_EN
 * 			2-  UART_u8_TX_DIS*/
#define UART_u8_TX_OPTION 				 UART_u8_TX_EN
/********************************* RX circuit Configuration ******************/
/* options :
 * 			1-  UART_u8_RX_EN
 * 			2-  UART_u8_RX_DIS*/
#define UART_u8_RX_OPTION 				 UART_u8_RX_EN
/******************************* Double Speed Configuration ****************/

/* options :
 * 			1- UART_u8_U2X_DISABLE
 * 			2- UART_u8_U2X_ENABLE					*/
#define UART_u8_U2X_OPTION    	 	UART_u8_U2X_DISABLE



/************** UART interrupts options ****************/
#define UART_u8_RXCIE_OPTION 	UART_INT_DIS
#define UART_u8_TXCIE_OPTION 	UART_INT_DIS
#define UART_u8_UDRIE_OPTION 	UART_INT_DIS

/************ Time out Configuration ************** */
#define UART_TIME_OUT		1000000UL

#endif /* UART_CONFIG_H_ */

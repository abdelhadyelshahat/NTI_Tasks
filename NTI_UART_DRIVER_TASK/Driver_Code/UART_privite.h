/*
 * UART_privite.h
 *
 *  Created on: Mar 19, 2024
 *      Author: hady
 */

#ifndef UART_PRIVITE_H_
#define UART_PRIVITE_H_


#define UART_u8_UDR_REG      *((volatile u8 *)0x2C)

/******************************************/
#define UART_u8_UCSRA_REG      *((volatile u8 *)0x2B)

/* macros for UART_u8_UCSRA_REG bits*/
#define UCSRA_UDRE       5
#define UCSRA_RXC        7

/******************************************/

#define UART_u8_UCSRB_REG      *((volatile u8 *)0x2A)

/* macros for UART_u8_UCSRB_REG bits */
#define UCSRB_RXCIE      7
#define UCSRB_TXCIE      6
#define UCSRB_UDRIE      5
#define UCSRB_RXEN       4
#define UCSRB_TXEN       3
#define UCSRB_UCSZ2      2
/********************************************/

#define UART_u8_UBRRL_REG      *((volatile u8 *)0x29)


/******************************************/
#define UART_u8_UBRRH_REG      *((volatile u8 *)0x40)
#define UART_u8_UBRRH_SHIFT_VALUE 8


/******************************************/
#define UART_u8_UCSRC_REG      *((volatile u8 *)0x40)

/* UART_u8_UCSRC_REG bits macros*/
#define UCSRC_URSEL_BIT      7
#define UCSRC_UMSEL_BIT      6
#define UCSRC_UPM1_BIT       5
#define UCSRC_UPM0_BIT       4
#define UCSRC_USBS_BIT       3
#define UCSRC_UCSZ1_BIT      2
#define UCSRC_UCSZ0_BIT      1
#define USCRC_UPDATED_VAR    0b10000000
/******************************************/


/************************************* privite macros********************/
/* opreation mode macros*/
#define UART_u8_ASYNCHRONOUS  		1

#define UART_u8_SYNCHRONOUS  		0

/* Parity mode macros*/
#define DISABLED_PARITY_MODE 		0
#define EVEN_PARITY_MODE 			1
#define ODD_PARITY_MODE 			2

/* Stop bits macros */
#define UART_u8_ONE_STOP_BIT	    0
#define UART_u8_TWO_STOP_BIT 		1

/*macros for baud rate */
#define UAR_BAUD_RATE_9600   		51


/* macros for data bits number */
#define UART_DATA_5_BITS   			0
#define UART_DATA_6_BITS  			1
#define UART_DATA_7_BITS  			2
#define UART_DATA_8_BITS 		  	3

/* macros for interrupt */
#define UART_INT_EN       			 1
#define UART_INT_DIS      			 0

/* macros for state flag*/

/* Macros for Double Speed */
#define UART_u8_U2X_DISABLE     	0
#define UART_u8_U2X_ENABLE 			1
#define UCSRA_U2X 					1

/* Macros for TX CCT **/
#define UART_u8_TX_EN   1
#define UART_u8_TX_DIS	0

/* Macros for RX CCT **/
#define UART_u8_RX_EN   1
#define UART_u8_RX_DIS	0



#endif /* UART_PRIVITE_H_ */

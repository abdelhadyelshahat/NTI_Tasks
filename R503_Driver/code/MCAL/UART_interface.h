
/* Author : Abdelhady Elshahat Abdelhady
 * Layer  : MCAL
 * SWC    : UART

 */

#ifndef UART_INTERFACE_H_
#define UART_INTERFACE_H_

#include "../LIB/STD_TYPES.h"





/* Function   : M_UART_void_UARTInit
 * Brief   	  : This Function initialize the UART peripheral depend on the UART_config.h file
 * Parameters : void
 * return     : void
 */
void M_UART_void_UARTInit (void);

/* Function   : M_UART_u8_UARTSendCharacter
 * Brief   	  : This Function send character out of the AVR by the UART Communication protocol
 * Parameters : Copy_u8Character (the character wanted to send)
 * return     : function error State
 */

u8 M_UART_u8_UARTSendCharacter (u8 Copy_u8Character);

/* Function   : M_UART_u8_Recievecharacter
 * Brief   	  : This Function receive character from outside the AVR using the UART communication protocol
 * Parameters : Copy_Pu8Character
 * return     : function error State
 */

u8 M_UART_u8_Recievecharacter(u8 * Copy_Pu8Character);

/* Function   : M_UART_u8_SendStringSynch
 * Brief   	  : This Function send string using synch mechanism technique
 * Parameters : Copy_Pu8String
 * return     : function error State
 */

u8 M_UART_u8_SendStringSynch(u8 * Copy_Pu8String);


/* Function   : M_UART_u8SendStringAsynch
 * Brief   	  : This Function send string using Asynchronous mechanism technique
 * Parameters : =>Copy_Pu8String
 * 				=>AppCallBackFunction
 * return     : function error State
 */

u8 M_UART_u8SendStringAsynch(u8 * Copy_Pu8String , void (* AppCallBackFunction) (void));


/* Function   : M_UART_u8RecieveBufferSynch
 * Brief   	  : This Function receive string using synchronous technique
 * Parameters : => Copy_Pu8String
 * 				=> Copy_u8StringIterator
 * return     : function error State
 */

u8 M_UART_u8RecieveBufferSynch (u8 * Copy_Pu8String , u8 Copy_u8StringIterator) ;

/* Function   : M_UART_u8RecieveBufferASynch
 * Brief   	  : This Function receive string using Asynchronous technique
 * Parameters : => Copy_Pu8String
 * 				=> Copy_u8StringIterator
 * 				=>AppCallBackFunction
 * return     : function error State
 */

u8 M_UART_u8RecieveBufferASynch (u8 * Copy_Pu8String , u8 Copy_u8StringIterator , void (* AppCallBackFunction) (void));


#endif /* UART_INTERFACE_H_ */

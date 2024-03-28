/*
 * <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<< DIO_interface.h >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
 * Author : ABDELHADY ELSHAHAT ABDELHADY
 * Layer  : MCAL
 * SWC    : DIO
 */

/* Header Guard */
#ifndef MCAL_DIO_DIO_INTERFACE_H_
#define MCAL_DIO_DIO_INTERFACE_H_

#include "../../LIB/BIT_MATH.h"
#include "../../LIB/STD_TYPES.h"


/* Macros for Port Numbers*/
#define DIO_u8_PORTA		     0
#define DIO_u8_PORTB		     1
#define DIO_u8_PORTC		     2
#define DIO_u8_PORTD		     3

/* Macros for Pin Numbers*/
#define DIO_u8_PIN0			     0
#define DIO_u8_PIN1			     1
#define DIO_u8_PIN2			     2
#define DIO_u8_PIN3			     3
#define DIO_u8_PIN4			     4
#define DIO_u8_PIN5			     5
#define DIO_u8_PIN6			     6
#define DIO_u8_PIN7			     7

/* Macros for Pin Directions*/
#define DIO_u8_PIN_OUTPUT_DIRECTION    0
#define DIO_u8_PIN_INPUT_DIRECTION     1

/* Macros for Port Directions*/
#define DIO_u8_PORT_DIRECTION_OUTPUT   0xff
#define DIO_u8_PORT_DIRECTION_INPUT    0x00

/*Macros for the Port Value */
#define DIO_u8_PORT_VALUE_HIGH			0xff
#define DIO_u8_PORT_VALUE_LOW			0x00

/* Macros for Pin Value */
#define DIO_u8_PIN_VALUE_HIGH        1
#define DIO_u8_PIN_VALUE_LOW         0

/*Macros for Pull-up Resistor Enable or Disable */
#define DIO_u8_PULLUP_RES_EN    1
#define DIO_u8_PULLUP_RES_DIS    0

/*<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<< 1- DIO Initialization  >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>*/
/*----------------------------------------------------------------------------------------------
 *  Function: M_DIO_void_DIOInit
 *  Arguments   : void
 * Return type : void
 *  Description : This Function Initialize the DIO Pins [ I/P (Pull-up or floating ) - O/P (High or Low) ]
 * ----------------------------------------------------------------------------------------------
 */

void M_DIO_void_DIOInit(void);


/*<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<< 2- Set Pin Direction  >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>*/
/*----------------------------------------------------------------------------------------------
 *  Function: M_DIO_voidSetPinDirection
 *  Arguments   :
 * 				 =>Copy_u8PortNumber  Options: DIO_u8_PORTA, DIO_u8_PORTB, DIO_u8_PORTC, DIO_u8_PORTD
 * 				 =>Copy_u8PinNumber   Options: DIO_u8_PIN0 --> DIO_u8_PIN7
 * 				 =>Copy_u8Direction   Options: DIO_u8_PIN_OUTPUT_DIRECTION, DIO_u8_PIN_INPUT_DIRECTION  	                             	    																**/
 /* Return type :(u8 variable)  Error State  (ERROR, NO_ERROR)
 *  Description : This Function Sets the Direction of a specific pin (I/P - O/P)
 * ----------------------------------------------------------------------------------------------
 */

u8 M_DIO_u8_SetPinDirection(u8 Copy_u8PortNumber , u8 Copy_u8PinNumber, u8 Copy_u8Direction );






/*<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<< 3- Set Pin Value >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>*/
/*----------------------------------------------------------------------------------------------
 *  Function    : M_DIO_u8_SetPinValue
 *  Arguments   :
 * 				 =>Copy_u8PortNumber  Options: DIO_u8_PORTA, DIO_u8_PORTB, DIO_u8_PORTC, DIO_u8_PORTD
 * 				 =>Copy_u8PinNumber   Options: DIO_u8_PIN0 --> DIO_u8_PIN7
 * 				 =>Copy_u8OValue      Options: DIO_u8_PIN_VALUE_HIGH, DIO_u8_PIN_VALUE_LOW  	                             	    																**/
 /* Return type :(u8 variable)        Error State  (ERROR, NO_ERROR)
 *  Description : This Function Sets the value of a specific pin (HIGH - LOW)
 * ----------------------------------------------------------------------------------------------
 */
u8 M_DIO_u8_SetPinValue (u8 Copy_u8PortNumber , u8 Copy_u8PinNumber, u8 Copy_u8Value);






/*<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<< 4- Get Pin Value >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>*/
/*----------------------------------------------------------------------------------------------
 *  Function    : M_DIO_u8_GetPinValue
 *  Arguments   :
 * 				 =>Copy_u8PortNumber  Options: DIO_u8_PORTA, DIO_u8_PORTB, DIO_u8_PORTC, DIO_u8_PORTD
 * 				 =>Copy_u8PinNumber   Options: DIO_u8_PIN0 --> DIO_u8_PIN7
 * 				 =>Copy_Pu8PinValue   pointer to receive the pin value  	                             	    																**/
 /* Return type :(u8 variable)        Error State  (ERROR, NO_ERROR)
 *  Description : This Function Gets the value of a specific pin (HIGH - LOW)
 * ----------------------------------------------------------------------------------------------
 */
u8 M_DIO_u8_GetPinValue (u8 Copy_u8PortNumber,u8 Copy_u8PinNumber, u8 * Copy_Pu8PinValue);



/*<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<< 5- Toggle Pin Value >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>*/
/*----------------------------------------------------------------------------------------------
 *  Function    : M_DIO_u8_TogglePinValue
 *  Arguments   :
 * 				 =>Copy_u8PortNumber  Options: DIO_u8_PORTA, DIO_u8_PORTB, DIO_u8_PORTC, DIO_u8_PORTD
 * 				 =>Copy_u8PinNumber   Options: DIO_u8_PIN0 --> DIO_u8_PIN7
 * Return type :(u8 variable)        Error State  (ERROR, NO_ERROR)
 *  Description : This Function Toggles the value of a specific Pin
 * ----------------------------------------------------------------------------------------------
 */

u8 M_DIO_u8_TogglePinValue (u8 Copy_u8PortNumber,u8 Copy_u8PinNumber);




/*<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<< 6- Set Port Direction  >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>*/
/*----------------------------------------------------------------------------------------------
 *  Function    : M_DIO_u8_SetPortDirection
 *  Arguments   :
 * 				 =>Copy_u8PortNumber  Options: DIO_u8_PORTA, DIO_u8_PORTB, DIO_u8_PORTC, DIO_u8_PORTD
 * 				 =>Copy_u8PortDirection   Options: DIO_u8_PORT_DIRECTION_OUTPUT, DIO_u8_PORT_DIRECTION_INPUT                           	    																**/
 /* Return type :(u8 variable)        Error State  (ERROR, NO_ERROR)
 *  Description : This Function Sets the Direction of a specific PORT (O/P - I/P)
 * ----------------------------------------------------------------------------------------------
 */

u8 M_DIO_u8_SetPortDirection (u8 Copy_u8PortNumber , u8 Copy_u8PortDirection );





/*<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<< 7- Set Port Value >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>*/
/*----------------------------------------------------------------------------------------------
 *  Function    : M_DIO_u8_SetPortValue
 *  Arguments   :
 * 				 =>Copy_u8PortNumber  Options: DIO_u8_PORTA, DIO_u8_PORTB, DIO_u8_PORTC, DIO_u8_PORTD
 * 				 =>Copy_u8PortDirection   Options: DIO_u8_PORT_VALUE_HIGH, DIO_u8_PORT_VALUE_LOW                           	    																**/
 /* Return type :(u8 variable)        Error State  (ERROR, NO_ERROR)
 *  Description : This Function Sets the Value of a specific PORT (HIGH - LOW)
 * ----------------------------------------------------------------------------------------------
 */
u8 M_DIO_u8_SetPortValue (u8 Copy_u8PortNumber , u8 Copy_u8PortValue );


/*<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<< 8- Active Pull-up Resistor  >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>*/
/*----------------------------------------------------------------------------------------------
 *  Function    : M_DIO_u8_ActivePullupResistor
 *  Arguments   :
 * 				 =>Copy_u8PortNumber      Options: DIO_u8_PORTA, DIO_u8_PORTB, DIO_u8_PORTC, DIO_u8_PORTD
 * 				 =>Copy_u8PinNumber       Options: Options: DIO_u8_PIN0 --> DIO_u8_PIN7
 * 				 =>Copy_u8State           Options: DIO_u8_PULLUP_RES_EN, DIO_u8_PULLUP_RES_DIS              	    																**/
 /* Return type :(u8 variable)        	  Error State  (ERROR, NO_ERROR)
 *  Description : This Function Enables and Disables  the internal Pull-up Resistor on a specific pin
 * ----------------------------------------------------------------------------------------------
 */

u8 M_DIO_u8_ActivePullupResistor (u8 Copy_u8PortNumber ,u8 Copy_u8PinNumber , u8 Copy_u8State);


#endif /* MCAL_DIO_DIO_INTERFACE_H_ */

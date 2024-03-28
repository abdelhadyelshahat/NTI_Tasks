/*
 *<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<    DIO_privite.h    >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
 *
 *  Author : ABDELHADY ELSHAHAT ABDELHADY
 *  Layer  : MCAL
 *  SWD    : DIO
 *
 */

#ifndef MCAL_DIO_DIO_PRIVITE_H_
#define MCAL_DIO_DIO_PRIVITE_H_

/*Registers Macros*/

/* Group A Registers */
#define DIO_u8_DDRA_REG         *(( volatile u8*)0x3A)
#define DIO_u8_PORTA_REG        *(( volatile u8*)0x3B)
#define DIO_u8_PINA_REG         *(( volatile u8*)0x39)

/* Group B Registers */
#define DIO_u8_DDRB_REG         *(( volatile u8*)0x37)
#define DIO_u8_PORTB_REG        *(( volatile u8*)0x38)
#define DIO_u8_PINB_REG         *(( volatile u8*)0x36)

/* Group C Registers */
#define DIO_u8_DDRC_REG         *(( volatile u8*)0x34)
#define DIO_u8_PORTC_REG        *(( volatile u8*)0x35)
#define DIO_u8_PINC_REG         *(( volatile u8*)0x33)

/* Group D Registers */
#define DIO_u8_DDRD_REG         *(( volatile u8*)0x31)
#define DIO_u8_PORTD_REG        *(( volatile u8*)0x32)
#define DIO_u8_PIND_REG         *(( volatile u8*)0x30)

/* Private Macros for Initial Direction */
#define DIO_u8_PIN_INTIAL_DIRECTION_OUTPUT   1
#define DIO_u8_PIN_INTIAL_DIRECTION_INPUT    0

/* Private Macros for Initial Value */
#define DIO_u8_PIN_INTIAL_VALUE_HIGH			1
#define DIO_u8_PIN_INTIAL_VALUE_LOW 			0
#define DIO_u8_PIN_INTIAL_VALUE_PULLUP			1
#define DIO_u8_PIN_INTIAL_VALUE_FLOATING    	0

/* Concatenation Macro*/
#define CONC(b7,b6,b5,b4,b3,b2,b1,b0) 	        	CONC_HELP(b7,b6,b5,b4,b3,b2,b1,b0)
#define CONC_HELP(b7,b6,b5,b4,b3,b2,b1,b0)  		0b##b7##b6##b5##b4##b3##b2##b1##b0



#endif /* MCAL_DIO_DIO_PRIVITE_H_ */

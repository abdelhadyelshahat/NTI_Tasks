/*
 * <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<< LCD_config.h >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
 * Author : ABDELHADY ELSHAHAT ABDELHADY
 * Layer  : HAL
 * SWC    : LCD
 */

#ifndef HAL_LCD_LCD_CONFIG_H_
#define HAL_LCD_LCD_CONFIG_H_


#define LCD_u8_MODE          LCD_u8_4_BIT_MODE


/* <<<<<<<<<<<< 8 bit mode >>>>>>>>>>>>>>>>*/
/* Data PORT for 8 bit configuration mode */
#define LCD_u8_Data_PORT       DIO_u8_PORTA

/* <<<<<<<<<<<< 4 bit mode >>>>>>>>>>>>>>>>*/
/* Data Port for 4 bits mode */
#define LCD_u8_D4_PORT			DIO_u8_PORTB
#define LCD_u8_D5_PORT			DIO_u8_PORTB
#define LCD_u8_D6_PORT			DIO_u8_PORTB
#define LCD_u8_D7_PORT			DIO_u8_PORTB
/* Data pins for 4 bits mode */
#define LCD_u8_D4_PIN			DIO_u8_PIN0
#define LCD_u8_D5_PIN			DIO_u8_PIN1
#define LCD_u8_D6_PIN			DIO_u8_PIN2
#define LCD_u8_D7_PIN			DIO_u8_PIN3


/* <<<<<<<< RS /EN/RW selection >>>>>>>>>*/
#define LCD_u8_RS_PORT         DIO_u8_PORTB
#define LCD_u8_EN_PORT         DIO_u8_PORTB
#define LCD_u8_RW_PORT         DIO_u8_PORTB
/* PINs configuration */
#define LCD_u8_RS_PIN           DIO_u8_PIN4
#define LCD_u8_EN_PIN           DIO_u8_PIN5
#define LCD_u8_RW_PIN           DIO_u8_PIN2



#endif /* HAL_LCD_LCD_CONFIG_H_ */

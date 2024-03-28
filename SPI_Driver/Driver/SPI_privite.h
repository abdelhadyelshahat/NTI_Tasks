/*>>>>>>>>>>>>>>>>>>>>>>>>>>>>>> SPI_privite.h*/

/*
*** Layer : MCAL
*** Author : Abdelhady
*** version :1.0
*/



#ifndef SPI_PRIVITE_H_
#define SPI_PRIVITE_H_

/* Reg defintion*/

/********************** SPDR (SPI DATA REG) *************** */

#define SPI_SPDR_REG    *((volatile u8 *)0x2F)


/********************** SPSR (SPI STATUES REG) *************** */
#define SPI_SPSR_REG    *((volatile u8 *)0x2E)

#define SPIF_BIT  7
#define WCOL_BIT  6
#define SP2X_BIT  0


/********************** SPSR (SPI CONTROL REG) *************** */
#define SPI_SPCR_REG    *((volatile u8 *)0x2D)

#define SPIE_BIT  7
#define SPE_BIT   6
#define DORD_BIT  5
#define MSTR_BIT  4
#define CPOL_BIT  3
#define CPHA_BIT  2
#define SPR1_BIT  1
#define SPR0_BIT  0

/*************************** privite macros defination **************/

/* opreation mode macros*/
#define SPI_SLAVE_MODE    2
#define SPI_MASTER_MODE   1

/* interuupt mode macros */
#define SPI_INTERRUPT_DIS  1
#define SPI_INTERRUPT_EN   2

/* macros for ata direction mode*/
#define SPI_DODR_LSB_FIRST 1
#define SPI_DODR_MSB_FIRST 2

/* macros for CPOL mode */
#define SPI_CPOL_RISING_LEADING  1
#define SPI_CPOL_FALLING_LEADING 2

/* macros for clock phase */
#define SPI_CPHL_SETUP_FIRET   1
#define SPI_CPHL_SAMPLE_FIRET  2

/* macros for clock rate */
#define SPI_CLOCK_OVER_64   1 
#define SPI_CLOCK_OVER_4	2
#define SPI_CLOCK_OVER_16	3
#define SPI_CLOCK_OVER_128	4

/* macros for state flag*/

#define IDLE 1
#define BUSY 2


#endif 

/*>>>>>>>>>>>>>>>>>>>>>>>>>>>>>> SPI_config.h*****************/


/*
*** Layer : MCAL
*** Author : Abdelhady
*** version :1.0
*/

#ifndef SPI_CONFIG_H_
#define SPI_CONFIG_H_


/* Select config mode 
** 1- SPI_MASTER_MODE
** 2- SPI_SLAVE_MODE
*/

#define SPI_OPREATION_MODE  SPI_MASTER_MODE


/* Select interrupt mode 
** 1- SPI_INTERRUPT_DIS
** 2- SPI_INTERRUPT_EN
*/
#define SPI_INTERRUPT_MODE  SPI_INTERRUPT_DIS


/* Select Data direction mode 
** 1- SPI_DODR_LSB_FIRST
** 2- SPI_DODR_MSB_FIRST
*/

#define SPI_DATA_ORDER_DIRECTION_MODE    SPI_DODR_LSB_FIRST

/* Select clock polaity mode 
** 1- SPI_CPOL_RISING_LEADING
** 2- SPI_CPOL_FALLING_LEADING
*/
#define SPI_CPOL_MODE    SPI_CPOL_RISING_LEADING


/* Select clock phase mode 
** 1- SPI_CPHL_SETUP_FIRET
** 2- SPI_CPHL_SAMPLE_FIRET
*/

#define SPI_CPHA_MODE   SPI_CPHL_SETUP_FIRET


/* Select clock Rate mode 
** 1- SPI_CLOCK_OVER_64
** 2- SPI_CLOCK_OVER_4
** 3- SPI_CLOCK_OVER_16
** 4- SPI_CLOCK_OVER_128
*/

#define SPI_CLOCK_RATE  SPI_CLOCK_OVER_64

#endif 

/*>>>>>>>>>>>>>>>>>>>>>>>>>>> TWI_config.h <<<<<<<<<<<<<<<<<<<<<<*/

/*
** Layer : MCAL 
** Author : Abdelhady Elshahat 
** version : 1.0
**
*/

#ifndef TWI_CONFIG_H_
#define TWI_CONFIG_H_

#define SYS_Frq            4000000UL

#define TWI_SCL_BIT_RATE   100000UL


/* options for TWI_PRESCALLER
** 1- PRESCALLER_BY_1
** 2- PRESCALLER_BY_4
** 3- PRESCALLER_BY_16
** 4- PRESCALLER_BY_64
*/
#define TWI_PRESCALLER      PRESCALLER_BY_1



/* macros for Statues Code */

#define TWI_STATUES_REG_MSKING_VALUE    0xF8


#define TWI_START_COND_SENT             0x08
#define TWI_SLA_W_SENT					0x18
#define TWI_SLA_W_NOT_SENT				0x20
#define TWI_SLA_R_SENT					0x40
#define TWI_MASTER_DATA_SENT			0x28
#define TWI_MASTER_DATA_REC				0x50
#define TWI_SLAVE_SENT_DATA  			0xB8
#define TWI_SLAVE_REC_DATA  			0x80


#endif

/*>>>>>>>>>>>>>>>>>>>>>>>>>>> TWI_privite.h <<<<<<<<<<<<<<<<<<<<<<*/

/*
** Layer : MCAL 
** Author : Abdelhady Elshahat 
** version : 1.0
**
*/



#ifndef TWI_PRIVITE_H_ 
#define TWI_PRIVITE_H_

/* TWI_TWCR_REG Control REG*/
#define TWI_TWCR_REG     *((volatile u8* )0x56)

#define TWINT	  7
#define TWEA      6
#define TWSTA     5
#define TWSTO	  4
#define TWEN      2




/* Data REg */
#define TWI_TWDR_REG     *((volatile u8* )0x23)

#define TWD0      0





#define TWI_TWAR_REG     *((volatile u8* )0x23)

/*  TWI_TWSR_REG  */
#define TWI_TWSR_REG     *((volatile u8* )0x21)
#define TWPS1 1
#define TWPS0 0

#define TWI_TWBR_REG     *((volatile u8* )0x20)


/*>>>>>>>>>>>>>>>>>>>>>>>>> privite macros <<<<<<<<<<<<<<<<<<<<<<*/

#define PRESCALLER_BY_1     1
#define PRESCALLER_BY_4		4
#define PRESCALLER_BY_16	16
#define PRESCALLER_BY_64	46

#endif 

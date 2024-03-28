/*>>>>>>>>>>>>>>>>>>>>>>>>>>>>>> SPI_interface.h*****************/

/*
*** Layer : MCAL
*** Author : Abdelhady
*** version :1.0
*/

#ifndef SPI_INTERFACE_H_
#define SPI_INTERFACE_H_

void SPI_voidInit (void);


u8 SPI_u8TransRec (u8 Copy_u8TransData , u8 *Copy_Pu8RecData);


void SPI_u8TransData (u8 Copy_u8TransData);


u8 SPI_u8RecData (u8 *SPI_Pu8RecData);

u8 SPI_u8SendRecStringAsync (u8 *Copy_Pu8SendString , u8 *Copy_Pu8RecString, void (*NofificationFunc) (void));






#endif








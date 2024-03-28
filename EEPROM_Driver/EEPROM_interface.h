/*>>>>>>>>>>>>>>>>>>>>>>>>>>> EEPROM_intrface.h <<<<<<<<<<<<<<<<<<<<<<*/

/*
** Layer : HAL 
** Author : Abdelhady Elshahat 
** version : 1.0
**
*/


#ifndef EEPROM_INTERFACE_H_ 
#define EEPROM_INTERFACE_H_


u8 EEPROM_u8WriteByte(u16 Copy_u16ByteAdress , u8 Copy_u8Data);


u8 EEPROM_u8ReadByte (u16 Copy_u16ByteAdress , u8 *Copy_Pu8Data);







#endif 
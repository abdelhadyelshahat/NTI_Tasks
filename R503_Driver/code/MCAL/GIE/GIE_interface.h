/***************  Author : Abdelhady Elshahat */
/**************  Layer   : MCAL       ********/
/**************  SWC     : GIE        ********/
/**************  Date    : 03/08/2023 ********/
/**************  Version : 1.0        ********/
/**************                       ********/
/********************************************/

#ifndef GIE_INTERFACE_
#define GIE_INTERFACE_


#define SREG_REG           *((volatile u8 *)0x5f)

#define SREG_REG_L_BIT     7

void GIE_voidGIEEnable (void);

void GIE_voidGIEDisable (void);






#endif 
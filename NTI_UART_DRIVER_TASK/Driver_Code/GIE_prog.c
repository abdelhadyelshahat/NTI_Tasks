/***************  Author : Abdelhady Elshahat */
/**************  Layer   : MCAL       ********/
/**************  SWC     : GIE        ********/
/**************  Date    : 03/08/2023 ********/
/**************  Version : 1.0        ********/
/**************                       ********/
/********************************************/

/* LIB includes*/
#include "STD_TYPES.h"
#include "BIT_MATH.h"

/*MCAl includes*/
#include "GIE_interface.h"


void GIE_voidGIEEnable (void)
{
	
	SET_BIT(SREG_REG,SREG_REG_L_BIT);
	
}

void GIE_voidGIEDisable (void)
{
	CLR_BIT(SREG_REG,SREG_REG_L_BIT);
	
}

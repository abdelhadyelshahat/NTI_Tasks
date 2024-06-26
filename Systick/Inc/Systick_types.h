/*****************************************************************/
/* FILE DESCRIPTION:
----------------------------------------------------------------
*  file     : Systick_Types.h
*  Module   : Systick 
*  breif    : contains types
*  
*****************************************************************   
*/
#ifndef SYSTICK_TYPES_H
#define SYSTICK_TYPES_H
/******************************************
  INCLUDES 
*******************************************/
#include "Std_Types.h"

/******************************************
  GLOBAL CONSTANT MACROS   
*******************************************/


/******************************************
  GLOBAL FUNCTIONS MACROS
*******************************************/

/******************************************
  Global Data TYPES AND STRUCTURES 
*******************************************/

typedef enum
{
    PIOSC_4 = 0,
    FCPU = 1
} Systick_clkSrc_t;

#endif

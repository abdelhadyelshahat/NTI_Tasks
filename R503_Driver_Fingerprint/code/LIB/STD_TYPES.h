/*********************************************/
/********** Name : STD_TYPES.h **************/
/********* DAte : 20/06/2023 ***************/
/******** Author : Abdelhady Elshahat *****/
/******* version : 1.0 *******************/
/****************************************/
 
#ifndef STD_TYPES_H 
#define STD_TYPES_H

/*macros for error state */
#define STD_TYPES_NOK 	 0
#define STD_TYPES_OK 	 1
#define TIME_OUT_ERROR   2
#define FUNCTION_BUSY    3


/* macros for functions states */
#define IDLE  0
#define BUSY  1
/*macro for Null Pointer*/
#define NULL ((void *)0)


/*unsigned and signed keyword modifer only used with char and int */
typedef unsigned char u8 ;
typedef signed char s8 ;

/*the short modifer only used with int datatype*/
typedef unsigned short int u16;
typedef signed short int s16;

/*the long keyword modifer only used with int and double datatypes*/
typedef unsigned long int u32;
typedef signed long int s32;

typedef unsigned long long int u64;
typedef signed long long int s64;

typedef float f32;
typedef double f64;

#endif 

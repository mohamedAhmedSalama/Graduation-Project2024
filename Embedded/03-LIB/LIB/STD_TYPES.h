/*
 *
 * Author	    :	Mohamed Ahmed
 * Date		    :	11 SEP 2023
 * Version		:	V1
 * Description  : 	STD_TYPES LIB
 *
 **/

#ifndef STD_TYPES_H_
#define STD_TYPES_H_

typedef unsigned char         uint8 ;
typedef unsigned short int    uint16;
typedef unsigned  int 		  uint32;
typedef unsigned  long long   uint64;


typedef signed char		   sint8 ;
typedef signed short int   sint16;
typedef signed long  int   sint32;


typedef float	f32;
typedef double	f64;

typedef enum{
	FALSE=0,
	TRUE=1
	}bool_t;

#define NULL     0
#define NULLPTR   ((void*)0)



#endif

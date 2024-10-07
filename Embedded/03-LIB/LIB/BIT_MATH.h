/*
 *
 * Author	    :	Mohamed Ahmed
 * Date		    :	11 SEP 2023
 * Version		:	V1
 * Description  : 	BIT_MATH LIB
 *
 **/

#ifndef BIT_MATH_H_
#define BIT_MATH_H_

#define    SET_BIT(reg,bit)          		(reg|=(1<<bit))

#define    CLR_BIT(reg,bit)          		(reg&=(~(1<<bit)))

#define    TOG_BIT(reg,bit)          		(reg^=(1<<bit))

#define    READ_BIT(reg,bit)         		((reg>>bit)&1)

#define    WRITE_BIT(reg,bit,val)    	  	(reg=(reg&=(~(1<<bit)) | (val<<bit)))

#define CONC_BIT(b7,b6,b5,b4,b3,b2,b1,b0) 	0b##b7##b6##b5##b4##b3##b2##b1##b0

#endif

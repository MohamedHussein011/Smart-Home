/*
 * Name: Muhammad Hussein Muhammad Salem
 * Layer: LIB
 * Version: V1.0 - 01/10/2021
 *
 */

#ifndef _BIT_MATH_H
#define _BIT_MATH_H


#define SET_BIT(REG,BIT) ( (REG) |=  (1 << (BIT) ) )
#define CLR_BIT(REG,BIT) ( (REG) &= ~(1 << (BIT) ) )
#define TOG_BIT(REG,BIT) ( (REG) ^=  (1 << (BIT) ) )

#define GET_BIT(REG,BIT) ( ((REG) >> (BIT)) & 0x01 )
										/* |      Clear          | OR | Write Value|  */
#define WRT_BIT(REG, BIT, VAL) ( (REG) = ( ((REG) & (~(1<<(BIT)))) |  ((VAL)<<(BIT)) ) )


#endif
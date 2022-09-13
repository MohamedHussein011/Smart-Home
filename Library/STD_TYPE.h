/*
 * Name: Mohamed Hussein
 * Layer: LIBRARY
 * Version: V1.0 - 01/10/2021
 *
 */

#ifndef _STD_TYPE_H
#define _STD_TYPE_H

#define NULL ( (void *)0 )

typedef unsigned char        uint8_t;            /*           0 .. 255             */
typedef unsigned short int   uint16_t;           /*           0 .. 65535           */
typedef unsigned long  int   uint32_t;           /*           0 .. 4294967295      */

typedef signed char          int8_t;            /*        -128 .. +127            */
typedef signed short int     int16_t;           /*      -32768 .. +32767          */
typedef signed long  int     int32_t;           /* -2147483648 .. +2147483647     */

typedef void (*pvFunction_t) (void);           /*Pointer to function*/

#define OK               0
#define NOK              1
#define IDLE             2
#define BUSY             3
#define NULLPOINTER      4
#define TIMEOUT_STATE    5
#define WORKING          6
#define NOT_WORKING      7
#define OUT_RANGE        8

#endif

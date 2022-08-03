/*
 * Platform_Types.h
 *
 * Created: 7/17/2022 4:20:05 PM
 *  Author: ThoPH
 */ 


#ifndef PLATFORM_TYPES_H_
#define PLATFORM_TYPES_H_

/* SWS_Platform_00013, SWS_Platform_00014, SWS_Platform_00015, SWS_Platform_00066 */
typedef unsigned char       uint8;
typedef unsigned short      uint16;
typedef unsigned long       uint32;
typedef unsigned long long  uint64;

/* SWS_Platform_00016, SWS_Platform_00017, SWS_Platform_00018, SWS_Platform_00067 */
typedef signed char         sint8;
typedef signed short        sint16;
typedef signed long         sint32;
typedef signed long long    sint64;

/* SWS_Platform_00041 */
typedef float               float32;
typedef double              double64;

/* SWS_Platform_91001 */
#define VoidPtr         (void*)
/* SWS_Platform_91002 */
#define ConstVoidPtr    (const void*)

#define NULL_PTR ((void*)0)

/* [SWS_Platform_00026] */
#define ARG_TRUE (1==1)
#define ARG_FALSE (0==1)

/* [SWS_Platform_00026] */
#ifndef ARG_TRUE
#define ARG_TRUE 0x01
#endif

/* [SWS_Platform_00026] */
#ifndef ARG_FALSE
#define ARG_FALSE 0x00
#endif


#endif /* PLATFORM_TYPES_H_ */
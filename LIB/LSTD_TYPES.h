#ifndef STD_TYPES_H_
#define STD_TYPES_H_

typedef enum{
	NOK,
	OK
}Error_State;

#define NULL_POINTER	((void * )1)
#define NULL_CHARACTER	'\0'
#define NULL_0 	0
#define NULL 	0

typedef unsigned char   u8;
typedef signed char     s8;

typedef unsigned short int    u16;
typedef signed short int      s16;

typedef unsigned long int    u32;
typedef signed long int      s32;

typedef unsigned long long int u64;
typedef signed long long int s64;

typedef float     f32;
typedef double    f64;
typedef long double f96;

typedef enum{
	BIT0=0,
	BIT1,
	BIT2,
	BIT3,
	BIT4,
	BIT5,
	BIT6,
	BIT7
}E_Bit_t;

#endif 

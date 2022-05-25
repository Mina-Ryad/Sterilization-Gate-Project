/*
 * MGIE_Program.c
 *
 *  Created on: Nov 15, 2021
 *      Author: Mina-Ryad
 */

#include "..\..\LIB\LSTD_TYPES.h"
#include "..\..\LIB\LBIT_MATH.h"

#include "..\MDIO\MDIO_Interface.h"
#include "MGIE_Private.h"

/****************************/
/**Enable General Interrupt**/
/****************************/
void MGIE_VidEnable(void)
{
	SET_BIT(SREG,I_SREG);
}

/*****************************/
/**Disable General Interrupt**/
/*****************************/
void MGIE_VidDisable(void)
{
	CLR_BIT(SREG,I_SREG);
}
